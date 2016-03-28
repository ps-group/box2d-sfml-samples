#pragma once

#include "IPuppeteer.h"
#include "IPhysicsWorld.h"
#include <boost/noncopyable.hpp>

struct SMaterial
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
};

class CPuppeteer : public IPuppeteer, private boost::noncopyable
{
public:
    CPuppeteer(sf::Transformable & puppet, IPhysicsWorld &world, b2Body *body);
    ~CPuppeteer();

    b2Body *GetBody();
    void AddBox(const sf::FloatRect &bounds, const SMaterial &mat);
    void AddCircle(const sf::Vector2f &position, float radius, const SMaterial &mat);

protected:
    void OnBeforeTick(float deltaTime) override;
    void OnAfterTick() override;
    void OnBeginContact(const SPhysicsContact &contact) override;
    void OnEndContact(const SPhysicsContact &contact) override;

    void AddFixture(const b2Shape &shape, const SMaterial &mat);

private:
    sf::Transformable &m_puppet;
    IPhysicsWorld &m_world;
    b2Body *m_body;
};

using CPuppeteerUniquePtr = std::unique_ptr<CPuppeteer>;
