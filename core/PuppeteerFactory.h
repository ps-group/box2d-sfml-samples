#pragma once

#include "IPhysicsWorld.h"
#include "Puppeteer.h"
#include "Joint.h"

struct SPuppeteerOptions
{
public:
    /// Коэффициент силы трения, обычно в диапазоне [0,1].
    float32 friction = 0;

    /// Коэффициент упругости тела (эластичность), обычно в диапазоне [0,1].
    float32 restitution = 0;

    /// Плотность, обычно в кг/м^2.
    float32 density = 1;

    /// Сенсорные (призрачные) формы получают информацию о контактах,
    /// но никогда не влияют на другие тела и не отталкивают их.
    bool isSensor = false;

    /// Статичные тела не двигаются.
    bool isStatic = false;
};

class CPuppeteerFactory
{
public:
    CPuppeteerFactory(IPhysicsWorld & world);

    CPuppeteerUniquePtr Make(sf::CircleShape &shape, SPuppeteerOptions const& options = SPuppeteerOptions());
    CPuppeteerUniquePtr Make(sf::RectangleShape & shape, SPuppeteerOptions const& options = SPuppeteerOptions());

    CJointUniquePtr MakeRope(CPuppeteer &a, CPuppeteer &b, float maxLength);

private:
    b2Body *CreateBody(sf::Transformable const& entity, bool isStatic, bool isBullet);
    void AddFixture(b2Shape const &shape, b2Body & body, SPuppeteerOptions const& options);
    CPuppeteerUniquePtr Finalize(sf::Transformable & entity, b2Body * body);

    IPhysicsWorld & m_world;
};
