#include "BlitzSurvivalGames.hpp"

#include "../GamemodeManager/GamemodeManager.hpp"
#include "../NickManager/NickManager.hpp"

BlitzSurvivalGames::BlitzSurvivalGames()
    : HypixelModule{ false, Hypixel::Gamemode::BLITZSURVIVALGAMES }
{
    this->mode = Mode::LOBBY;
}

BlitzSurvivalGames::~BlitzSurvivalGames() = default;

auto BlitzSurvivalGames::Update() -> void
{
    this->HandleMode();
    if (this->mode == Mode::LOBBY) return;

    this->LoadMissingPlayers();
    this->UpdateNameTags();
    this->OrginizeTeams();
    this->AssignTeamNumbers();
    this->AssignTeamColors();
    this->UpdateTabList();
    this->UpdateChat();
}

auto BlitzSurvivalGames::LoadPlayersData(const std::vector<std::string>& playerNames) -> void
{
    const std::vector<nlohmann::json>& responses = Network::GetBatchPlayerStats(playerNames);

    for (Size i = 0; i < playerNames.size(); ++i)
    {
        const std::string& playerName = playerNames[i];
        const nlohmann::json& response = responses[i];
        Player playerData{};

        try
        {
            if (HypixelAPI::IsNicked(response))
            {
                playerData.prefix = std::format("{}[NICK]{}", MinecraftCode::RED, MinecraftCode::WHITE);
                playerData.isNick = true;
                playerData.cacheTime = std::chrono::steady_clock::now();

                NickManager::AddNickPlayer(playerName);
                this->playerCache[playerName] = playerData;
                continue;
            }

            playerData.rank = HypixelRank::GetRankPrefix(response);

            const auto& hg = response.at("player").at("stats").at("HungerGames");

            const I32 wins = hg.value("wins", 0) + hg.value("wins_teams", 0);
            const I32 kills = hg.value("kills", 0);
            const I32 deaths = hg.value("deaths", 0);

            playerData.prefix = std::to_string(wins);
            playerData.suffix = std::format("{:.1f}", static_cast<float>(kills) / max(1, deaths));
            playerData.cacheTime = std::chrono::steady_clock::now();
            playerData.retryCount = 0;

            if (playerData.rank.empty())
            {
                std::println("[WARNING] {} has an empty rank", playerName);
            }

            this->playerCache[playerName] = playerData;
        }
        catch (...)
        {
            auto it = this->playerCache.find(playerName);
            playerData.retryCount = (it != this->playerCache.end()) ? it->second.retryCount + 1 : 1;
            playerData.error = true;
            playerData.isLoading = false;
            playerData.lastRequestTime = std::chrono::steady_clock::now();
            this->playerCache[playerName] = playerData;
        }
    }
}

auto BlitzSurvivalGames::HandleMode() -> void
{
    const std::string currentMode = GamemodeManager::GetCurrentMode();

    if ((this->mode == Mode::SOLO and currentMode == "teams_normal") or
        (this->mode == Mode::TEAMS and currentMode == "solo_normal"))
    {
        this->ClearCache();
    }

    if (currentMode == "solo_normal") this->mode = Mode::SOLO;
    else if (currentMode == "teams_normal") this->mode = Mode::TEAMS;
    else this->mode = Mode::LOBBY;
}

auto BlitzSurvivalGames::UpdateChat() const -> void
{
    const auto& chatLines = mc->GetIngameGUI()->GetPersistantChatGUI()->GetChatLines();
    bool refresh = false;

    for (I32 i{ 0 }; i < 10; ++i)
    {
        if (!chatLines[i]->GetInstance()) continue;

        std::string text = chatLines[i]->GetLineString()->GetFormattedText();
        if (text.find("§k") != std::string::npos and !text.contains(":"))
        {
            size_t pos{};
            while ((pos = text.find("§k")) != std::string::npos)
                text.erase(pos, 3);

            chatLines[i]->SetLineString(std::make_unique<ChatComponentText>(text));
            refresh = true;
        }
    }

    if (refresh)
        mc->GetIngameGUI()->GetPersistantChatGUI()->RefreshChat();
}

auto BlitzSurvivalGames::FormatTabName(const std::unique_ptr<EntityPlayer>& player) -> std::string
{
    Player playerData = this->GetPlayerData(player->GetName());
    const float health = player->GetHealth() + player->GetAbsorptionAmount();

    std::string teamPrefix{};
    if (this->mode == Mode::TEAMS and this->GetTeamCount() > 3)
    {
        const std::string teamColor = this->GetPlayerTeamColor(player->GetName());
        if (!teamColor.empty())
        {
            teamPrefix = std::format("{}{}O{} ", teamColor, MinecraftCode::OBFUSCATED, MinecraftCode::RESET);
        }
    }

    if (playerData.error)
    {
        return std::format(" {}{}? {}{} {}{:.1f}",
            teamPrefix,
            MinecraftCode::DARK_RED,
            MinecraftCode::DARK_AQUA,
            player->GetName(),
            this->GetHpColor(health),
            health
        );
    }

    if (playerData.isNick)
    {
        return std::format(" {}{} {} {}{:.1f}",
            teamPrefix,
            playerData.prefix,
            player->GetName(),
            this->GetHpColor(health),
            health
        );
    }

    const std::string rankSection = playerData.rank.empty() ? "" : (playerData.rank + " ");
    return std::format(" {}{}[{}] {}{} {}{:.1f} {}; {}{}",
        teamPrefix,
        this->GetWinsColor(playerData.prefix),
        playerData.prefix,
        rankSection,
        player->GetName(),
        this->GetHpColor(health),
        health,
        MinecraftCode::DARK_AQUA,
        this->GetKDRColor(playerData.suffix),
        playerData.suffix
    );
}

