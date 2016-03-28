#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include "IPhysicsWorld.h"

class CDebugDraw : public b2Draw
{
public:
    CDebugDraw(sf::RenderTarget & target, IPhysicsWorld & world);

    void DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;
    void DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color) override;
    void DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color) override;
    void DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color) override;
    void DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color) override;
    void DrawTransform(const b2Transform &xf) override;

private:
    sf::Vector2f ConvertVertex(const b2Vec2 &vertex) const;
    std::vector<sf::Vector2f> ConvertVerticies(const b2Vec2 *vertices, int32 vertexCount) const;
    sf::Color ConvertColor(b2Color const& color) const;

    sf::RenderStates m_states;
    sf::RenderTarget & m_target;
    IPhysicsWorld & m_world;
};
