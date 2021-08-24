//
// Created by Jim Marsden on 6/6/20.
//
#include "DesignerWindow.h"
#include "scene_designer.hpp"

#include "designer_menu.hpp"

#include <imgui.h>
#include <imgui-SFML.h>

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

[[deprecated]] int main_old()
{
	auto c{0};
	sf::RenderWindow sf_window{sf::VideoMode{500, 500}, "Bunny Hope Engine: Designer"};
	tgui::Gui gui{sf_window};
//
	DesignerWindow window(sf_window, gui);

	bhe::designer::gui_modes mode_1{.mode_name{L"!designer \U0001f98a!"}, .panel{tgui::Panel::create()}};
	auto mode_2{bhe::designer::create_scene_designer()};

	auto l = tgui::Label::create("stuff, stuff, stuff, more stuff!");
	l->setAutoSize(true);
	l->setPosition(0, 40);
	mode_1.panel->add(l);

//    window.add_mode(bhe::designer::create_scene_designer());

	window.add_mode(mode_1);
	window.add_mode(mode_2);
	window.run();

	return {};
}