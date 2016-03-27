#include "Application.h"
#include "../scenes/PendulumScene.h"

CApplication::CApplication(sf::RenderWindow &window)
    : m_window(window)
{
}

void CApplication::EnterLoop()
{
    auto factory = m_sceneFactories[0];
    m_scene = factory();

    sf::Clock clock;
    while (m_window.isOpen())
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return;
            }
            // TODO: switch scenes.
            m_scene->OnEvent(event);
        }

        sf::Time time = clock.restart();
        m_scene->OnUpdate(time.asSeconds());

        m_window.clear(sf::Color::Black);
        m_scene->OnDraw(m_window);
        m_window.display();
    }
}
