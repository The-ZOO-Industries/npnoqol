#pragma once

#include "../../../Feature/Feature.hpp"

class Module : public Feature
{
public:
	explicit Module(const bool enable = true);

	virtual ~Module();

	virtual auto IsEnable() const -> bool final;
	virtual auto SetEnable(const bool state) -> void final;

private:
	bool enable;
};