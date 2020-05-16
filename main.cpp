#include "GameScene.h"
#include "Print_helper.hpp"

#include <iostream>
#include <boost/timer/timer.hpp>
#include <cmath>

#include <SFML/Graphics.hpp>

sf::Event process_events(sf::RenderWindow & window){
    sf::Event event{};
    while(window.pollEvent(event)){
        switch (event.type) {

            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::KeyPressed:
                break;
            case sf::Event::KeyReleased:
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseEntered:
                break;
            case sf::Event::MouseLeft:
                break;
            case sf::Event::JoystickButtonPressed:
                break;
            case sf::Event::JoystickButtonReleased:
                break;
            case sf::Event::JoystickMoved:
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::TouchBegan:
                break;
            case sf::Event::TouchMoved:
                break;
            case sf::Event::TouchEnded:
                break;
            case sf::Event::SensorChanged:
                break;
            case sf::Event::Count:
                break;
        }

    }

    return event;
}


int main() {
    //boost::timer::auto_cpu_timer t;

    MT::TextureManager textureManager;
    MT::GameScene gameScene;
    auto entities = gameScene.LoadFromJson("./Scenes/TestScene.json",
            textureManager);

    std::cout << gameScene.Name() << '\n';

    sf::RenderWindow window(
            sf::VideoMode(1900, 900),
            "Moonilight Trails~");

    while(window.isOpen()){
        //boost::timer::auto_cpu_timer t;

        process_events(window);
        window.clear(sf::Color::Blue);
        for(auto const & bg : gameScene.DoParallax({0, 0}))
            do_draw(bg, window);

        for(auto const & element : gameScene.BackDecoration())
            do_draw(element, window);


        for(auto const & element : gameScene.FrontDecoration())
            do_draw(element, window);

        for(auto const &shape : gameScene.GetCollisionBoxes())
            do_draw(shape, window);

        for(auto &entity : entities){
            entity.DoGravity(!entity.isColliding(gameScene.GetCollisionBoxes()));
            //if(entity.isColliding(gameScene.GetCollisionBoxes()))std::cout << "can be const!\n";
            do_draw(entity, window);
        }


        window.display();



    }
    return 0;
}
