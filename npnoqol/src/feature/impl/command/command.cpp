#include "command.hpp"

zoo::command::command(const std::string& name, const std::string& usage) noexcept
    : zoo::feature()
    , name{ name }
    , usage{ std::format("{}Usage: {}", enum_chat_formatting::green, usage) }
{

}

zoo::command::~command() noexcept = default;

auto zoo::command::on_send_chat_message(const std::string& message) const noexcept
    -> bool
{
    if (const std::vector<std::string>& args{ this->get_arguments(message) }; !args.empty() && this->name == args[0])
    {
        return true;
    }

    return false;
}

auto zoo::command::get_name() const noexcept
    -> std::string
{
    return this->name;
}

auto zoo::command::print_usage() const noexcept
    -> void
{
	zoo::chat::add_chat_message(this->usage);
}

auto zoo::command::get_arguments(const std::string& command) const noexcept
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
