#pragma once

#include "../../HypixelModule/HypixelModule.hpp"

class NickManager final : public HypixelModule
{
public:
    NickManager();

    ~NickManager() override;

    auto Update() -> void override;

    struct Nick
    {
        std::string realName{ "" };
        std::string nick{ "" };

        bool warned{ false };

        bool skinDenicker{ false };
    };

    static auto GetNickList() -> std::map<std::string, Nick>;

private:
    auto Warn(const std::string& name, const std::string& realName) -> void;

    auto SkinDenicker() -> void;

    auto ParseSkinData(const std::string& playerName, const std::string& skinHash, const std::string& profileName) -> void;
    auto IsNickHash(const std::string& hash) -> bool;

    std::vector<std::string> nickHashes;

    inline static std::map<std::string, Nick> nickList{};
};