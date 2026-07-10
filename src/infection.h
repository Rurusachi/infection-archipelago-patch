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
    char color;
    char type;
    ushort time;
    char text[100];
};

struct ArchipelagoData {
    ArchipelagoMessage messages[4];
};

extern ArchipelagoData archipelagoData; // 0x6FA5B0

// Names from www.color-name.com
enum PresetColor {
    PRESET_MOON_GRAY,
    PRESET_TANGY_BLUE,
    PRESET_BRILLIANT_RED,
    PRESET_FLUORESCENT_MAGENTA,
    PRESET_LASER_GREEN,
    PRESET_AQUA,
    PRESET_DIGITAL_YELLOW,
    PRESET_WHITE,
    PRESET_DARK_GREY,
    PRESET_INTERNATIONAL_KLEIN_BLUE,
    PRESET_PERFECT_RED,
    PRESET_SHOCKING_PURPLE,
    PRESET_PURE_GREEN,
    PRESET_DEEP_AQUA,
    PRESET_RIO_GRANDE,
    PRESET_BLACK,
    PRESET_ARGENT,
    PRESET_ADONIS,
    PRESET_COCKTAIL_RED,
    PRESET_PURE_PINK,
    PRESET_PALE_GREEN,
    PRESET_ICE_BLUE,
    PRESET_DOLLY,
    PRESET_BLAZE_ORANGE,
};

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