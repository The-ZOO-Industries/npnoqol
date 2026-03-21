#pragma once

#include <easy_jni/easy_jni.hpp>

#include "entity/entity_player_sp.hpp"
#include "multiplayer/world_client.hpp"
#include "gui/gui_ingame.hpp"
#include "../entity/item/entity_armor_stand.hpp"

namespace jni
{
	class minecraft final : public jni::object
	{
	public:
		explicit minecraft(const jobject instance)
			: jni::object{ instance }
		{

		}

		auto get_the_minecraft() const
			-> std::unique_ptr<jni::minecraft>
		{
			return get_field<jni::minecraft>(mapping::minecraft::theMinecraft, jni::field_type::STATIC)->get();
		}
		
		auto get_the_player() const
			-> std::unique_ptr<jni::entity_player_sp>
		{
			return get_field<jni::entity_player_sp>(mapping::minecraft::thePlayer)->get();
		}

		auto get_the_world() const
			-> std::unique_ptr<jni::world_client>
		{
			return get_field<jni::world_client>(mapping::minecraft::theWorld)->get();
		}

		auto get_ingame_gui() const
			-> std::unique_ptr<jni::gui_ingame>
		{
			return get_field<jni::gui_ingame>(mapping::minecraft::ingameGUI)->get();
		}
	};
}