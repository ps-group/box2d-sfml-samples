#pragma once

#include <memory>
#include "IScene.h"

class CApplication
{
public:
    CApplication(sf::RenderWindow & window);

    template <class T>
    void RegisterScene()
    {
        auto factory = []() { return std::unique_ptr<IScene>(new T); };
        m_sceneFactories.push_back(factory);
    }

    void EnterLoop();

private:
    using SceneFactoryFn = std::function<std::unique_ptr<IScene>()>;

    sf::RenderWindow & m_window;
    std::unique_ptr<IScene> m_scene;
    std::vector<SceneFactoryFn> m_sceneFactories;
};
