#include "ChatManager.hpp"

ChatManager::ChatManager()
    : HypixelGamemodeModule{ true, HypixelGamemode::Gamemode::ALL }
{
    this->blacklistedLines = 
    {
        "Sending you to",
        "Slow down! You can only use /tip",
        "You are sen
	};ding commands too fast! Please slow dowm.",
        "You tipped"
}

ChatManager::~ChatManager() = default;

auto ChatManager::Update() -> void 
{
    const std::vector<std::unique_ptr<ChatLine>>& chatLines = mc->GetIngameGUI()->GetPersistantChatGUI()->GetChatLines();

    bool refresh = false;
    if (!chatLines[0]->GetLineString()->GetFormattedText().contains(":")) 
    {
        for (const std::string& line : this->blacklistedLines) 
        {
            if (chatLines[0]->GetLineString()->GetFormattedText().find(line) != std::string::npos) 
            {
                mc->GetIngameGUI()->GetPersistantChatGUI()->DeleteChatLine(chatLines[0]->GetChatLineID());
                refresh = true; 
                break; 
            }
        }
    }

    if (refresh) 
    {
        mc->GetIngameGUI()->GetPersistantChatGUI()->RefreshChat();
    }
}