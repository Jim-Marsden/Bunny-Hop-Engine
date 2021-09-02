//
// Created by james on 9/1/2021.
//

#include "designer_pallet.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

void bhe::designer::designer_pallet()
{
	ImGui::Begin("Designer Pallet");
	if(ImGui::CollapsingHeader("Placeholder 1")) {
		ImGui::Text("placeholder :c");
	}
	if(ImGui::CollapsingHeader("Placeholder 2")) {
		ImGui::Text("another placeholder :c");
	}
//	ImGui::LabelText("hello!", nullptr);
	ImGui::End();
}
