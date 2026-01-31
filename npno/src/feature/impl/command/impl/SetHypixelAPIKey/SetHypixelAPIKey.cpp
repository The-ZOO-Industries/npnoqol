#include "SetHypixelAPIKey.hpp"

SetHypixelAPIKey::SetHypixelAPIKey()
	: Command{ "sethypixelapikey", std::format("{}/sethypixelapikey {}<hypixel api key>", MinecraftCode::DARK_AQUA, MinecraftCode::AQUA) }
{

}

SetHypixelAPIKey::~SetHypixelAPIKey() = default;

auto SetHypixelAPIKey::OnCommand(const std::vector<std::string>& args) -> void
{
	if (args[0] != this->name)
	{
		return;
	}

	if (args.size() != 2)
	{
		mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(this->usage));
		return;
	}

	HypixelAPI::SetAPIKey(args[1]);
	mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(
		std::format("{}Set hypixel api key to {}{}",
			MinecraftCode::DARK_AQUA,
			MinecraftCode::AQUA,
			args[1]
		)));

	if (HypixelAPI::CheckKey())
	{
		mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(std::format("{}Hypixel API key is valid", MinecraftCode::GREEN)));
	}
	else
	{
		mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(std::format("{}Hypixel API key is invalid", MinecraftCode::RED)));
	}
}