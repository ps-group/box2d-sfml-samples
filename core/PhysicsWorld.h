#pragma once

#include "IPhysicsWorld.h"
#include "IPuppeteer.h"
#include <functional>

class CPhysicsWorld : public IPhysicsWorld
{
public:
    CPhysicsWorld();
    ~CPhysicsWorld();

    void Tick(float deltaTime);

protected:
    b2Body *CreateBody(const b2BodyDef &bodyDef) const override;
    b2Joint *CreateJoint(const b2JointDef &jointDef) const override;
    void DeleteBodyLater(b2Body *body) override;

    sf::Vector2f GetScreenPosition(b2Body *body) const override;
    float GetScreenRotation(b2Body *body) const override;
    b2Vec2 GetPhysicsPosition(const sf::Transformable &entity)const override;
    float GetPhysicsRotation(const sf::Transformable &entity)const override;
    float ScaleToPhysics(float size)const override;
    b2Vec2 ScaleToPhysics(sf::Vector2f const& size)const override;

private:
    void Init();
    void CollectGarbage();
    void DoForeachPuppeteer(std::function<void(IPuppeteer &)> const& func);

    const float m_pixelsPerMeter;
    std::unique_ptr<b2World> m_world;
    std::unique_ptr<b2ContactListener> m_contactsListener;
    std::vector<b2Body *> m_bodiesToDelete;
};
