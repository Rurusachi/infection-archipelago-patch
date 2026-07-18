#pragma once
#include "typedefs.h"
#include "ghidraSymbols.h"

void hook_ccMenuCtrl___ct();
ccMenuCtrl* orig_ccMenuCtrl___ct(ccMenuCtrl *menuCtrl) __attribute__ ((noinline));
ccMenuCtrl* h_ccMenuCtrl___ct(ccMenuCtrl *menuCtrl);

void hook_ccMenuCtrl___dt();
void orig_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1) __attribute__ ((noinline));
void h_ccMenuCtrl___dt(ccMenuCtrl *menuCtrl, int param_1);
