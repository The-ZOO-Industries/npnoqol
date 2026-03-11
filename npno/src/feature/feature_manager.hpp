#pragma once

#include "feature.hpp"

#include "impl/command/command_manager.hpp"

namespace npno
{
	class feature_manager final
	{
	public:
		feature_manager();

		~feature_manager();

		auto update() const 
			-> void;

	private:
		static auto send_chat_message_hook(jni::hotspot::frame* frame, jni::hotspot::java_thread* thread, bool* cancel)
			-> void;

		inline static std::unique_ptr<npno::command_manager> command_manager{};
	};
}