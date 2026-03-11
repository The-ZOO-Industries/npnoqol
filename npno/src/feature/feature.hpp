#pragma once

#include "../wrapper/sdk/net/minecraft/client/minecraft.hpp"

#include "../util/enum_chat_formatting.hpp"

#include <format>
#include <print>
#include <sstream>
#include <mutex>

namespace npno
{
	class feature
	{
	public:
		feature();

		virtual ~feature();

		virtual auto update() const
			-> void = 0;

		virtual auto sanity_check() const 
			-> bool;

	protected:
		inline static std::unique_ptr<jni::minecraft> mc{};
	};
}