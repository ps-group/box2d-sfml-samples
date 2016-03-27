#include "PendulumScene.h"
#include "../core/PuppeteerFactory.h"

CPendulumScene::CPendulumScene()
{
    m_weight.setRadius(25);
    m_weight.setPosition(200, 300);
    m_weight.setFillColor(sf::Color::Red);

    m_mount.setPosition(300, 100);
    m_mount.setRadius(5);
    m_mount.setFillColor(sf::Color::White);

    CPuppeteerFactory factory(GetWorld());

    m_weightPuppeteer = factory.Make(m_weight);
    SPuppeteerOptions options;
    options.isStatic = true;
    m_mountPuppeteer = factory.Make(m_mount, options);
    m_rope = factory.MakeRope(*m_weightPuppeteer, *m_mountPuppeteer, 100);
}

void CPendulumScene::OnEvent(const sf::Event &event)
{
    (void)event;
}

void CPendulumScene::OnDraw(sf::RenderTarget &target)
{
    sf::RenderStates states = sf::RenderStates::Default;
    target.draw(m_mount, states);
    target.draw(m_weight, states);
}
