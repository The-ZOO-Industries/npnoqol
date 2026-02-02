#pragma once

#include "../Module/Module.hpp"

#include "../../../../util/ChatUtil/ChatUtil.hpp"

class ModuleManager final
{
public:
	ModuleManager();

	~ModuleManager();

	auto Update() const -> void;

private:
	template<typename M>
	auto RegisterModule() -> void;

	std::vector<std::unique_ptr<Module>> modules;

	std::unique_ptr<ChatUtil> chatUtil;
};