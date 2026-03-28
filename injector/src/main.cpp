#include <string>
#include <vector>
#include <windows.h>
#include <tlhelp32.h>
#include <d3d11.h>
#include <dwmapi.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_win32.h>
#include <imgui/imgui_impl_dx11.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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
            return {};
        }

        const HGLOBAL hData{ LoadResource(nullptr, hRes) };
        if (!hData)
        {
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
            return false;
        }

        const std::size_t path_len{ strlen(dll_path) + 1 };
        void* remote_memory{ VirtualAllocEx(hProcess, nullptr, path_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) };
        if (!remote_memory)
        {
            CloseHandle(hProcess);
            return false;
        }

        if (!WriteProcessMemory(hProcess, remote_memory, dll_path, path_len, nullptr))
        {
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
            CloseHandle(hProcess);
            return false;
        }

        WaitForSingleObject(hThread, INFINITE);

        DWORD exit_code{ 0 };
        GetExitCodeThread(hThread, &exit_code);

        CloseHandle(hThread);
        CloseHandle(hProcess);

        return exit_code != 0;
    }

    static auto refresh_windows() noexcept
        -> std::vector<javaw_window>
    {
        std::vector<javaw_window> windows;
        EnumWindows(EnumWindowsCallback, reinterpret_cast<LPARAM>(&windows));
        return windows;
    }
}

namespace style
{
    static auto apply() noexcept 
        -> void
    {
        ImGuiStyle& s{ ImGui::GetStyle() };

        s.WindowPadding = { 16.f, 16.f };
        s.FramePadding = { 10.f, 6.f };
        s.ItemSpacing = { 8.f, 6.f };
        s.ItemInnerSpacing = { 6.f, 4.f };
        s.ScrollbarSize = 6.f;
        s.GrabMinSize = 6.f;

        s.WindowRounding = 0.f;
        s.ChildRounding = 4.f;
        s.FrameRounding = 4.f;
        s.PopupRounding = 4.f;
        s.ScrollbarRounding = 4.f;
        s.GrabRounding = 4.f;
        s.TabRounding = 4.f;

        s.WindowBorderSize = 0.f;
        s.FrameBorderSize = 0.f;

        ImVec4* c{ ImGui::GetStyle().Colors };

        c[ImGuiCol_WindowBg] = { 0.07f, 0.07f, 0.09f, 1.f };
        c[ImGuiCol_ChildBg] = { 0.10f, 0.10f, 0.13f, 1.f };
        c[ImGuiCol_PopupBg] = { 0.07f, 0.07f, 0.09f, 1.f };

        c[ImGuiCol_FrameBg] = { 0.13f, 0.13f, 0.17f, 1.f };
        c[ImGuiCol_FrameBgHovered] = { 0.18f, 0.18f, 0.23f, 1.f };
        c[ImGuiCol_FrameBgActive] = { 0.20f, 0.20f, 0.26f, 1.f };

        c[ImGuiCol_Button] = { 0.20f, 0.44f, 0.90f, 1.f };
        c[ImGuiCol_ButtonHovered] = { 0.30f, 0.54f, 1.00f, 1.f };
        c[ImGuiCol_ButtonActive] = { 0.15f, 0.36f, 0.78f, 1.f };

        c[ImGuiCol_Header] = { 0.20f, 0.44f, 0.90f, 0.30f };
        c[ImGuiCol_HeaderHovered] = { 0.20f, 0.44f, 0.90f, 0.50f };
        c[ImGuiCol_HeaderActive] = { 0.20f, 0.44f, 0.90f, 0.70f };

        c[ImGuiCol_ScrollbarBg] = { 0.07f, 0.07f, 0.09f, 1.f };
        c[ImGuiCol_ScrollbarGrab] = { 0.20f, 0.20f, 0.26f, 1.f };
        c[ImGuiCol_ScrollbarGrabHovered] = { 0.28f, 0.28f, 0.36f, 1.f };
        c[ImGuiCol_ScrollbarGrabActive] = { 0.20f, 0.44f, 0.90f, 1.f };

        c[ImGuiCol_Separator] = { 0.18f, 0.18f, 0.24f, 1.f };

        c[ImGuiCol_Text] = { 0.92f, 0.92f, 0.96f, 1.f };
        c[ImGuiCol_TextDisabled] = { 0.40f, 0.40f, 0.50f, 1.f };
    }
}

