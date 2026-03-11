#pragma once

#include "../feature/feature_manager.hpp"

namespace npno
{
    class base final
    {
    public:
        base();

        ~base();

        auto run() 
            -> void;

    private:
        std::unique_ptr<feature_manager> features;

        bool running;
    };
}