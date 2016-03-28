#include "PendulumScene.h"
#include "../core/PuppeteerFactory.h"

CPendulumScene::CPendulumScene()
{
    m_weight.setRadius(25);
    m_weight.setPosition(150, 500);
    m_weight.setOrigin(25, 25);
    m_weight.setFillColor(sf::Color::Red);

    m_mount.setPosition(400, 100);
    m_mount.setRadius(5);
    m_mount.setOrigin(5, 5);
    m_mount.setFillColor(sf::Color::White);

    CPuppeteerFactory factory(GetWorld());
    SMaterial mat;
    mat.density = 100;

    m_weightPuppeteer = factory.MakeDynamic(m_weight, mat);
    m_mountPuppeteer = factory.MakeStatic(m_mount, mat);
    m_rope = factory.MakeRope(*m_weightPuppeteer, *m_mountPuppeteer, 500);
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

    /// Чтобы включить отладочную отрисовку, достаточно раскоментировать код ниже.
//    CAbstractScene::OnDraw(target);
}
