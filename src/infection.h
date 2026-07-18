#pragma once
#include "typedefs.h"
#include "ghidraSymbols.h"

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

#define MessageNum 4
#define KanjiNum 4

extern ccKanji* kanjiList[KanjiNum];

int entry(ccMenuCtrl* menuCtrl) __attribute__ ((section (".text.entry")));
