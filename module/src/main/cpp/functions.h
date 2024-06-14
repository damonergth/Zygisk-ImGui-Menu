#ifndef FUNCTION_H
#define FUNCTION_H

/*
   FOR ARM64
   200080D2C0035FD6 TRUE
   000080D2C0035FD6 FALSE
   00E0AFD2C0035FD6 HIGH VALUE
   1F2003D5 NOP
*/

bool bot, mana, updHp, updFrame, attach;
bool IState; // 0x77a0fe8 public static IState Create(Character character) { } CharacterDeadStateGenerator
// public class CharacterControllerDeadState : IState
bool enterDeadState; // 0x509c260 private Void Oak.IState.Enter(IState prev) { }

void Pointers() {}

void Patches() {
    PATCH_SWITCH("0xF148A4", "E07C80D2C0035FD6", freeItems);
    PATCH_SWITCH("0x50e1b58", "000080D2C0035FD6", bot);
    PATCH_SWITCH("0x777b90c", "00E0AFD2C0035FD6", mana);
    PATCH_SWITCH("0x777d534", "000080D2C0035FD6", updHp); // force close
    PATCH_SWITCH("0x777fb70", "000080D2C0035FD6", updFrame); // force close
    PATCH_SWITCH("0x777de28", "000080D2C0035FD6", attach); // force close
    PATCH_SWITCH("0x77a0fe8", "1F2003D5", IState);
    PATCH_SWITCH("0x509c260", "1F2003D5", enterDeadState);
}

int damage = 0;
int (*old_damageMultiplier)(void *instance);
int damageMultiplier(void *instance) {
    if (instance != NULL && damage) {
        return (int) damage;
    }
    return old_damageMultiplier(instance);
}
int walkspeed = 1; // 0x777f2a4 public Single get_WalkSpeed() { }
float (*old_getWalkspeed)(void *instance);
float getWalkspeed(void *instance) {
    if (instance != NULL && walkspeed > 1) {
        return (float) walkspeed;
    }
    return old_getWalkspeed(instance);
}

void Hooks() {
    HOOK("0x65A226C", damageMultiplierplier, old_damageMultiplier);
    HOOK("0x777f2a4", getWalkspeed, old_getWalkspeed):
}

using namespace ImGui;

int i1 = 0;
float f1 = 0.123f;

void DrawMenu() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
    {
        Begin(OBFUSCATE("EZCHEATS"));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
        if (BeginTabBar("Menu", tab_bar_flags)) {
            SliderInt("slider int", &dmg, 0, 100);
            SliderFloat("slider float", &walkspeed, 0.0f, 10.0f, "ratio = %.3f");
            if (BeginTabItem(OBFUSCATE("PLAYER"))) {
                Checkbox(OBFUSCATE("One Hit"), &attackScale);
                Checkbox(OBFUSCATE("Dumb Enemt"), &bot);
                Checkbox(OBFUSCATE("No CD"), &mana);
                Checkbox(OBFUSCATE("Hp Update"), &updHp);
                Checkbox(OBFUSCATE("Frame Updater"), &updFrame);
                Checkbox(OBFUSCATE("Attach"), &attach);
                EndTabItem();
            }
            EndTabBar();
        }
        TextUnformatted(OBFUSCATE ("BY DAPZ"));
        Patches();
        End();
    }
}

#endif // FUNCTION_H