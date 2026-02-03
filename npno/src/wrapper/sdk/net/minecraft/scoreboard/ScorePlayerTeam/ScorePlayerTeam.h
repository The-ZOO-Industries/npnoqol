#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class ScorePlayerTeam final : public JavaClass
{
public:
	explicit ScorePlayerTeam(const jobject instance);

	virtual ~ScorePlayerTeam() override;

	[[nodiscard]] std::string GetNamePrefix() const;
	[[nodiscard]] std::string GetNameSuffix() const;
	[[nodiscard]] std::string GetTeamName() const;

	[[nodiscard]] std::vector<std::string> GetMembershipCollection() const;

	void SetNamePrefix(const std::string& prefix) const;
	void SetNameSuffix(const std::string& suffix) const;
};