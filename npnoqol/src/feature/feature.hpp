#pragma once

#include "../sdk/net/minecraft/client/minecraft.hpp"
#include "../util/config.hpp"
#include "../util/enum_chat_formatting.hpp"
#include "../util/hypixel_api.hpp"
#include "../util/hypixel_gametype.hpp"
#include "../util/hypixel_mode.hpp"
#include "../util/network.hpp"
#include "../util/zoo_api.hpp"

#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <format>

namespace zoo
{
	class chat;
	class player;

	inline std::string watermark{ std::format("{} > {}", enum_chat_formatting::aqua, enum_chat_formatting::reset) };
	
	class feature
	{
	public:
		feature() noexcept;

		virtual ~feature() noexcept;

		auto sanity_check() const noexcept
			-> bool;

	protected:
		static inline std::unique_ptr<sdk::minecraft> minecraft{};

		friend class chat;
		friend class player;
	};

    class chat final
    {
    public:
        static auto add_chat_message(const std::string& message) noexcept
            -> void
        {
            if (!feature::minecraft)
            {
                return;
            }

            const auto player{ feature::minecraft->get_the_player() };
            if (player && player->get_instance())
            {
				player->add_chat_message(
					vmhook::make_unique<sdk::chat_component_text>(std::format("{} {}", zoo::watermark, message))
				);
            }
        }
    };

	class entity final
	{
	public:
		static auto is_bot(const std::unique_ptr<sdk::entity>& entity) noexcept
			-> bool
		{
			return entity->get_unique_id()->version() == 2;
		}
	};

	struct hook_handler
	{
		bool detected{ false };

		virtual auto clear() ->
			void
		{
			this->detected = false;
		}
	};
}
