#pragma once

#include "../../feature.hpp"

namespace npno
{
	class module : public npno::feature
	{
	public:
		explicit module(const bool enable = true);

		virtual ~module();

		virtual auto on_load_world()
			-> void = 0;

		virtual auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> void = 0;

		auto is_enable() const
			-> bool;

		auto set_enable(const bool state)
			-> void;

	protected:
		bool enable;
	};
}