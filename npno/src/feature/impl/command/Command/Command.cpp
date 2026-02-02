#include "Command.hpp"

Command::Command(const std::string& name, const std::string& usage)
	: Feature()
	, name{ name }
    , usage{ std::format("{}Usage: {}", MinecraftCode::GREEN, usage) }
{

}

Command::~Command() = default;

auto Command::Update() -> void
{
    const std::vector<std::unique_ptr<ChatLine>>& chatLines = mc->GetIngameGUI()->GetPersistantChatGUI()->GetChatLines();
    const std::string line = chatLines[0]->GetLineString()->GetFormattedText();

    const std::regex nameRegex{ this->name, std::regex_constants::icase };
    if (this->SentByHypixel(line) and std::regex_search(line, nameRegex))
    {
        mc->GetIngameGUI()->GetPersistantChatGUI()->DeleteChatLine(chatLines[0]->GetChatLineID());

        this->OnCommand(this->GetArguments(this->ExtractBetweenQuotes(line)));

        mc->GetIngameGUI()->GetPersistantChatGUI()->RefreshChat();
    }
}

auto Command::ExtractBetweenQuotes(const std::string& line) const -> std::string
{
    const Size first{ line.find('\'') };
    if (first == std::string::npos)
    {
        return "";
    }

    const Size second{ line.find('\'', first + 1) };
    if (second == std::string::npos)
    {
        return "";
    }

    return line.substr(first + 1, second - first - 1);
}

auto Command::GetArguments(const std::string& command) const -> std::vector<std::string>
{
    std::vector<std::string> args;
    std::istringstream stream(command);
    std::string word;

    while (stream >> word) 
    {
        args.push_back(word);
    }

    return args;
}