#include "base.hpp"

#include "../wrapper/register_classes.hpp"
#include "../wrapper/mapping.hpp"

npno::base::base()
    : running{ jni::init() and mapping::init() }
{
    if (running)
    {
        jni::register_classes();

        this->features = std::make_unique<feature_manager>();
    }
}

npno::base::~base()
{
    jni::shutdown();
}

auto npno::base::run()
    -> void
{
    while (this->running)
    {
        this->features->update();

        std::this_thread::sleep_for(std::chrono::milliseconds{ 40 });

        //if (GetAsyncKeyState(VK_DELETE) bitand 0x8000)
        //{
        //    this->running = false;
        //}
    }
}