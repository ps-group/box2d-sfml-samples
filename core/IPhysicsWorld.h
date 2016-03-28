#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

class IPhysicsWorld
{
public:
    virtual ~IPhysicsWorld() = default;

    virtual b2Body *CreateBody(const b2BodyDef &bodyDef) const = 0;
    virtual b2Joint *CreateJoint(const b2JointDef &jointDef) const = 0;
    virtual void DeleteBodyLater(b2Body *body) = 0;

    virtual sf::Vector2f GetScreenPosition(b2Body *body) const = 0;
    virtual float GetScreenRotation(b2Body *body) const = 0;
    virtual b2Vec2 GetPhysicsPosition(sf::Transformable const& entity)const = 0;
    virtual float GetPhysicsRotation(sf::Transformable const& entity)const = 0;
    virtual float ScaleToPhysics(float value)const = 0;
    virtual b2Vec2 ScaleToPhysics(sf::Vector2f const& value)const = 0;
    virtual float ScaleToGraphics(float value)const = 0;
    virtual sf::Vector2f ScaleToGraphics(b2Vec2 const& value)const = 0;
};


