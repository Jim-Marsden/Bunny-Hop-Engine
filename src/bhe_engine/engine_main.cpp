#include "bhe_core/gameScene.hpp"
#include "bhe_core/Print_helper.hpp"
#include "bhe_core/player.hpp"
#include "bhe_core/SystemEvent.hpp"
#include "bhe_core/Json_Parser.hpp"
#include "bhe_core/pipeline.hpp"


#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <algorithm>



#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <chrono>

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS
#define CATCH_CONFIG_RUNNER

#include <catch2/catch.hpp>

#endif

void move_player_right(bhe::player &Player, bool Is_down) {

    Player.MoveRight(Is_down);

}

void move_player_left(bhe::player &Player, bool Is_down) {

    Player.MoveLeft(Is_down);

}

void move_player_down(bhe::player &Player, bool Is_down) {
    Player.MoveDown(Is_down);
}

void move_player_jump(bhe::player &Player, bool Is_down) {
    Player.DoJump(Is_down);
}

std::string_view do_game_update(std::string_view const &Scene_file,
                                bhe::textureManager &Texture_manager, sf::RenderWindow &Window, bhe::player &Player,
                                bhe::SystemEvent &System_event) {
    uint_fast64_t frame_counter{};
    auto started = std::chrono::high_resolution_clock::now();

    bhe::gameScene game_scene;

    auto entities = game_scene.LoadFromJson("./Scenes/TestScene.json",
                                            Texture_manager);

    bhe::entity::collisionDirection collision_direction{};


    std::chrono::time_point<std::chrono::steady_clock> fps_timer(std::chrono::steady_clock::now());
    std::chrono::duration<int32_t, std::ratio<1, 60>> fps{};

    while (game_scene.IsActive() && Window.isOpen()) {


        ++frame_counter;

        System_event.DoEvents();

        Window.clear(sf::Color(0xaa, 0xaa, 0xaa));


        started = std::chrono::high_resolution_clock::now();
        for (auto const &bg : game_scene.DoParallax(Player.GetPos()))
            bhe::do_draw(bg, Window);

        for (auto const &element : game_scene.BackDecoration())
            bhe::do_draw(element, Window);


        for (auto const &element : game_scene.FrontDecoration())
            bhe::do_draw(element, Window);

        for (auto const &shape : game_scene.GetCollisionBoxes())
            bhe::do_draw(shape, Window);

        //for (auto const &item : entities)
        //bhe::do_draw(item, Window);

        if (std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 60>>>(
                std::chrono::steady_clock::now() - fps_timer).count() >= 1) {
            fps_timer = std::chrono::steady_clock::now();
            { // Explisit scope
                bhe::pipeline<decltype(Player)> loop_pipeline(Player);

                loop_pipeline | [&collision_direction, &game_scene](bhe::player &e) {
                    collision_direction = e.IsColliding(game_scene.GetCollisionBoxes());
                }
                | [&collision_direction](bhe::player &e) { e.DoGravity(collision_direction.bottom); }
                | [](bhe::player &e) { e.Move(); }
                | [](bhe::player &e) { e.DoAnimation(); };

            }
            Window.setView(sf::View(static_cast<sf::Sprite>(Player).getPosition(),
                                    {static_cast<float>(Window.getSize().x),
                                     static_cast<float>(Window.getSize().y)}));


            for (auto &entity : entities) {

                bhe::pipeline<decltype(entity)> loop_pipeline(entity);
                loop_pipeline | [&collision_direction, &game_scene](bhe::entity &e) {
                    collision_direction = e.IsColliding(game_scene.GetCollisionBoxes());
                }
                | [&collision_direction](bhe::entity &e) { e.DoGravity(collision_direction.bottom); }
                | [](bhe::entity &e) { e.Move(); }
                | [](bhe::entity &e) { e.DoAnimation(); };
            }

        }

        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                      [](bhe::entity const &Entity) { return Entity.GetHealth() < 1; }),
                       entities.end());


        for (auto &entity : entities) {
            do_draw(entity, Window);
        }
        do_draw(Player, Window);

        Window.display();
    }
    return " ";

}

int main(int Argc, char **Argv) {
    auto return_value{0};

#ifdef MOON_LIGHTTRAILS_CMAKE_OPTION_DO_TESTS
    return_value = Catch::Session().run(Argc, Argv);
#endif
    //boost::timer::auto_cpu_timer t;

    bhe::textureManager texture_manager;

    bhe::gameScene game_scene;


    std::cout << game_scene.Name() << '\n';

    bhe::player player = bhe::json_parsers::parse_player("Player/Player.json", texture_manager);

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");
    bhe::SystemEvent system_event(window, player);
    window.setKeyRepeatEnabled(false);

    window.setFramerateLimit(60);

    system_event.AddMoveLeft(move_player_left);
    system_event.AddMoveRight(move_player_right);
    system_event.AddMoveDown(move_player_down);
    system_event.AddMoveJump(move_player_jump);


    std::string_view file_path = "./Scenes/TestScene.json";


    while (window.isOpen()) {
        file_path = do_game_update(file_path, texture_manager, window, player, system_event);
    }
    return return_value;
}
