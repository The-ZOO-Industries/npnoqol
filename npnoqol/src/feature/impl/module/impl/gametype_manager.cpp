#include "gametype_manager.hpp"

#include "../../../../util/enum_chat_formatting.hpp"
#include "../../../../util/hypixel_gametype.hpp"
#include "../../../../util/hypixel_mode.hpp"

zoo::gametype_manager::gametype_manager() noexcept = default;

zoo::gametype_manager::~gametype_manager() noexcept = default;

auto zoo::gametype_manager::on_run_tick() noexcept
	-> void
{

}

auto zoo::gametype_manager::on_minecraft_tick() noexcept
	-> void
{
	if (this->locraw_queued.exchange(false, std::memory_order_acq_rel))
	{
		if (zoo::feature::minecraft)
		{
			const std::unique_ptr<sdk::entity_player_sp> player{ zoo::feature::minecraft->get_the_player() };
			if (player && player->get_instance())
			{
				player->send_chat_message("/locraw");
			}
		}
	}

	std::vector<std::string> messages{};
	{
		std::lock_guard<std::mutex> lock{ this->chat_messages_mutex };
		messages.swap(this->queued_chat_messages);
	}

	for (const std::string& message : messages)
	{
		zoo::chat::add_chat_message(message);
	}
}

auto zoo::gametype_manager::on_load_world(const std::unique_ptr<sdk::minecraft>& minecraft) noexcept
	-> void
{
	const auto now{ std::chrono::steady_clock::now() };

	{
		std::lock_guard<std::mutex> lock{ this->load_world_mutex };

		if (this->last_load_world.time_since_epoch().count() != 0
			&& now - this->last_load_world < std::chrono::seconds{ 3 })
		{
			return;
		}

		this->last_load_world = now;
	}

	this->locraw_queued.store(true, std::memory_order_release);

	if (!this->api_check_running.exchange(true, std::memory_order_acq_rel))
	{
		this->queue_chat_messages(zoo::gametype_manager::check_api_keys());
		this->api_check_running.store(false, std::memory_order_release);
	}
}

auto zoo::gametype_manager::on_print_chat_message(vmhook::return_value& return_value, const std::unique_ptr<sdk::i_chat_component>& chat_component) noexcept
	-> bool
{
	const std::string json_part{ this->extract_json(chat_component->get_unformatted_text()) };
	if (json_part.empty() || !nlohmann::json::accept(json_part))
	{
		return false;
	}

	const std::int64_t now{ std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::steady_clock::now().time_since_epoch()).count() };

	std::int64_t next_allowed{ this->next_locraw_chat_ms.load(std::memory_order_relaxed) };
	while (now >= next_allowed)
	{
		if (this->next_locraw_chat_ms.compare_exchange_weak(next_allowed, now + 3000, std::memory_order_acq_rel))
		{
			break;
		}
	}

	if (now < next_allowed)
	{
		return true;
	}

	const nlohmann::json json{ nlohmann::json::parse(json_part, nullptr, false) };
	bool handled{ false };

	if (json.contains("gametype") && json["gametype"].is_string())
	{
		const std::string gametype{ json["gametype"].get<std::string>() };
		const auto gametype_it{ hypixel_gametype::string_to_gametype.find(gametype) };

		hypixel_gametype::current_gametype = gametype_it != hypixel_gametype::string_to_gametype.end()
			? gametype_it->second
			: hypixel_gametype::string_to_gametype.at("UNKNOWN");

		handled = true;
	}

	hypixel_mode::current_mode = json.contains("mode") && json["mode"].is_string()
		? json["mode"].get<std::string>()
		: "unknown";

	return handled;
}

auto zoo::gametype_manager::extract_json(const std::string& line) const noexcept
	-> std::string
{
	const std::size_t pos{ line.find('{') };
	if (pos == std::string::npos)
	{
		return {};
	}

	return line.substr(pos);
}

auto zoo::gametype_manager::check_api_keys() noexcept
	-> std::vector<std::string>
{
	const bool hypixel_valid{ hypixel_api::check_apikey(config::get<std::string>("api.hypixel")) };
	const bool zoo_valid{ zoo_api::check_apikey(config::get<std::string>("api.zoo")) };

	std::vector<std::string> messages{};

	if (!hypixel_valid)
	{
		messages.push_back(std::format("{}Hypixel API key is invalid", enum_chat_formatting::red));
	}

	if (!zoo_valid)
	{
		messages.push_back(std::format("{}Zoo API key is invalid", enum_chat_formatting::red));
	}

	return messages;
}

auto zoo::gametype_manager::queue_chat_messages(std::vector<std::string>&& messages) noexcept
	-> void
{
	std::lock_guard<std::mutex> lock{ this->chat_messages_mutex };
	this->queued_chat_messages.insert(this->queued_chat_messages.end(), messages.begin(), messages.end());
}
