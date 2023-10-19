#include "spoofer.h"

void Spoofer::SpoofDDnetFolders(bool backup) {

    WCHAR desktopPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, desktopPath))) {
        std::wstring desktopDir(desktopPath);

        if (!std::filesystem::exists(desktopDir + L"\\BackupDDNetFiles") && backup)
            std::filesystem::create_directory(desktopDir + L"\\BackupDDNetFiles");

        std::cout << ("Spoofing loading...") << std::endl;

        Spoofer::CheckDDNetFolders(desktopDir, backup);
        std::cout << ("Spoofing DDNet folder done!") << std::endl;

        Spoofer::CheckTeeworldsFolders(desktopDir, backup);
        std::cout << ("Spoofing Teeworlds folder done!") << std::endl;

        std::cout << ("Spoofed!") << std::endl;

    } else {
        std::cerr << ("Unable to obtain the path to the user's Desktop folder.") << std::endl;
    }
}

void Spoofer::CheckDDNetFolders(std::wstring desktopDir, bool backup){

    auto pathDDNet = std::filesystem::temp_directory_path().parent_path().parent_path().parent_path() / "Roaming\\DDNet";

    if (!std::filesystem::exists(pathDDNet)) { 
        std::cout << ("DDNet folder not found!") << std::endl;
        return;
    }

    if(backup){
        std::filesystem::copy(pathDDNet, desktopDir + L"\\BackupDDNetFiles/DDNet", std::filesystem::copy_options::recursive);
    }

    std::cout << ("Operation completed successfully (DDNet backup)!") << std::endl;

    std::filesystem::remove_all(pathDDNet);
}

void Spoofer::CheckTeeworldsFolders(std::wstring desktopDir, bool backup){

    auto pathTeeworlds = std::filesystem::temp_directory_path().parent_path().parent_path().parent_path() / "Roaming\\Teeworlds";

    if (!std::filesystem::exists(pathTeeworlds)) { 
        std::cout << ("Teeworlds folder not found!") << std::endl;
        return;
    }

    if(backup){
        std::filesystem::copy(pathTeeworlds, desktopDir + L"\\BackupDDNetFiles/Teeworlds", std::filesystem::copy_options::recursive);
    }

    std::cout << ("Operation completed successfully (Teeworlds backup)!") << std::endl;

    std::filesystem::remove_all(pathTeeworlds);
}