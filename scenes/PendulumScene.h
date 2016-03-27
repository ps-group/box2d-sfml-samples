#pragma once

#include "../core/Puppeteer.h"
#include "../core/Joint.h"
#include "../core/AbstractScene.h"

class CPendulumScene : public CAbstractScene
{
public:
    CPendulumScene();

    void OnEvent(const sf::Event &event) override;
    void OnDraw(sf::RenderTarget &target) override;

private:
    sf::CircleShape m_weight;
    sf::CircleShape m_mount;
    CPuppeteerUniquePtr m_weightPuppeteer;
    CPuppeteerUniquePtr m_mountPuppeteer;
    CJointUniquePtr m_rope;
};
