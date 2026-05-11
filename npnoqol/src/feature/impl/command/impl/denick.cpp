#include "denick.hpp"

zoo::denick::denick() noexcept
	: zoo::command{ "/denick", std::format("{}/denick {}<nick>",
		enum_chat_formatting::dark_aqua,
		enum_chat_formatting::aqua) }
{

}

zoo::denick::~denick() noexcept = default;

auto zoo::denick::on_command(const std::vector<std::string>& args) const noexcept
-> void
{
	if (args.size() != 2)
	{
		this->print_usage();

		return;
	}

	try
	{
		const std::string result{ network::get(std::format("/denick/{}", args[1]), network::url::ZOO) };
		if (!nlohmann::json::accept(result))
		{
			zoo::util::add_chat_message(std::format("{}Nick not found", enum_chat_formatting::red));

			return;
		}

		const nlohmann::json json_response{ nlohmann::json::parse(result, nullptr, false) };
		if (!json_response.contains("real_name") || !json_response["real_name"].is_string())
		{
			zoo::util::add_chat_message(std::format("{}Nick not found", enum_chat_formatting::red));

			return;
		}

		zoo::util::add_chat_message(std::format("{}{} {}is {}{}",
			enum_chat_formatting::dark_aqua,
			args[1],
			enum_chat_formatting::aqua,
			enum_chat_formatting::green,
			json_response["real_name"].get<std::string>()));
	}
	catch (...)
	{
		zoo::util::add_chat_message(std::format("{}Failed to denick {}", enum_chat_formatting::red, args[1]));
	}
}