#include "DemoState.h"

#include <Peach/Log.h>
#include <Peach/GUI/Button.h>
#include <Peach/GUI/Checkbox.h>
#include <Peach/GUI/TextBox.h>

#include "GameState.h"

DemoState::DemoState(Peach::Ref<Peach::Data> data)
	: State(data, "Demo")
{
	Peach::Button* button1 = new Peach::Button({ 225.f, 55.f }, "RIMPIAZZA", getAsset<Peach::Font>("consola"));
	Peach::Button* button2 = new Peach::Button({ 225.f, 55.f }, "GIOCA", getAsset<Peach::Font>("consola"));

	Peach::Checkbox* box1 = new Peach::Checkbox({ 32.f, 32.f });
	box1->setCheckTexture(getAsset<Peach::Texture>("check"));

	Peach::TextBox* textbox1 = new Peach::TextBox({ 200.f, 50.f }, "Placeholder", getAsset<Peach::Font>("consola"), 16);
	Peach::TextBox* textbox2 = new Peach::TextBox({ 200.f, 50.f }, "PIN", getAsset<Peach::Font>("consola"), 16);

	m_GUIManager.add(RIMPIAZZA, button1);
	m_GUIManager.add(GIOCA, button2);
	m_GUIManager.add(BOX, box1);
	m_GUIManager.add(TEXTBOX1, textbox1);
	m_GUIManager.add(TEXTBOX2, textbox2);

	m_Sound.setBuffer(getAsset<Peach::Sound>("removed"));

	getAsset<Peach::Texture>("invalid key example");

	button1->setCallback
	(
		[&]() {
			PEACH_INFO("RIMPIAZZA");
			addState<DemoState>(true);
		}
	);

	button2->setCallback
	(
		[&]() {
			PEACH_INFO("GIOCA");
			addState<GameState>(false);
		}
	);

	std::vector<Peach::Button*> buttons;
	for (auto& [key, button] : m_GUIManager.getGUIObjects<Peach::Button>(Peach::GUIType::Button))
	{
		buttons.push_back(button);
	}

	for (auto& button : buttons)
	{
		button->setPrimaryColor(sf::Color(230, 230, 230));
		button->setSecondaryColor(sf::Color::Black);
		button->setOutlineThickness(2.f);
	}

	button1->setLabelStyle(sf::Text::Bold);
	button2->setLabelStyle(sf::Text::Italic);

	button1->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - button1->getSize().x / 2.f, 100 });
	button2->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - button2->getSize().x / 2.f, 165 });

	box1->setPrimaryColor(sf::Color(230, 230, 230));
	box1->setSecondaryColor(sf::Color::Black);
	box1->setOutlineThickness(3.f);
	box1->setPosition({ 150.f, 40.f });

	textbox1->setRestriction(Peach::TextBox::Restriction::Regular);
	textbox2->setRestriction(Peach::TextBox::Restriction::Digit);

	textbox1->setOutlineThickness(2.f);
	textbox1->setPrimaryColor(sf::Color::Black);
	textbox1->setSecondaryColor(sf::Color::Black);
	textbox1->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - textbox1->getSize().x / 2.f, 250 });

	textbox2->setOutlineThickness(2.f);
	textbox2->setPrimaryColor(sf::Color::Magenta);
	textbox2->setSecondaryColor(sf::Color::Green);
	textbox2->setPosition({ m_Data->window.getRenderer()->getSize().x / 2.f - textbox2->getSize().x / 2.f, 350 });

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
		m_Data->window.handleEvent(event);
		m_GUIManager.handleEvent(event);
		switch (event.type)
		{
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
	m_GUIManager.update();
}

void DemoState::onRender()
{
	m_Data->window.setMouseCursor(m_GUIManager.getCursor());

	m_Data->window.getRenderer()->setView(m_Data->window.getRenderer()->getView());

	m_Data->window.getRenderer()->clear(sf::Color::White);

	m_GUIManager.render(m_Data->window.getRenderer());

	m_Data->window.display();
}
