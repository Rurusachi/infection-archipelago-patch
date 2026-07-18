#include "colors.h"

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
