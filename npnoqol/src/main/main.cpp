#include "main.hpp"

#include <thread>
#include <chrono>
#include <print>

#include "../sdk/mapping.hpp"
#include "../sdk/register_classes.hpp"
#include "../feature/feature_manager.hpp"

#include <windows.h>

zoo::main::main() noexcept
    : running{ mapping::init() }
{
	std::println("[INFO] main initialized");

    if (!this->running)
    {
        return;
    }

    sdk::register_classes();
}

zoo::main::~main() noexcept
{
    std::println("[INFO] main destroyed");
}

auto zoo::main::run() noexcept
    -> void
{
    if (!this->running)
    {
        return;
    }

    feature_manager features{};

    while (this->running)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });

        if (GetAsyncKeyState(VK_DELETE) & 0x8000)
        {
            this->running = false;
        }
    }
}
