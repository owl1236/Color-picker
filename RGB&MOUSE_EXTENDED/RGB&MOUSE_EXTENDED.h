#pragma once

#include "resource.h"
#include<Windows.h>
#include <vector>
#include <string>
#include <cmath>
#include <tuple>

extern std::vector<unsigned int> PRGB;
extern DWORD dw;
extern POINT cursor;
extern bool paused;
extern std::vector<unsigned int> frozenPRGB;
inline std::vector<unsigned int> RGB_POS(HWND hwnd,HDC hdc)
{
    std::vector<unsigned int> prgb;
    BYTE R, G, B;

    if (GetCursorPos(&cursor)) 
    {
        COLORREF color = GetPixel(hdc, cursor.x, cursor.y);
        R = GetRValue(color);
        G = GetGValue(color);
        B = GetBValue(color);
        dw = MAKEWORD(cursor.x, cursor.y);
        unsigned int X = cursor.x;
        unsigned int Y = cursor.y;
        unsigned int r = (unsigned int)R;
        unsigned int g = (unsigned int)G;
        unsigned int b = (unsigned int)B;
        prgb.push_back(X);
        prgb.push_back(Y);
        prgb.push_back(r);
        prgb.push_back(g);
        prgb.push_back(b);
    }
    else { MessageBoxA(hwnd,"Error","Couldn't get a cursor info.", MB_OK); }

    return prgb;
}
inline std::string ColorName();

inline void DrawSampleInfo(HWND hwnd, HDC hdc)
{
    
    
    static SHORT lastF6 = 0;
    SHORT curF6 = GetAsyncKeyState(VK_F6);
    if ((curF6 & 0x8000) && !(lastF6 & 0x8000)) {
        
        paused = !paused;
        if (paused) {
            
            HDC hdcScreen = GetDC(HWND_DESKTOP);
            frozenPRGB = RGB_POS(hwnd, hdcScreen);
            ReleaseDC(HWND_DESKTOP, hdcScreen);
        } else {
            frozenPRGB.clear();
        }
        
        InvalidateRect(hwnd, NULL, TRUE);
    }
    lastF6 = curF6;

    
    if (hdc == NULL) return;

    
    COLORREF fillColor = RGB(255, 255, 255);
    const std::vector<unsigned int> *useVec = &PRGB;
    if (paused && frozenPRGB.size() >= 5) useVec = &frozenPRGB;
    if (useVec->size() >= 5) {
        unsigned int r = (*useVec)[2];
        unsigned int g = (*useVec)[3];
        unsigned int b = (*useVec)[4];
        fillColor = RGB(r, g, b);
    }

    HBRUSH hBrush = CreateSolidBrush(fillColor);
    RECT rect = { 280, 30, 420, 180 };
    FillRect(hdc, &rect, hBrush);
    DeleteObject(hBrush);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(220,220,220));

    int tx = 20;
    int ty = 30;
    char buf[64];
    unsigned int xv = 0, yv = 0, rv = 0, gv = 0, bv = 0;
    if (useVec->size() >= 5) {
        xv = (*useVec)[0];
        yv = (*useVec)[1];
        rv = (*useVec)[2];
        gv = (*useVec)[3];
        bv = (*useVec)[4];
    }

    wsprintfA(buf, "X: %u", xv);
    TextOutA(hdc, tx, ty, buf, lstrlenA(buf));

    
    std::string hint = "Press F6 to toggle pause. ";
    hint += (paused ? "PAUSED" : "RUNNING");
    SetTextColor(hdc, RGB(220,220,220));
    TextOutA(hdc, 20, 200, hint.c_str(), (int)hint.size());
    SetTextColor(hdc, RGB(220,220,220));
    ty += 20;
    wsprintfA(buf, "Y: %u", yv);
    TextOutA(hdc, tx, ty, buf, lstrlenA(buf));
    ty += 20;
    wsprintfA(buf, "R: %u", rv);
    TextOutA(hdc, tx, ty, buf, lstrlenA(buf));
    ty += 20;
    wsprintfA(buf, "G: %u", gv);
    TextOutA(hdc, tx, ty, buf, lstrlenA(buf));
    ty += 20;
    wsprintfA(buf, "B: %u", bv);
    TextOutA(hdc, tx, ty, buf, lstrlenA(buf));
    
    ty += 20;
    std::string cname = ColorName();
    if (!cname.empty()) {
        SetTextColor(hdc, RGB(220,220,220));
        TextOutA(hdc, tx, ty, cname.c_str(), (int)cname.size());
    }
}

