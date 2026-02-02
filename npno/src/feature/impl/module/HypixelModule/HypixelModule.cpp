#include "HypixelModule.hpp"

HypixelModule::HypixelModule(const bool enable, const Hypixel::Gamemode gamemode)
    : Module{ enable }
    , gamemode{ gamemode }
{

}

HypixelModule::~HypixelModule() = default;

auto HypixelModule::SanityCheck() const -> bool
{
    return
        mc->GetThePlayer()->GetInstance() and
        mc->GetTheWorld()->GetInstance() and
        mc->GetIngameGUI()->GetInstance() and
        mc->GetTheWorld()->GetScoreboard()->GetInstance() and
        mc->GetThePlayer()->GetSendQueue()->GetInstance();
}

auto HypixelModule::GetGamemode() const -> Hypixel::Gamemode
{
    return this->gamemode;
}

auto HypixelModule::ClearCache() -> void
{
    this->playerCache.clear();
    this->teamManager.clear();
}

auto HypixelModule::UpdateTabList() -> void
{
    const std::unique_ptr<EntityPlayerSP>& thePlayer{ mc->GetThePlayer() };
    const std::unique_ptr<WorldClient>& theWorld{ mc->GetTheWorld() };
    const std::vector<std::unique_ptr<NetworkPlayerInfo>>& playerInfoMap{ thePlayer->GetSendQueue()->GetPlayerInfoMap() };

    for (Size i{ 0 }; i < playerInfoMap.size(); ++i)
    {
        const std::unique_ptr<EntityPlayer>& playerEntity{ theWorld->GetPlayerEntityByName(playerInfoMap[i]->GetGameProfile()->GetName()) };

        if (playerEntity->GetInstance())
        {
            if (this->IsBot(playerEntity))
            {
                continue;
            }

            playerInfoMap[i]->SetDisplayName(std::make_unique<ChatComponentText>(this->FormatTabName(playerEntity)));
        }
    }
}

auto HypixelModule::UpdateNameTags() -> void
{
    this->FillTeamManagerWithHypixelTeams();
    this->OrginizeTeams();
    this->AssignNpnoTeams();
    this->ApplyTeamsAndNametags();
}

auto HypixelModule::LoadMissingPlayers() -> void
{
    static std::chrono::steady_clock::time_point lastBatchTime{ std::chrono::steady_clock::now() };
    std::chrono::steady_clock::time_point now{ std::chrono::steady_clock::now() };

    if (now - lastBatchTime < std::chrono::seconds(2))
    {
        return;
    }

    lastBatchTime = now;

    std::vector<std::string> playerNames;
    constexpr I32 MAX_BATCH_SIZE{ 10 };
    constexpr I32 MAX_RETRY_COUNT{ 5 };

    for (const std::unique_ptr<EntityPlayer>& player : mc->GetTheWorld()->GetPlayerEntities())
    {
        if (this->IsBot(player))
        {
            continue;
        }

        const std::string& playerName{ player->GetName() };
        auto it = this->playerCache.find(playerName);

        if (it == this->playerCache.end())
        {
            playerNames.push_back(playerName);

            Player loadingPlayer{};
            loadingPlayer.isLoading = true;
            loadingPlayer.lastRequestTime = now;
            this->playerCache[playerName] = loadingPlayer;
        }
        else if (it->second.error and !it->second.isLoading)
        {
            if (it->second.retryCount >= MAX_RETRY_COUNT)
            {
                continue;
            }

            const I32 retryDelay{ 5 * (1 << it->second.retryCount) };
            const I64 timeSinceLastRequest{ std::chrono::duration_cast<std::chrono::seconds>(now - it->second.lastRequestTime).count() };

            if (timeSinceLastRequest >= retryDelay)
            {
                playerNames.push_back(playerName);
                it->second.isLoading = true;
                it->second.lastRequestTime = now;
            }
        }

        if (playerNames.size() >= MAX_BATCH_SIZE)
        {
            break;
        }
    }

    if (!playerNames.empty())
    {
        this->LoadPlayersData(playerNames);
    }
}

auto HypixelModule::GetPlayerData(const std::string& playerName) -> Player
{
    if (auto it = this->playerCache.find(playerName); it != this->playerCache.end())
    {
        return it->second;
    }

    Player playerData{};
    playerData.error = true;

    return playerData;
}

