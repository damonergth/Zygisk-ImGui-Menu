#ifndef IMGUI_MENU_H
#define IMGUI_MENU_H

using namespace ImGui;

// For arm64 only
#define retTrue "200080D2C0035FD6"
#define retFalse "000080D2C0035FD6"
#define retHigh "00E0AFD2C0035FD6"
#define NOP "1F2003D5"

bool bot, mana, updHp, updFrame, attach;
bool IState; // 0x77a0fe8 public static IState Create(Character character) { } CharacterDeadStateGenerator
// public class CharacterControllerDeadState : IState
bool enterDeadState; // 0x509c260 private Void Oak.IState.Enter(IState prev) { }

void Pointers() {}

void Patches() {
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
float walkspeed = 1.0f; // 0x777f2a4 public Single get_WalkSpeed() { }
float (*old_getWalkspeed)(void *instance);
float getWalkspeed(void *instance) {
    if (instance != NULL && walkspeed > 1) {
        return (float) walkspeed;
    }
    return old_getWalkspeed(instance);
}

void Hooks() {
    HOOK("0x65A226C", damageMultiplier, old_damageMultiplier);
    HOOK("0x777736c", getWalkspeed, old_getWalkspeed);
}

void DrawMenu() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
    {
        Begin(OBFUSCATE("EZCHEATS"));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
        if (BeginTabBar("Menu", tab_bar_flags)) {
            // if (BeginTabItem(OBFUSCATE("PLAYER"))) {}
			TextUnformatted(OBFUSCATE ("Damage Multiplier"));
			SliderInt(" ", &damage, 0, 100);
			TextUnformatted(OBFUSCATE ("Walkspeed"));
            SliderFloat(" ", &walkspeed, 0.0f, 10.0f/*"ratio = %.3f"*/);
			Checkbox(OBFUSCATE("Dumb Enemt"), &bot);
			Checkbox(OBFUSCATE("No CD"), &mana);
            EndTabBar();
        }
        TextUnformatted(OBFUSCATE ("BY DAPZ"));
        Patches();
        End();
    }
}

#endif // IMGUI_MENU_H