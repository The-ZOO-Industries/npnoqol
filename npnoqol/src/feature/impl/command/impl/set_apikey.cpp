#include "set_apikey.hpp"

zoo::set_apikey::set_apikey() noexcept
	: zoo::command{ "/setapikey", std::format("{}/setapikey {}<type> <apikey>",
		enum_chat_formatting::dark_aqua,
		enum_chat_formatting::aqua) }
{

}

zoo::set_apikey::~set_apikey() noexcept = default;

auto zoo::set_apikey::on_command(const std::vector<std::string>& args) const noexcept
	-> void
{
	if (args.size() != 3)
	{
		this->print_usage();

		return;
	}

	if (args[1] == "hypixel")
	{
		if (hypixel_api::check_apikey(args[2]))
		{
			zoo::util::add_chat_message(std::format("{}Hypixel API key is valid", enum_chat_formatting::green));
		}
		else
		{
			zoo::util::add_chat_message(std::format("{}Hypixel API key is invalid", enum_chat_formatting::red));
		}
	}
	else if (args[1] == "zoo")
	{
		config::set<std::string>("api.zoo", args[2]);
		zoo::util::add_chat_message(std::format("{}Set the API key for zoo", enum_chat_formatting::green));
	}
	else
	{
		this->print_usage();
	}
}