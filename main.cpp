#include "GameScene.hpp"
#include "Print_helper.hpp"
#include "Player.hpp"
#include "SystemEvent.hpp"

#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <algorithm>


#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <chrono>

void Move_Player_Left(MT::Player & player, bool is_down){
    if(is_down) player.AddSpeedX(-5);
    else player.AddSpeedX(5);


}
void Move_Player_Right(MT::Player & player, bool is_down){

    if(is_down) player.AddSpeedX(5);
    else player.AddSpeedX(-5);
}

void Move_Player_Up(MT::Player & player, bool is_down){

    std::cout << "Down!" << is_down << '\n';

}

void Move_Player_Down(MT::Player & player, bool is_down){
    if(is_down) player.AddSpeedY(5);
    else player.AddSpeedY(-5);
}

void Move_Player_Jump(MT::Player & player, bool is_down){
    if(is_down) player.AddSpeedY(-5);
    else player.AddSpeedY(5);
}

std::string_view Do_Game_Update(std::string_view const & scene_File, MT::TextureManager & textureManager, sf::RenderWindow & window, MT::Player &player, MT::SystemEvent &systemEvent){
    uint_fast64_t frame_counter{};
    auto started = std::chrono::high_resolution_clock::now();



    MT::GameScene gameScene;

    auto entities = gameScene.LoadFromJson("./Scenes/TestScene.json",
                                           textureManager);


    std::chrono::time_point<std::chrono::steady_clock> fpsTimer(std::chrono::steady_clock::now());
    std::chrono::duration<int32_t, std::ratio<1, 60>> FPS{};

    while(gameScene.isActive() && window.isOpen()) {
        ++frame_counter;

        systemEvent.DoEvents();

        window.clear(sf::Color(0xaa, 0xaa, 0xaa));


        ;
        started = std::chrono::high_resolution_clock::now();
        for (auto const &bg : gameScene.DoParallax(player.GetSpeed()))
            MT::do_draw(bg, window);

        for (auto const &element : gameScene.BackDecoration())
            MT::do_draw(element, window);


        for (auto const &element : gameScene.FrontDecoration())
            MT::do_draw(element, window);

        for (auto const &shape : gameScene.GetCollisionBoxes())
            MT::do_draw(shape, window);

        for (auto const &item : entities)
            MT::do_draw(item, window);

        if (std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 60>>>(
                std::chrono::steady_clock::now() - fpsTimer).count() >= 1) {
            fpsTimer = std::chrono::steady_clock::now();

            auto bad = player.isColliding(gameScene.GetCollisionBoxes());
            player.DoGravity(!bad.bottom);


            player.Move();
            window.setView(sf::View(static_cast<sf::Sprite>(player).getPosition(),
                                    {static_cast<float>(window.getSize().x),
                                     static_cast<float>(window.getSize().y)}));


            for(auto  & entity : entities) {
                //TODO Check if player is touching monster


                auto bad_my = entity.isColliding(gameScene.GetCollisionBoxes()).bottom;
                //if(bad_my) MT::deal_damage(entity, 1000);

                entity.DoGravity(!bad_my);
                entity.Move();
                entity.DoAnimation(frame_counter);

            }

        }

        entities.erase( std::remove_if(entities.begin(), entities.end(),
                [](MT::Entity const & entity){return entity.GetHealth() < 1;}), entities.end());

         do_draw(player, window);

        window.display();
    }
    return " ";

}

int main(int argc, char ** argv) {
    //boost::timer::auto_cpu_timer t;

    MT::TextureManager textureManager;

    MT::GameScene gameScene;


    std::cout << gameScene.Name() << '\n';

    MT::Player player;
    player.setTexture(*(textureManager+="Scenes/Textures/default.png"));

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");
    MT::SystemEvent systemEvent(window, player);
    window.setKeyRepeatEnabled(false);

    window.setFramerateLimit(60);

    systemEvent.AddMoveLeft(Move_Player_Left);
    systemEvent.AddMoveRight(Move_Player_Right);
    systemEvent.AddMoveUp(Move_Player_Up);
    systemEvent.AddMoveDown(Move_Player_Down);
    systemEvent.AddMoveJump(Move_Player_Jump);


    std::string_view file_path = "./Scenes/TestScene.json";


    while(window.isOpen()){
        file_path = Do_Game_Update(file_path, textureManager, window, player, systemEvent);
    }
    return 0;
}
