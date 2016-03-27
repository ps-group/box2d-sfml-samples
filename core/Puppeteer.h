#pragma once

#include "IPuppeteer.h"
#include "IPhysicsWorld.h"
#include <boost/noncopyable.hpp>

class CPuppeteer : public IPuppeteer, private boost::noncopyable
{
public:
    CPuppeteer(sf::Transformable & puppet, IPhysicsWorld &world, b2Body *body);
    ~CPuppeteer();

    b2Body *GetBody();

protected:
    void OnBeforeTick(float deltaTime) override;
    void OnAfterTick() override;
    void OnBeginContact(const SPhysicsContact &contact) override;
    void OnEndContact(const SPhysicsContact &contact) override;

private:
    sf::Transformable &m_puppet;
    IPhysicsWorld &m_world;
    b2Body *m_body;
};

using CPuppeteerUniquePtr = std::unique_ptr<CPuppeteer>;
