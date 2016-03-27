#pragma once

#include "IScene.h"
#include "../core/PhysicsWorld.h"

class CAbstractScene : public IScene
{
public:
    CAbstractScene();

    void OnUpdate(float deltaTime) override;

protected:
    CPhysicsWorld &GetWorld();

private:
    CPhysicsWorld m_world;
};
