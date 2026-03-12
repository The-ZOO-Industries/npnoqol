#include "set_apikey.hpp"

npno::set_apikey::set_apikey()
	: npno::command{ "/setapikey", std::format("{}/setapikey {}<apikey>",
		enum_chat_formatting::dark_aqua,
		enum_chat_formatting::aqua) }
{

}

npno::set_apikey::~set_apikey() = default;

auto npno::set_apikey::on_command(const std::vector<std::string>& args) const
	-> void
{
	if (args.size() != 2)
	{
		mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(this->usage));
		return;
	}

	std::println("you set the api key to {}", args[1]);
}