namespace dx11
{
    static ID3D11Device* device{ nullptr };
    static ID3D11DeviceContext* device_context{ nullptr };
    static IDXGISwapChain* swap_chain{ nullptr };
    static ID3D11RenderTargetView* render_target{ nullptr };

    static auto create_render_target() noexcept 
        -> void
    {
        ID3D11Texture2D* back_buffer{ nullptr };
        swap_chain->GetBuffer(0, IID_PPV_ARGS(&back_buffer));
        device->CreateRenderTargetView(back_buffer, nullptr, &render_target);
        back_buffer->Release();
    }

    static auto cleanup_render_target() noexcept 
        -> void
    {
        if (render_target)
        {
            render_target->Release();
            render_target = nullptr;
        }
    }

    static auto init(HWND hwnd) noexcept 
        -> bool
    {
        DXGI_SWAP_CHAIN_DESC sd{};
        sd.BufferCount = 2;
        sd.BufferDesc.Width = 0;
        sd.BufferDesc.Height = 0;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hwnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;
        sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        const D3D_FEATURE_LEVEL feature_levels[]{ D3D_FEATURE_LEVEL_11_0 };
        D3D_FEATURE_LEVEL feature_level{};

        if (D3D11CreateDeviceAndSwapChain(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            0,
            feature_levels,
            1,
            D3D11_SDK_VERSION,
            &sd,
            &swap_chain,
            &device,
            &feature_level,
            &device_context
        ) != S_OK)
        {
            return false;
        }

        create_render_target();
        return true;
    }

    static auto cleanup() noexcept 
        -> void
    {
        cleanup_render_target();
        if (swap_chain) 
        { 
            swap_chain->Release();     
            swap_chain = nullptr; 
        }

        if (device_context) 
        { 
            device_context->Release(); 
            device_context = nullptr; 
        }

        if (device) 
        { 
            device->Release();         
            device = nullptr; 
        }
    }
}

