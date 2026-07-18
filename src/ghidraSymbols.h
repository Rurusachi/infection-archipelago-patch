#pragma once
#include "ghidra/ccSystem.h"
#include "ghidra/ccMenuCtrl.h"
#include "ghidra/ccEnemyParam.h"
#include "ghidra/ccBossParamData.h"
#include "ghidra/SkillParam.h"

typedef struct ccFont ccFont, *PccFont;
struct ccFont {
    ccSprite sprite;
};

extern ccSystem* ccSys;
extern ccChar* cmndTarget;
extern ccChar* cmndTargetPrev;
extern ccFont* font;
extern ulong ccSpriteColorTable[24];

extern SkillParam skillTbl[];

extern ccMenuCtrl *ccMenuCtrl___ct(ccMenuCtrl *menuCtrl);
extern void ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1);

extern byte ccCheckTarget (ccChar *param_1);
extern void DispButton(ccMenuWindow *menuWindow, int param_1);
extern ccEnemyParam* ccGetEnemyParam(int param_1);
extern ccBossParamData* ccGetBossParam(int param_1);

extern char* ccKanjiStrcat(char *__dest, char *__src, int length);
extern char* strcat(char *__dest, char *__src);

extern void ccFont_SetType(ccFont *font, int param_1); // 0-3 are valid. 2-3 = numbers only?
extern void ccFont_MakeNum(ccFont *font, int param_1, int param_2, ulong param_3);

extern ccSprite *ccSprite___ct(ccSprite *sprite);
extern void ccSprite_MakePacketStr(ccSprite *sprite, char *param_1, int param_2);
extern void ccSprite_MakePacket(ccSprite *sprite, int param_1, int param_2);
extern void ccSprite_SendPacket(ccSprite *sprite);

extern ccKanji *ccInitKanji(int param_1, int param_2);

extern ccKanji *ccKanji___dt(ccKanji *kanji, int param_1);
extern void ccKanji_Init(ccKanji *kanji, int param_1, int param_2);
extern void ccKanji_Extract(ccKanji *kanji, char *param_1);
extern void ccKanji_SetClm(ccKanji *kanji, int param_1, int param_2, int param_3, int param_4);
extern void ccKanji_Disp(ccKanji *kanji, char *param_1, int param_2, float param_3, float param_4);
