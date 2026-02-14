#pragma once

#include <windows.h>
#include <dbghelp.h>
#include <iostream>

auto inline PrintStackTrace() -> void
{
    HANDLE process{ GetCurrentProcess() };

    SymInitialize(process, NULL, TRUE);

    void* stack[64]{};
    const USHORT frameCount{ CaptureStackBackTrace(0, 64, stack, NULL) };

    SYMBOL_INFO* symbol{
        reinterpret_cast<SYMBOL_INFO*>(
            malloc(sizeof(SYMBOL_INFO) + 256)
        )
    };

    if (!symbol)
    {
        return;
    }

    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen = 255;

    std::cout << "Stack trace:\n";

    for (USHORT i{}; i < frameCount; i++)
    {
        SymFromAddr(
            process,
            reinterpret_cast<DWORD64>(stack[i]),
            0,
            symbol
        );

        std::cout
            << frameCount - i - 1
            << ": "
            << symbol->Name
            << "\n";
    }

    free(symbol);

    SymCleanup(process);
}