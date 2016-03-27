#pragma once

#include <SFML/Graphics.hpp>

class IScene
{
public:
    virtual ~IScene() = default;
    virtual void OnEvent(sf::Event const& event) = 0;
    virtual void OnUpdate(float deltaTime) = 0;
    virtual void OnDraw(sf::RenderTarget & target) = 0;
};
