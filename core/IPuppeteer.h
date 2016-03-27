#pragma once

#include <Box2D/Box2D.h>

class IPuppeteer;

// Поле other может хранить nullptr, если у другого тела нет кукловода.
struct SPhysicsContact
{
    b2Fixture const& myFixture;
    b2Fixture const& otherFixture;
    IPuppeteer *other = nullptr;

    SPhysicsContact(b2Fixture const& myFixture, b2Fixture const& otherFixture, IPuppeteer *other)
        : myFixture(myFixture)
        , otherFixture(otherFixture)
        , other(other)
    {
    }

    template <class T>
    bool IsContactWith() const
    {
        return (nullptr != dynamic_cast<T *>(other));
    }
};

class IPuppeteer
{
public:
    virtual ~IPuppeteer() = default;

    virtual void OnBeforeTick(float deltaTime) = 0;
    virtual void OnAfterTick() = 0;
    virtual void OnBeginContact(SPhysicsContact const& contact) = 0;
    virtual void OnEndContact(SPhysicsContact const& contact) = 0;
};
