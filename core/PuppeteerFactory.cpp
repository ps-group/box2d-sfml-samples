#include "PuppeteerFactory.h"

CPuppeteerFactory::CPuppeteerFactory(IPhysicsWorld &world)
    : m_world(world)
{
}

void CPuppeteerFactory::MakeLandscape(const std::vector<sf::Vector2f> &points)
{
    b2BodyDef def;
    def.type = b2_staticBody;
    b2Body *body = m_world.CreateBody(def);

    std::vector<b2Vec2> boxPoints(points.size());
    for (size_t i = 0, n = points.size(); i < n; ++i)
    {
        boxPoints[i] = m_world.ScaleToPhysics(points[i]);
    }

    b2ChainShape shape;
    shape.CreateChain(boxPoints.data(), int(boxPoints.size()));

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

CPuppeteerUniquePtr CPuppeteerFactory::MakeDynamic(sf::Transformable &entity)
{
    return MakePuppeteer(entity, CreateBody(entity, false, false));
}

CPuppeteerUniquePtr CPuppeteerFactory::MakeDynamic(sf::Sprite &sprite, SMaterial const& mat)
{
    auto body = CreateBody(sprite, false, false);
    auto ret = MakePuppeteer(sprite, body);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    bounds.top = 0;
    bounds.left = 0;
    ret->AddBox(bounds, mat);

    return ret;
}

CPuppeteerUniquePtr CPuppeteerFactory::MakeStatic(sf::CircleShape &shape, const SMaterial &mat)
{
    auto body = CreateBody(shape, true, false);
    auto ret = MakePuppeteer(shape, body);
    ret->AddCircle(sf::Vector2f(0, 0), shape.getRadius(), mat);

    return ret;
}

CPuppeteerUniquePtr CPuppeteerFactory::MakeDynamic(sf::CircleShape &shape, SMaterial const& mat)
{
    auto body = CreateBody(shape, false, false);
    auto ret = MakePuppeteer(shape, body);
    ret->AddCircle(sf::Vector2f(0, 0), shape.getRadius(), mat);

    return ret;
}

CPuppeteerUniquePtr CPuppeteerFactory::MakeDynamic(sf::RectangleShape &shape, SMaterial const& mat)
{
    auto body = CreateBody(shape, false, false);
    auto ret = MakePuppeteer(shape, body);

    sf::FloatRect bounds = shape.getGlobalBounds();
    bounds.top = 0;
    bounds.left = 0;
    ret->AddBox(bounds, mat);

    return ret;
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

void CPuppeteerFactory::AddFixture(const b2Shape &shape, b2Body &body, const SMaterial &options)
{
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = options.density;
    fixtureDef.friction = options.friction;
    fixtureDef.isSensor = options.isSensor;
    fixtureDef.restitution = options.restitution;

    body.CreateFixture(&fixtureDef);
}

CPuppeteerUniquePtr CPuppeteerFactory::MakePuppeteer(sf::Transformable & entity, b2Body *body)
{
    auto ret = std::make_unique<CPuppeteer>(entity, m_world, body);

    IPuppeteer *puppeteer = ret.get();
    body->SetUserData(reinterpret_cast<void*>(puppeteer));

    return ret;
}
