#include <SFML/Graphics.hpp>
#include "Application.h"
#include "../scenes/PendulumScene.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D Demo", sf::Style::Titlebar | sf::Style::Close);
    CApplication app(window);
    app.RegisterScene<CPendulumScene>();

    app.EnterLoop();

    return 0;
}
