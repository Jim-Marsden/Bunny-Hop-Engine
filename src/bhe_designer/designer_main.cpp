//
// Created by Jim Marsden on 6/6/20.
//
#include "DesignerWindow.h"
#include "scene_designer.hpp"

#include "designer_menu.hpp"
#include "designer_pallet.hpp"

#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>

//Do I really want to keep this style of ugly gui interface? All the objects, etc.?
/* TODO:
 * 1) get designer mode setup, 100%
 * 2) Finish a minimum save/load
 * 3) have default designer
 */

int main()
{
	sf::RenderWindow window{sf::VideoMode{900, 900}, "Bunny Hop Engine: Designer"};
	ImGui::SFML::Init(window);

	sf::Event event{};

	bhe::designer::menu_struct menu{};
	sf::Clock deltaClock{};
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type==sf::Event::Closed)
				window.close();
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		menu = bhe::designer::generate_menu(menu);
		if(menu.exit){window.close();}
		if (menu.demo){ImGui::ShowDemoWindow();}
		if(menu.designer_pallet){bhe::designer::designer_pallet();}
		ImGui::Begin("Hello, world!");
		if (ImGui::Button("Look at this pretty button")) {
			std::cout << "pretty button pressed!";
		}
		ImGui::End();
		window.clear();
		ImGui::SFML::Render(window);
		window.display();
	}

}
