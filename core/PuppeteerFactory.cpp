#include "PuppeteerFactory.h"

CPuppeteerFactory::CPuppeteerFactory(IPhysicsWorld &world)
    : m_world(world)
{
}

CPuppeteerUniquePtr CPuppeteerFactory::Make(sf::CircleShape &shape, SPuppeteerOptions const& options)
{
    b2CircleShape boxShape;
    boxShape.m_radius = m_world.ScaleToPhysics(shape.getRadius());
    auto body = CreateBody(shape, options.isStatic, false);
    AddFixture(boxShape, *body, options);

    return Finalize(shape, body);
}

CPuppeteerUniquePtr CPuppeteerFactory::Make(sf::RectangleShape &shape, const SPuppeteerOptions &options)
{
    b2PolygonShape boxShape;
    b2Vec2 size = m_world.ScaleToPhysics(shape.getSize());
    boxShape.SetAsBox(size.x, size.y);
    auto body = CreateBody(shape, options.isStatic, false);
    AddFixture(boxShape, *body, options);

    return Finalize(shape, body);
}

CJointUniquePtr CPuppeteerFactory::MakeRope(CPuppeteer &a, CPuppeteer &b, float maxLength)
{
    b2RopeJointDef def;
    def.bodyA = a.GetBody();
    def.bodyB = b.GetBody();
    def.maxLength = m_world.ScaleToPhysics(maxLength);

    return std::make_unique<CJoint>(m_world, def);
}

b2Body *CPuppeteerFactory::CreateBody(const sf::Transformable &entity, bool isStatic, bool isBullet)
{
    b2BodyDef def;
    def.type = isStatic ? b2_staticBody : b2_dynamicBody;
    def.bullet = isBullet;
    def.position = m_world.GetPhysicsPosition(entity);
    def.angle = m_world.GetPhysicsRotation(entity);

    return m_world.CreateBody(def);
}

void CPuppeteerFactory::AddFixture(const b2Shape &shape, b2Body &body, const SPuppeteerOptions &options)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = options.density;
    fixtureDef.friction = options.friction;
    fixtureDef.isSensor = options.isSensor;
    fixtureDef.restitution = options.restitution;

    body.CreateFixture(&fixtureDef);
}

CPuppeteerUniquePtr CPuppeteerFactory::Finalize(sf::Transformable & entity, b2Body *body)
{
    auto ret = std::make_unique<CPuppeteer>(entity, m_world, body);

    IPuppeteer *puppeteer = ret.get();
    body->SetUserData(reinterpret_cast<void*>(puppeteer));

    return ret;
}
