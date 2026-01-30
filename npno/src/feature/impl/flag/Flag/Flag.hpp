#pragma once

#include "../../../Feature/Feature.hpp"

class Flag : public Feature
{
public:
    explicit Flag(const std::string& name);

    virtual ~Flag();

    static auto GetPlayers() -> void;

    static auto GetPlayersLastTick() -> std::vector<Player>;

    struct Player
    {
        std::string name;

        struct
        {
            F64 x;
            F64 y;
            F64 z;
        } position;

        struct
        {
            F64 x;
            F64 y;
            F64 z;
        } velocity;

        F32 yaw;
        F32 pitch;

        bool isOnGround;
        std::chrono::time_point<std::chrono::system_clock> onGroundTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceOnGround;

        bool isSprinting;
        std::chrono::time_point<std::chrono::system_clock> sprintingTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceSprinted;

        bool isSneaking;
        std::chrono::time_point<std::chrono::system_clock> sneakingTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceSneaking;

        bool isSwingingSword;
        std::chrono::time_point<std::chrono::system_clock> swingingSwordTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceSwingingSword;

        bool isBlockingSword;
        std::chrono::time_point<std::chrono::system_clock> blockingSwordTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceBlockingSword;

        bool isEating;
        std::chrono::time_point<std::chrono::system_clock> isEatingTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceEating;

        bool isRiding;
        std::chrono::time_point<std::chrono::system_clock> isRidingTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceRiding;

        bool isBowing;
        std::chrono::time_point<std::chrono::system_clock> isBowingTime;
        std::chrono::time_point<std::chrono::system_clock> timeSinceBowing;
    };

protected:
    inline static std::vector<Player> playersLastTick{};

    std::string name;
};