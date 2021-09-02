//
// Created by james on 8/23/2021.
//

#include <imgui.h>
#include "designer_menu.hpp"

bhe::designer::menu_struct bhe::designer::generate_menu(const bhe::designer::menu_struct& menu)
{
	bhe::designer::menu_struct result{menu};
	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			result.new_file = ImGui::MenuItem("New");
			result.exit = ImGui::MenuItem("Exit");
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Tools")) {
			result.settings = ImGui::MenuItem("Settings");
			result.about =  ImGui::MenuItem("About");
			result.designer_pallet = ImGui::MenuItem("Pallet");
			result.demo = ImGui::MenuItem("Demo");
			ImGui::EndMenu();
		}

		ImGui::EndMainMenuBar();
	}
	return result;
}
