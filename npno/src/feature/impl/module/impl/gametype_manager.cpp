#include "gametype_manager.hpp"

npno::gametype_manager::gametype_manager()
	: npno::module{ true }
{

}

npno::gametype_manager::~gametype_manager() = default;

auto npno::gametype_manager::update()
	-> void
{
	
}

auto npno::gametype_manager::on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
	-> void
{
	const std::string message{ chat_component->get_unformatted_text() };

    const std::string json_part{ this->extract_json(message) };
    if (json_part.empty()) return;

    if (nlohmann::json::accept(json_part))
    {
        const auto json{ nlohmann::json::parse(json_part) };

        if (json.contains("gametype"))
        {
            hypixel_gametype::current_gametype = hypixel_gametype::string_to_gametype.at(json["gametype"].get<std::string>());
        }

        if (json.contains("mode"))
        {
            hypixel_mode::current_mode = json["mode"].get<std::string>();
        }
        else
        {
            hypixel_mode::current_mode = "unknown";
        }
    }
}

auto npno::gametype_manager::extract_json(const std::string& line) const
	-> std::string
{
	if (const std::size_t pos{ line.find('{') }; pos != std::string::npos)
	{
		return line.substr(pos);
	}

	return "";
}