auto BlitzSurvivalGames::FormatNametag(const std::unique_ptr<EntityPlayer>& player) -> std::pair<std::string, std::string>
{
    const float health = player->GetHealth() + player->GetAbsorptionAmount();
    std::pair<std::string, std::string> nametag{
        std::format("{} ", MinecraftCode::DARK_AQUA),
        std::format(" {}{:.1f} ", this->GetHpColor(health), health)
    };

    if (this->mode == Mode::TEAMS)
    {
        const std::string teamColor = this->GetPlayerTeamColor(player->GetName());
        if (!teamColor.empty())
            nametag.first += teamColor;
    }

    return nametag;
}

auto BlitzSurvivalGames::GetWinsColor(const std::string& wins) const -> std::string
{
    if (wins.empty() or !std::all_of(wins.begin(), wins.end(), ::isdigit)) return MinecraftCode::GRAY;

    I32 winsValue = std::stoi(wins);
    if (winsValue >= 2500) return MinecraftCode::DARK_RED;
    if (winsValue >= 1000) return MinecraftCode::RED;
    if (winsValue >= 500)  return MinecraftCode::GOLD;
    if (winsValue >= 200)  return MinecraftCode::DARK_GREEN;
    if (winsValue >= 100)  return MinecraftCode::GREEN;
    return MinecraftCode::GRAY;
}

auto BlitzSurvivalGames::GetKDRColor(const std::string& kdr) const -> std::string
{
    if (kdr.empty()) return MinecraftCode::GRAY;

    float kdrValue = std::stof(kdr);
    if (kdrValue >= 10.0f) return MinecraftCode::DARK_RED;
    if (kdrValue >= 5.0f)  return MinecraftCode::RED;
    if (kdrValue >= 3.0f)  return MinecraftCode::GOLD;
    if (kdrValue >= 2.0f)  return MinecraftCode::DARK_GREEN;
    if (kdrValue >= 1.0f)  return MinecraftCode::GREEN;
    return MinecraftCode::GRAY;
}

auto BlitzSurvivalGames::AssignTeamNumbers() -> void
{
    this->teamNumbers.clear();
    U32 counter{ 1 };
    for (const auto& [teamName, _] : this->sortedTeams)
        this->teamNumbers[teamName] = counter++;
}

auto BlitzSurvivalGames::AssignTeamColors() -> void
{
    const std::vector<std::string> baseColors{
        MinecraftCode::DARK_AQUA,
        MinecraftCode::BLACK,
        MinecraftCode::DARK_BLUE,
        MinecraftCode::DARK_GREEN,
        MinecraftCode::DARK_RED,
        MinecraftCode::DARK_PURPLE,
        MinecraftCode::GOLD,
        MinecraftCode::GRAY,
        MinecraftCode::BLUE,
        MinecraftCode::GREEN,
        MinecraftCode::AQUA,
        MinecraftCode::RED,
        MinecraftCode::LIGHT_PURPLE,
        MinecraftCode::YELLOW,
        MinecraftCode::WHITE
    };

    for (const auto& [teamName, _] : this->sortedTeams)
    {
        if (this->teamColors.find(teamName) == this->teamColors.end())
        {
            std::string color = baseColors[nextColorIndex % baseColors.size()];
            if (this->nextColorIndex >= baseColors.size())
                color = MinecraftCode::BOLD + color;

            this->teamColors[teamName] = color;
            ++this->nextColorIndex;
        }
    }
}

auto BlitzSurvivalGames::GetTeamIndex(const std::string& playerName) const -> I32
{
    std::string teamName = this->GetTeamFromTeamManager(playerName).hypixelTeam;
    if (teamName.find("§") != std::string::npos) return -1;

    auto it = teamNumbers.find(teamName);
    return (it != teamNumbers.end()) ? it->second : -1;
}

auto BlitzSurvivalGames::GetPlayerTeamName(const std::string& playerName) const -> std::string
{
    return this->GetTeamFromTeamManager(playerName).hypixelTeam;
}

auto BlitzSurvivalGames::GetPlayerTeamColor(const std::string& playerName) const -> std::string
{
    const std::string teamName = this->GetPlayerTeamName(playerName);
    auto it = teamColors.find(teamName);
    return (it != teamColors.end()) ? it->second : "";
}

auto BlitzSurvivalGames::GetTeamCount() const -> I32
{
    return static_cast<I32>(this->sortedTeams.size());
}