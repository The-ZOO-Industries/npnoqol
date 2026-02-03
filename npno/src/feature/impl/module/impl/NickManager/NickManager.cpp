#include "NickManager.hpp"

NickManager::NickManager()
    : Module{ true }
    , nickHashes{ Config::GetNickSkins() }
{
    
}

NickManager::~NickManager() = default;

auto NickManager::Update() -> void
{
    this->SkinDenicker();

    for (auto& [name, player] : nickList)
    {
        if (!player.warned)
        {
            player.warned = true;
            this->Warn(name, player.realName);
        }
    }
}

auto NickManager::SkinDenicker() -> void
{
    for (auto& [name, player] : nickList)
    {
        if (player.skinDenicker)
        {
            continue;
        }

        const std::unique_ptr<GameProfile>& profile = mc->GetTheWorld()->GetPlayerEntityByName(name)->GetGameProfile();

        for (const std::unique_ptr<Property>& property : profile->GetProperties()->GetValues())
        {
            if (property->GetName() == "textures")
            {
                const std::string encoded{ property->GetValue() };
                const std::string decoded{ Base64::Decode(encoded) };

                try
                {
                    std::string skinUrl = nlohmann::json::parse(decoded).at("textures").at("SKIN").at("url");
                    this->ParseSkinData(name, skinUrl, profile->GetName());
                }
                catch (...)
                {
                    continue;
                }

                break;
            }
        }
    }
}

auto NickManager::ParseSkinData(const std::string& playerName, const std::string& skinHash, const std::string& profileName) -> void
{
    if (!this->IsNickHash(skinHash) and !profileName.empty() and profileName != playerName)
    {
        if (nickList.find(playerName) != nickList.end())
        {
            nickList[playerName].realName = profileName;
        }
    }
}

auto NickManager::IsNickHash(const std::string& hash) -> bool
{
    return std::find(this->nickHashes.begin(), this->nickHashes.end(), hash) != this->nickHashes.end();
}

auto NickManager::AddNickPlayer(const std::string& player) -> void
{
    nickList.insert({player, {}});
}

auto NickManager::GetNickList() -> std::map<std::string, Nick>
{
    return nickList;
}

auto NickManager::Warn(const std::string& name, const std::string& realName) -> void
{
    std::string message;
    if (!realName.empty())
    {
        message = std::format("{}{} {}is nicked as {}{}", 
            MinecraftCode::DARK_AQUA,
            realName,
            MinecraftCode::AQUA,
            MinecraftCode::DARK_AQUA,
            name);
    }
    else
    {
        message = std::format("{}{} {}is nicked",
            MinecraftCode::DARK_AQUA,
            name,
            MinecraftCode::AQUA);
    }

    mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(message));
}