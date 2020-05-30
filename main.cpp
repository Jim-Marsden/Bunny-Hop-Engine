#include "gameScene.hpp"
#include "Print_helper.hpp"
#include "player.hpp"
#include "SystemEvent.hpp"
#include "Json_Parser.hpp"

#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <algorithm>


#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <chrono>

void move_player_left(mt::player &Player, bool Is_down) {
    Player.MoveLeft(Is_down);


}

void move_player_right(mt::player &Player, bool Is_down) {

    Player.MoveRight(Is_down);

}

void move_player_up(mt::player &Player, bool Is_down) {
    //Player.MoveDown(Is_down);

}

void move_player_down(mt::player &Player, bool Is_down) {
    Player.MoveDown(Is_down);
}

void move_player_jump(mt::player &Player, bool Is_down) {
    Player.DoJump(Is_down);
}

std::string_view do_game_update(std::string_view const &Scene_file,
                                mt::textureManager &Texture_manager, sf::RenderWindow &Window, mt::player &Player,
                                mt::SystemEvent &System_event) {
    uint_fast64_t frame_counter{};
    auto started = std::chrono::high_resolution_clock::now();

    mt::gameScene game_scene;

    auto entities = game_scene.LoadFromJson("./Scenes/TestScene.json",
                                            Texture_manager);


    std::chrono::time_point<std::chrono::steady_clock> fps_timer(std::chrono::steady_clock::now());
    std::chrono::duration<int32_t, std::ratio<1, 60>> fps{};

    while (game_scene.IsActive() && Window.isOpen()) {
        ++frame_counter;

        System_event.DoEvents();

        Window.clear(sf::Color(0xaa, 0xaa, 0xaa));


        started = std::chrono::high_resolution_clock::now();
        for (auto const &bg : game_scene.DoParallax(Player.GetPos()))
            mt::do_draw(bg, Window);

        for (auto const &element : game_scene.BackDecoration())
            mt::do_draw(element, Window);


        for (auto const &element : game_scene.FrontDecoration())
            mt::do_draw(element, Window);

        for (auto const &shape : game_scene.GetCollisionBoxes())
            mt::do_draw(shape, Window);

        for (auto const &item : entities)
            mt::do_draw(item, Window);

        if (std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 60>>>(
                std::chrono::steady_clock::now() - fps_timer).count() >= 1) {
            fps_timer = std::chrono::steady_clock::now();

            auto bad = Player.IsColliding(game_scene.GetCollisionBoxes());
            Player.DoGravity(!bad.bottom);

            Player.Move();
            Player.DoAnimation();
            Window.setView(sf::View(static_cast<sf::Sprite>(Player).getPosition(),
                                    {static_cast<float>(Window.getSize().x),
                                     static_cast<float>(Window.getSize().y)}));


            for (auto &entity : entities) {
                //TODO Check if player is touching monster


                auto bad_my = entity.IsColliding(game_scene.GetCollisionBoxes()).bottom;
                //if(bad_my) mt::deal_damage(entity, 1000);

                entity.DoGravity(!bad_my);
                entity.Move();
                entity.DoAnimation();

            }

        }

        entities.erase(std::remove_if(entities.begin(), entities.end(),
                                      [](mt::entity const &Entity) { return Entity.GetHealth() < 1; }), entities.end());

        do_draw(Player, Window);

        Window.display();
    }
    return " ";

}

int main() {
    //boost::timer::auto_cpu_timer t;

    mt::textureManager texture_manager;

    mt::gameScene game_scene;


    std::cout << game_scene.Name() << '\n';

    mt::player player = mt::json_parsers::parse_player("Player/Player.json", texture_manager);

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");
    mt::SystemEvent system_event(window, player);
    window.setKeyRepeatEnabled(false);

    window.setFramerateLimit(60);

    system_event.AddMoveLeft(move_player_left);
    system_event.AddMoveRight(move_player_right);
    system_event.AddMoveUp(move_player_up);
    system_event.AddMoveDown(move_player_down);
    system_event.AddMoveJump(move_player_jump);


    std::string_view file_path = "./Scenes/TestScene.json";


    while (window.isOpen()) {
        file_path = do_game_update(file_path, texture_manager, window, player, system_event);
    }
    return 0;
}
