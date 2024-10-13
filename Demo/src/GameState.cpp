#include "GameState.h"

GameState::GameState(Peach::DataRef data)
	: Peach::State(data, "Game"), m_Map({ 0, 0 }, { 50, 50.f })
{
	sf::Image image;
	image.loadFromFile("assets/map.png");
	m_Map.convertImage
	(
		image,
		{
			{sf::Color::Black.toInteger(), {1, {0, 0, 16, 16}}},
			{sf::Color::White.toInteger(), {2, {16, 0, 16, 16}}}
		},
		true
	);

	m_Map.setTexture(m_Data->assets.getAsset<Peach::Texture>("TEXTURE_TILES"));

	m_View.width = m_Map.getSize().x;
	m_View.height = m_Map.getSize().y;
}

GameState::~GameState()
{
}

void GameState::onEvent()
{
	for (sf::Event event; m_Data->window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Data->window.close();
			break;
		case sf::Event::KeyPressed:
			PEACH_TRACE("KeyPressedEvent: {}", sf::Keyboard::getDescription(event.key.scancode).toAnsiString());

			const auto& tilesize = m_Map.getTileSize();
			const auto& mapsize = m_Map.getSize();
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
				m_Data->machine.removeState();
				break;
			case sf::Keyboard::A:
				m_Map.setTileSize({ tilesize.x - 1.f, tilesize.y - 1.f });
				break;
			case sf::Keyboard::B:
				m_Map.setTileSize({ tilesize.x + 1.f, tilesize.y + 1.f });
				break;
			case sf::Keyboard::C:
				m_Map.setSize({ mapsize.x + 1, mapsize.y });
				break;
			case sf::Keyboard::D:
				m_Map.setSize({ mapsize.x - 1, mapsize.y });
				break;
			case sf::Keyboard::E:
				m_Map.setSize({ mapsize.x, mapsize.y + 1 });
				break;
			case sf::Keyboard::F:
				m_Map.setSize({ mapsize.x, mapsize.y - 1 });
				break;
			case sf::Keyboard::I:
				m_View.width += 1;
				m_View.height += 1;
				break;
			case sf::Keyboard::K:
				m_View.x += 1;
				m_View.y += 1;
				break;
			case sf::Keyboard::O:
				if (m_View.width == 0)
				{
					continue;
				}
				m_View.width -= 1;
				m_View.height -= 1;
				break;
			case sf::Keyboard::L:
				m_View.x -= 1;
				m_View.y -= 1;
				break;
			}
			break;
		}
	}
}

void GameState::onUpdate()
{
}

void GameState::onRender()
{
	m_Data->window.getRenderer()->setView(m_Data->window.getRenderer()->getView());

	m_Data->window.getRenderer()->clear();

	m_Map.render(m_Data->window.getRenderer(), m_View);

	m_Data->window.display();
}
