#include "infection.h"

#define MessageNum 4
#define KanjiNum 4

const float pos_x = 20.0; // 20.0
const float pos_y = 20.0; // 20.0 + 20 * i
const char received_message[] = "#VReceived#W ";

// BGR format in range 0-128
const uint custom_colors[] = {
    0x000077, // red
    0x408000, // green
    0x697d7d, // yellow
    0x764a32, // blue
    0x770077, // magenta
    0x777700, // cyan
    0x744636, // slateblue
    0x784c58, // plum
    0x39407d, // salmon
    0x003c80, // orange
};

ccKanji* kanjiList[KanjiNum];

// Helper functions
inline void ccSprite_SetPos(ccSprite *this, int x, int y) {
    this->pos_x = x;
    this->pos_y = y;
}

inline void ccSprite_SetAlpha(ccSprite *this, uint alpha) {
    this->color1 = (ulong)this->color1 | ((ulong)alpha << 0x20);
}

inline void ccSprite_SetColor(ccSprite *this, ulong color) {
    this->color0 = (color & 0xff) | ((color & 0xff00) << 0x18);
    this->color1 = (this->color1 & 0xffffffff00000000) | ((color & 0xff0000) >> 0x10);
}

inline void ccSprite_SetColorFromPreset(ccSprite *this, int colorIndex) {
    ccSprite_SetColor(this, ccSpriteColorTable[colorIndex]);
}


void orig_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) {
    asm volatile("addiu $sp, $sp, -0x40\n"
                 "sd $ra, 0x30($sp)\n"
                 "j 0x0051cc08\n"
                 "nop");
}

void h_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) {
    for (int i = 0; i < KanjiNum; i++) {
        ccKanji___dt(kanjiList[i], 1);
    }
    
    orig_ccMenuCtrl___dt(menuCtrl, param_1);
}

#define COLOR_CODE(preset_color) COLOR_CODE_(preset_color)

#define COLOR_CODE_(preset_color) \
    asm volatile("lui       $at, 0x30\n"  \
                 "ld         $a1, -0x4BD0 + 8*" #preset_color "($at)\n" \
                 "andi       $a0, $a1, 0xff\n" \
                 "andi       $v1, $a1, 0xff00\n" \
                 "dsll       $v1, $v1, 0x18\n" \
                 "or         $v1, $a0, $v1\n" \
                 "sd         $v1, 0x68($s1)\n" \
                 "ld         $a0, 0x70($s1)\n" \
                 "li         $v1, -0x1\n" \
                 "dsll32     $v1, $v1, 0x0\n" \
                 "and        $a0, $a0, $v1\n" \
                 "lui        $v1, 0xff\n" \
                 "and        $v1, $a1, $v1\n" \
                 "dsrl       $v1, $v1, 0x10\n" \
                 "or         $v1, $a0, $v1\n" \
                 "sd         $v1, 0x70($s1)\n" \
                 "j          0x0015ed38\n");

#define COLOR_CASE(case, function) \
                 "li $v1, " #case "\n" \
                 "beq $a0, $v1, (" #function ")\n"


void ccKanji_Disp_ColorCodes_White() {
    COLOR_CODE(PRESET_WHITE)
}

void h_ccKanji_Disp_ColorCodes() {
    asm volatile(COLOR_CASE(0x56, ccKanji_Disp_ColorCodes_White) // 0x56 = "V" ("W" is already taken)
                 "j 0x0015ed38\n");
}

void hook_ccKanji_Disp_ColorCodes() {
    asm volatile("j (h_ccKanji_Disp_ColorCodes)\n");
}

void hook_ccMenuCtrl___dt() {
    asm volatile("j (h_ccMenuCtrl___dt)\n"
                 "nop");
}

int entry(ccMenuCtrl* menuCtrl) {

    if (archipelagoData.messages[0].status == (char)0x83) {
        // Initialize
        for (int i = 0; i < MessageNum; i++) {
            archipelagoData.messages[i].time = 0;
            archipelagoData.messages[i].queue_pos = 0;
            archipelagoData.messages[i].text[0] = 0;
            archipelagoData.messages[i].status = 0;
        }
        
        // Kanji
        for (int i = 0; i < KanjiNum; i++) {
            kanjiList[i] = ccInitKanji(0xC, 2);
            kanjiList[i]->sprite.layer = menuCtrl->layer;
        }

        // Setup destructor hook
        byte* dst = (byte*)ccMenuCtrl___dt;
        byte* src = (byte*)hook_ccMenuCtrl___dt;
        for (int i = 0; i < 8; i++) {
            dst[i] = src[i];
        }
        
        // Setup colorcode hook
        *(int*)0x0015ec00 = *(int*)hook_ccKanji_Disp_ColorCodes;
    }

    for (int i = 0; i < MessageNum; i++) {
        if (archipelagoData.messages[i].status == 1) {
            char max = 0;
            for (int j = 0; j < MessageNum; j++) {
                if (archipelagoData.messages[j].queue_pos > max) {
                    max = archipelagoData.messages[j].queue_pos;
                }
            }
            archipelagoData.messages[i].queue_pos = max+1;
            archipelagoData.messages[i].status = 2;
        } else if (archipelagoData.messages[i].status == 2) {
            if (archipelagoData.messages[i].time <= 0) {
                for (int j = 0; j < MessageNum; j++) {
                    if (archipelagoData.messages[j].queue_pos > archipelagoData.messages[i].queue_pos) {
                        archipelagoData.messages[j].queue_pos--;
                    }
                }
                archipelagoData.messages[i].queue_pos = 0;
                archipelagoData.messages[i].status = 0;
            } else {
                archipelagoData.messages[i].time--;
            }
        }
    }

    int nextKanji = 0;
    for (int i = 0; i < MessageNum; i++) {
        if (archipelagoData.messages[i].status != 2) continue;
        if (nextKanji >= KanjiNum) break;
        ccKanji* kanji = kanjiList[nextKanji++];

        ccSprite_SetPos(&kanji->sprite, pos_x + 10.0f, pos_y * (archipelagoData.messages[i].queue_pos + 1) - 5.0f);
        ccSprite_SetAlpha(&kanji->sprite, menuCtrl->field58_0x3c);
        if (archipelagoData.messages[i].color < 24) {
            ccSprite_SetColorFromPreset(&kanji->sprite, archipelagoData.messages[i].color);
        } else {
            ccSprite_SetColor(&kanji->sprite, custom_colors[archipelagoData.messages[i].color-24]);
        }

        char final_string[200];
        final_string[0] = 0;
        if (archipelagoData.messages[i].type == 1) {
            strcat(final_string, received_message);
        }
        strcat(final_string, archipelagoData.messages[i].text);

        ccKanji_Disp(kanji, final_string, -1, 1.0f, 1.0f);
        //ccKanji_Extract(kanji, final_string);
        //ccKanji_SetClm(kanji, 0x10, 0, 0, 1);
        //ccSprite_MakePacket(kanji.sprite, 0, 1);
        //ccSprite_SendPacket(kanji.sprite);
    }
    
    byte bVar12 = ccCheckTarget(cmndTarget);
    return bVar12;
}