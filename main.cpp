#include "src/aimbot.h"
#include "src/server.h"
#include "src/signature.hpp"
#include "src/ui.h"
#include "src/esp.h"
#include "src/moves.h"
#include "src/game_info.hpp"
#include "src/spinbot.h"

#include <thread>
#include <chrono>

int main(int, char**){

    const std::string DDPERClient = "DDPER Client";
    const std::string DDNetClient = "DDNet Client";

    int client = GameInfo::WhichIsRunning(DDPERClient.c_str(), DDNetClient.c_str());

    GameInfo gameInfo;
    gameInfo.Initialize(
                        client == GameInfo::DDPER ? DDPERClient.c_str() : DDNetClient.c_str(), 
                        client == GameInfo::DDPER ? "DDPER.exe" : "DDNet.exe"
                       );

    if(client == GameInfo::NONE){
        std::cout << ("No client is not running!") << std::endl;
        return 0;
    }

    offsets::Initialize(client);

    std::cout << ("DPerX by kio opened successfully!") << std::endl;
    std::cout << ("Open mod menu: F6") << std::endl;
    std::cout << ("Close mod menu: F7") << std::endl;
    
    ui::CreateHUIWindow(&gameInfo);
    ui::CreateUIDevice();
    ui::CreateUIImGui();

    const auto& players_address = gameInfo.memory->Read<uintptr_t>(gameInfo.baseAddress + offsets::static_server);
    const auto& localPlayer_address = gameInfo.memory->Read<uintptr_t>(gameInfo.baseAddress + offsets::static_localplayer);

    Server server(players_address, localPlayer_address, gameInfo.memory);
    Aimbot aimbot(localPlayer_address, gameInfo.memory);
    Moves moves(localPlayer_address, gameInfo.memory);
    Spinbot spinbot(localPlayer_address, gameInfo.memory);
    ESP esp = ESP();

    while(ui::isRunning){

        ui::BeginRenderUI();
        ui::RenderUI(&aimbot, &esp, &server, &moves, &spinbot);
        ui::EndRenderUI();

        if(GetAsyncKeyState(VK_F6)){
            ui::isMenuOpen = true;
            ui::SetMenuOpen();
        }else if(GetAsyncKeyState(VK_F7)){
            ui::isMenuOpen = false;
            ui::SetMenuClose();
        }

        if(!gameInfo.isRunning()){ esp.enabled = false; continue; }

        server.UpdateServerData();

        if(aimbot.global_fov_enabled || (aimbot.silent_enabled && aimbot.CheckHotkeys()) || aimbot.focused_fov_enabled){           
            Player player =  aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            if(aimbot.global_fov_enabled) 
                player = aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            else if(aimbot.focused_fov_enabled)
                player =  aimbot.GetNearestInSector(static_cast<float>(aimbot.fov_angle), aimbot.fov_distance, &server, aimbot.avoid_freezed_tee);
            if (Server::GetValidPlayer(player) && player.id != Server::localPlayer.id && (player.id > 0 || player.id < Server::MAX_PLAYERS))
                aimbot.AimTarget(player.position, &Server::localPlayer);
        
        }

        if(moves.CheckHotkeys() || moves.enabled){
            Player player = aimbot.GetNearestToPlayer(static_cast<float>(aimbot.fov_distance), &server, aimbot.avoid_freezed_tee);
            moves.Stabilize(player);
        }else if(moves.needReset){
            moves.ResetWalk();
        }
    
        if(spinbot.CheckHotkeys() || spinbot.enabled){
            spinbot.Rotate();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(5));

    }

    ui::DestroyUIImGui();
    ui::DestroyUIDevice();
    ui::DestroyHUIWindow();

    return 0;
}
