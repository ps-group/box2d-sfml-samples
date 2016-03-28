#include <SFML/Graphics.hpp>
#include "Application.h"
#include "../scenes/PendulumScene.h"
#include "../scenes/CarScene.h"
#include <unistd.h>

int main()
{
    chdir("../../box2d-demos/resources");

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Box2D Demo", sf::Style::Titlebar | sf::Style::Close, settings);
    CApplication app(window);

    app.RegisterScene<CCarScene>();
    app.RegisterScene<CPendulumScene>();

    app.EnterLoop();

    return 0;
}