static bool  g_dragging{ false };
static POINT g_drag_cursor{};
static POINT g_drag_window{};

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
    {
        return true;
    }

    switch (msg)
    {
    case WM_SIZE:
        if (dx11::device && wParam != SIZE_MINIMIZED)
        {
            dx11::cleanup_render_target();
            dx11::swap_chain->ResizeBuffers(0, LOWORD(lParam), HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
            dx11::create_render_target();
        }
        return 0;
    case WM_LBUTTONDOWN:
    {
        const int my{ HIWORD(lParam) };
        if (my < 36)
        {
            g_dragging = true;
            GetCursorPos(&g_drag_cursor);
            RECT wr{};
            GetWindowRect(hwnd, &wr);
            g_drag_window = { wr.left, wr.top };
            SetCapture(hwnd);
        }
        break;
    }
    case WM_MOUSEMOVE:
        if (g_dragging)
        {
            POINT cur{};
            GetCursorPos(&cur);
            SetWindowPos(hwnd, nullptr,
                g_drag_window.x + (cur.x - g_drag_cursor.x),
                g_drag_window.y + (cur.y - g_drag_cursor.y),
                0, 0, SWP_NOSIZE | SWP_NOZORDER);
        }
        break;
    case WM_LBUTTONUP:
        if (g_dragging)
        {
            g_dragging = false;
            ReleaseCapture();
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"zoo_client";
    RegisterClassExW(&wc);

    const HWND hwnd{ CreateWindowExW(
        0,
        wc.lpszClassName,
        L"Zoo Client",
        WS_POPUP,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        440,
        340,
        nullptr,
        nullptr,
        hInstance,
        nullptr
    ) };

    if (!dx11::init(hwnd))
    {
        dx11::cleanup();
        UnregisterClassW(wc.lpszClassName, hInstance);
        return EXIT_FAILURE;
    }

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    style::apply();

    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(dx11::device, dx11::device_context);

    std::vector<injector::javaw_window> windows{ injector::refresh_windows() };
    std::int32_t selected{ -1 };
    std::string status{};
    bool status_ok{ false };

    const ImVec4 clear_color{ 0.07f, 0.07f, 0.09f, 1.00f };

    MSG msg{};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
            continue;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        const ImVec2 display{ ImGui::GetIO().DisplaySize };

        ImGui::SetNextWindowPos({ 0, 0 });
        ImGui::SetNextWindowSize(display);
        ImGui::Begin("##main", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoBringToFrontOnFocus
        );

        const ImVec2 win_pos{ ImGui::GetWindowPos() };
        ImGui::GetWindowDrawList()->AddRectFilled(
            win_pos,
            { win_pos.x + display.x, win_pos.y + 36.f },
            IM_COL32(10, 10, 14, 255)
        );

        ImGui::SetCursorPos({ 14.f, 10.f });
        ImGui::Text("Zoo Client");

        ImGui::SetCursorPos({ display.x - 72.f, 0.f });
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.f, 0.f, 0.f, 0.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.22f, 0.22f, 0.28f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.15f, 0.15f, 0.20f, 1.f });
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
        if (ImGui::Button("-##min", { 36.f, 36.f }))
        {
            ShowWindow(hwnd, SW_MINIMIZE);
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);

        ImGui::SetCursorPos({ display.x - 36.f, 0.f });
        ImGui::PushStyleColor(ImGuiCol_Button, { 0.f, 0.f, 0.f, 0.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.85f, 0.20f, 0.20f, 1.f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.65f, 0.10f, 0.10f, 1.f });
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0.f);
        if (ImGui::Button("x##cls", { 36.f, 36.f }))
        {
            PostQuitMessage(0);
        }
        ImGui::PopStyleVar();
        ImGui::PopStyleColor(3);

        ImGui::SetCursorPos({ 16.f, 52.f });

        ImGui::TextDisabled("SELECT PROCESS");
        ImGui::Spacing();

        if (ImGui::Button("Refresh", { -1.f, 28.f }))
        {
            windows = injector::refresh_windows();
            selected = -1;
            status.clear();
        }

        ImGui::Spacing();

        ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.05f, 0.05f, 0.07f, 1.f });
        ImGui::BeginChild("##list", { -1.f, 140.f }, false, ImGuiWindowFlags_NoScrollbar);

        if (windows.empty())
        {
            ImGui::SetCursorPosY(60.f);
            const float tw{ ImGui::CalcTextSize("No javaw.exe found").x };
            ImGui::SetCursorPosX((ImGui::GetContentRegionAvail().x - tw) * 0.5f);
            ImGui::TextDisabled("No javaw.exe found");
        }
        else
        {
            for (std::int32_t i = 0; i < static_cast<std::int32_t>(windows.size()); i++)
            {
                const std::string label{ windows[i].title + "  |  PID " + std::to_string(windows[i].process_id) };
                if (ImGui::Selectable(label.c_str(), selected == i))
                {
                    selected = i;
                    status.clear();
                }
            }
        }

        ImGui::EndChild();
        ImGui::PopStyleColor();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        const bool can_inject{ selected >= 0 && selected < static_cast<std::int32_t>(windows.size()) };

        if (!can_inject)
        {
            ImGui::BeginDisabled();
        }

        if (ImGui::Button("Inject", { -1.f, 36.f }))
        {
            const std::string dll_path{ injector::extract_dll_to_temp() };
            if (dll_path.empty())
            {
                status = "Failed to extract DLL";
                status_ok = false;
            }
            else if (injector::inject_dll(windows[selected].process_id, dll_path.c_str()))
            {
                status = "Injected successfully";
                status_ok = true;
            }
            else
            {
                status = "Injection failed";
                status_ok = false;
            }
        }

        if (!can_inject)
        {
            ImGui::EndDisabled();
        }

        if (!status.empty())
        {
            ImGui::Spacing();
            if (status_ok)
            {
                ImGui::TextColored({ 0.30f, 0.85f, 0.45f, 1.f }, "%s", status.c_str());
            }
            else
            {
                ImGui::TextColored({ 0.90f, 0.30f, 0.30f, 1.f }, "%s", status.c_str());
            }
        }

        ImGui::End();

        ImGui::Render();

        const float clear[]{ clear_color.x, clear_color.y, clear_color.z, clear_color.w };
        dx11::device_context->OMSetRenderTargets(1, &dx11::render_target, nullptr);
        dx11::device_context->ClearRenderTargetView(dx11::render_target, clear);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        dx11::swap_chain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    dx11::cleanup();
    DestroyWindow(hwnd);
    UnregisterClassW(wc.lpszClassName, hInstance);

    return EXIT_SUCCESS;
}