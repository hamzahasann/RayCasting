#include<bits/stdc++.h>
using namespace std;

#include<chrono>
#include<fstream>
#include<SFML/Graphics.hpp>
#include "constants.cpp"
#include "map.cpp"
#include "player.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT),"NoName");
    sf::RenderWindow window2(sf::VideoMode(WIDTH,HEIGHT),"3D");
    window.setFramerateLimit(FRAMERATE);
    window2.setFramerateLimit(FRAMERATE);
    Map map;
    Player p(400,400-205,0,5,5,&map);
    while(window.isOpen()){

        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
                window2.close();
            }
        }
        sf::Event event2;
        while(window2.pollEvent(event2)){
            if(event2.type==sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                window.close();
                window2.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            p.turnACW();
        }if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            p.turnCW();
        }if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            p.moveF();
        }if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            p.moveB();
        }
        window.clear();
        window2.clear();
        // p.draw(window2);
        map.draw(window);
        
        p.castRays(window,window2);
        // p.castRays(window2);
        // map.draw(window2);
        p.draw(window);

        window.display();
        window2.display();
    }
}