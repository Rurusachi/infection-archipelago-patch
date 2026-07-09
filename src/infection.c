#include "infection.h"

const float pos_x = 20.0; // 20.0
const float pos_y = 20.0; // 20.0 + 20 * i

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


int entry(ccMenuCtrl* menuCtrl) {

    if (archipelagoData.messages[0].status == (char)0x83) {
        // Initialize
        for (int i = 0; i < 4; i++) {
            archipelagoData.messages[i].time = 0;
            archipelagoData.messages[i].queue_pos = 0;
            archipelagoData.messages[i].text[0] = 0;
            archipelagoData.messages[i].status = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (archipelagoData.messages[i].status == 1) {
            char max = 0;
            for (int j = 0; j < 4; j++) {
                if (archipelagoData.messages[j].queue_pos > max) {
                    max = archipelagoData.messages[j].queue_pos;
                }
            }
            archipelagoData.messages[i].queue_pos = max+1;
            archipelagoData.messages[i].status = 2;
        } else if (archipelagoData.messages[i].status == 2) {
            if (archipelagoData.messages[i].time <= 0) {
                for (int j = 0; j < 4; j++) {
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

    ulong tempFontColor0 = font->sprite.color0;
    ulong tempFontColor1 = font->sprite.color1;
    ccSprite_SetAlpha(&font->sprite, menuCtrl->field58_0x3c);
    for (int i = 0; i < 4; i++) {
        if (archipelagoData.messages[i].status != 2) continue;

        float x = pos_x + 10.0f;
        float y = pos_y * (archipelagoData.messages[i].queue_pos + 1) - 5.0f;
        
        // Draw drop shadow first
        ccSprite_SetColor(&font->sprite, 0x80000000);
        ccFont_SetType(font, 0);
        font->sprite.pos_x = x - 2.0f;
        font->sprite.pos_y = y + 2.0f;
        ccSprite_MakePacketStr(&font->sprite, archipelagoData.messages[i].text, 0);

        ccSprite_SetColorFromPreset(&font->sprite, 22); // TODO: Pick better color. (Possibly attempt drop shadow and set color from client instead)
        ccFont_SetType(font, 0);
        font->sprite.pos_x = x;
        font->sprite.pos_y = y;
        ccSprite_MakePacketStr(&font->sprite, archipelagoData.messages[i].text, 0);
    }
    font->sprite.color0 = tempFontColor0;
    font->sprite.color1 = tempFontColor1;
    
    byte bVar12 = ccCheckTarget(cmndTarget);
    return bVar12;
}