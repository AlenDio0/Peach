#include "DemoState.h"

#include <Peach/Log.h>
#include <Peach/GUI/Button.h>
#include <Peach/GUI/Checkbox.h>

#include "GameState.h"

DemoState::DemoState(Peach::Ref<Peach::Data> data)
	: State(data, "Demo")
{
	Peach::Button* button1 = new Peach::Button({ 225.f, 55.f }, "RIMPIAZZA", NULL);
	Peach::Button* button2 = new Peach::Button({ 225.f, 55.f }, "GIOCA", NULL);
	m_GUIManager.add(RIMPIAZZA, button1);
	m_GUIManager.add(GIOCA, button2);

	button1->setCallback
	(
		[&]() {
			PEACH_INFO("RIMPIAZZA");
			m_Data->machine.addState(Peach::Ref<Peach::IState>(new DemoState(m_Data)), true);
		}
	);

	button2->setCallback
	(
		[&]() {
			PEACH_INFO("GIOCA");
			m_Data->machine.addState(Peach::Ref<Peach::IState>(new GameState(m_Data)), false);
		}
	);

	std::vector<Peach::Button*> buttons;

	for (auto& [key, value] : m_GUIManager.getGUIObjects({ Peach::GUIType::Button }))
	{
		buttons.push_back(static_cast<Peach::Button*>(value.get()));
	}

	for (auto& button : buttons)
	{
		button->setFont(m_Data->assets.getAsset<Peach::Font>("FONT_CONSOLA"));
		button->setPrimaryColor(sf::Color(230, 230, 230));
		button->setSecondaryColor(sf::Color::Black);
		button->setOutlineThickness(2.f);
	}

	button1->setLabelStyle(sf::Text::Bold);
	button2->setLabelStyle(sf::Text::Italic);

	button1->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - button1->getSize().x / 2.f, 100 });
	button2->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - button2->getSize().x / 2.f, 165 });

	Peach::Checkbox* box1 = new Peach::Checkbox({ 32.f, 32.f });
	m_GUIManager.add(BOX, box1);

	box1->setCheckTexture(m_Data->assets.getAsset<Peach::Texture>("TEXTURE_CHECK"));

	box1->setPrimaryColor(sf::Color(230, 230, 230));
	box1->setSecondaryColor(sf::Color::Black);
	box1->setOutlineThickness(3.f);
	box1->setPosition({ 150.f, 40.f });

	m_Sound.setBuffer(m_Data->assets.getAsset<Peach::Sound>("SOUND_GENERIC"));
}

DemoState::~DemoState()
{
	m_Sound.play();
	while (m_Sound.getStatus() == sf::Sound::Status::Playing);
}

void DemoState::onEvent()
{
	for (sf::Event event; m_Data->window.pollEvent(event);)
	{
		m_GUIManager.handleEvent(event);
		switch (event.type)
		{
		case sf::Event::Closed:
			m_Data->window.close();
			break;
		case sf::Event::KeyPressed:
			PEACH_TRACE("KeyPressedEvent: {}", sf::Keyboard::getDescription(event.key.scancode).toAnsiString());

			switch (event.key.code)
			{
			case sf::Keyboard::B:
				int x = m_Data->window.getRenderer()->getSize().x;
				int y = m_Data->window.getRenderer()->getSize().y;
				PEACH_TRACE("Window Size: {}, {}", x, y);
				break;
			}
			break;
		}
	}
}

void DemoState::onUpdate()
{
	sf::Cursor cursor;
	cursor.loadFromSystem(m_GUIManager.getCursor());
	m_Data->window.setMouseCursor(cursor);

	m_GUIManager.update();
}

void DemoState::onRender()
{
	m_Data->window.getRenderer()->setView(m_Data->window.getRenderer()->getView());

	m_Data->window.getRenderer()->clear(sf::Color::White);

	m_GUIManager.render(m_Data->window.getRenderer());

	m_Data->window.display();
}
