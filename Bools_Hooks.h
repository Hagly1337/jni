int glwidth, glheight;

uintptr_t il2cpp_base;
uintptr_t unity_base;

ImFont *Pixel;
ImFont *Weapon;


auto checker = false;
float esphpsize = 2;
float espstroke = 2;
void ColorPicker(const char* name, ImColor& color) {
        static ImColor backup_color;

        ImVec4 color_vec4 = color;
        bool open_popup = ImGui::ColorButton((std::string(name) + "##3b").c_str(), color_vec4);

        if (open_popup) {
            ImGui::OpenPopup(name);
            backup_color = color;
        }

        if (ImGui::BeginPopup(name)) {
            ImGui::ColorPicker4((std::string(name) + "##picker").c_str(),
                                (float *) &color.Value,
                                ImGuiColorEditFlags_NoSidePreview |
                                ImGuiColorEditFlags_NoSmallPreview |
                                ImGuiColorEditFlags_NoLabel |
                                ImGuiColorEditFlags_NoTooltip |
                                ImGuiColorEditFlags_NoInputs);
            ImGui::EndPopup();
        }
    }
    
const char* hptype[] = {"Default","Gradient"};
int healthtype;
bool health;
float HpColor[] = {1,1,1};
float hpcolor1[] = { 1,0,0 };
float hpcolor2[] = { 1,0,0 };
bool lineoutline;
bool line;
float ColorLine[] = {91,32,233};
float fillboxcolor[4] = {1,1,1};
float fill_value = 150;
bool fillbox;
int boxrounding = 3;
bool boxoutline = true;
bool esp_en, espbox, espname, espdistance;
namespace colors {
ImColor line = ImColor(255, 255, 255);
ImColor boxcolor = ImColor(255,255,255);
float fillboxcolor[4] = {1,1,1};
}
bool aimbot_enable, aimbot_drawfov, aimbot_visiblecheck;
float aimbot_fov = 75.0f;
ImVec4 aimbot_fovcolor = ImVec4(255, 255, 255, 255);

uintptr_t get_photon(uintptr_t impelog) { return *(uintptr_t*)(impelog + 0x130); } // 0.32.1
Quaternion PlayerLook;

Vector3 (*get_position)(uintptr_t);
Vector3 (*WorldToScreenPoint)(uintptr_t,Vector3);
uintptr_t (*get_transform)(uintptr_t);
uintptr_t (*get_camera)();
int (*GetTeam)(uintptr_t);
int (*GetHealth)(uintptr_t);
uintptr_t (*get_bipedmap)(uintptr_t);
Vector3(*get_forward) (uintptr_t);
monoString*(*GetName)(uintptr_t);

Vector3 GetPlayerHead(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0x20)); }
Vector3 GetPlayerHip(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0x80)); }
Vector3 GetPlayerleftLowerArm(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0x50)); }
Vector3 GetPlayerrightLowerArm(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0x70)); }
Vector3 GetPlayerleftLowerLeg(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0x90)); }
Vector3 GetPlayerrightLowerLeg(uintptr_t impelog) { return get_position(*(uintptr_t*) ((uintptr_t) get_bipedmap(impelog) + 0xA8)); }

bool (*Linecast)(Vector3, Vector3, int);
bool IsPlayerVisible(uintptr_t impelog) {
if (get_camera()) {
Vector3 CameraPos = get_position(get_transform(get_camera()));
bool CanSeeHead = !Linecast(CameraPos, GetPlayerHead(impelog), 16384);
bool CanSeeHip = !Linecast(CameraPos, GetPlayerHip(impelog), 16384);
bool CanSeeLeftLowerArm = !Linecast(CameraPos, GetPlayerleftLowerArm(impelog), 16384);
bool CanSeeRightLowerArm = !Linecast(CameraPos,GetPlayerrightLowerArm(impelog), 16384);
bool CanSeeLeftLowerLeg = !Linecast(CameraPos, GetPlayerleftLowerLeg(impelog), 16384);
bool CanSeeRightLowerLeg = !Linecast(CameraPos,GetPlayerrightLowerLeg(impelog), 16384);
return CanSeeHead || CanSeeHip || CanSeeLeftLowerArm || CanSeeRightLowerArm || CanSeeLeftLowerLeg || CanSeeRightLowerLeg;
}
return false;
}

std::vector<uintptr_t>get_player_list() {
std::vector<uintptr_t>null_vec;
uintptr_t playermanager_getinstance = *(uintptr_t*)(il2cpp_base + 85171760); // 0.32.1
uintptr_t playermanager_il2cppclass = *(uintptr_t*)(playermanager_getinstance + 0x20); // 0.32.1
uintptr_t playermanager_staticfields = *(uintptr_t*)(playermanager_il2cppclass + 0xB8); // 0.32.1
uintptr_t playermanager_instance = *(uintptr_t*)(playermanager_staticfields + 0x0); // 0.32.1
if (playermanager_instance)  {
auto entities = *(monoDictionary<int,uintptr_t>**)(playermanager_instance + 0x28); // 0.32.1
return entities->getValues();
}
else
return null_vec;
}

uintptr_t get_local_player() {
uintptr_t playermanager_getinstance = *(uintptr_t*)(il2cpp_base + 85171760); // 0.32.1
uintptr_t playermanager_il2cppclass = *(uintptr_t*)(playermanager_getinstance + 0x20); // 0.32.1
uintptr_t playermanager_staticfields = *(uintptr_t*)(playermanager_il2cppclass + 0xB8); // 0.32.1
uintptr_t playermanager_instance = *(uintptr_t*)(playermanager_staticfields + 0x0); // 0.32.1
auto local_player = *(uintptr_t*)(playermanager_instance + 0x70); // 0.32.1
return local_player;
}
int get_3D_Distance(int Self_x, int Self_y, int Self_z, int Object_x, int Object_y, int Object_z) {
int x, y, z;
x = Self_x - Object_x;
y = Self_y - Object_y;
z = Self_z - Object_z;
return (int)(sqrt(x * x + y * y + z * z));
}
inline float lerp(float a, float b, float f) {
    return std::clamp<float>(a + f * (b - a), a > b ? b : a, a > b ? a : b);
}
ImVec2 world2screen_c(Vector3 pos, bool &checker) {
    auto cam = get_camera();
    if (!cam) return {0,0};

    Vector3 worldPoint = WorldToScreenPoint(cam,pos);

    checker = worldPoint.z > 1;
    return ImVec2(worldPoint.x,glheight - worldPoint.y);
}

ImVec2 world2screen_i(Vector3 pos) {
    auto cam = get_camera();
    if (!cam) return {0,0};

    Vector3 worldPoint = WorldToScreenPoint(cam,pos);

    return {worldPoint.x,glheight - worldPoint.y};
}