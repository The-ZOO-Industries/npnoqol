#include "feature_manager.hpp"

npno::feature_manager::feature_manager()
{
	command_manager = std::make_unique<npno::command_manager>();
	module_manager = std::make_unique<npno::module_manager>();

	jni::hook<jni::entity_player_sp>("sendChatMessage", &npno::feature_manager::send_chat_message_hook);
	jni::hook<jni::minecraft>("loadWorld", &npno::feature_manager::load_world_hook);
	jni::hook<jni::gui_new_chat>("printChatMessage", &npno::feature_manager::print_chat_message);
}

npno::feature_manager::~feature_manager() = default;

auto npno::feature_manager::update() const 
	-> void
{
	command_manager->update();
	module_manager->update();
}

auto npno::feature_manager::send_chat_message_hook(jni::hotspot::frame* frame, jni::hotspot::java_thread* thread, bool* cancel) 
	-> void
{
	auto [self, message] = frame->get_arguments<jni::entity_player_sp, std::string>();

	(*cancel) = command_manager->on_chat_message(message);
}

auto npno::feature_manager::load_world_hook(jni::hotspot::frame* frame, jni::hotspot::java_thread* thread, bool* cancel)
	-> void
{
	auto [self, _] = frame->get_arguments<jni::entity_player_sp, jni::world_client>();

	module_manager->on_load_world();
}

auto npno::feature_manager::print_chat_message(jni::hotspot::frame* frame, jni::hotspot::java_thread* thread, bool* cancel)
	-> void
{
	auto [self, chat_component] = frame->get_arguments<jni::gui_new_chat, jni::i_chat_component>();

	std::println("hook {}", chat_component->get_unformatted_text());

	(*cancel) = module_manager->on_print_chat_message(std::move(chat_component));
}