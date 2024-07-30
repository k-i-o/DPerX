#include "src/aimbot.h"
#include "src/server.h"
#include "src/moves.h"
#include "src/game_info.hpp"
#include "src/spinbot.h"
#include "src/offsets.hpp"

#include <thread>
#include <chrono>
#include <iostream>
#include <atlstr.h> 

int main(int, char**) {

    const LPCTSTR DDPERClient = _T("DDPER Client");
    const LPCTSTR DDNetClient = _T("DDNet Client");

    int client = GameInfo::WhichIsRunning(DDPERClient, DDNetClient);

    GameInfo gameInfo;
    gameInfo.Initialize(
        client == GameInfo::DDPER ? DDPERClient : DDNetClient,
        client == GameInfo::DDPER ? "DDPER.exe" : "DDNet.exe");

    if (client == GameInfo::NONE) {
        std::cout << ("No client is not running!") << std::endl;
        return 0;
    }

    variables::Offsets::Initialize(client);

    std::cout << "DPerX 2024 by kiocode opened successfully!" << std::endl;
    std::cout << (GameInfo::DDPER ? "DDPER" : "DDNet") << " is running!" << std::endl;
    std::cout << "Open mod menu: F6" << std::endl;
    std::cout << "Close mod menu: F7" << std::endl;

    const auto& players_address = gameInfo.memory->Read<uintptr_t>(gameInfo.baseAddress + variables::Offsets::static_server);
    const auto& localPlayer_address = gameInfo.memory->Read<uintptr_t>(gameInfo.baseAddress + variables::Offsets::static_localplayer);

    Server server(players_address, localPlayer_address, gameInfo.memory);
    Aimbot aimbot(localPlayer_address, gameInfo.memory);
    Moves moves(localPlayer_address, gameInfo.memory);
    Spinbot spinbot(localPlayer_address, gameInfo.memory);

    aimbot.silent_enabled = true;
    aimbot.hotkeys = { VK_MENU };

    while (gameInfo.isRunning()) {

        server.UpdateServerData();

        if (aimbot.global_fov_enabled || (aimbot.silent_enabled && aimbot.CheckHotkeys()) || aimbot.focused_fov_enabled) {
            Player player = aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            if (aimbot.global_fov_enabled)
                player = aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            else if (aimbot.focused_fov_enabled)
                player = aimbot.GetNearestInSector(static_cast<float>(aimbot.fov_angle), aimbot.fov_distance, &server, aimbot.avoid_freezed_tee);
            if (Server::GetValidPlayer(player) && player.id != Server::localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS))
                aimbot.AimTarget(player.position, &Server::localPlayer);

        }

        if (moves.CheckHotkeys() || moves.enabled) {
            Player player = aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            moves.Stabilize(player);
        }
        else if (moves.needReset) {
            moves.ResetWalk();
        }

        if (spinbot.CheckHotkeys() || spinbot.enabled) {
            spinbot.Rotate();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

    }

    return 0;
}
