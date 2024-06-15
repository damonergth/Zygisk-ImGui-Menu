#ifndef IMGUI_MENU_H
#define IMGUI_MENU_H

using namespace ImGui;

/*
   FOR ARM64
   200080D2C0035FD6 TRUE
   000080D2C0035FD6 FALSE
   00E0AFD2C0035FD6 HIGH VALUE
   1F2003D5 NOP
*/
// public class MonsterCharacterController : IFieldObjectController, IComponent, IEventListener, ILateUpdatable
bool isBattleOn; // 0x50e1b58 public Boolean OnEvent(Event e) { }
// public class CharacterStatsBehaviour : FieldObjectStatsBehaviour
bool manaRegen; // 0x777b90c public Single get_ManaRegenScale() { }
int walkSpeed = 1; // 0x777f2a4 public Single get_WalkSpeed() { }
int dashSpeed = 1; // 0x777736c public Single get_DashSpeed() { }
// public class Weapon : Item, IWeapon, IItem, IIdHolder, IJSONObject, IEquipment, IDeepCloneable`1
int getDamage = 0; // 0x65a226c public Single GetElementalAttackScale(ElementalType elementalType, Int32 level, Int32 limitBreaks, Int32 characterOriginId) { }
// public struct BuffStats
int speedv2 = 1;  // 0x56bceac public ObscuredFloat get_SpeedMult() { }

void Pointers() {}

void Patches() {
    PATCH_SWITCH("0x50e1b58", "000080D2C0035FD6", isBattleOn);
    PATCH_SWITCH("0x777b90c", "00E0AFD2C0035FD6", manaRegen);
}

int (*old_GetElementalAttackScale)(void *instance);
int GetElementalAttackScale(void *instance) {
    if (instance != NULL && getDamage) {
        return (int) getDamage;
    }
    return old_GetElementalAttackScale(instance);
}

int (*old_charSpeed)(void *instance);
int charSpeed(void *instance) {
	if (instance != NULL && walkSpeed) {/*walkSpeed && dashSpeed*/
		return (int) walkSpeed;
		// return (int) dashSpeed;
		// return (int) speedv2;
	}
	return old_charSpeed(instance);
}
/*
float (*old_getWalkspeed)(void *instance);
float getWalkspeed(void *instance) {
    if (instance != NULL && walkspeed > 1) {
        return (float) walkspeed;
    }
    return old_getWalkspeed(instance);
}
*/
void Hooks() {
    HOOK("0x65a226c", GetElementalAttackScale, old_GetElementalAttackScale);
    HOOK("0x777f2a4", charSpeed, old_charSpeed);
}

void DrawMenu() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
    {
        Begin(OBFUSCATE("EZCHEATS"));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
        if (BeginTabBar("Menu", tab_bar_flags)) {
            // if (BeginTabItem(OBFUSCATE("PLAYER"))) {}
			SliderInt("dmg", &getDamage, 1, 100);
			SameLine(); TextUnformatted(OBFUSCATE ("Damage Multiplier"));
                        SliderInt("spd", &walkSpeed, 1, 10);
			SameLine(); TextUnformatted(OBFUSCATE("Walkspeed"));
			Checkbox(OBFUSCATE("Dumb Enemy"), &isBattleOn);
			Checkbox(OBFUSCATE("No CD"), &manaRegen);
            EndTabBar();
        }
        TextUnformatted(OBFUSCATE ("BY DAPZ"));
        Patches();
        End();
    }
}

#endif // IMGUI_MENU_H
