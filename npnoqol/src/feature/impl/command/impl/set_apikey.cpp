#include "set_apikey.hpp"

zoo::set_apikey::set_apikey() noexcept
    : zoo::command{ "/setapikey", std::format("{}/setapikey {}<type> <apikey>",
        enum_chat_formatting::dark_aqua,
        enum_chat_formatting::aqua) }
{
    static std::once_flag flag{};

	std::call_once(flag, []() noexcept
		{
			if (!hypixel_api::check_apikey(config::get<std::string>("api.hypixel")))
			{
				zoo::chat::add_chat_message(std::format("{}Hypixel API key is invalid",
					enum_chat_formatting::red
                ));
			}
            else
            {
				zoo::chat::add_chat_message(std::format("{}Hypixel API key is valid",
					enum_chat_formatting::green
				));
            }

			if (!zoo_api::check_apikey(config::get<std::string>("api.zoo")))
			{
				zoo::chat::add_chat_message(std::format("{}Zoo API key is invalid",
					enum_chat_formatting::red
				));
			}
            else
            {
                zoo::chat::add_chat_message(std::format("{}Zoo API key is valid",
                    enum_chat_formatting::green
                ));
            }
		});
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
            zoo::chat::add_chat_message(std::format("{}Hypixel API key is valid", enum_chat_formatting::green));
        }
        else
        {
            zoo::chat::add_chat_message(std::format("{}Hypixel API key is invalid", enum_chat_formatting::red));
        }
    }
    else if (args[1] == "zoo")
    {
        if (zoo_api::check_apikey(args[2]))
        {
            zoo::chat::add_chat_message(std::format("{}Zoo API key is valid", enum_chat_formatting::green));
        }
        else
        {
            zoo::chat::add_chat_message(std::format("{}Zoo API key is invalid", enum_chat_formatting::red));
        }
    }
    else
    {
        this->print_usage();
    }
}