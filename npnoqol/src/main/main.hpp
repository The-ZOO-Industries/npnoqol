#pragma once

namespace zoo
{
    class main final
    {
    public:
        main() noexcept;

        ~main() noexcept;

        auto run() noexcept
            -> void;

    private:
        bool running;
    };

	inline constexpr const bool use_console{ false };
}