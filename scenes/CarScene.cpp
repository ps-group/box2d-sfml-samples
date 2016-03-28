#include "CarScene.h"
#include "../core/PuppeteerFactory.h"

CCarUnit::CCarUnit()
{
    m_bodyTexture.loadFromFile("red_car_body.png");
    m_body.setTexture(m_bodyTexture);

    sf::Vector2f carSize(m_body.getTextureRect().width, m_body.getTextureRect().height);
    sf::Color wheelFillColor = sf::Color(100, 100, 100, 255);
    sf::Color wheelOutlineColor = sf::Color::Blue;
    const float outlineWidth = 5.f;

    m_frontWheel.setRadius(25);
    m_frontWheel.setFillColor(wheelFillColor);
    m_frontWheel.setOutlineColor(wheelOutlineColor);
    m_frontWheel.setOutlineThickness(outlineWidth);
    m_frontWheel.setPosition(0.18f * carSize.x, 0.66f * carSize.y);

    m_rearWheel.setRadius(25);
    m_rearWheel.setFillColor(wheelFillColor);
    m_rearWheel.setOutlineColor(wheelOutlineColor);
    m_rearWheel.setOutlineThickness(outlineWidth);
    m_rearWheel.setPosition(0.64f * carSize.x, 0.66f * carSize.y);
}

void CCarUnit::InitPuppeteer(CPuppeteer &puppeteer)
{
    SMaterial mat;
    sf::Vector2f carSize(m_body.getTextureRect().width, m_body.getTextureRect().height);
    puppeteer.AddBox(sf::FloatRect(0, 0, carSize.x, carSize.y), mat);
    auto getPosition = [](sf::CircleShape const& shape) {
        sf::Vector2f pos = shape.getPosition();
        pos.x += shape.getRadius();
        pos.y += shape.getRadius();
        return pos;
    };

    puppeteer.AddCircle(getPosition(m_frontWheel), m_frontWheel.getRadius() + m_frontWheel.getOutlineThickness(), mat);
    puppeteer.AddCircle(getPosition(m_rearWheel), m_rearWheel.getRadius() + m_frontWheel.getOutlineThickness(), mat);
}

void CCarUnit::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Сохраняем старую трансформацию,
    // модифицируем (домножаем) и рисуем детали машины.
    sf::Transform transform = states.transform;
    states.transform.combine(getTransform());
    {
        target.draw(m_frontWheel, states);
        target.draw(m_rearWheel, states);
        target.draw(m_body, states);
    }
    states.transform = transform;
}

CCarScene::CCarScene()
{
    std::vector<sf::Vector2f> terrainPoints = {
        {0, 200},
        {100, 200},
        {200, 250},
        {300, 300},
        {400, 320},
        {500, 340},
        {600, 350},
        {700, 365},
        {800, 355},
        {900, 365},
        {1000, 370},
        {1100, 380},
        {1200, 390},
    };
    m_car.setPosition(0, 100);

    CPuppeteerFactory factory(GetWorld());

    m_carPuppeteer = factory.MakeDynamic(m_car);
    m_car.InitPuppeteer(*m_carPuppeteer);

    factory.MakeLandscape(terrainPoints);

    m_terrain.reserve(terrainPoints.size());
    for (sf::Vector2f point : terrainPoints)
    {
        m_terrain.emplace_back(point, sf::Color::Magenta);
    }
}

CCarScene::~CCarScene()
{
}

void CCarScene::OnEvent(const sf::Event &event)
{
    (void)event;
}

void CCarScene::OnDraw(sf::RenderTarget &target)
{
    sf::RenderStates states = sf::RenderStates::Default;
    target.draw(m_terrain.data(), unsigned(m_terrain.size()), sf::LinesStrip, states);
    target.draw(m_car, states);

    /// Чтобы включить отладочную отрисовку, достаточно раскоментировать код ниже.
//    CAbstractScene::OnDraw(target);
}
