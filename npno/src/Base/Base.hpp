#pragma once

#include "../feature/FeratureManager/FeratureManager.hpp"

class Base final
{
public:
    Base();

    ~Base();

    auto Run() const -> void;

private:
    std::unique_ptr<FeratureManager> ;

    bool running;
};