#include "base.hpp"

static DWORD WINAPI ThreadEntry(const HMODULE module)
{
    //FILE* outputBuffer{ nullptr };

    //AllocConsole();
    //freopen_s(&outputBuffer, "CONOUT$", "w", stdout);

    {
        const std::unique_ptr<npno::base> base{ std::make_unique<npno::base>() };
        base->run();
    }

    //FreeConsole();
    FreeLibraryAndExitThread(module, 0ul);

    return 0l;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        DisableThreadLibraryCalls(hModule);
        HANDLE thread_handle = CreateThread(nullptr, 0ull, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadEntry), hModule, 0ul, nullptr);
        if (thread_handle)
        {
            CloseHandle(thread_handle);
        }
        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}