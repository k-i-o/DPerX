#pragma once

#include "memory.h"

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

class Cheat {  
    public:
        Cheat(const uintptr_t memory_address, const Memory *memory) : memory_address(memory_address), memory(memory){}
        
        Cheat(){}

        uintptr_t memory_address;
        const Memory *memory;

        std::vector<int> hotkeys = { };

        bool CheckHotkeys(){
            if(!hotkeys.size()) return false;

            for(int i = 0; i < hotkeys.size(); i++){
                if(!GetAsyncKeyState(hotkeys[i])){
                    return false;
                }
            }
            return true;
        }

        static std::string GetHotkeysText(std::vector<int> hotkeys){
                
            std::unordered_map<int, std::string> specialKeys = {
                {VK_CONTROL, "Ctrl"},
                {VK_MENU, "Alt"},
                {VK_SHIFT, "Shift"},
                {VK_CAPITAL, "Caps Lock"},
                {VK_TAB, "Tab"},
                {VK_RETURN, "Enter"},
                {VK_SPACE, "Space"},
                {VK_OEM_PERIOD, "."},
                {VK_OEM_COMMA, ","},
                {VK_DELETE, "Delete"},
                {VK_OEM_5, "\\"}, // Backslash
                {VK_LWIN, "Left Windows"},
                {VK_RWIN, "Right Windows"},
                {VK_LEFT, "Left Arrow"},
                {VK_UP, "Up Arrow"},
                {VK_RIGHT, "Right Arrow"},
                {VK_DOWN, "Down Arrow"},
                {VK_PRIOR, "Page Up"},
                {VK_NEXT, "Page Down"},
                {VK_OEM_2, "/"}, // Slash
                {VK_BACK, "Backspace"}, // Backspace
            };

            std::string pressedKeysString = "";

            for (int key : hotkeys) {
                if (specialKeys.find(key) != specialKeys.end()) {
                    pressedKeysString.append(" ").append(specialKeys[key]);
                }
                else if (key >= VK_F1 && key <= VK_F24) {
                    pressedKeysString.append(" F").append(std::to_string(key - VK_F1 + 1));
                }
                else if (key >= 32 && key <= 126) {
                    pressedKeysString.append(" ").append(1, static_cast<char>(key));
                }
            }

            return pressedKeysString;
        }
};