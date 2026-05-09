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

			zoo::util::add_chat_message(
				std::format("{}Hello {}{}", enum_chat_formatting::aqua, enum_chat_formatting::dark_aqua, minecraft->get_the_player()->get_name())
			);
		}
	);
}

zoo::feature::~feature() noexcept
{
	static std::once_flag destructor_flag{};

	std::call_once(destructor_flag, []()
		{
			zoo::util::add_chat_message(
				std::format("{}See you {}{}", enum_chat_formatting::aqua, enum_chat_formatting::dark_aqua, minecraft->get_the_player()->get_name())
			);
		}
	);
}

auto zoo::feature::sanity_check() const noexcept
	-> bool
{
	if (!minecraft || !minecraft->get_the_player()->get_instance() || !minecraft->get_the_world()->get_instance())
	{
		return false;
	}

	return true;
}
