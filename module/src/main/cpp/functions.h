#ifndef FUNCTION_H
#define FUNCTION_H

// here you can define variables for the patches
bool addCurrency, freeItems, everythingUnlocked, showAllItems, addSkins;
bool attackScale;

/*
   FOR ARM64
   200080D2C0035FD6 TRUE
   000080D2C0035FD6 FALSE
   00E0AFD2C0035FD6 HIGH VALUE
   1F2003D5 NOP
*/

bool bot, mana, updHp, updFrame, attach;

void Pointers() {}

void Patches() {
    PATCH_SWITCH("0x64A226C", "C0035FD6", attackScale);
    PATCH_SWITCH("0xF148A4", "E07C80D2C0035FD6", freeItems);
    PATCH_SWITCH("0x50e1b58", "000080D2C0035FD6", bot);
    PATCH_SWITCH("0x777b90c", "00E0AFD2C0035FD6", mana);
    PATCH_SWITCH("0x777d534", "1F2003D5", updHp);
    PATCH_SWITCH("0x777fb70", "1F2003D5", updFrame);
    PATCH_SWITCH("0x777de28", "1F2003D5", attach);

}

// declare your hooks here
/*
int dmg = 0;
int (*old_dmg)(void *instance);
int dmgmulti(void *instance) {
    if (instance != NULL && dmg) {
        return (int) dmg;
    }
    return old_dmg(instance);
}
*/
void Hooks() {}
    // HOOK("0x65A226C", dmgmulti, old_dmg);
   
#endif // FUNCTION_H
