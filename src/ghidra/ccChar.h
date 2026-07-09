#pragma once
#include "typedefs.h"

typedef struct ccChar ccChar, *PccChar;

typedef struct ccSpcParam ccSpcParam, *PccSpcParam;

typedef struct vector4f vector4f, *Pvector4f;

typedef struct CharData CharData, *PCharData;

typedef struct ccTolerance ccTolerance, *PccTolerance;

typedef struct ccCharParamElement ccCharParamElement, *PccCharParamElement;

typedef struct ccBattleAbility ccBattleAbility, *PccBattleAbility;

typedef struct ccAttribute ccAttribute, *PccAttribute;

struct ccTolerance { /* PlaceHolder Structure */
    short soul;
    short body;
};

struct ccAttribute { /* PlaceHolder Structure */
    short earth;
    short water;
    short fire;
    short wood;
    short light;
    short dark;
};

struct ccBattleAbility { /* PlaceHolder Structure */
    short attack;
    short defense;
    short accuracy;
    short evasion;
    short magic_attack;
    short magic_defense;
    short magic_accuracy;
    short magic_evasion;
};

struct ccCharParamElement { /* PlaceHolder Structure */
    struct ccBattleAbility battleAbility;
    struct ccAttribute attribute;
    struct ccTolerance tolerance;
};

struct vector4f {
    float x;
    float y;
    float z;
    float w;
};

struct CharData {
    char *name;
    char *model;
    uint field_0x8;
    short char_id; /* Created by Rename Structure Field action */
    short level;
    undefined field8_0x10;
    undefined field9_0x11;
    undefined field10_0x12;
    undefined field11_0x13;
    int GP;
    float height;
    float width;
    uint base_msg;
    short max_hp;
    short max_sp;
    struct ccBattleAbility battleAbility;
    struct ccAttribute attribute;
    struct ccTolerance tolerance;
    ushort equip_head;
    ushort equip_body;
    ushort equip_arms;
    ushort equip_legs;
    ushort equip_weapon;
    ushort field26_0x52;
    float field27_0x54;
    ushort char_class;
    undefined field29_0x5a;
    undefined field30_0x5b;
};

struct ccChar { /* PlaceHolder Structure */
    struct ccSpcParam *spcParam0;
    struct ccSpcParam *spcParam1;
    ushort condition_0;
    ushort condition_1;
    ushort condition_2;
    ushort condition_3;
    ushort condition_4;
    ushort condition_5;
    ushort condition_6;
    ushort condition_7;
    ushort condition_8;
    ushort condition_9;
    ushort condition_10;
    ushort condition_11;
    ushort condition_12;
    ushort condition_13;
    ushort condition_14;
    ushort condition_15;
    uint condition_16;
    undefined field19_0x2c;
    undefined field20_0x2d;
    undefined field21_0x2e;
    undefined field22_0x2f;
    undefined field23_0x30;
    undefined field24_0x31;
    undefined field25_0x32;
    undefined field26_0x33;
    undefined field27_0x34;
    undefined field28_0x35;
    undefined field29_0x36;
    undefined field30_0x37;
    undefined field31_0x38;
    undefined field32_0x39;
    undefined field33_0x3a;
    undefined field34_0x3b;
    undefined field35_0x3c;
    undefined field36_0x3d;
    undefined field37_0x3e;
    undefined field38_0x3f;
    struct vector4f pos;
    struct vector4f field40_0x50;
    struct vector4f field41_0x60;
    short hp; /* Created by Rename Structure Field action */
    short sp; /* Created by Rename Structure Field action */
    short max_hp;
    short max_sp; /* Created by Rename Structure Field action */
    undefined field46_0x78;
    undefined field47_0x79;
    undefined field48_0x7a;
    undefined field49_0x7b;
    ushort field50_0x7c;
    ushort field51_0x7e;
    undefined field52_0x80;
    undefined field53_0x81;
    undefined field54_0x82;
    undefined field55_0x83;
    undefined field56_0x84;
    undefined field57_0x85;
    undefined field58_0x86;
    undefined field59_0x87;
    undefined field60_0x88;
    undefined field61_0x89;
    undefined field62_0x8a;
    undefined field63_0x8b;
    undefined field64_0x8c;
    undefined field65_0x8d;
    undefined field66_0x8e;
    undefined field67_0x8f;
    undefined field68_0x90;
    undefined field69_0x91;
    undefined field70_0x92;
    undefined field71_0x93;
};

struct ccSpcParam { /* PlaceHolder Structure */
    struct CharData data;
    undefined field1_0x5c;
    undefined field2_0x5d;
    undefined field3_0x5e;
    undefined field4_0x5f;
    short     break_damage;
    undefined field7_0x62;
    undefined field8_0x63;
    struct ccTolerance tolerance;
    struct ccCharParamElement param_elements[3];
    ushort equip_head;
    ushort equip_body;
    ushort equip_arms;
    ushort equip_legs;
    ushort equip_weapon;
    ushort equip_unused;
    uint field17_0xd4;
    ushort char_class;
    ushort friendship;
};

