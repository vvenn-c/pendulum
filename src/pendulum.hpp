#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>

#include "global.hpp"

class Pendulum {

    private:

        sf::Vector2f anchor;

        float length; // rod length
        float mass; // bob mass
        float r = 10; // bob radius

        sf::Vector2f pos;
        sf::Vector2f vel;
        sf::Vector2f acc;

        sf::CircleShape bob;
        

    public:

        Pendulum(sf::Vector2f a, float l, float m) : anchor(a), length(l), mass(m) {

            sf::Vector2f initAngle = {1, 0.25};
            initAngle = initAngle.normalized() * length;

            pos = anchor + initAngle;

            bob.setRadius(r);
            bob.setFillColor(sf::Color::White);

        }

        void update(float dt);
        void render(sf::RenderWindow *window);

        sf::Vector2f calcAcc(sf::Vector2f pos, sf::Vector2f vel);

        float KE();
        float PE();

};