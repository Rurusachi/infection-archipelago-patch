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

extern void ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1);

extern byte ccCheckTarget (ccChar *param_1);
extern void DispButton(ccMenuWindow *menuWindow, int param_1);
extern ccEnemyParam* ccGetEnemyParam(int param_1);
extern ccBossParamData* ccGetBossParam(int param_1);

extern void ccFont_SetType(ccFont *font, int param_1); // 0-3 are valid. 2-3 = numbers only?
extern void ccFont_MakeNum(ccFont *font, int param_1, int param_2, ulong param_3);

extern ccSprite *ccSprite___ct(ccSprite *sprite);
extern void ccSprite_MakePacketStr(ccSprite *sprite, char *param_1, int param_2);
extern void ccSprite_MakePacket(ccSprite *sprite, int param_1, int param_2);
extern void ccSprite_SendPacket(ccSprite *sprite);


extern ccKanji *ccKanji___dt(ccKanji *kanji, int param_1);
extern void ccKanji_Init(ccKanji *kanji, int param_1, int param_2);
extern void ccKanji_Extract(ccKanji *kanji, char *param_1);
extern void ccKanji_SetClm(ccKanji *this, int param_1, int param_2, int param_3, int param_4);
extern void ccKanji_Disp(ccKanji *kanji, char *param_1, int param_2, float param_3, float param_4);

extern char* strcat(char *__dest, char *__src);
extern char* ccKanjiStrcat(char *__dest, char *__src, int length);
extern ccKanji *ccInitKanji(int param_1, int param_2);



typedef struct ArchipelagoData ArchipelagoData, *PArchipelagoData;
typedef struct ArchipelagoMessage ArchipelagoMessage, *PArchipelagoMessage;

struct ArchipelagoMessage {
    char status; // 0 = empty, 1 = ready, 2 = active
    char queue_pos;
    char color;
    char type;
    ushort time;
    char text[64];
};

struct ArchipelagoData {
    ArchipelagoMessage messages[4];
};

extern ArchipelagoData archipelagoData; // 0x006FA660

// Names from www.color-name.com
#define PRESET_MOON_GRAY 0
#define PRESET_TANGY_BLUE 1
#define PRESET_BRILLIANT_RED 2
#define PRESET_FLUORESCENT_MAGENTA 3
#define PRESET_LASER_GREEN 4
#define PRESET_AQUA 5
#define PRESET_DIGITAL_YELLOW 6
#define PRESET_WHITE 7
#define PRESET_DARK_GREY 8
#define PRESET_INTERNATIONAL_KLEIN_BLUE 9
#define PRESET_PERFECT_RED 10
#define PRESET_SHOCKING_PURPLE 11
#define PRESET_PURE_GREEN 12
#define PRESET_DEEP_AQUA 13
#define PRESET_RIO_GRANDE 14
#define PRESET_BLACK 15
#define PRESET_ARGENT 16
#define PRESET_ADONIS 17
#define PRESET_COCKTAIL_RED 18
#define PRESET_PURE_PINK 19
#define PRESET_PALE_GREEN 20
#define PRESET_ICE_BLUE 21
#define PRESET_DOLLY 22
#define PRESET_BLAZE_ORANGE 23



enum CustomColor {
    CUSTOM_RED,
    CUSTOM_GREEN,
    CUSTOM_YELLOW,
    CUSTOM_BLUE,
    CUSTOM_MAGENTA,
    CUSTOM_CYAN,
    CUSTOM_SLATEBLUE,
    CUSTOM_PLUM,
    CUSTOM_SALMON,
    CUSTOM_ORANGE,
};

int entry(ccMenuCtrl* menuCtrl) __attribute__ ((section (".text.entry")));

void orig_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) __attribute__ ((noinline));
void h_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1);
