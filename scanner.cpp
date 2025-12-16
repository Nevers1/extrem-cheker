#include <windows.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;


std::vector<std::string> keywords = {
    "aimbot","freecam","elytra_swap","smart_moving","hitbox","flauncher",
    "doomsday","viaversion","viamcp","dauntiblyat","bariton","xray","x-ray",
    "spambot","spam_bot","inventory_walk","player_highlighter",
    "bedrock_breaker_mode","double_hotbar","armor_hotswap","chest_locater",
    "savesearcher","tweakeroo","mob_hitbox","librarian_trade_finder",
    "wise_folder_hider","jopapopa","r3d","cheat","nathox","inertia","akrien",
    "nova","kilo","squad","vape","kyprak","jessica","hcl","zamorozka",
    "nodus","matix","wurst","weepcraft","impact","skillclient","wexside",
    "richfreeloader","neverhook","celestial","deadcode","wolfram",
    "aristois","flux","jigsaw","liquidbounce","sigma","wintware",
    "celestal","yammi","ecelon","kamiblue","meteor","ares","zeusclient",
    "nursultan","konas","vaneclient","shitclient","reach","trash",
    "rename_me_please","editme","crackthisshit","baritone"
};

std::string lower(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return s;
}

bool matchByName(const fs::path& p) {
    std::string name = lower(p.stem().string()); 
    for (const auto& k : keywords) {
        if (name.rfind(k, 0) == 0)  
            return true;
    }
    return false;
}

int main() {
    char cwd[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, cwd);
    std::ofstream out(std::string(cwd) + "\\result.txt", std::ios::out);

    DWORD drives = GetLogicalDrives();
    for (char d = 'A'; d <= 'Z'; d++) {
        if (!(drives & (1 << (d - 'A')))) continue;
        std::string root = std::string(1, d) + ":\\";

        try {
            for (auto& e : fs::recursive_directory_iterator(
                root, fs::directory_options::skip_permission_denied)) {

                if (!e.is_regular_file()) continue;

                std::string ext = lower(e.path().extension().string());
                if (ext != ".exe" && ext != ".pf") continue;

                if (matchByName(e.path())) {
                    out << e.path().string() << "\n";
                }
            }
        } catch (...) {}
    }

    out.close();
    return 0;
}
