#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <SFML/Graphics.hpp>

#include "global.hpp"
#include "pendulum.hpp"

int main() {

    std::cout << std::endl;

    // ========== //

    sf::Clock clock;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGHT}),
        "pendulum", 
        sf::Style::Default, 
        sf::State::Windowed,
        settings
    );
    window.setVerticalSyncEnabled(false);

    const sf::Font font("fonts/Consolas.ttf");

    sf::Text fpsText(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color(255, 255, 255, 100));
    fpsText.setPosition({10, 10});

    sf::Text deltaTimeText(font);
    deltaTimeText.setCharacterSize(20);
    deltaTimeText.setFillColor(sf::Color(255, 255, 255, 100));
    deltaTimeText.setPosition({10, 30});

    sf::Vector2f anchorPos = {WIDTH / 2, (HEIGHT / 2) - 100};
    float length = 250;
    float mass = 10;

    Pendulum pendulum(anchorPos, length, mass);

    int frameCounter = 0;
    const int updateEvery = 2500;

    while (window.isOpen()) {

        float dt = clock.restart().asSeconds();

        frameCounter++;
        if (frameCounter >= updateEvery) {

            frameCounter = 0;

            std::ostringstream ss;
            ss << "fps: " << std::fixed << std::setprecision(0) << 1 / dt;
            fpsText.setString(ss.str());

            ss.str("");
            ss.clear();

            ss << "dt: " << std::fixed << std::setprecision(2) << (dt * 1000) << "ms";
            deltaTimeText.setString(ss.str());

        }

        if (dt > 0.002) dt = 0.002;

        while (const std::optional event = window.pollEvent()) {

            if (event->is<sf::Event::Closed>())
                window.close();

        }

        pendulum.update(dt);

        window.clear(sf::Color(20, 20, 20));

            pendulum.render(&window);
            
            window.draw(fpsText);
            window.draw(deltaTimeText);

        window.display();
    }

    // ========== //

    std::cout << std::endl;
    return 0;

}