#include "Feature.hpp"

Feature::Feature()
{
	static std::once_flag mcFlag{};

	std::call_once(mcFlag, [this]()
		{
			mc = std::make_unique<Minecraft>();

			this->Welcome();
		});
}

Feature::~Feature()
{
	this->Farewell();
}

auto Feature::SanityCheck() const -> bool
{
	return mc->GetTheWorld()->GetInstance() and mc->GetThePlayer()->GetInstance();
}

auto Feature::IsBot(const std::unique_ptr<EntityPlayer>& player) const -> bool
{
	return static_cast<I32>(player->GetUniqueID()->Version()) == 2;
}

auto Feature::SentByHypixel(const std::string& line) const -> bool
{
	return line.contains(":");
}

auto Feature::ToRegex(const std::vector<std::string>& lines) const -> std::vector<std::regex>
{
	std::vector<std::regex> regexes;

	for (const std::string& line : lines)
	{
		regexes.emplace_back(line, std::regex_constants::icase);
	}
	
	return regexes;
}

auto Feature::Welcome() const -> void
{
	if (!this->SanityCheck())
	{
		return;
	}

	mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(
		std::format("{}Welcome to the ZOO {}{}",
			MinecraftCode::AQUA,
			MinecraftCode::DARK_AQUA,
			mc->GetThePlayer()->GetName()
		)));
}

auto Feature::Farewell() const -> void
{
	if (!this->SanityCheck())
	{
		return;
	}

	mc->GetThePlayer()->AddChatMessage(std::make_unique<ChatComponentText>(
		std::format("{}I hope you envoyed your trip in the ZOO {}{}",
			MinecraftCode::AQUA,
			MinecraftCode::DARK_AQUA,
			mc->GetThePlayer()->GetName()
		)));
}