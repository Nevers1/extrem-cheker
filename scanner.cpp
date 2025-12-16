#include <windows.h>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

namespace fs = std::filesystem;

/* ===== КЛЮЧЕВЫЕ СЛОВА (В КОДЕ) ===== */
std::vector<std::string> keywords = {
    "aimbot","freecam","elytra_swap","smart_moving","hitbox","flauncher",
    "doomsday","viaversion","viamcp","dauntiblyat","bariton","x-ray","xray",
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
    "rename_me_please","editme","crackthisshit.dll","baritone"
};

std::string lower(std::string s){
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c){ return std::tolower(c); });
    return s;
}

bool containsKeyword(const fs::path& p){
    std::ifstream f(p, std::ios::binary);
    if(!f) return false;

    std::string data(
        (std::istreambuf_iterator<char>(f)),
        std::istreambuf_iterator<char>()
    );

    data = lower(data);
    for(const auto& k : keywords)
        if(data.find(k) != std::string::npos)
            return true;

    return false;
}

int main(){
    char cwd[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, cwd);
    std::ofstream out(std::string(cwd) + "\\result.txt", std::ios::out);

    DWORD drives = GetLogicalDrives();
    for(char d='A'; d<='Z'; d++){
        if(!(drives & (1 << (d - 'A')))) continue;
        std::string root = std::string(1, d) + ":\\";

        try {
            for(auto& e : fs::recursive_directory_iterator(
                root, fs::directory_options::skip_permission_denied)) {

                if(!e.is_regular_file()) continue;

                auto ext = lower(e.path().extension().string());
                if(ext != ".exe" && ext != ".pf") continue;

                if(containsKeyword(e.path())) {
                    out << e.path().string() << "\n";
                }
            }
        } catch(...) {}
    }

    out.close();
    return 0;
}