inline std::string ColorName()
{
    
    static const std::vector<std::pair<std::string, std::tuple<int, int, int>>> colors = {
        { "Black", {0, 0, 0} },
        { "Cyan (process)", {0, 183, 235} },
        { "Deep sky blue", {0, 191, 255} },
        { "Caribbean green", {0, 204, 153} },
        { "Dark turquoise", {0, 206, 209} },
        { "Blue", {0, 0, 255} },
        { "Erin", {0, 255, 64} },
        { "Aqua", {0, 255, 255} },
        { "Dark jungle green", {26, 36, 33} },
        { "Eerie black", {27, 27, 27} },
        { "Cerulean (Crayola)", {29, 172, 214} },
        { "Dodger blue", {30, 144, 255} },
        { "Blue (Crayola)", {31, 117, 254} },
        { "Cerulean blue", {42, 82, 190} },
        { "Cosmic cobalt", {46, 45, 136} },
        { "B'dazzled blue", {46, 88, 148} },
        { "Dark slate gray", {47, 79, 79} },
        { "Black olive", {59, 60, 54} },
        { "Amazon", {59, 122, 87} },
        { "Bluetiful", {60, 105, 231} },
        { "Dark sienna", {60, 20, 20} },
        { "Black bean", {61, 12, 2} },
        { "Bistre", {61, 43, 31} },
        { "Android green", {61, 220, 132} },
        { "Drab dark brown", {74, 65, 42} },
        { "Deep Space Sparkle", {74, 100, 108} },
        { "Artichoke green", {75, 111, 68} },
        { "Deep jungle green", {0, 75, 73} },
        { "Café noir", {75, 54, 33} },
        { "Fern green", {79, 121, 66} },
        { "Dark byzantium", {93, 57, 84} },
        { "Blue jeans", {93, 173, 236} },
        { "Cadet blue", {95, 158, 160} },
        { "Cadmium green", {0, 107, 60} },
        { "Field drab", {108, 84, 30} },
        { "Eminence", {108, 48, 130} },
        { "Cerulean frost", {109, 155, 195} },
        { "Coffee", {111, 78, 55} },
        { "Chocolate (traditional)", {123, 63, 0} },
        { "Cerulean", {0, 123, 167} },
        { "Bud green", {123, 182, 97} },
        { "Barn red", {124, 10, 2} },
        { "Aero", {124, 185, 232} },
        { "Deep taupe", {126, 94, 96} },
        { "Claret", {127, 23, 52} },
        { "Azure", {0, 127, 255} },
        { "Aquamarine", {127, 255, 212} },
        { "Blue-violet", {138, 43, 226} },
        { "Burnt umber", {138, 51, 36} },
        { "Dark red", {139, 0, 0} },
        { "Dark cyan", {0, 139, 139} },
        { "Dark magenta", {139, 0, 139} },
        { "Cool grey", {140, 146, 172} },
        { "Dark sky blue", {140, 206, 214} },
        { "Electric violet", {143, 0, 255} },
        { "Dark sea green", {143, 188, 143} },
        { "Duke blue", {0, 0, 156} },
        { "Big dip o'ruby", {156, 37, 66} },
        { "Crimson (UA)", {158, 27, 50} },
        { "French lime", {158, 253, 56} },
        { "Amaranth deep purple", {159, 43, 104} },
        { "Beaver", {159, 129, 112} },
        { "Citron", {159, 169, 31} },
        { "Blue (Pantone)", {0, 24, 168} },
        { "Cerulean (RGB)", {0, 64, 255} },
        { "Absolute Zero", {0, 72, 186} },
        { "Emerald", {80, 200, 120} },
        { "Carolina blue", {86, 160, 211} },
        { "Air superiority blue", {114, 160, 193} },
        { "French blue", {0, 114, 187} },
        { "French sky blue", {119, 181, 254} },
        { "Chartreuse (web)", {128, 255, 0} },
        { "Blue (NCS)", {0, 135, 189} },
        { "Baby blue", {137, 207, 240} },
        { "Cadet grey", {145, 163, 176} },
        { "Blue (Munsell)", {0, 147, 175} },
        { "Eton blue", {150, 200, 162} },
        { "Forest green (web)", {34, 139, 34} },
        { "Bleu de France", {49, 140, 231} },
        { "Dark lava", {72, 60, 50} },
        { "Dark slate blue", {72, 61, 139} },
        { "Dark liver (horses)", {84, 61, 55} },
        { "Ebony", {85, 93, 80} },
        { "Dark olive green", {85, 107, 47} },
        { "English violet", {86, 60, 92} },
        { "Antique bronze", {102, 93, 30} },
        { "Antique ruby", {132, 27, 45} },
        { "French bistre", {133, 109, 77} },
        { "Cordovan", {137, 63, 69} },
        { "Antique fuchsia", {145, 92, 131} },
        { "Brown", {150, 75, 0} },
        { "Denim", {21, 96, 189} },
        { "Denim blue", {34, 67, 182} },
        { "British racing green", {0, 66, 37} },
        { "Blue yonder", {80, 114, 167} },
        { "Dark green (X11)", {0, 100, 0} },
        { "Cornflower blue", {100, 149, 237} },
        { "Blue-gray (Crayola)", {102, 153, 204} },
        { "French violet", {136, 6, 206} },
        { "Dark violet", {148, 0, 211} },
        { "Dark orchid", {153, 50, 204} },
        { "Amethyst", {153, 102, 204} },
        { "Charcoal", {54, 69, 79} },
        { "Black coral", {84, 98, 111} },
        { "Cyber grape", {88, 66, 124} },
        { "Bole", {121, 68, 59} },
        { "Coyote brown", {129, 97, 60} },
        { "French lilac", {134, 96, 142} },
        { "Fuzzy Wuzzy", {135, 66, 31} },
        { "Cinereous", {152, 129, 123} },
        { "Blue sapphire", {18, 97, 128} },
        { "Dark spring green", {23, 114, 69} },
        { "Dark purple", {48, 25, 52} },
        { "Blue (pigment)", {51, 51, 153} },
        { "Dark electric blue", {83, 104, 120} },
        { "Davy's grey", {85, 85, 85} },
        { "Eggplant", {97, 64, 81} },
        { "Dark brown", {101, 67, 33} },
        { "Blood red", {102, 0, 0} },
        { "Finn", {104, 48, 104} },
        { "Dim gray", {105, 105, 105} },
        { "Byzantium", {112, 41, 99} },
        { "Catawba", {112, 54, 66} },
        { "Burgundy", {128, 0, 32} },
        { "Falu red", {128, 24, 24} },
        { "Battleship grey", {132, 132, 130} },
        { "Chinese violet", {133, 96, 136} },
        { "Chestnut", {149, 69, 53} },
        { "Carmine", {150, 0, 24} },
        { "Bistre brown", {150, 113, 23} },
        { "Copper rose", {153, 102, 102} },
        { "Baby blue eyes", {161, 202, 241} },
        { "Blue bell", {162, 162, 208} },
        { "Cambridge blue", {163, 193, 173} },
        { "Burnished brown", {161, 123, 116} },
        { "Café au lait", {166, 123, 91} },
        { "French beige", {166, 123, 91} },
        { "Flirt", {162, 0, 109} },
        { "Blast-off bronze", {165, 113, 100} },
        { "Chinese red", {170, 56, 30} },
        { "English red", {171, 75, 82} },
        { "Amaranth purple", {171, 39, 79} },
        { "Celadon", {172, 225, 175} },
        { "Blizzard blue", {172, 229, 238} },
        { "Copper penny", {173, 111, 105} },
        { "Brown sugar", {175, 110, 77} },
        { "Acid green", {176, 191, 26} },
        { "Ash gray", {178, 190, 181} },
        { "Celeste", {178, 255, 255} },
        { "Columbia Blue", {185, 217, 235} },
        { "Carnelian", {179, 27, 27} },
        { "Deep chestnut", {185, 78, 72} },
        { "African violet", {178, 132, 190} },
        { "Dark goldenrod", {184, 134, 11} },
        { "Firebrick", {178, 34, 34} },
        { "English lavender", {180, 131, 149} },
        { "Fandango", {181, 51, 137} },
        { "Copper", {184, 115, 51} },
        { "Beau blue", {188, 212, 230} },
        { "Byzantine", {189, 51, 164} },
        { "Dark khaki", {189, 183, 107} },
        { "Electric purple", {191, 0, 255} },
        { "Black Shadows", {191, 175, 178} },
        { "Ecru", {194, 178, 128} },
        { "Camel", {193, 154, 107} },
        { "Desert", {193, 154, 107} },
        { "Fallow", {193, 154, 107} },
        { "Cardinal", {196, 30, 58} },
        { "French raspberry", {199, 44, 72} },
        { "Antique brass", {200, 138, 101} },
        { "Cedar Chest", {201, 90, 73} },
        { "Fuchsia (Crayola)", {193, 84, 193} },
        { "Alloy orange", {196, 98, 16} },
        { "Bitter lemon", {202, 224, 13} },
        { "Copper red", {203, 109, 81} },
        { "Brick red", {203, 65, 84} },
        { "English vermillion", {204, 71, 75} },
        { "Burnt orange", {204, 85, 0} },
        { "Electric lime", {204, 255, 0} },
        { "Bronze", {205, 127, 50} },
        { "Cinnamon Satin", {205, 96, 126} },
        { "Fire engine red", {206, 32, 41} },
        { "Arctic lime", {208, 255, 20} },
        { "French mauve", {212, 115, 212} },
        { "Bright lilac", {216, 145, 239} },
        { "Chocolate (web)", {210, 105, 30} },
        { "Carmine (M&P)", {215, 0, 64} },
        { "Copper (Crayola)", {218, 138, 103} },
        { "Barbie Pink", {218, 24, 132} },
        { "Deep cerise", {218, 50, 135} },
        { "Alizarin", {219, 45, 67} },
        { "Crimson", {220, 20, 60} },
        { "Blush", {222, 93, 131} },
        { "China pink", {222, 111, 161} },
        { "Cerise", {222, 49, 99} },
        { "Fandango pink", {222, 82, 133} },
        { "Burlywood", {222, 184, 135} },
        { "Bone", {227, 218, 201} },
        { "Citrine", {228, 208, 10} },
        { "Fawn", {229, 170, 112} },
        { "Arylide yellow", {233, 214, 107} },
        { "Chili red", {226, 61, 40} },
        { "Charm pink", {230, 143, 172} },
        { "Frostbite", {233, 54, 167} },
        { "Candy pink", {228, 113, 122} },
        { "Dark salmon", {233, 150, 122} },
        { "Flame", {226, 88, 34} },
        { "Cinnabar", {227, 66, 52} },
        { "Fulvous", {228, 132, 0} },
        { "Burnt sienna", {233, 116, 81} },
        { "Cadmium orange", {237, 135, 45} },
        { "Carrot orange", {237, 145, 33} },
        { "Desert sand", {237, 201, 175} },
        { "Almond", {238, 217, 196} },
        { "Flax", {238, 220, 130} },
        { "Cameo pink", {239, 187, 204} },
        { "Dutch white", {239, 223, 187} },
        { "Eggshell", {240, 234, 214} },
        { "Alice blue", {240, 248, 255} },
        { "Azure (X11/web color)", {240, 255, 255} },
        { "Champagne pink", {241, 221, 207} },
        { "Baby pink", {244, 194, 194} },
        { "Beige", {245, 245, 220} },
        { "Cultured Pearl", {245, 245, 245} },
        { "Champagne", {247, 231, 206} },
        { "Amaranth pink", {241, 156, 187} },
        { "Cyclamen", {245, 111, 161} },
        { "Congo pink", {248, 131, 121} },
        { "Coral pink", {248, 131, 121} },
        { "Deep champagne", {250, 214, 165} },
        { "Banana Mania", {250, 231, 181} },
        { "Antique white", {250, 235, 215} },
        { "Apricot", {251, 206, 177} },
        { "Corn", {251, 236, 93} },
        { "French fuchsia", {253, 63, 146} },
        { "French pink", {253, 108, 158} },
        { "Aureolin", {253, 238, 0} },
        { "Dandelion", {254, 232, 93} },
        { "Baby powder", {254, 254, 250} },
        { "Fuchsia", {255, 0, 255} },
        { "Coral", {255, 127, 80} },
        { "Dark orange", {255, 140, 0} },
        { "Baker-Miller pink", {255, 145, 175} },
        { "Deep pink", {255, 20, 147} },
        { "Coquelicot", {255, 56, 0} },
        { "Fiery rose", {255, 84, 112} },
        { "Deep saffron", {255, 153, 51} },
        { "Atomic tangerine", {255, 153, 102} },
        { "Carnation pink", {255, 166, 201} },
        { "Bright yellow (Crayola)", {255, 170, 29} },
        { "Cherry blossom pink", {255, 183, 197} },
        { "Chinese yellow", {255, 178, 0} },
        { "Cotton candy", {255, 188, 217} },
        { "Amber", {255, 191, 0} },
        { "Buff", {255, 198, 128} },
        { "Cyber yellow", {255, 211, 0} },
        { "Bisque", {255, 228, 196} },
        { "Blanched almond", {255, 235, 205} },
        { "Canary yellow", {255, 239, 0} },
        { "Cornsilk", {255, 248, 220} },
        { "Cosmic latte", {255, 248, 231} },
        { "Floral white", {255, 250, 240} },
        { "Cream", {255, 253, 208} },
        { "Canary", {255, 255, 153} },
    };

    
    const std::vector<unsigned int> *useVec = &PRGB;
    if (paused && frozenPRGB.size() >= 5) useVec = &frozenPRGB;

    if (useVec->size() < 5) {
        return "Unknown";
    }

    unsigned int r = (*useVec)[2];
    unsigned int g = (*useVec)[3];
    unsigned int b = (*useVec)[4];

    
    double minDistance = 1e9;
    std::string closestName = "Unknown";

    for (const auto& color : colors) {
        int cr = std::get<0>(color.second);
        int cg = std::get<1>(color.second);
        int cb = std::get<2>(color.second);

        double distance = std::sqrt(
            (r - cr) * (r - cr) +
            (g - cg) * (g - cg) +
            (b - cb) * (b - cb)
        );

        if (distance < minDistance) {
            minDistance = distance;
            closestName = color.first;
        }
    }

    return closestName;
}