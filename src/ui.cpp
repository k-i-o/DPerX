/*#include "ui.h"

#include "libs/imgui/imgui_impl_dx11.h"
#include "libs/imgui/imgui_impl_win32.h"
#include "libs/imgui/imgui_internal.h"
#include "spoofer.h"
#include "game_info.hpp"
#include "cheat.h"

#include <iostream>
#include <algorithm>
#include <vector>
#include <windows.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND window,
    UINT message,
    WPARAM wideParameter,
    LPARAM longParameter
);


LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param) {
    if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
        return 0L;

    if (message == WM_DESTROY) {
        PostQuitMessage(0);
        return 0L;
    }

    return DefWindowProc(window, message, w_param, l_param);
}


void ui::CreateHUIWindow(GameInfo* gameInfoE) noexcept
{
    // wc.cbSize = sizeof(WNDCLASSEX);
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    // wc.lpfnWndProc = window_procedure;
    // wc.hInstance = GetModuleHandle(nullptr);
    // wc.hCursor = 0;
    // wc.lpszClassName = L"UI";

    gameInfo = gameInfoE;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_CLASSDC;
    wc.lpfnWndProc = window_procedure;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(nullptr);
    wc.hIcon = 0;
    wc.hCursor = 0;
    wc.hbrBackground = 0;
    wc.lpszMenuName = 0;
    wc.lpszClassName = L"overlay";
    wc.hIconSm = 0;

    RegisterClassExW(&wc);

    window = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        wc.lpszClassName,
        L"DPerX",
        WS_POPUP,
        static_cast<int>(gameInfo->viewportX), static_cast<int>(gameInfo->viewportY), static_cast<int>(gameInfo->viewportWidth), static_cast<int>(gameInfo->viewportHeight),
        nullptr, nullptr, wc.hInstance, nullptr
    );

    SetLayeredWindowAttributes(window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);
    {
        RECT client_area{};
        GetClientRect(window, &client_area);

        RECT window_area{};
        GetWindowRect(window, &window_area);

        POINT diff{};
        ClientToScreen(window, &diff);

        const MARGINS margins{
            window_area.left + (diff.x - window_area.left),
            window_area.top + (diff.y - window_area.top),
            client_area.right,
            client_area.bottom
        };

        DwmExtendFrameIntoClientArea(window, &margins);
    }


    ShowWindow(window, SW_SHOWDEFAULT);
    UpdateWindow(window);

}

void ui::DestroyHUIWindow() noexcept
{
    DestroyWindow(window);
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
}

bool ui::CreateUIDevice() noexcept {
    DXGI_SWAP_CHAIN_DESC sd{};
    sd.BufferDesc.RefreshRate.Numerator = 60U;
    sd.BufferDesc.RefreshRate.Denominator = 1U;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1U;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2U;
    sd.OutputWindow = window;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    constexpr D3D_FEATURE_LEVEL levels[2]{
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };


    D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0U,
        levels,
        2U,
        D3D11_SDK_VERSION,
        &sd,
        &swap_chain,
        &device,
        &level,
        &device_context
    );

    ID3D11Texture2D* back_buffer{ nullptr };
    swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));

    if (back_buffer) {
        device->CreateRenderTargetView(back_buffer, nullptr, &render_target_view);
        back_buffer->Release();
        return true;
    }
    return false;

}


void ui::ResetUIDevice() noexcept
{
    ImGui_ImplDX11_InvalidateDeviceObjects();

    ui::DestroyUIDevice();

    ImGui_ImplDX11_CreateDeviceObjects();
}

void ui::DestroyUIDevice() noexcept
{
    if (device)
    {
        device->Release();
        device = nullptr;
    }

    if (swap_chain)
    {
        swap_chain->Release();
        swap_chain = nullptr;
    }
}

void ui::CreateUIImGui() noexcept
{

    ImGui::CreateContext();
    ImGuiIO& io = ::ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(device, device_context);
}

void ui::DestroyUIImGui() noexcept
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    if (swap_chain) {
        swap_chain->Release();
    }

    if (device_context) {
        device_context->Release();
    }

    if (device) {
        device->Release();
    }

    if (render_target_view) {
        render_target_view->Release();
    }

}

void ui::BeginRenderUI() noexcept
{

    MSG message;
    while (PeekMessage(&message, nullptr, 0U, 0U, PM_REMOVE)) {

        TranslateMessage(&message);
        DispatchMessage(&message);

        if (message.message == WM_QUIT)
        {
            isRunning = !isRunning;
            return;
        }
    }


    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

}

void ui::EndRenderUI() noexcept
{
    ImGui::EndFrame();

    ImGui::Render();

    constexpr float color[4]{ 0.f, 0.f, 0.f, 0.f };
    device_context->OMSetRenderTargets(1U, &render_target_view, nullptr);
    device_context->ClearRenderTargetView(render_target_view, color);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    swap_chain->Present(1U, 0U);
}

std::vector<int> ListenAndPrintKeys() {
    std::vector<int> pressedKeys;
    bool started = false;

    while (true) {

        if (started && pressedKeys.size() > 0 && GetAsyncKeyState(VK_RETURN)) {
            break;
        }

        for (int key = 8; key <= 255; ++key) {
            if (GetAsyncKeyState(key)) {
                if (std::find(pressedKeys.begin(), pressedKeys.end(), key) == pressedKeys.end()) {
                    pressedKeys.push_back(key);
                    started = true;
                }
            }
            // else {
            //     auto it = std::find(pressedKeys.begin(), pressedKeys.end(), key);
            //     if (it != pressedKeys.end()) {
            //         pressedKeys.erase(it);
            //     }
            // }
        }

        Sleep(5);
    }

    return pressedKeys;

}

void ui::RenderUI(Aimbot* aimbot, ESP* esp, Server* server, Moves* moves, Spinbot* spinbot) noexcept
{

    if (!gameInfo->isFocused() && !(GetForegroundWindow() == window)) return;

    if (ui::isMenuOpen) {

        ImGui::SetNextWindowSize({ GUI_WIDTH, GUI_HEIGHT });
        ImGui::Begin(
            "Cheats by Kio",
            &isRunning,
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoCollapse
        );


        ImGui::Text("Aimbot settings");
        ImGui::Checkbox("Enable Global Aimbot", &aimbot->global_fov_enabled);
        // ImGui::Checkbox("Enable Focused Aimbot", &aimbot->global_fov_enabled);
        ImGui::Checkbox("Enable Silent Aimbot", &aimbot->silent_enabled);
        if (aimbot->global_fov_enabled || aimbot->focused_fov_enabled || aimbot->silent_enabled) {
            ImGui::Checkbox("Enable Aimbot autofire", &aimbot->autofire);
            ImGui::SliderInt("Aimbot FOV Distance", &aimbot->fov_distance, 0, 1000);
            if (aimbot->autofire) {
                ImGui::SliderInt("Aimbot autofire trigger distance", &aimbot->autofire_distance, 0, 1500);
            }
            if (aimbot->focused_fov_enabled)
                ImGui::SliderAngle("Aimbot FOV Angle", &aimbot->fov_angle, 0, 360);

        }

        ImGui::Checkbox("Aimbot avoid freezed tees", &aimbot->avoid_freezed_tee);

        if (ImGui::Button("Custom hokey silent aimbot")) {
            aimbot->hotkeys = ListenAndPrintKeys();
        }
        else if (Cheat::GetHotkeysText(aimbot->hotkeys) != "") {
            ImGui::Text(Cheat::GetHotkeysText(aimbot->hotkeys).c_str());
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Moves settings");
        ImGui::Checkbox("Enable Stabilize", &moves->enabled);
        if (ImGui::Button("Custom hokey stabilize")) {
            moves->hotkeys = ListenAndPrintKeys();
        }
        else if (Cheat::GetHotkeysText(moves->hotkeys) != "") {
            ImGui::Text(Cheat::GetHotkeysText(moves->hotkeys).c_str());
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Spinbot settings");
        ImGui::Checkbox("Enable Spinbot", &spinbot->enabled);
        if (ImGui::Button("Custom hokey spinbot")) {
            spinbot->hotkeys = ListenAndPrintKeys();
        }
        else if (Cheat::GetHotkeysText(spinbot->hotkeys) != "") {
            ImGui::Text(Cheat::GetHotkeysText(spinbot->hotkeys).c_str());
        }

        ImGui::Text("Spinbot speed");
        ImGui::SliderFloat("Spinbot speed", &spinbot->spinbotSpeed, 0, 100);

        ImGui::Text("Spinbot range");
        ImGui::SliderInt("Spinbot range", &spinbot->spinbotRange, 0, 900);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("UnBan (from some servers)");

        if (ImGui::Button("Spoof")) {
            if (gameInfo->isRunning()) {
                ImGui::OpenPopup("closeclient");
            }
            else {
                ImGui::OpenPopup("backup");
            }
        }

        if (ImGui::BeginPopupModal("backup", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("Do you want a backup?");
            ImGui::Separator();

            if (ImGui::Button("Yes", ImVec2(120, 0))) {
                Spoofer::SpoofDDnetFolders(true);
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("No", ImVec2(120, 0))) {
                Spoofer::SpoofDDnetFolders(false);
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();

        }

        if (ImGui::BeginPopupModal("closeclient", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::Text("You need to close the client to spoof!");

            ImGui::Separator();

            if (ImGui::Button("Close the game", ImVec2(200, 0))) {
                gameInfo->CloseGame();
                ImGui::CloseCurrentPopup();
            }

            ImGui::SameLine();

            if (ImGui::Button("Let me play!", ImVec2(200, 0))) {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();

        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox("Enable ESP", &esp->enabled);
        ImGui::Checkbox("Show nearest player", &esp->show_nearest);
        ImGui::ColorEdit4("Box color", (float*)&esp->color_box);
        ImGui::ColorEdit4("Name color", (float*)&esp->color_name);
        ImGui::ColorEdit4("Line color", (float*)&esp->color_line);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();


        ImGui::End();

    }

    if (esp->enabled) {
        ImVec2 centerScreen = { gameInfo->viewportWidth / 2, gameInfo->viewportHeight / 2 };

        for (int i = 0; i < Server::MAX_PLAYERS; i++) {
            Player player = server->players[i];

            ImVec2 pos = {
                        ((player.position.x - Server::localPlayer.position.x) - 20 + centerScreen.x) - player.player_size / 2,
                        ((player.position.y - Server::localPlayer.position.y) - 20 + centerScreen.y) - player.player_size / 2
            };

            if (Server::GetValidPlayer(player) && player.id != Server::localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS)) {

                ImGui::GetBackgroundDrawList()->AddRect(pos, { pos.x + player.player_size + 10, pos.y + player.player_size + 10 }, esp->color_box, 0, 0, 1);
                ImGui::GetBackgroundDrawList()->AddText({ pos.x, pos.y - 20 }, esp->color_name, std::to_string(player.id).c_str());
                ImGui::GetBackgroundDrawList()->AddLine({ centerScreen.x, centerScreen.y }, { pos.x + player.player_size / 2, pos.y + player.player_size / 2 }, esp->color_line, 1);
                char dist[100];
                sprintf_s(dist, "Distance: %i", (int)Aimbot::distance(player.position, Server::localPlayer.position));
                ImGui::GetBackgroundDrawList()->AddText({ pos.x, pos.y - 35 }, esp->color_name, dist);

            }
            else if (player.id == Server::localPlayer.id && esp->show_nearest) {

                Aimbot::GetNearestToPlayer(9999, server);
                char dist[100];
                sprintf_s(dist, "Nearest player distance: %i", (int)Aimbot::distance(Server::localPlayer.nearestPlayer.position, Server::localPlayer.position));
                ImGui::GetBackgroundDrawList()->AddText({ pos.x - 60, pos.y - 40 }, esp->color_name, dist);
            }
        }
    }

}

void ui::SetMenuOpen() noexcept {

    SetWindowLongW(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT);

}

void ui::SetMenuClose() noexcept {

    SetWindowLongW(window, GWL_EXSTYLE, WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED);

}*/