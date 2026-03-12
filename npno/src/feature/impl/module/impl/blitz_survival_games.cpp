#include "blitz_survival_games.hpp"

npno::blitz_survival_games::blitz_survival_games()
	: npno::hypixel_gametype_module{ hypixel_gametype::gametype::BLITZSURVIVALGAMES }
{

}

npno::blitz_survival_games::~blitz_survival_games() = default;

auto npno::blitz_survival_games::update()
	-> void
{
	
}

auto npno::blitz_survival_games::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
	-> bool
{
	if (std::string line{ chat_component->get_formatted_text() }; line.contains(enum_chat_formatting::obfuscated))
	{
		std::size_t pos{};
		while ((pos = line.find(enum_chat_formatting::obfuscated)) != std::string::npos)
		{
			line.erase(pos, 3);
		}

		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(line));

		return true;
	}

	return false;
}