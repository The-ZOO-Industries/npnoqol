#include "ChatManager.hpp"

ChatManager::ChatManager()
    : Module{ true }
{
    this->blacklistedLines = this->ToRegex(Config::GetBlackListedLines());
}

ChatManager::~ChatManager() = default;

auto ChatManager::Update() -> void 
{
    const std::vector<std::unique_ptr<ChatLine>>& chatLines{ mc->GetIngameGUI()->GetPersistantChatGUI()->GetChatLines() };
    const std::string& line{ chatLines[0]->GetLineString()->GetFormattedText() };

    if (!this->SentByHypixel(line))
    {
        for (const std::regex& blackListedLine : this->blacklistedLines) 
        {
            if (std::regex_search(line, blackListedLine))
            {
                mc->GetIngameGUI()->GetPersistantChatGUI()->DeleteChatLine(chatLines[0]->GetChatLineID());

                mc->GetIngameGUI()->GetPersistantChatGUI()->RefreshChat();

                break; 
            }
        }
    }
}