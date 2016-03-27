#include "AbstractScene.h"

CAbstractScene::CAbstractScene()
{
}

void CAbstractScene::OnUpdate(float deltaTime)
{
    m_world.Tick(deltaTime);
}

CPhysicsWorld &CAbstractScene::GetWorld()
{
    return m_world;
}
