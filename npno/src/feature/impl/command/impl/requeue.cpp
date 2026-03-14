#include "requeue.hpp"

npno::requeue::requeue()
	: npno::command{ "/rq", std::format("{}/rq",
		enum_chat_formatting::dark_aqua) }
{

}

npno::requeue::~requeue() = default;

auto npno::requeue::on_command(const std::vector<std::string>& args) const
	-> void
{
	if (args.size() != 1)
	{
		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(this->usage));
		return;
	}

	const std::pair<hypixel_gametype::gametype, std::string> pair{ hypixel_gametype::current_gametype, hypixel_mode::current_mode };

	if (this->command_map.find(pair) != this->command_map.end())
	{
		mc->get_the_player()->send_chat_message(this->command_map.at(pair));

		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(
			std::format("{}Requeued", enum_chat_formatting::green)
		));
	}
	else
	{
		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(
			std::format("{}Wasn't able to requeue", enum_chat_formatting::red)
		));
	}
}