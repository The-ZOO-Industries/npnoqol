#include "mapping.hpp"

#include "net/minecraft/client/minecraft.hpp"

namespace mapping
{
	auto can_inject() noexcept
		-> bool
	{
		if (vmhook::find_class("net/minecraft/client/Minecraft"))
		{
			vmhook::register_class<sdk::minecraft>("net/minecraft/client/Minecraft");

			if (sdk::minecraft::get_field("theMinecraft"))
			{
				std::println("[INFO] Using MCP mapping");
				mode = mapping_mode::MCP;
				return true;
			}

			if (sdk::minecraft::get_field("field_71432_P"))
			{
				std::println("[INFO] Using SRG mapping");
				mode = mapping_mode::SRG;
				return true;
			}

			std::println("[INFO] Cannot inject in this client");
			return false;
		}

		if (vmhook::find_class("ave"))
		{
			vmhook::register_class<sdk::minecraft>("ave");

			std::println("[INFO] Using OBF mapping");
			mode = mapping_mode::OBF;
			return true;
		}

		std::println("[INFO] Cannot inject in this client");
		return false;
	}
}