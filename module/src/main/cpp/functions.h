#ifndef FUNCTION_H
#define FUNCTION_H

// here you can define variables for the patches
bool addCurrency, freeItems, everythingUnlocked, showAllItems, addSkins;
bool attackScalxe;

/*
   FOR ARM64
   200080D2C0035FD6 TRUE
   000080D2C0035FD6 FALSE
   00E0AFD2C0035FD6 HIGH VALUE
   1F2003D5 NOP
*/

monoString *CreateIl2cppString(const char *str) {
    monoString *(*String_CreateString)(void *instance, const char *str) = (monoString*(*)(void*, const char*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0x2596B20")));
    return String_CreateString(NULL, str);
}

void (*PurchaseRealMoney) (void* instance, monoString* itemId, monoString* receipt, void* callback);

void Pointers() {
    PurchaseRealMoney = (void(*)(void*, monoString*, monoString*, void*)) (g_il2cppBaseMap.startAddress + string2Offset(OBFUSCATE("0xE7AADC")));
}

bool bot, mana, updHP, updFrame, attach;

void Patches() {
    PATCH_SWITCH("0x65A226C", "C0035FD6", attackScale);
    PATCH_SWITCH("0xF148A4", "E07C80D2C0035FD6", freeItems);
PATCH_SWITCH("0x50e1b58", "000080D2C0035FD6", bot);
PATCH_SWITCH("0x777b90c", "00E0AFD2C0035FD6", mana);
PATCH_SWITCH("0x777d534", "1F2003D5", updHp);
PATCH_SWITCH("0x777fb70", "1F2003D5", updFrame);
PATCH_SWITCH("0x777de28", "1F2003D5", attach);

}

// declare your hooks here
void (*old_Backend)(void *instance);
void Backend(void *instance) {
    if (instance != NULL) {
        if (addCurrency) {
            LOGW("Calling Purchase");
            PurchaseRealMoney(instance, CreateIl2cppString("special_offer1"), CreateIl2cppString("dev"), NULL);
            addCurrency = false;
        }
        if (addSkins) {
            LOGW("Calling Skins");
            addSkins = false;
        }
    }
    return old_Backend(instance);
}

void* (*old_ProductDefinition)(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts);
void* ProductDefinition(void *instance, monoString* id, monoString* storeSpecificId, int type, bool enabled, void* payouts) {
    if (instance != NULL) {
        LOGW("Called ProductDefinition! Here are the parameters:");
        LOGW("id: %s", id->getChars());
        LOGW("storeSpecificId: %s", storeSpecificId->getChars());
        LOGW("type: %i", type);
    }
    return old_ProductDefinition(instance, id, storeSpecificId, type, enabled, payouts);
}

void Hooks() {
    HOOK("0xE7BC74", Backend, old_Backend);
    HOOK("0x29DA08C", ProductDefinition, old_ProductDefinition);
}

#endif // FUNCTION_H
