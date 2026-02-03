#include "AutoGG.hpp"

AutoGG::AutoGG()
    : Module{ true }
{
    this->autoGGLines = this->ToRegex(Config::GetAutoGGLines());
}

AutoGG::~AutoGG() = default;

auto AutoGG::Update() -> void
{
    for (const std::string& line : ChatUtil::GetNewLines())
    {
        for (const std::regex& autoGGLine : this->autoGGLines)
        {
            if (std::regex_search(line, autoGGLine))
            {
                mc->GetThePlayer()->SendChatMessage(std::format("{} {}", "/ac", this->RandomCase("good game")));
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