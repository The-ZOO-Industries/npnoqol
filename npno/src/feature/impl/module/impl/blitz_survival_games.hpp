#pragma once

#include "../hypixel_gametype_module.hpp"

namespace npno
{
	class blitz_survival_games final : public npno::hypixel_gametype_module
	{
	public:
		blitz_survival_games();

		~blitz_survival_games();

		auto update()
			-> void override;

		auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> bool override;
	};
}