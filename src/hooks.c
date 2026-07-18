#include "hooks.h"
#include "infection.h"

// ccMenuCtrl constructor
ccMenuCtrl* orig_ccMenuCtrl___ct(ccMenuCtrl *menuCtrl) {
    asm volatile ("addiu $sp, $sp, -0x60\n"
                  "sd $ra, 0x30($sp)\n"
                  "j (ccMenuCtrl___ct + 8)\n"
                  "nop"
                  :
                  :
                  : "v0", "v1");
}

ccMenuCtrl* h_ccMenuCtrl___ct(ccMenuCtrl *menuCtrl) {
    ccMenuCtrl* result = orig_ccMenuCtrl___ct(menuCtrl);

    for (int i = 0; i < KanjiNum; i++) {
        if (kanjiList[i] == 0) {
            kanjiList[i] = ccInitKanji(0xC, 2);
            kanjiList[i]->sprite.layer = menuCtrl->layer;
        }
    }
    return result;
}

void hook_ccMenuCtrl___ct() {
    asm volatile("j (h_ccMenuCtrl___ct)\n"
                 "nop");
}

// ccMenuCtrl destructor
void orig_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) {
    asm volatile("addiu $sp, $sp, -0x40\n"
                 "sd $ra, 0x30($sp)\n"
                 "j (ccMenuCtrl___dt + 8)\n"
                 "nop");
}

void h_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) {
    for (int i = 0; i < KanjiNum; i++) {
        if (kanjiList[i] != 0) {
            ccKanji___dt(kanjiList[i], 1);
            kanjiList[i] = 0;
        }
    }
    
    orig_ccMenuCtrl___dt(menuCtrl, param_1);
}

void hook_ccMenuCtrl___dt() {
    asm volatile("j (h_ccMenuCtrl___dt)\n"
                 "nop");
}
