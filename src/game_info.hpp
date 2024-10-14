#pragma once

#include "memory.h"
#include "offsets.hpp"
#include <string>

class GameInfo{
    public:
    
        enum {
            DDPER,
            DDNET,
            NONE
        };

        std::string pName;
        LPCSTR windowName;
        float windowWidth;
        float windowHeight;
        float windowX;
        float windowY;

        float viewportWidth;
        float viewportHeight;
        float viewportX;
        float viewportY;
        Memory *memory;
        uintptr_t baseAddress;

        void Initialize(LPCSTR windowName, std::string pName){
            this->pName = pName;
            this->windowName = windowName;
            
            this->memory = new Memory(pName.c_str());
            this->baseAddress = memory->GetModuleAddress(pName.c_str());
            GetGameInfo();
        }

        void GetGameInfo(){

            if(isRunning()){
                hwnd = FindWindow(NULL, windowName);

                RECT rect;
                GetWindowRect(hwnd, &rect);

                windowWidth = static_cast<float>(rect.right - rect.left);
                windowHeight = static_cast<float>(rect.bottom - rect.top); 
                windowX = static_cast<float>(rect.left); 
                windowY = static_cast<float>(rect.top);

                viewportWidth = windowWidth - 14;
                viewportHeight = windowHeight - 37;
                viewportX = windowX + 8;
                viewportY = windowY + 31;

            }

        }

        bool isFocused() {
            return GetForegroundWindow() == hwnd;
        }

        static int WhichIsRunning(LPCTSTR ddper, LPCTSTR ddnet)
        {
            HWND window1 = FindWindow(NULL, ddper);
            if (window1 != 0) { 
                return GameInfo::DDPER;
            } 

            HWND window2 = FindWindow(NULL, ddnet);
            if (window2 != 0) { 
                return GameInfo::DDNET;
            } 

            return GameInfo::NONE;
        }

        bool isRunning()
        {
            hwnd = FindWindow(NULL, windowName);
            if (hwnd != 0) { 
                return true;
            } else { 
                return false;
            } 
        }

        void CloseGame()
        {
            hwnd = FindWindow(NULL, windowName);
            if (hwnd != 0) { 
                PostMessage(hwnd, WM_CLOSE, 0, 0);
            } 
        }
    private:
        HWND hwnd;
        
};