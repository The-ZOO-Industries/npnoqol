#pragma once

#include "../../src/wrapper/JavaClass/JavaClass.h"

class Score final : public JavaClass
{
public:
    explicit Score(maps::Score instance);

    virtual ~Score() override;

    [[nodiscard]] I32 GetScorePoints() const;

    [[nodiscard]] std::string GetPlayerName() const;
};