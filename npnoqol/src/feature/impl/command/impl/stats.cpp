#include "stats.hpp"

zoo::stats::stats() noexcept
    : zoo::command{ "/s", std::format("{}/s {}<type> <player>", 
        enum_chat_formatting::dark_aqua, 
        enum_chat_formatting::aqua) }
{

}

zoo::stats::~stats() noexcept = default;

auto zoo::stats::on_command(const std::vector<std::string>& args) const noexcept
    -> void
{
    if (args.size() != 2 && args.size() != 3)
    {
        this->print_usage();

        return;
    }

	std::string player_name{};

    if (args.size() == 2)
    {
		player_name = minecraft->get_the_player()->get_name();
    }
    else
    {
		player_name = args[2];
    }

    if (args[1] == "general")
    {
		zoo::chat::add_chat_message(std::format("{}{}'s general stats: {}",
			enum_chat_formatting::dark_aqua,
			player_name,
			enum_chat_formatting::aqua
		));
    }
}