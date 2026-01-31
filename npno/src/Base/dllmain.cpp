#include "Base.hpp"

#include <thread>
#include <windows.h>

static DWORD WINAPI ThreadEntry(const HMODULE module)
{
    FILE* outputBuffer = nullptr;

    AllocConsole();
    freopen_s(&outputBuffer, "CONOUT$", "w", stdout);

    {
        const std::unique_ptr<Base> base = std::make_unique<Base>();
        base->Run();
    }

    FreeConsole();
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
        HANDLE threadHandle = CreateThread(nullptr, 0ull, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadEntry), hModule, 0ul, nullptr);
        if (threadHandle)
        {
            CloseHandle(threadHandle);
        }
        break;
    }
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}