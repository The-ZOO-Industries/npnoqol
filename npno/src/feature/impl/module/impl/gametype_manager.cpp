#include "gametype_manager.hpp"

npno::gametype_manager::gametype_manager()
	: npno::module{ true }
{

}

npno::gametype_manager::~gametype_manager() = default;

auto npno::gametype_manager::on_load_world()
    -> void
{
    static std::chrono::time_point<std::chrono::steady_clock> last_sent_time{ std::chrono::steady_clock::now() - std::chrono::seconds{ 5 } };

    const std::chrono::time_point<std::chrono::steady_clock> now{ std::chrono::steady_clock::now() };
    if (std::chrono::duration_cast<std::chrono::seconds>(now - last_sent_time).count() < 5)
    {
        return;
    }

    mc->get_the_player()->send_chat_message("/locraw");

    const bool valid{ hypixel_api::check_apikey(config::get<std::string>("api.hypixel")) };

    if (not valid)
    {
        mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(
            std::format("{}Outdated hypixel apikey {}https://developer.hypixel.net/dashboard",
                enum_chat_formatting::red,
                enum_chat_formatting::aqua)
        ));
    }
}

auto npno::gametype_manager::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
    -> bool 
{
    const std::string message{ chat_component->get_unformatted_text() };

    const std::string json_part{ this->extract_json(message) };
    if (json_part.empty()) return false;

    bool result{ false };
    if (nlohmann::json::accept(json_part))
    {
        const auto json{ nlohmann::json::parse(json_part) };

        if (json.contains("gametype") 
            and hypixel_gametype::string_to_gametype.find(json["gametype"].get<std::string>()) != hypixel_gametype::string_to_gametype.end())
        {
            hypixel_gametype::current_gametype = hypixel_gametype::string_to_gametype.at(json["gametype"].get<std::string>());
            result = true;
        }

        if (not result and json.contains("gametype")
            and hypixel_gametype::string_to_gametype.find(json["gametype"].get<std::string>()) == hypixel_gametype::string_to_gametype.end())
        {
            hypixel_gametype::current_gametype = hypixel_gametype::string_to_gametype.at("UNKNOWN");
            result = true;
        }

        if (json.contains("mode"))
        {
            hypixel_mode::current_mode = json["mode"].get<std::string>();
            result = true;
        }
        else
        {
            hypixel_mode::current_mode = "unknown";
        }

        //mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(hypixel_mode::current_mode));
    }

    return result;
};

auto npno::gametype_manager::extract_json(const std::string& line) const
	-> std::string
{
	if (const std::size_t pos{ line.find('{') }; pos != std::string::npos)
	{
		return line.substr(pos);
	}

	return "";
}