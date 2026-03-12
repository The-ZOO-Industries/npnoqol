#include "feature_manager.hpp"

npno::feature_manager::feature_manager()
{
	command_manager = std::make_unique<npno::command_manager>();

	jni::hook<jni::entity_player_sp>("sendChatMessage", &npno::feature_manager::send_chat_message_hook);
}

npno::feature_manager::~feature_manager() = default;

auto npno::feature_manager::update() const 
	-> void
{
	command_manager->update();
}

auto npno::feature_manager::send_chat_message_hook(jni::hotspot::frame* frame, jni::hotspot::java_thread* thread, bool* cancel) -> void
{
	auto [self, message] = frame->get_arguments<jni::entity_player_sp, std::string>();

	(*cancel) = command_manager->on_chat_message(message);
}