#pragma once

#include "../module.hpp"

namespace npno
{
	class gametype_manager final : public npno::module 
	{
	public:
		gametype_manager();

		~gametype_manager();

		auto update() 
			-> void override;

		auto on_load_world()
			-> void override {};

		virtual auto on_print_chat_message(const std::unique_ptr<jni::i_chat_component>& chat_component)
			-> void override;

	private:
		auto extract_json(const std::string& line) const
			-> std::string;
	};
}