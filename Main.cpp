#include <Includes.h>

void DrawMenu() {
ImGui::Begin(OBFUSCATE("norton community"));
if(ImGui::CollapsingHeader(OBFUSCATE("Visuals"))) {
ImGui::Checkbox(OBFUSCATE("Render Esp"), &esp_en);
if(esp_en) {
	/*ImGui::Checkbox(OBFUSCATE("Line##d12321"), &line);
	if(line) {
		ImGui::Checkbox(OBFUSCATE("Outline##line"), &lineoutline);
		ColorPicker("Color##line", colors::line);
	}*/
ImGui::Checkbox(OBFUSCATE("Esp Box"), &espbox);
if (espbox){
ColorPicker(("Box Color##esp"), colors::boxcolor);
ImGui::Checkbox(("Outline##esp"),&boxoutline);
ImGui::Checkbox(("Fill Box##esp"),&fillbox);
if(fillbox){
ImGui::SameLine();
//ImGui::ColorEdit4(("##pasted"), colors::fillboxcolor,ImGuiColorEditFlags_NoInputs);
ImGui::SliderFloat(("Fill Value##esp"),&fill_value,1,255);
}
ImGui::SliderInt(("Box Rounding##esp"),&boxrounding,1,25);
}
ImGui::Checkbox(OBFUSCATE("Esp Name"), &espname);
ImGui::Checkbox(OBFUSCATE("Esp Distance"),&espdistance);
ImGui::Checkbox(OBFUSCATE("ESP Health"),&health);
ImGui::ColorEdit3(OBFUSCATE("ESP HpColor"), hpcolor1,ImGuiColorEditFlags_NoInputs);	
}
}
if(ImGui::CollapsingHeader(OBFUSCATE("Aimbot"))) {
ImGui::Checkbox(OBFUSCATE("Aimbot Enable"), &aimbot_enable);
if(aimbot_enable) {
ImGui::Checkbox(OBFUSCATE("Visible Check"), &aimbot_visiblecheck);
ImGui::Checkbox(OBFUSCATE("Draw Fov"), &aimbot_drawfov);
if(aimbot_drawfov) {
ImGui::SameLine();
AddColorPicker(OBFUSCATE("Fov Color"), aimbot_fovcolor);
}
ImGui::SliderFloat(OBFUSCATE("Aimbot Fov"), &aimbot_fov, 1.0f , 360.0f);
}
}
}

void Customization() {
IMGUI_CHECKVERSION();
ImGui::CreateContext();
ImGui::GetIO().DisplaySize = ImVec2((float)glwidth, (float)glheight);
ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 100"));
ImGui::StyleColorsDark();
ImGui::GetIO().Fonts->AddFontFromMemoryTTF(Roboto_Regular, sizeof(Roboto_Regular), 35, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
Pixel = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&PixelFont, sizeof PixelFont, 21, NULL, ImGui::GetIO().Fonts->GetGlyphRangesCyrillic());
Weapon = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(&weapon1, sizeof weapon1, 30.0f, NULL);
ImFontConfig font_cfg;
font_cfg.SizePixels = 22.0f;
ImGui::GetIO().Fonts->AddFontDefault(&font_cfg);
}

EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
eglQuerySurface(dpy, surface, EGL_WIDTH, &glwidth);
eglQuerySurface(dpy, surface, EGL_HEIGHT, &glheight);
static bool setup;
if (!setup) { Customization(); setup = true; }
ImGui_ImplOpenGL3_NewFrame();
ImGui::NewFrame();
DrawMenu();
DrawEsp();
Aimbot();
ImGui::EndFrame();
ImGui::Render();
ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
return old_eglSwapBuffers(dpy, surface);
}

HOOKAF(void, Input, void *thiz, void *ex_ab, void *ex_ac) {
origInput(thiz, ex_ab, ex_ac);
ImGui_ImplAndroid_HandleInputEvent((AInputEvent *)thiz);
return;
}

auto TrampolineHook = A64HookFunction;
void *hacks(void *) {
do { sleep(1); } while (!isLibraryLoaded(OBFUSCATE("libil2cpp.so")));
il2cpp_base = GetBaseAddress(OBFUSCATE("libil2cpp.so"));
unity_base = GetBaseAddress(OBFUSCATE("libunity.so"));	
void *egl = dlopen_ex(OBFUSCATE("libinput.so"), 4);
while (!egl) { egl = dlopen_ex(OBFUSCATE("libinput.so"), 4); sleep(7); }
void *addr = dlsym_ex(egl, (xorstr_("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE")));
TrampolineHook((void *) (unity_base + string2Offset(OBFUSCATE("0x68222C"))), (void *) hook_eglSwapBuffers, (void **) &old_eglSwapBuffers);
TrampolineHook((void *) addr, (void *) myInput, (void **) &origInput);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

GetHealth = (int(*)(uintptr_t))(il2cpp_base+0x251EFB0);//0x251ED7C
GetName = (monoString*(*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x27F4094")));
get_bipedmap = (uintptr_t(*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x23EED2C")));
Linecast = (bool (*)(Vector3, Vector3, int)) (il2cpp_base + string2Offset(OBFUSCATE("0x49FFF28")));
get_forward = (Vector3(*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x49B5BA8")));
get_transform = (uintptr_t(*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x49A906C")));
get_position = (Vector3(*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x49B5628")));
get_camera = (uintptr_t(*)()) (il2cpp_base + string2Offset(OBFUSCATE("0x497BE08")));
WorldToScreenPoint = (Vector3 (*)(uintptr_t, Vector3)) (il2cpp_base + string2Offset(OBFUSCATE("0x497B75C")));
GetTeam = (int (*)(uintptr_t)) (il2cpp_base + string2Offset(OBFUSCATE("0x23F0F84")));
return nullptr;
}

__attribute__((constructor))
void lib_main() {
pthread_t impelog;
pthread_create(&impelog, NULL, hacks, NULL);
}
