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

extern byte ccCheckTarget (ccChar * param_1);
extern void DispButton(ccMenuWindow *menuWindow,int param_1);
extern void MakePacket(ccSprite *sprite,int param_1,int param_2);
extern ccEnemyParam* ccGetEnemyParam(int param_1);
extern ccBossParamData* ccGetBossParam(int param_1);

extern void ccFont_SetType(ccFont *font,int param_1); // 0-3 are valid. 2-3 = numbers only?
extern void ccFont_MakeNum(ccFont *font,int param_1,int param_2,ulong param_3);
extern void ccSprite_MakePacketStr(ccSprite *sprite,char *param_1,int param_2);




typedef struct ArchipelagoData ArchipelagoData, *PArchipelagoData;
typedef struct ArchipelagoMessage ArchipelagoMessage, *PArchipelagoMessage;

struct ArchipelagoMessage {
    char status; // 0 = empty, 1 = ready, 2 = active
    char queue_pos;
    ushort time;
    char text[100];
};

struct ArchipelagoData {
    ArchipelagoMessage messages[4];
};

extern ArchipelagoData archipelagoData; // 0x6FA5B0




int entry(ccMenuCtrl* menuCtrl) __attribute__ ((section (".text.entry")));
void ccSprite_SetPos(ccSprite *this, int x, int y);
void ccSprite_SetAlpha(ccSprite *this, uint alpha);
void ccSprite_SetColor(ccSprite *this, ulong color);
void ccSprite_SetColorFromPreset(ccSprite *this, int colorIndex);