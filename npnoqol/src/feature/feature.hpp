#pragma once

#include "../sdk/net/minecraft/client/minecraft.hpp"
#include "../util/config.hpp"
#include "../util/enum_chat_formatting.hpp"
#include "../util/hypixel_api.hpp"
#include "../util/hypixel_gametype.hpp"
#include "../util/hypixel_mode.hpp"
#include "../util/network.hpp"

#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <format>

namespace zoo
{
	class util;

	inline std::string watermark{ std::format("{}{}*{}zoo{}*{}", enum_chat_formatting::italic, enum_chat_formatting::aqua, enum_chat_formatting::dark_aqua, enum_chat_formatting::aqua, enum_chat_formatting::reset) };
	
	class feature
	{
	public:
		feature() noexcept;

		virtual ~feature() noexcept;

		auto sanity_check() const noexcept
			-> bool;

	protected:
		static inline std::unique_ptr<sdk::minecraft> minecraft{};

		friend class util;
	};

    class util final
    {
    public:
        static auto add_chat_message(const std::string& message) noexcept
            -> void
        {
            if (feature::minecraft && feature::minecraft->get_the_player()->get_instance())
            {
                std::unique_ptr<sdk::chat_component_text> chat_component{ vmhook::make_unique<sdk::chat_component_text>(std::format("{} {}", zoo::watermark, message)) };
                if (chat_component && chat_component->get_instance())
                {
                    feature::minecraft->get_the_player()->add_chat_message(
                        std::unique_ptr<sdk::i_chat_component>{ static_cast<sdk::i_chat_component*>(chat_component.release()) });
                }
            }
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
