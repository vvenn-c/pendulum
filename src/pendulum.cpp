#include "pendulum.hpp"

void Pendulum::update(float dt) {

    acc = calcAcc(pos, vel);
    vel += acc * dt;
    pos += vel * dt;

}

void Pendulum::render(sf::RenderWindow *window) {

    sf::Vertex line[] = {
        {anchor, sf::Color::White},
        {pos, sf::Color::White}
    };

    sf::CircleShape c1;
    c1.setRadius(5);
    c1.setPosition({anchor.x - c1.getRadius(), anchor.y - c1.getRadius()});

    bob.setPosition({pos.x - r, pos.y - r});

    window->draw(bob);
    window->draw(line, 2, sf::PrimitiveType::Lines);
    window->draw(c1);

}

sf::Vector2f Pendulum::calcAcc(sf::Vector2f pos, sf::Vector2f vel) {

    sf::Vector2f Fg = {0, 200.f * mass}; // force due to gravity

    float dist = sf::Vector2f(pos - anchor).length();
    float disp = dist - length;

    float k = 8000; // coefficient of stiffness
    sf::Vector2f Fs = pos - anchor; // spring force
    Fs = Fs.normalized();
    Fs *= -k * disp;

    float c = 2 * sqrt(k * mass); // coefficient of damping
    sf::Vector2f Fd = -c * vel.projectedOnto(anchor - pos);

    return (Fg + Fs + Fd) / mass;

}

float Pendulum::KE() {

    return 0.5 * mass * vel.lengthSquared();

}

float Pendulum::PE() {

    return mass * 200 * ((anchor.y + length) - pos.y);

}