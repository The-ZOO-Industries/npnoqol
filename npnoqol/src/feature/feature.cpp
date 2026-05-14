#include "feature.hpp"

#include <mutex>
#include <print>

#include "../util/enum_chat_formatting.hpp"

zoo::feature::feature() noexcept
{
	static std::once_flag init_flag{};

	std::call_once(init_flag, []() 
		{
			minecraft = sdk::minecraft::get_minecraft();

			const auto player{ minecraft ? minecraft->get_the_player() : nullptr };
			if (player && player->get_instance())
			{
				zoo::chat::add_chat_message(
					std::format("{}Hello {}{}", enum_chat_formatting::aqua, enum_chat_formatting::dark_aqua, player->get_name())
				);
			}
		}
	);
}

zoo::feature::~feature() noexcept
{
	static std::once_flag destructor_flag{};

	std::call_once(destructor_flag, []()
		{
			const auto player{ minecraft ? minecraft->get_the_player() : nullptr };
			if (player && player->get_instance())
			{
				zoo::chat::add_chat_message(
					std::format("{}See you {}{}", enum_chat_formatting::aqua, enum_chat_formatting::dark_aqua, player->get_name())
				);
			}
		}
	);
}

auto zoo::feature::sanity_check() const noexcept
	-> bool
{
	if (!minecraft)
	{
		return false;
	}

	const auto player{ minecraft->get_the_player() };
	const auto world{ minecraft->get_the_world() };
	if (!player || !player->get_instance() || !world || !world->get_instance())
	{
		return false;
	}

	return true;
}
