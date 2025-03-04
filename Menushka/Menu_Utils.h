void Switch(const char* label, bool* v) {
ImVec2 p = ImGui::GetCursorScreenPos();
ImDrawList* draw_list = ImGui::GetWindowDrawList();
ImGuiStyle& style = ImGui::GetStyle();
float height = ImGui::GetFrameHeight();
float width = height * 1.55f;
float radius = height * 0.50f;
ImGui::InvisibleButton(label, ImVec2(width, height));
if (ImGui::IsItemClicked())
*v = !*v;
float t = *v ? 1.0f : 0.0f;
ImGuiContext& g = *GImGui;
float ANIM_SPEED = 0.08f;
if (g.LastActiveId == g.CurrentWindow->GetID(label)){
float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
t = *v ? (t_anim) : (1.0f - t_anim);
}
ImU32 col_bg;
if (ImGui::IsItemHovered())
col_bg = ImGui::GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBgHovered], style.Colors[ImGuiCol_FrameBg], t));
else
col_bg = ImGui::GetColorU32(ImLerp(style.Colors[ImGuiCol_FrameBg], style.Colors[ImGuiCol_FrameBgActive], t));
draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));
ImGui::SameLine();
ImGui::Text(label);
}
