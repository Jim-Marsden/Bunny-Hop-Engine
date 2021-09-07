#include "bhe_core/Json_Parser.hpp"
#include "bhe_core/Print_helper.hpp"
#include "bhe_core/GameScene.hpp"
#include "bhe_core/Pipeline.hpp"
#include "bhe_core/SystemEvent.hpp"

#include <algorithm>
#include <iostream>

#include <chrono>


std::string_view do_game_update(std::string_view const &Scene_file,
                                bhe::textureManager &Texture_manager, sf::RenderWindow &Window, bhe::player &Player,
                                bhe::SystemEvent &System_event) {

    uint_fast64_t frame_counter{};
    auto started = std::chrono::high_resolution_clock::now();

    bhe::GameScene game_scene;

    auto entities = game_scene.load_from_json("./Scenes/TestScene.json",
			Texture_manager);

    bhe::Entity::collisionDirection collision_direction{};

    std::chrono::time_point<std::chrono::steady_clock> fps_timer(std::chrono::steady_clock::now());
    std::chrono::duration<int32_t, std::ratio<1, 60>> fps{};

    auto time_start_loop = std::chrono::steady_clock::now();
    auto movement_time_point = std::chrono::steady_clock::now();

    std::chrono::duration<double> time_check = time_start_loop - movement_time_point;

    while (game_scene.is_active() && Window.isOpen()) {
        //boost::timer::auto_cpu_timer timer;

        time_start_loop = std::chrono::steady_clock::now();

        //std::cout << std::chrono::duration_cast<std::chrono::microseconds >(time_check).count() << '\n';


        ++frame_counter;

		System_event.do_events();

        Window.clear(sf::Color(0xaa, 0xaa, 0xaa));


        //started = std::chrono::high_resolution_clock::now();
        Window.setView(sf::View(static_cast<sf::Sprite>(Player).getPosition(),
                                {static_cast<float>(Window.getSize().x),
                                 static_cast<float>(Window.getSize().y)}));

        for (auto const &bg : game_scene.do_parallax(Player.get_pos()))
			bhe::draw(bg, Window);

        for (auto const &element : game_scene.back_decoration())
			bhe::draw(element, Window);

        for (auto const &element : game_scene.front_decoration())
			bhe::draw(element, Window);

        for (auto const &shape : game_scene.get_collision_boxes())
			bhe::draw(shape, Window);

        auto update_lambda = [&game_scene, &time_check](bhe::Entity &e) {
            if (auto const &[collision_direction, exit_code, exit_status] = e
                        .is_colliding(game_scene.get_collision_boxes());
                exit_code && exit_status == bhe::ReturnStatusCode::Normal) {
				e.do_gravity(collision_direction.bottom);
				e.move(std::chrono::duration_cast<std::chrono::microseconds>(time_check));
				e.do_animation(std::chrono::duration_cast<std::chrono::microseconds>(time_check));
            }
        };
        std::for_each(entities.begin(), entities.end(), update_lambda);

        update_lambda(Player);

        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                      [](bhe::Entity const &Entity) { return Entity.get_health().value < 1; }),
                       entities.end());


        //TODO base game time on last loop so everything will be more even.


        for (auto &entity : entities) {
            DoDraw(entity, Window);
        }
		do_draw(Player, Window);

        Window.display();
        time_check = std::chrono::steady_clock::now() - time_start_loop;
        //movement_time_point = std::chrono::steady_clock::now();//time_start_loop;
        //time_start_loop = std::chrono::system_clock::now();
    }
    return " ";
}

int main(int Argc, char **Argv) {

    auto return_value{0};

    bhe::textureManager texture_manager;

    bhe::GameScene game_scene;

    std::cout << game_scene.get_name() << '\n';

    bhe::player player = bhe::json_parsers::parse_player("Player/Player.json", texture_manager);

    std::function<bhe::SystemEvent::KeyboardFunctionType> move_player_right = [&player](bool Is_down) {
		player.move_right(Is_down);
    };

    std::function<bhe::SystemEvent::KeyboardFunctionType> move_player_left = [&player](bool Is_down) {
		player.move_left(Is_down);
    };

    std::function<bhe::SystemEvent::KeyboardFunctionType> move_player_down = [&player](bool Is_down) {
		player.move_down(Is_down);
    };

    std::function<bhe::SystemEvent::KeyboardFunctionType> move_player_jump = [&player](bool Is_down) {
        player.do_jump(Is_down);
    };

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");
    bhe::SystemEvent system_event(window);
    window.setKeyRepeatEnabled(false);

    //window.setFramerateLimit(60);

	system_event.add_move_left(move_player_left);
	system_event.add_move_right(move_player_right);
	system_event.add_move_down(move_player_down);
	system_event.add_move_jump(move_player_jump);

    std::string_view file_path = "./Scenes/TestScene.json";

    while (window.isOpen()) {
        file_path = do_game_update(file_path, texture_manager, window, player, system_event);
    }
    return return_value;
}
