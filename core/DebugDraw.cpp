#include "DebugDraw.h"

CDebugDraw::CDebugDraw(sf::RenderTarget & target, IPhysicsWorld &world)
    : m_target(target)
    , m_world(world)
{
    SetFlags(e_shapeBit | e_jointBit);
}

void CDebugDraw::DrawPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    std::vector<sf::Vector2f> points = ConvertVerticies(vertices, vertexCount);
    unsigned count = static_cast<unsigned>(points.size());
    sf::ConvexShape shape;
    shape.setPointCount(count);
    for (unsigned i = 0; i < count; ++i)
    {
        shape.setPoint(i, points[i]);
    }
    shape.setOutlineColor(ConvertColor(color));
    shape.setOutlineThickness(2.f);
    m_target.draw(shape, m_states);
}

void CDebugDraw::DrawSolidPolygon(const b2Vec2 *vertices, int32 vertexCount, const b2Color &color)
{
    std::vector<sf::Vector2f> points = ConvertVerticies(vertices, vertexCount);
    unsigned count = static_cast<unsigned>(points.size());
    sf::ConvexShape shape;
    shape.setPointCount(count);
    for (unsigned i = 0; i < count; ++i)
    {
        shape.setPoint(i, points[i]);
    }
    shape.setFillColor(ConvertColor(color));
    m_target.draw(shape, m_states);
}

void CDebugDraw::DrawCircle(const b2Vec2 &center, float32 radius, const b2Color &color)
{
    float scaledRadius = m_world.ScaleToGraphics(radius);

    sf::CircleShape shape;
    shape.setPosition(ConvertVertex(center) - sf::Vector2f(scaledRadius, scaledRadius));
    shape.setRadius(scaledRadius);
    shape.setOutlineColor(ConvertColor(color));
    shape.setOutlineThickness(1.f);
    m_target.draw(shape, m_states);
}

void CDebugDraw::DrawSolidCircle(const b2Vec2 &center, float32 radius, const b2Vec2 &axis, const b2Color &color)
{
    (void)axis;
    float scaledRadius = m_world.ScaleToGraphics(radius);

    sf::CircleShape shape;
    shape.setPosition(ConvertVertex(center) - sf::Vector2f(scaledRadius, scaledRadius));
    shape.setRadius(scaledRadius);
    shape.setFillColor(ConvertColor(color));
    m_target.draw(shape, m_states);
}

void CDebugDraw::DrawSegment(const b2Vec2 &p1, const b2Vec2 &p2, const b2Color &color)
{
    sf::Vertex vertex[2];
    vertex[0].color = ConvertColor(color);
    vertex[0].position = ConvertVertex(p1);
    vertex[1].color = ConvertColor(color);
    vertex[1].position = ConvertVertex(p2);
    m_target.draw(vertex, 2, sf::Lines, m_states);
}

void CDebugDraw::DrawTransform(const b2Transform &xf)
{
    (void)xf;
}

sf::Vector2f CDebugDraw::ConvertVertex(const b2Vec2 &vertex) const
{
    return m_world.ScaleToGraphics(vertex);
}

std::vector<sf::Vector2f> CDebugDraw::ConvertVerticies(const b2Vec2 *vertices, int32 vertexCount) const
{
    size_t size = static_cast<size_t>(vertexCount);
    std::vector<sf::Vector2f> ret(size);
    for (size_t i = 0; i < size; ++i)
    {
        ret[i] = m_world.ScaleToGraphics(vertices[i]);
    }
    return ret;
}

sf::Color CDebugDraw::ConvertColor(const b2Color &color) const
{
    return sf::Color(uint8_t(255 * color.r),
                     uint8_t(255 * color.g),
                     uint8_t(255 * color.b),
                     uint8_t(255 * color.a));
}
