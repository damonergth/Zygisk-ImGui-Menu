#ifndef IMGUI_MENU_H
#define IMGUI_MENU_H

using namespace ImGui;

int i1 = 0;
float f1 = 0.123f;

void DrawMenu() {
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f); 
    {
        Begin(OBFUSCATE("EZCHEATS"));
        ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
        if (BeginTabBar("Menu", tab_bar_flags)) {
            if (BeginTabItem(OBFUSCATE("PLAYER"))) {
                Checkbox(OBFUSCATE("One Hit"), &attackScale);
                Checkbox(OBFUSCATE("Dumb Enemt"), &bot);
                Checkbox(OBFUSCATE("No CD"), &mana);
                Checkbox(OBFUSCATE("Hp Update"), &updHp);
                Checkbox(OBFUSCATE("Frame Updater"), &updFrame);
                Checkbox(OBFUSCATE("Attach"), &attach);
                EndTabItem();
            }
            SliderInt("slider int", &dmg, 0, 100);
            SliderFloat("slider float", &f1, 0.0f, 1.0f, "ratio = %.3f");
            EndTabBar();
            
        }
        TextUnformatted(OBFUSCATE ("BY DAPZ"));
        Patches();
        End();
    }
}

void SetupImgui() {
    IMGUI_CHECKVERSION();
    CreateContext();
    ImGuiIO &io = GetIO();
    io.DisplaySize = ImVec2((float) glWidth, (float) glHeight);
    ImGui_ImplOpenGL3_Init("#version 100");
    StyleColorsDark();
    ImFontConfig font_cfg;
    font_cfg.SizePixels = 22.0f;
    io.Fonts->AddFontDefault(&font_cfg);
    GetStyle().ScaleAllSizes(7.0f);
    
}


EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);

    if (!setupimg) {
        SetupImgui();
        setupimg = true;
    }

    ImGuiIO &io = GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    NewFrame();

    DrawMenu();

    EndFrame();
    Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return old_eglSwapBuffers(dpy, surface);
}

#endif // IMGUI_MENU_H
