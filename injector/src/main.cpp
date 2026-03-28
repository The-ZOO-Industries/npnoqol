#include <iostream>
#include <print>
#include <string>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>

namespace injector
{
    struct javaw_window
    {
        DWORD process_id{};
        std::string title{};
    };

    static auto is_javaw_process(const DWORD process_id) noexcept
        -> bool
    {
        const HANDLE hSnap{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
        if (hSnap == INVALID_HANDLE_VALUE)
        {
            return false;
        }

        PROCESSENTRY32W pe{};
        pe.dwSize = sizeof(pe);

        bool found{ false };
        if (Process32FirstW(hSnap, &pe))
        {
            do {
                if (pe.th32ProcessID == process_id)
                {
                    const std::wstring name{ pe.szExeFile };
                    found = (name == L"javaw.exe");
                    break;
                }
            } while (Process32NextW(hSnap, &pe));
        }

        CloseHandle(hSnap);
        return found;
    }

    BOOL CALLBACK EnumWindowsCallback(HWND hwnd, LPARAM lParam)
    {
        if (!IsWindowVisible(hwnd))
        {
            return TRUE;
        }

        char title[512];
        if (!GetWindowTextA(hwnd, title, sizeof(title)))
        {
            return TRUE;
        }

        if (strlen(title) == 0)
        {
            return TRUE;
        }

        DWORD process_id{ 0 };
        GetWindowThreadProcessId(hwnd, &process_id);

        if (injector::is_javaw_process(process_id))
        {
            auto* windows{ reinterpret_cast<std::vector<injector::javaw_window>*>(lParam) };
            windows->push_back({ process_id, title });
        }

        return TRUE;
    }

    static auto extract_dll_to_temp() noexcept
        -> std::string
    {
        const HRSRC hRes{ FindResourceW(nullptr, MAKEINTRESOURCEW(256), RT_RCDATA) };
        if (!hRes)
        {
            std::println("[ERROR] FindResource failed");
            return {};
        }

        const HGLOBAL hData{ LoadResource(nullptr, hRes) };
        if (!hData)
        {
            std::println("[ERROR] LoadResource failed");
            return {};
        }

        const void* data{ LockResource(hData) };
        const DWORD size{ SizeofResource(nullptr, hRes) };

        char temp_path[MAX_PATH];
        char temp_file[MAX_PATH];
        GetTempPathA(MAX_PATH, temp_path);
        GetTempFileNameA(temp_path, "dll", 0, temp_file);

        const HANDLE hFile{ CreateFileA(temp_file, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) };
        if (hFile == INVALID_HANDLE_VALUE)
        {
            std::println("[ERROR] CreateFile failed");
            std::cin.get();
            return {};
        }

        DWORD written{ 0 };
        WriteFile(hFile, data, size, &written, nullptr);
        CloseHandle(hFile);

        return std::string{ temp_file };
    }

    static auto inject_dll(const DWORD process_id, const char* dll_path) noexcept
        -> bool
    {
        const HANDLE hProcess{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id) };
        if (!hProcess || hProcess == INVALID_HANDLE_VALUE)
        {
            std::println("[ERROR] OpenProcess failed");
            return false;
        }

        const std::size_t path_len{ strlen(dll_path) + 1 };
        void* remote_memory{ VirtualAllocEx(hProcess, nullptr, path_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) };
        if (!remote_memory)
        {
            std::println("[ERROR] VirtualAllocEx failed");
            CloseHandle(hProcess);
            return false;
        }

        if (!WriteProcessMemory(hProcess, remote_memory, dll_path, path_len, nullptr))
        {
            std::println("[ERROR] WriteProcessMemory failed");
            CloseHandle(hProcess);
            return false;
        }

        const HANDLE hThread{ CreateRemoteThread(
            hProcess,
            nullptr,
            0,
            reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryA),
            remote_memory,
            0,
            nullptr
        ) };

        if (!hThread)
        {
            std::println("[ERROR] CreateRemoteThread failed");
            CloseHandle(hProcess);
            return false;
        }

        WaitForSingleObject(hThread, INFINITE);

        DWORD exit_code{ 0 };
        GetExitCodeThread(hThread, &exit_code);
        if (!exit_code)
        {
            std::println("[ERROR] LoadLibrary failed in remote process");
            CloseHandle(hThread);
            CloseHandle(hProcess);
            return false;
        }

        std::println("[INFO] LoadLibrary succeeded (module: {:#x})", exit_code);

        CloseHandle(hThread);
        CloseHandle(hProcess);
        return true;
    }
}

auto main()
    -> std::int32_t
{
    std::vector<injector::javaw_window> windows;
    EnumWindows(injector::EnumWindowsCallback, reinterpret_cast<LPARAM>(&windows));

    if (windows.empty())
    {
        std::println("[ERROR] No javaw.exe window found");
        std::cin.get();

        return EXIT_FAILURE;
    }

    DWORD target_pid{ 0 };

    if (windows.size() == 1)
    {
        target_pid = windows[0].process_id;
    }
    else
    {
        for (std::size_t i = 0; i < windows.size(); i++)
        {
            std::println("[{}] {} (PID: {})", i, windows[i].title, windows[i].process_id);
        }

        std::print("\n[INPUT] Choose a window: ");
        std::size_t choice{ 0 };
        std::cin >> choice;

        if (choice >= windows.size())
        {
            std::println("[ERROR] Invalid choice");
            std::cin.get();
            return EXIT_FAILURE;
        }

        target_pid = windows[choice].process_id;
    }

    const std::string dll_path{ injector::extract_dll_to_temp() };
    if (dll_path.empty())
    {
        std::cin.get();
        return EXIT_FAILURE;
    }

    if (!injector::inject_dll(target_pid, dll_path.c_str()))
    {
        std::cin.get();
        return EXIT_FAILURE;
    }
}