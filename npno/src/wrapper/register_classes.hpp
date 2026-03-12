#pragma once

#include <easy_jni/easy_jni.hpp>

#include "sdk/net/minecraft/client/minecraft.hpp"

namespace jni
{
	static auto register_classes()
		-> void
	{
		jni::register_class<jni::minecraft>("net/minecraft/client/Minecraft");

		jni::register_class<jni::entity>("net/minecraft/entity/Entity");
		jni::register_class<jni::entity_living_base>("net/minecraft/entity/EntityLivingBase");
		jni::register_class<jni::entity_player>("net/minecraft/entity/player/EntityPlayer");
		jni::register_class<jni::entity_player_sp>("net/minecraft/client/entity/EntityPlayerSP");

		jni::register_class<jni::world>("net/minecraft/world/World");
		jni::register_class<jni::world_client>("net/minecraft/client/multiplayer/WorldClient");

		jni::register_class<jni::i_chat_component>("net/minecraft/util/IChatComponent");
		jni::register_class<jni::chat_component_text>("net/minecraft/util/ChatComponentText");

		jni::register_class<jni::gui_ingame>("net/minecraft/client/gui/GuiIngame");
		jni::register_class<jni::gui_new_chat>("net/minecraft/client/gui/GuiNewChat");
	}
}