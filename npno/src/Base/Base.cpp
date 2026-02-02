#include "Base.hpp"

#include "../wrapper/Jvm/Jvm.h"

#include <chrono>
#include <thread>
#include <windows.h>

Base::Base()
    : running{ Jvm::Init() }
{
    if (running)
    {
        this->featureManager = std::make_unique<FeatureManager>();
    }
}

Base::~Base() = default;

auto Base::Run() -> void
{
    while (this->running)
    {
        this->featureManager->Update();

        if (GetAsyncKeyState(VK_DELETE) bitand 0x8000)
        {
            this->running = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
}