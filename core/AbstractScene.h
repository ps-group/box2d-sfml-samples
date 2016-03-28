#pragma once

#include "IScene.h"
#include "PhysicsWorld.h"

class CAbstractScene : public IScene
{
public:
    CAbstractScene();

    void OnUpdate(float deltaTime) override;
    void OnDraw(sf::RenderTarget & target) override;

protected:
    CPhysicsWorld &GetWorld();

private:
    CPhysicsWorld m_world;
};
