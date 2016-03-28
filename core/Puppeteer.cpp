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

void CPuppeteer::AddBox(const sf::FloatRect &bounds, const SMaterial &mat)
{
    b2Vec2 pos = m_world.ScaleToPhysics(sf::Vector2f(bounds.left, bounds.top));
    b2Vec2 halfSize = 0.5f * m_world.ScaleToPhysics(sf::Vector2f(bounds.width, bounds.height));
    b2PolygonShape boxShape;
    boxShape.SetAsBox(halfSize.x, halfSize.y, b2Vec2(pos + halfSize), 0);
    AddFixture(boxShape, mat);
}

void CPuppeteer::AddCircle(const sf::Vector2f &position, float radius, const SMaterial &mat)
{
    b2CircleShape boxShape;
    boxShape.m_p = m_world.ScaleToPhysics(position);
    boxShape.m_radius = m_world.ScaleToPhysics(radius);
    AddFixture(boxShape, mat);
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

void CPuppeteer::AddFixture(const b2Shape &shape, const SMaterial &mat)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = mat.density;
    fixtureDef.friction = mat.friction;
    fixtureDef.isSensor = mat.isSensor;
    fixtureDef.restitution = mat.restitution;

    m_body->CreateFixture(&fixtureDef);
}
