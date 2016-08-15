#include <SFML/Graphics.hpp>
#include "game.h"
#include <thread>
#include <chrono>

using namespace sf;

int main(){
    RenderWindow window(VideoMode(320, 320), "SNAKE");
    window.setKeyRepeatEnabled(false); // para processar a mudança de direção só uma vez
    window.setFramerateLimit(4);
    Game game(window);
    // CircleShape shape(100.f);
    // shape.setFillColor(Color::Green);
    Event event;
    while (window.isOpen()){
        if(game.status == INGAME){
            while (window.pollEvent(event)){
                if (event.type == Event::Closed){
                    window.close();
                } else if (event.type == Event::KeyPressed){
                    switch(event.key.code){
                        case sf::Keyboard::Up:
                            game.setDir(UP);
                            break;
                        case sf::Keyboard::Down:
                            game.setDir(DOWN);
                            break;
                        case sf::Keyboard::Left:
                            game.setDir(LEFT);
                            break;
                        case sf::Keyboard::Right:
                            game.setDir(RIGHT);
                            break;
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                    }
    
                }
    
            }
            window.clear(sf::Color::Black); // pode ser vazio também
            game.updateAll();
            game.drawAll();
            
            //window.draw(shape);
            window.display();
        } else if (game.status == GAME_OVER){
            // while (window.pollEvent(event)){
            //     if (event.type == Event::Closed){
            //         window.close();
            //     } else if (event.type == Event::KeyPressed){
            //         switch(event.key.code){
            //             case sf::Keyboard::Escape:
            //                 window.close();
            //                 break;
            //         }
            //     }
            // }
            sf::Text text;
            text.setFont(game.mainFont); // font is a sf::Font
            text.setString("Game Over");
            text.setCharacterSize(48); // in pixels, not points!
            text.setColor(sf::Color::Red);
            text.setStyle(sf::Text::Bold);
            text.setPosition(window.getSize().x/2-100, window.getSize().y/2-20);
            window.draw(text);
            window.display();
            std::this_thread::sleep_for(std::chrono::seconds(3));
            game.restart();
        }
    }

    return 0;
}
