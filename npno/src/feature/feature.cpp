#include "feature.hpp"

npno::feature::feature()
{
	static std::once_flag mc_flag{};

	std::call_once(mc_flag, [this]()
		{
			mc = std::make_unique<jni::minecraft>(nullptr)->get_the_minecraft();

			if (mc->get_the_player()->get_instance())
			{
				mc->get_the_player()->add_chat_message(jni::make_unique<jni::chat_component_text>(
					std::format(
						"{}Welcome to the zoo {}{}",
						enum_chat_formatting::aqua,
						enum_chat_formatting::dark_aqua,
						mc->get_the_player()->get_name()
					)
				));
			}
		});
}

npno::feature::~feature() = default;

auto npno::feature::sanity_check() const 
	-> bool
{
	return mc->get_the_player()->get_instance() and mc->get_the_world()->get_instance();
}

auto npno::feature::is_bot(const std::unique_ptr<jni::entity_player>& entity) const
	-> bool
{
	return entity->get_unique_id()->version() == 2;
}