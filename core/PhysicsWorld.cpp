#include "PhysicsWorld.h"
#include "IPuppeteer.h"
#include <cmath>


using std::bind;
using namespace std::placeholders;


namespace
{

static const float PIXEL_PER_METER = 10;
static const float C_GRAVITY = 9.8f;

class CPhysicsContactsListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;

private:
    typedef void (IPuppeteer::*ContactMethod)(SPhysicsContact const&);

    void CallBothContactMethods(b2Contact & contact, ContactMethod method);
    IPuppeteer *GetPuppeteer(b2Body *body);
};

void CPhysicsContactsListener::BeginContact(b2Contact *contact)
{
    CallBothContactMethods(*contact, &IPuppeteer::OnBeginContact);
}

void CPhysicsContactsListener::EndContact(b2Contact *contact)
{
    CallBothContactMethods(*contact, &IPuppeteer::OnEndContact);
}

void CPhysicsContactsListener::CallBothContactMethods(b2Contact & contact, ContactMethod method)
{
    b2Fixture &fixtureA = *contact.GetFixtureA();
    b2Fixture &fixtureB = *contact.GetFixtureB();
    auto puppeteerA = GetPuppeteer(fixtureA.GetBody());
    auto puppeteerB = GetPuppeteer(fixtureB.GetBody());

    if (puppeteerA)
    {
        SPhysicsContact infoA(fixtureA, fixtureB, puppeteerB);
        (puppeteerA->*method)(infoA);
    }

    if (puppeteerB)
    {
        SPhysicsContact infoB(fixtureB, fixtureA, puppeteerA);
        (puppeteerB->*method)(infoB);
    }
}

IPuppeteer *CPhysicsContactsListener::GetPuppeteer(b2Body *body)
{
    if (body->GetUserData())
    {
        return reinterpret_cast<IPuppeteer *>(body->GetUserData());
    }
    return nullptr;
}
}


CPhysicsWorld::CPhysicsWorld()
    : m_pixelsPerMeter(PIXEL_PER_METER)
    , m_world(new b2World(b2Vec2(0.0f, C_GRAVITY)))
    , m_contactsListener(new CPhysicsContactsListener)
{
    m_world->SetContactListener(m_contactsListener.get());
}

CPhysicsWorld::~CPhysicsWorld()
{
    CollectGarbage();
}

void CPhysicsWorld::Tick(float deltaTime)
{
    // Удаляем уничтоженные тела перед симуляцией.
    // Во время симуляции удалять тела нельзя.
    CollectGarbage();

    // Вызываем метод OnBeforeTick у каждого кукловода.
    DoForeachPuppeteer(bind(&IPuppeteer::OnBeforeTick, _1, deltaTime));

    // Вызываем у b2World метод, выполняющий один шаг симуляции физики.
    // В идеале deltaTime и число итераций за шаг не должны меняться.
    int velocityIterations = 2;
    int positionIterations = 2;
    m_world->Step(deltaTime, velocityIterations, positionIterations);

    // Вызываем метод OnAfterTick у каждого кукловода.
    DoForeachPuppeteer(bind(&IPuppeteer::OnAfterTick, _1));

    // Удаляем уничтоженные тела ещё и после симуляции.
    CollectGarbage();
}

void CPhysicsWorld::Draw(b2Draw &draw)
{
    m_world->SetDebugDraw(&draw);
    m_world->DrawDebugData();
    m_world->SetDebugDraw(nullptr);
}

b2Body *CPhysicsWorld::CreateBody(const b2BodyDef &bodyDef) const
{
    return m_world->CreateBody(&bodyDef);
}

b2Joint *CPhysicsWorld::CreateJoint(const b2JointDef &jointDef) const
{
    return m_world->CreateJoint(&jointDef);
}

void CPhysicsWorld::DeleteBodyLater(b2Body *body)
{
    body->SetUserData(nullptr);
    m_bodiesToDelete.push_back(body);
}

sf::Vector2f CPhysicsWorld::GetScreenPosition(b2Body *body) const
{
    b2Vec2 pos = body->GetPosition();
    float ratio = m_pixelsPerMeter;

    return sf::Vector2f(ratio * pos.x, ratio * pos.y);
}

float CPhysicsWorld::GetScreenRotation(b2Body *body) const
{
    return body->GetAngle() * float(180.0 / M_PI);
}

b2Vec2 CPhysicsWorld::GetPhysicsPosition(const sf::Transformable &entity)const
{
    sf::Vector2f pos = entity.getPosition();
    float factor = 1.f / m_pixelsPerMeter;

    return b2Vec2(factor * pos.x, factor * pos.y);
}

float CPhysicsWorld::GetPhysicsRotation(const sf::Transformable &entity)const
{
    return entity.getRotation() * float(M_PI / 180.0);
}

float CPhysicsWorld::ScaleToPhysics(float size)const
{
    float factor = 1.f / m_pixelsPerMeter;
    return factor * size;
}


b2Vec2 CPhysicsWorld::ScaleToPhysics(sf::Vector2f const& value)const
{
    float factor = 1.f / m_pixelsPerMeter;
    return b2Vec2(factor * value.x, factor * value.y);
}

float CPhysicsWorld::ScaleToGraphics(float value) const
{
    return m_pixelsPerMeter * value;
}

sf::Vector2f CPhysicsWorld::ScaleToGraphics(const b2Vec2 &value) const
{
    float factor = m_pixelsPerMeter;
    return sf::Vector2f(factor * value.x, factor * value.y);
}

void CPhysicsWorld::CollectGarbage()
{
    for (b2Body *body : m_bodiesToDelete)
        m_world->DestroyBody(body);
    m_bodiesToDelete.clear();
}

void CPhysicsWorld::DoForeachPuppeteer(std::function<void(IPuppeteer &)> const& func)
{
    for (b2Body const* b = m_world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData())
        {
            auto puppeteer = reinterpret_cast<IPuppeteer *>(b->GetUserData());
            func(*puppeteer);
        }
    }
}
