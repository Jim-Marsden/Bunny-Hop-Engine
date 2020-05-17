#include "GameScene.hpp"
#include "Print_helper.hpp"
#include "Player.hpp"
#include "SystemEvent.hpp"

#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>
#include <algorithm>


#include <SFML/Graphics.hpp>
#include <chrono>

void Move_Player_Left(Player & player, bool is_down){
    if(is_down) player.AddSpeedX(-5);
    else player.AddSpeedX(5);


}
void Move_Player_Right(Player & player, bool is_down){

    if(is_down) player.AddSpeedX(5);
    else player.AddSpeedX(-5);
}

void Move_Player_Up(Player & player, bool is_down){

    std::cout << "Down!" << is_down << '\n';

}

void Move_Player_Down(Player & player, bool is_down){
    if(is_down) player.AddSpeedY(5);
    else player.AddSpeedY(-5);
}

void Move_Player_Jump(Player & player, bool is_down){
    if(is_down) player.AddSpeedY(-5);
    else player.AddSpeedY(5);
}



int main() {
    //boost::timer::auto_cpu_timer t;
    std::vector<std::vector<Entity>::iterator > cleanup;

    MT::TextureManager textureManager;

    MT::GameScene gameScene;
    auto entities = gameScene.LoadFromJson("./Scenes/TestScene.json",
            textureManager);

    std::cout << gameScene.Name() << '\n';

    Player player;
    player.setTexture(*(textureManager+="Scenes/Textures/default.png"));

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");
    SystemEvent systemEvent(window, player);
    window.setKeyRepeatEnabled(false);

    systemEvent.AddMoveLeft(Move_Player_Left);
    systemEvent.AddMoveRight(Move_Player_Right);
    systemEvent.AddMoveUp(Move_Player_Up);
    systemEvent.AddMoveDown(Move_Player_Down);
    systemEvent.AddMoveJump(Move_Player_Jump);

    auto started = std::chrono::high_resolution_clock::now();




    std::chrono::time_point<std::chrono::steady_clock> fpsTimer(std::chrono::steady_clock::now());
    std::chrono::duration<int32_t, std::ratio<1, 60>> FPS{};


    while(window.isOpen()){
        //boost::timer::auto_cpu_timer t;

        systemEvent.DoEvents();
        cleanup.clear();
        window.clear(sf::Color(0xaa, 0xaa, 0xaa));



;
            started = std::chrono::high_resolution_clock::now();
            for (auto const &bg : gameScene.DoParallax({0, 0}))
                do_draw(bg, window);

            for (auto const &element : gameScene.BackDecoration())
                do_draw(element, window);


            for (auto const &element : gameScene.FrontDecoration())
                do_draw(element, window);

            for (auto const &shape : gameScene.GetCollisionBoxes())
                do_draw(shape, window);

            for(auto const & item : entities)
                do_draw(item, window);

        if (std::chrono::duration_cast<std::chrono::duration<int32_t, std::ratio<1, 60>>>( std::chrono::steady_clock::now() - fpsTimer).count() >= 1) {
            fpsTimer = std::chrono::steady_clock::now();

            auto bad = player.isCollidingDown(gameScene.GetCollisionBoxes());
            player.DoGravity(!bad);
            if(bad){
                std::cout <<"colliding\n";
            }
            player.Move();
            window.setView(sf::View(static_cast<sf::Sprite>(player).getPosition(),
                                    {static_cast<float>(window.getSize().x),
                                     static_cast<float>(window.getSize().y)} ));


        for (auto iterator = entities.begin(); entities.end() != iterator; ++iterator) {
                //TODO Check if player is touching monster


                    auto bad = iterator->isColliding(gameScene.GetCollisionBoxes());
                    iterator->DoGravity(!bad);
                    iterator->Move();
                    if (bad) {
                        MT::deal_damage(*iterator, 1,
                                        [](Entity &entity1) { std::cout << entity1.GetHealth() << "is dead!\n"; });

                    }
                    //if(entity.isColliding(gameScene.GetCollisionBoxes()))std::cout << "can be const!\n";
                    if (iterator->GetHealth() < 1) {
                        cleanup.push_back(iterator);
                    }
                }

            }

            for (auto const &cleanup_i: cleanup) {
                entities.erase(cleanup_i);
            }


        do_draw(player, window);

        window.display();



    }
    return 0;
}
