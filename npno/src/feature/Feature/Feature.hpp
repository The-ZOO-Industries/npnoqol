#pragma once

#include "../../src/wrapper/sdk/net/minecraft/client/Minecraft/Minecraft.h"

#include "../../util/api/HypixelAPI/HypixelAPI.hpp"
#include "../../util/Base64/Base64.hpp"
#include "../../util/ChatUtil/ChatUtil.hpp"
#include "../../util/HypixelGamemode/HypixelGamemode.hpp"
#include "../../util/HypixelRank/HypixelRank.hpp"
#include "../../util/MinecraftCode/MinecraftCode.hpp"
#include "../../util/Network/Network.hpp"

#include <sstream>
#include <print>
#include <string>
#include <vector>
#include <regex>
#include <memory>
#include <mutex>
#include <algorithm>
#include <set>
#include <random>
#include <cmath>
#include <unordered_map>
#include <chrono>

#include <npno/Type.hpp>
#include <nlohmann/json.hpp>

class Feature
{
public:
	Feature();

	virtual ~Feature();

	virtual auto Update() -> void = 0;
	virtual auto ClearCache() -> void = 0;

	virtual auto SanityCheck() const -> bool;

protected:
	auto IsBot(const std::unique_ptr<EntityPlayer>& player) const -> bool;
	auto SentByHypixel(const std::string& line) const -> bool;
	auto ToRegex(const std::vector<std::string>& lines) const -> std::vector<std::regex>;

	inline static std::unique_ptr<Minecraft> mc{};

private:
	auto Welcome() const -> void;
	auto Farewell() const -> void;
};