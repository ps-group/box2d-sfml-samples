#include "Puppeteer.h"

CPuppeteer::CPuppeteer(sf::Transformable & puppet, IPhysicsWorld &world, b2Body *body)
    : m_puppet(puppet)
    , m_world(world)
    , m_body(body)
{
}

CPuppeteer::~CPuppeteer()
{
    m_world.DeleteBodyLater(m_body);
}

b2Body *CPuppeteer::GetBody()
{
    return m_body;
}

void CPuppeteer::OnBeforeTick(float deltaTime)
{
    (void)deltaTime;
}

void CPuppeteer::OnAfterTick()
{
    // Обновляем позицию куклы.
    sf::Vector2f pos = m_world.GetScreenPosition(m_body);
    float rotation = m_world.GetScreenRotation(m_body);
    m_puppet.setPosition(pos);
    m_puppet.setRotation(rotation);
}

void CPuppeteer::OnBeginContact(const SPhysicsContact &contact)
{
    (void)contact;
}

void CPuppeteer::OnEndContact(const SPhysicsContact &contact)
{
    (void)contact;
}
