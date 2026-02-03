#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class ScoreObjective final : public JavaClass
{
public:
	explicit ScoreObjective(const jobject instance);

	virtual ~ScoreObjective() override;

	[[nodiscard]] std::string GetName() const;
	[[nodiscard]] std::string GetDisplayName() const;

	void SetDisplayName(const std::string& name) const;
};