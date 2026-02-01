#include "AutoGG.hpp"

AutoGG::AutoGG()
    : Module{ true }
{
    this->autoGGLines = this->ToRegex(
    {
        "1st - "
    });
}

AutoGG::~AutoGG() = default;

auto AutoGG::Update() -> void
{
    const std::vector<std::unique_ptr<ChatLine>>& chatLines{ mc->GetIngameGUI()->GetPersistantChatGUI()->GetChatLines() };
    const std::string& line{ chatLines[0]->GetLineString()->GetFormattedText() };

    if (this->SentByHypixel(line))
    {
        for (const std::regex& blackListedLine : this->autoGGLines)
        {
            if (std::regex_search(line, blackListedLine))
            {
                mc->GetThePlayer()->SendChatMessage(std::format("{} {}", "/ac", this->RandomCase("good game")));

                mc->GetIngameGUI()->GetPersistantChatGUI()->RefreshChat();

                return;
            }
        }
    }
}

auto AutoGG::RandomCase(const std::string& message) const -> std::string
{
    std::string result = message;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 1);
    
    for (char& c : result) 
    {
        if (std::isalpha(c) && dist(gen) == 1) 
        {
            c = std::toupper(c);
        } else 
        {
            c = std::tolower(c);
        }
    }
    
    return result;
}