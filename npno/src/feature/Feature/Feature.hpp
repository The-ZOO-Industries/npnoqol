#pragma once

#include "../../src/wrapper/sdk/net/minecraft/client/Minecraft/Minecraft.h"

#include "../../util/MinecraftCode/MinecraftCode.hpp"

#include <print>
#include <memory>
#include <mutex>

#include <npno/Type.hpp>
#include <nlohmann/json.hpp>

class Feature
{
public:
	Feature();

	virtual ~Feature();

	virtual auto Update() -> void = 0;

	virtual auto SanityCheck() const -> bool;

protected:
	auto IsBot(const std::unique_ptr<EntityPlayer>& player) const -> bool;
	auto SentByHypixel(const std::string& line) const -> bool;

	inline static std::unique_ptr<Minecraft> mc{};

private:
	auto Welcome() const -> void;
	auto Farewell() const -> void;
};