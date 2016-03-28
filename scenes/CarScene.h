#pragma once
#include "../core/AbstractScene.h"
#include "../core/Puppeteer.h"

class CCarUnit
        : public sf::Drawable
        , public sf::Transformable
{
public:
    CCarUnit();

    void InitPuppeteer(CPuppeteer & puppeteer);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    sf::Texture m_bodyTexture;
    sf::Sprite m_body;
    sf::CircleShape m_frontWheel;
    sf::CircleShape m_rearWheel;
};

class CCarScene : public CAbstractScene
{
public:
    CCarScene();
    ~CCarScene();

    void OnEvent(const sf::Event &event) override;
    void OnDraw(sf::RenderTarget &target) override;

private:
    CCarUnit m_car;
    std::vector<sf::Vertex> m_terrain;
    CPuppeteerUniquePtr m_carPuppeteer;
};
