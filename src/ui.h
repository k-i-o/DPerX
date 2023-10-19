#pragma once

#include "aimbot.h"
#include "player.h"
#include "server.h"
#include "esp.h"
#include "moves.h"
#include "game_info.hpp"
#include "spinbot.h"
#include "libs/imgui/imgui.h"

#include <Windows.h>
#include <dwmapi.h>
#include <d3d11.h>


namespace ui
{

	inline const int GUI_WIDTH = 500;
	inline const int GUI_HEIGHT = 400;

	inline GameInfo *gameInfo = nullptr;

	inline HWND window = nullptr;
    inline WNDCLASSEXW wc{};

	inline bool isRunning = true;
	inline bool isMenuOpen = false;

	inline POINTS position = { };

	inline ID3D11Device* device = nullptr;
    inline ID3D11DeviceContext* device_context = nullptr;
    inline IDXGISwapChain* swap_chain = nullptr;
    inline ID3D11RenderTargetView* render_target_view = nullptr;
    inline D3D_FEATURE_LEVEL level;

	void CreateHUIWindow(GameInfo *gameInfo) noexcept;
	void DestroyHUIWindow() noexcept;

	bool CreateUIDevice() noexcept;
	void ResetUIDevice() noexcept;
	void DestroyUIDevice() noexcept;

	void CreateUIImGui() noexcept;
	void DestroyUIImGui() noexcept;

	void BeginRenderUI() noexcept;
	void EndRenderUI() noexcept;
	void RenderUI(Aimbot *aimbot, ESP *esp, Server *server, Moves *moves, Spinbot *spinbot) noexcept;

	void SetMenuOpen() noexcept;
	void SetMenuClose() noexcept;
}
