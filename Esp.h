void DrawEsp() {
if (esp_en) {
auto localPlayer = get_local_player();
if (localPlayer == NULL) return;
int localTeam = GetTeam(localPlayer);
for (const auto & player : get_player_list()) {
if (player == NULL) continue;
auto pl = player;
int playerTeam = GetTeam(pl);
if (playerTeam == localTeam) continue;
Vector3 posup = get_position(get_transform(pl)) + Vector3(0, 1.9f, 0);
Vector3 posdown = get_position(get_transform(pl));
Vector3 posuponscr = WorldToScreenPoint(get_camera(), posup);
Vector3 posdownonscr = WorldToScreenPoint(get_camera(), posdown);

float height = posuponscr.y - posdownonscr.y;
float width = height / 2;
auto render = ImGui::GetBackgroundDrawList();
Vector2 DrawTo = Vector2(posuponscr.x, (glheight - posuponscr.y));
            ImColor boxColorDarkened = ImColor(
                    colors::boxcolor.Value.x * 0.7f,
                    colors::boxcolor.Value.y * 0.7f,
                    colors::boxcolor.Value.z * 0.7f,
                    colors::boxcolor.Value.w
            );

            ImColor boxColorDarkenedalpha = ImColor(
                    colors::boxcolor.Value.x * 0.7f,
                    colors::boxcolor.Value.y * 0.7f,
                    colors::boxcolor.Value.z * 0.7f,
                    colors::boxcolor.Value.w - 100
            );
            ImColor boxColorSlightlyDarkened = ImColor(
                    colors::boxcolor.Value.x * 0.85f,
                    colors::boxcolor.Value.y * 0.85f,
                    colors::boxcolor.Value.z * 0.85f,
                    colors::boxcolor.Value.w
            );
            


            auto w2sC = world2screen_c(posdown + Vector3(0, 0.9, 0), checker);
            auto w2sTop = world2screen_i(posdown + Vector3(0, 1.9, 0));
            auto w2sBottom = world2screen_i(posdown + Vector3(0, 0, 0));

            auto pmtXtop = w2sTop.x;
            auto pmtXbottom = w2sBottom.x;

            ImVec2 topLeft = ImVec2(posuponscr.x - (width / 2), glheight - posuponscr.y);
            ImVec2 bottomRight = ImVec2(posuponscr.x + (width / 2), glheight - posuponscr.y + glheight);

            if (w2sTop.x > w2sBottom.x) {
                pmtXtop = w2sBottom.x;
                pmtXbottom = w2sTop.x;
            }
            
if (posuponscr.z > 1.0f) {
if(fillbox) {
render->AddRectFilled(ImVec2(posuponscr.x - (width/2),glheight-posuponscr.y),ImVec2(posuponscr.x+(width/2),glheight-posuponscr.y+height),ImGui::ColorConvertFloat4ToU32(ImVec4(fillboxcolor[0],fillboxcolor[1],fillboxcolor[2],float(fill_value)/255.f)),boxrounding,0);
}
if(boxoutline){
render->AddRect(ImVec2(posuponscr.x - (width/2),glheight-posuponscr.y),ImVec2(posuponscr.x+(width/2),glheight-posuponscr.y+height),ImColor(0,0,0),boxrounding,0,2.8f);
}
if(espbox){
render->AddRect(ImVec2(posuponscr.x - (width/2),glheight-posuponscr.y),ImVec2(posuponscr.x+(width/2),glheight-posuponscr.y+height),ImGui::ColorConvertFloat4ToU32(colors::boxcolor),boxrounding,0,1.0f);
}

	if (line) {
					ImVec2 lineStart = ImVec2(width / 2, glheight);
					ImVec2 lineEnd = ImVec2(posdown.x, glheight - posdown.y);
					if (lineoutline) {
						render->AddLine(
								lineStart,
								lineEnd,
								ImColor(0, 0, 0, 255),
								3.0f
						);
					}
					render->AddLine(
							lineStart,
							lineEnd,
							colors::line,
							1.5f
					);
				}
if(espname){
monoString *isPlayerName = GetName(get_photon(pl));
ImGui::PushFont(Pixel);					
render->AddText(ImVec2((posuponscr.x-ImGui::CalcTextSize(isPlayerName->get_string().c_str()).x/2)+1.8f,(glheight-posuponscr.y- 20)+1.8f), ImGui::ColorConvertFloat4ToU32(ImVec4(0,0,0, 1)), isPlayerName->get_string().c_str());
render->AddText(ImVec2((posuponscr.x-ImGui::CalcTextSize(isPlayerName->get_string().c_str()).x/2),glheight-posuponscr.y- 20), ImGui::ColorConvertFloat4ToU32(ImVec4(1,1,1, 1)), isPlayerName->get_string().c_str());
ImGui::PopFont();
}
  if (espdistance) {
                    ImGui::PushFont(Pixel);
                    Vector3 mypos = get_position(get_transform(get_camera()));
                    int DistanceTo = get_3D_Distance(mypos.x, mypos.y, mypos.z, posup.x,
                                                     posup.y, posup.z);
                    ImGui::GetBackgroundDrawList()->AddText(
                            ImVec2((posuponscr.x + 5 + width / 2) - 1,
                                   (glheight - posuponscr.y - 2) + 1),
                            ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)),
                            (std::to_string(DistanceTo) + "M").c_str());
                    ImGui::GetBackgroundDrawList()->AddText(
                            ImVec2((posuponscr.x + 5 + width / 2) - 1,
                                   (glheight - posuponscr.y - 2) - 1),
                            ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)),
                            (std::to_string(DistanceTo) + "M").c_str());
                    ImGui::GetBackgroundDrawList()->AddText(
                            ImVec2((posuponscr.x + 5 + width / 2) + 1,
                                   (glheight - posuponscr.y - 2) + 1),
                            ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)),
                            (std::to_string(DistanceTo) + "M").c_str());
                    ImGui::GetBackgroundDrawList()->AddText(
                            ImVec2((posuponscr.x + 5 + width / 2) + 1,
                                   (glheight - posuponscr.y - 2) - 1),
                            ImGui::ColorConvertFloat4ToU32(ImVec4(0, 0, 0, 1)),
                            (std::to_string(DistanceTo) + "M").c_str());
                    ImGui::GetBackgroundDrawList()->AddText(
                            ImVec2(posuponscr.x + 5 + width / 2, glheight - posuponscr.y - 2),
                            ImGui::ColorConvertFloat4ToU32(ImVec4(1, 1, 1, 1)),
                            (std::to_string(DistanceTo) + "M").c_str());
                    ImGui::PopFont();
                }
		if(health){
						float health = GetHealth(get_photon(pl));;
                    	int h = ((int) health);
                    	int x = DrawTo.x - width/2 - 10;
                   		int y = DrawTo.y;
                    	auto Render = ImGui::GetBackgroundDrawList();
						if(healthtype==0) {
							Render->AddRectFilled(ImVec2(x, y - 1),ImVec2(x + 6, y + 1 + height),ImColor(0, 0, 0, 200));
							ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x + 1,y +height -(height *(health /100))),ImVec2(x + 5,y +height),ImGui::ColorConvertFloat4ToU32(ImVec4(hpcolor1[0],hpcolor1[1],hpcolor1[2],1)));
						}
						if(healthtype==1) {
							Render->AddRectFilled(ImVec2(x, y - 1),ImVec2(x + 6, y + 1 + height),ImColor(0, 0, 0, 200));
							ImGui::GetBackgroundDrawList()->AddRectFilledMultiColor(ImVec2(x + 1,y +height -(height *(health /100))),ImVec2(x + 5,y +height), ImGui::GetColorU32(ImVec4(hpcolor1[0], hpcolor1[1], hpcolor1[2], 1.0f)), ImGui::GetColorU32(ImVec4(hpcolor1[0], hpcolor1[1], hpcolor1[2], 1.0f)), ImGui::GetColorU32(ImVec4(hpcolor2[0], hpcolor2[1], hpcolor2[2], 1.0f)), ImGui::GetColorU32(ImVec4(hpcolor2[0], hpcolor2[1], hpcolor2[2], 1.0f)));
						}
						if(h <100){
							ImGui::PushFont(Pixel);
				   		ImGui::GetBackgroundDrawList()->AddText(ImVec2((x+3)-ImGui::CalcTextSize(std::to_string(h).c_str()).x/2,y-9 +height -(height *(health /100))), ImGui::ColorConvertFloat4ToU32(ImVec4(0,0,0, 1)), std::to_string(h).c_str());		  
																					  																					  ImGui::GetBackgroundDrawList()->AddText(ImVec2((x+3)-ImGui::CalcTextSize(std::to_string(h).c_str()).x/2,y -7+height -(height *(health /100))), ImGui::ColorConvertFloat4ToU32(ImVec4(0,0,0, 1)), std::to_string(h).c_str());		  
																					  																					  ImGui::GetBackgroundDrawList()->AddText(ImVec2((x+5)-ImGui::CalcTextSize(std::to_string(h).c_str()).x/2,y-9 +height -(height *(health /100))), ImGui::ColorConvertFloat4ToU32(ImVec4(0,0,0, 1)), std::to_string(h).c_str());		  
																																										ImGui::GetBackgroundDrawList()->AddText(ImVec2((x+5)-ImGui::CalcTextSize(std::to_string(h).c_str()).x/2,y -7+height -(height *(health /100))), ImGui::ColorConvertFloat4ToU32(ImVec4(0,0,0, 1)), std::to_string(h).c_str());		
																																										ImGui::GetBackgroundDrawList()->AddText(ImVec2((x+4)-ImGui::CalcTextSize(std::to_string(h).c_str()).x/2,y-8+height -(height *(health /100))), ImGui::ColorConvertFloat4ToU32(ImVec4(1,1,1, 1)), std::to_string(h).c_str());
						ImGui::PopFont();
						}
                    	
					}

}
}
}
}
