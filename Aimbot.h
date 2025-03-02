Vector3 NormalizeAngles(Vector3 ang){
ang.x = Vector3::NormalizeAngle(ang.x);
ang.y = Vector3::NormalizeAngle(ang.y);
ang.z = Vector3::NormalizeAngle(ang.z);
return ang;
}

Vector3 ToEulerRad(Quaternion q1){
float sqw = q1.w * q1.w;
float sqx = q1.x * q1.x;
float sqy = q1.y * q1.y;
float sqz = q1.z * q1.z;
float unit = sqx + sqy + sqz + sqw;
float test = q1.x * q1.w - q1.y * q1.z;
Vector3 v;
if (test>0.4995f*unit) {
v.y = 2.0f * atan2f (q1.y, q1.x);
v.x = M_PI / 2.0f;
v.z = 0;
return NormalizeAngles(v * Rad2Deg);
}
if (test<-0.4995f*unit) {
v.y = -2.0f * atan2f (q1.y, q1.x);
v.x = -M_PI / 2.0f;
v.z = 0;
return NormalizeAngles(v * Rad2Deg);
}
Quaternion q(q1.w, q1.z, q1.x, q1.y);
v.y = atan2f (2.0f * q.x * q.w + 2.0f * q.y * q.z, 1 - 2.0f * (q.z * q.z + q.w * q.w));
v.x = asinf (2.0f * (q.x * q.z - q.w * q.y));
v.z = atan2f (2.0f * q.x * q.y + 2.0f * q.z * q.w, 1 - 2.0f * (q.y * q.y + q.z * q.z));
return NormalizeAngles(v * Rad2Deg);
}

void AddColorPicker(const char* name, ImVec4 &color, bool prd = false, bool* rainbow = nullptr, bool* pulse = nullptr, bool* dark = nullptr) {
ImGuiColorEditFlags misc_flags = ImGuiColorEditFlags_AlphaPreview;
static ImVec4 backup_color;
bool open_popup = ImGui::ColorButton((std::string(name) + std::string(OBFUSCATE("##3b"))).c_str(), color, misc_flags);
if (open_popup) {
ImGui::OpenPopup(name);
backup_color = color;
}
if (ImGui::BeginPopup(name)) {
ImGui::Text(OBFUSCATE("%s"), std::string(name).c_str());
ImGui::Separator();
ImGui::ColorPicker4(OBFUSCATE("##picker"), (float *) &color,misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview | ImGuiColorEditFlags_AlphaBar);
ImGui::SameLine();
ImGui::BeginGroup();
ImGui::Text(OBFUSCATE("%s"),std::string(OBFUSCATE("Current")).c_str());
ImGui::ColorButton(OBFUSCATE("##current"), color,ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf,ImVec2(60, 40));
ImGui::Text(OBFUSCATE("%s"),std::string(OBFUSCATE("Previous")).c_str());
if (ImGui::ColorButton(OBFUSCATE("##previous"), backup_color,ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf,ImVec2(60, 40)))color = backup_color;
ImGui::EndGroup();
if (prd) {
if (rainbow) ImGui::Checkbox(OBFUSCATE("rainbow"), rainbow);
if (pulse) ImGui::Checkbox(OBFUSCATE("pulse"), pulse);
if (dark) ImGui::Checkbox(OBFUSCATE("dark"), dark);
}
ImGui::EndPopup();
}
}
void Aimbot() {
if(aimbot_enable) {
if(aimbot_drawfov){
ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(glwidth/2,glheight/2),aimbot_fov*2, ImGui::ColorConvertFloat4ToU32(aimbot_fovcolor));
}
auto localPlayer = get_local_player();
if (localPlayer == NULL) return;
int localTeam = GetTeam(localPlayer);
auto me = localPlayer;
for (const auto & player : get_player_list()) {
if (player == NULL) continue;
auto enemy = player;
int playerTeam = GetTeam(player);
if (playerTeam == localTeam) continue;
void *AimController = *(void **) ((uintptr_t) me + 0x60);
if (AimController) {
void *AimingData = *(void **) ((uintptr_t) AimController + 0x90);
if (AimingData) {
PlayerLook = Quaternion::LookRotation(Vector3(GetPlayerHead(enemy).x, GetPlayerHead(enemy).y - 1.400f, GetPlayerHead(enemy).z) - get_position(get_transform(me)), Vector3(0, 1, 0));
Vector3 angle = ToEulerRad(PlayerLook);
if (angle.x >= 275.0f) angle.x -= 360.0f;
if (angle.x <= -275.0f) angle.x += 360.0f;
Vector3 target = GetPlayerHead(enemy) - get_position(get_transform(get_camera()));
float aimAngle = Vector3::Angle(target, get_forward(get_transform(get_camera())) * 100);
if (target != Vector3(0, 0, 0) && aimAngle <= aimbot_fov / 360.0f) {
if (aimbot_visiblecheck) {
if (IsPlayerVisible(enemy)) {
*(Vector3 *) ((uintptr_t) AimingData + 0x18) = angle;
*(Vector3 *) ((uintptr_t) AimingData + 0x24) = angle;
}
} else {
*(Vector3 *) ((uintptr_t) AimingData + 0x18) = angle;
*(Vector3 *) ((uintptr_t) AimingData + 0x24) = angle;
}
}
}
}                                             
}
}
}
