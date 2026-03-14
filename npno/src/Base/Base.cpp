#include "base.hpp"

#include "../wrapper/register_classes.hpp"

npno::base::base()
    : running{ jni::init()}
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
    }
}