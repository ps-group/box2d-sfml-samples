#include <SFML/Graphics.hpp>
#include "core/Application.h"
#include "scenes/PendulumScene.h"
#include "scenes/CarScene.h"

#ifdef __linux__
#include <unistd.h>
#endif

int main()
{
#ifdef __linux__
    chdir("../../box2d-demos/resources");
#endif

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(1200, 800), "Box2D Demo", sf::Style::Titlebar | sf::Style::Close, settings);
    CApplication app(window);

    app.RegisterScene<CCarScene>();
    app.RegisterScene<CPendulumScene>();

    app.EnterLoop();

    return 0;
}
