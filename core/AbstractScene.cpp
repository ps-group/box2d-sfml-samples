#include "AbstractScene.h"
#include "DebugDraw.h"

CAbstractScene::CAbstractScene()
{
}

void CAbstractScene::OnUpdate(float deltaTime)
{
    m_world.Tick(deltaTime);
}

void CAbstractScene::OnDraw(sf::RenderTarget &target)
{
    CDebugDraw debugDraw(target, m_world);
    m_world.Draw(debugDraw);
}

CPhysicsWorld &CAbstractScene::GetWorld()
{
    return m_world;
}
