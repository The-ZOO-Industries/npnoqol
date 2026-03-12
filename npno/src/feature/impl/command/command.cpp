#include "command.hpp"

npno::command::command(const std::string& name, const std::string& usage)
	: npno::feature()
	, name{ name }
	, usage{ std::format("{}Usage: {}", enum_chat_formatting::green, usage) }
{

}

npno::command::~command() = default;

auto npno::command::on_chat_message(const std::string& message) const
    -> bool
{
    if (const std::vector<std::string>& args{ this->get_arguments(message) }; this->name == args[0])
    {
        return true;
    }

    return false;
}

auto npno::command::get_name() const
    -> std::string
{
    return this->name;
}

auto npno::command::get_arguments(const std::string& command) const 
    -> std::vector<std::string>
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