auto HypixelModule::GetHpColor(const float hp) const -> std::string
{
    if (hp >= 20.0f) return MinecraftCode::DARK_GREEN;
    if (hp >= 10.0f) return MinecraftCode::GREEN;
    if (hp >= 5.0f)  return MinecraftCode::YELLOW;
    return MinecraftCode::RED;
}

auto HypixelModule::OrginizeTeams() -> void
{
    this->sortedTeams.clear();

    for (const auto& [playerName, team] : teamManager)
    {
        if (!team.hypixelTeam.empty())
        {
            this->sortedTeams[team].push_back(playerName);
        }
    }
}

auto HypixelModule::FillTeamManagerWithHypixelTeams() -> void
{
    const std::unique_ptr<WorldClient> theWorld{ mc->GetTheWorld() };
    const std::unique_ptr<Scoreboard> scoreboard{ theWorld->GetScoreboard() };

    for (const std::unique_ptr<ScorePlayerTeam>& scoreTeam : scoreboard->GetTeams())
    {
        const std::string hypixelTeamName{ scoreTeam->GetTeamName() };

        for (const std::string& playerName : scoreTeam->GetMembershipCollection())
        {
            if (!theWorld->GetPlayerEntityByName(playerName)->GetInstance())
            {
                continue;
            }

            if (this->IsBot(theWorld->GetPlayerEntityByName(playerName)))
            {
                continue;
            }

            if (!hypixelTeamName.starts_with("npno_"))
            {
                auto it = this->teamManager.find(playerName);
                if (it == this->teamManager.end())
                {
                    Team team{};
                    team.hypixelTeam = hypixelTeamName;
                    this->teamManager.insert({ playerName, std::move(team) });
                }
                else if (it->second.hypixelTeam != hypixelTeamName)
                {
                    it->second.hypixelTeam = hypixelTeamName;
                    it->second.npnoTeam.clear();
                }
            }
        }
    }
}

auto HypixelModule::AssignNpnoTeams() -> void
{
    I32 teamCounter{ 0 };
    for (auto& [team, players] : sortedTeams)
    {
        for (std::string& playerName : players)
        {
            auto& playerTeam = this->teamManager[playerName];
            if (playerTeam.npnoTeam.empty())
            {
                playerTeam.npnoTeam = std::format("npno_{}", teamCounter);
            }
        }
        ++teamCounter;
    }
}

auto HypixelModule::ApplyTeamsAndNametags() -> void
{
    const std::unique_ptr<WorldClient> theWorld{ mc->GetTheWorld() };
    const std::unique_ptr<Scoreboard> scoreboard{ theWorld->GetScoreboard() };

    for (const auto& [playerName, playerTeam] : this->teamManager)
    {
        if (playerTeam.npnoTeam.empty())
        {
            continue;
        }

        std::unique_ptr<ScorePlayerTeam> team{ scoreboard->GetTeam(playerTeam.npnoTeam) };
        if (!team->GetInstance())
        {
            team = scoreboard->CreateTeam(playerTeam.npnoTeam);
        }

        std::unique_ptr<ScorePlayerTeam> currentTeam{ scoreboard->GetTeam(playerName) };
        if (currentTeam->GetInstance() and !currentTeam->GetTeamName().starts_with("npno_"))
        {
            scoreboard->RemovePlayerFromTeam(playerName, currentTeam);
        }

        if (!scoreboard->GetPlayersTeam(playerName) || scoreboard->GetPlayersTeam(playerName)->GetTeamName() != playerTeam.npnoTeam)
        {
            const bool unused{ scoreboard->AddPlayerToTeam(playerName, playerTeam.npnoTeam) };
        }

        const std::unique_ptr<EntityPlayer>& player{ theWorld->GetPlayerEntityByName(playerName) };
        if (player->GetInstance() and !this->IsBot(player))
        {
            const std::pair<std::string, std::string> nametag{ this->FormatNametag(player) };
            team->SetNamePrefix(JavaUtil::FixString(nametag.first));
            team->SetNameSuffix(JavaUtil::FixString(nametag.second));
        }
    }
}