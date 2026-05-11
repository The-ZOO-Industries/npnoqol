#include "find_nick.hpp"

zoo::find_nick::find_nick() noexcept
	: zoo::command{ "/find_nick", std::format("{}/find_nick {}<name>",
		enum_chat_formatting::dark_aqua,
		enum_chat_formatting::aqua) }
{

}

zoo::find_nick::~find_nick() noexcept = default;

auto zoo::find_nick::on_command(const std::vector<std::string>& args) const noexcept
-> void
{
	if (args.size() != 2)
	{
		this->print_usage();

		return;
	}

	try
	{
		const std::string result{ network::get(std::format("/find_nick/{}", args[1]), network::url::ZOO) };
		if (!nlohmann::json::accept(result))
		{
			zoo::util::add_chat_message(std::format("{}No nick found", enum_chat_formatting::red));

			return;
		}

		const nlohmann::json json_response{ nlohmann::json::parse(result, nullptr, false) };
		if (!json_response.contains("nick_name") || !json_response["nick_name"].is_string())
		{
			zoo::util::add_chat_message(std::format("{}No nick found", enum_chat_formatting::red));

			return;
		}

		zoo::util::add_chat_message(std::format("{}{} {}is nicked as {}{}",
			enum_chat_formatting::dark_aqua,
			args[1],
			enum_chat_formatting::aqua,
			enum_chat_formatting::green,
			json_response["nick_name"].get<std::string>()));
	}
	catch (...)
	{
		zoo::util::add_chat_message(std::format("{}Failed to find nick for {}", enum_chat_formatting::red, args[1]));
	}
}