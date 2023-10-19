#include <filesystem>
#include <iostream>
#include <string>
#include <windows.h>
#include <shlobj.h>

class Spoofer {
    public:
        static void SpoofDDnetFolders(bool backup);
        static void CheckDDNetFolders(std::wstring desktopDir, bool backup);
        static void CheckTeeworldsFolders(std::wstring desktopDir, bool backup);
};