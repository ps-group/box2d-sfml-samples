#pragma once

#include "IPhysicsWorld.h"
#include "Puppeteer.h"
#include "Joint.h"

class CPuppeteerFactory
{
public:
    CPuppeteerFactory(IPhysicsWorld & world);

    void MakeLandscape(std::vector<sf::Vector2f> const& points);
    CPuppeteerUniquePtr MakeDynamic(sf::Transformable &entity);
    CPuppeteerUniquePtr MakeDynamic(sf::Sprite &sprite, SMaterial const& mat);
    CPuppeteerUniquePtr MakeStatic(sf::CircleShape &shape, SMaterial const& mat);
    CPuppeteerUniquePtr MakeDynamic(sf::CircleShape &shape, SMaterial const& mat);
    CPuppeteerUniquePtr MakeDynamic(sf::RectangleShape & shape, SMaterial const& mat);
    CJointUniquePtr MakeRope(CPuppeteer &a, CPuppeteer &b, float maxLength);

private:
    b2Body *CreateBody(sf::Transformable const& entity, bool isStatic, bool isBullet);
    void AddFixture(b2Shape const &shape, b2Body & body, SMaterial const& options);
    CPuppeteerUniquePtr MakePuppeteer(sf::Transformable & entity, b2Body * body);

    IPhysicsWorld & m_world;
};
