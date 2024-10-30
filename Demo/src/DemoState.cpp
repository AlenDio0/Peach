#include "DemoState.h"

#include <Peach/Gui/Button.h>
#include <Peach/Gui/Checkbox.h>
#include <Peach/Gui/TextBox.h>

#include "GameState.h"

DemoState::DemoState(Peach::Ref<Peach::Data> data)
	: State(data, "Demo")
{
	Peach::Button* button1 = new Peach::Button({ 225.f, 55.f }, "RIMPIAZZA", getFont("consola"));
	Peach::Button* button2 = new Peach::Button({ 225.f, 55.f }, "GIOCA", getFont("consola"));

	Peach::Checkbox* box1 = new Peach::Checkbox({ 32.f, 32.f });
	box1->setCheckTexture(getTexture("check"));

	Peach::TextBox* textbox1 = new Peach::TextBox({ 300.f, 70.f }, getFont("consola"), "Placeholder", false);
	Peach::TextBox* textbox2 = new Peach::TextBox({ 300.f, 50.f }, getFont("consola"), "PIN", false);
	Peach::TextBox* textbox3 = new Peach::TextBox({ 300.f, 25.f }, getFont("consola"), "Text", false);

	m_GuiManager.add(RIMPIAZZA, button1);
	m_GuiManager.add(GIOCA, button2);
	m_GuiManager.add(BOX, box1);
	m_GuiManager.add(TEXTBOX1, textbox1);
	m_GuiManager.add(TEXTBOX2, textbox2);
	m_GuiManager.add(TEXTBOX3, textbox3);

	m_Sound.setBuffer(getSound("removed"));

	getTexture("invalid key example");

	button1->setOutlineThickness(3.f);
	button1->setLabelStyle(sf::Text::Bold);
	button1->setPosition({ getRenderer()->getSize().x / 2.f - button1->getSize().x / 2.f, 100 });
	button1->addCallback
	(
		[&]() {
			PEACH_INFO("RIMPIAZZA");
			addState<DemoState>(true);
		}
	);

	button2->setOutlineThickness(3.f);
	button2->setLabelStyle(sf::Text::Italic);
	button2->setPosition({ getRenderer()->getSize().x / 2.f - button2->getSize().x / 2.f, 165 });
	button2->addCallback
	(
		[&]() {
			PEACH_INFO("GIOCA");
			addState<GameState>(false);
		}
	);

	box1->setSecondaryColor(sf::Color::Blue);
	box1->setBackgroundColor(sf::Color(128, 128, 128, 50));
	box1->setOutlineThickness(3.f);
	box1->setPosition({ 150.f, 40.f });

	textbox1->setRestriction(isalnum);
	textbox1->setOutlineThickness(2.f);
	textbox1->setPrimaryColor(sf::Color::Black);
	textbox1->setSecondaryColor(sf::Color::Black);
	textbox1->setPosition({ getRenderer()->getSize().x / 2.f - textbox1->getSize().x / 2.f, 250 });

	textbox2->setRestriction(isdigit, false);
	textbox2->setOutlineThickness(2.f);
	textbox2->setPrimaryColor(sf::Color::Magenta);
	textbox2->setSecondaryColor(sf::Color::Green);
	textbox2->setPosition({ getRenderer()->getSize().x / 2.f - textbox2->getSize().x / 2.f, 325 });

	textbox3->setRestriction([](char c) { return c > ' ' && c <= '~'; });
	textbox3->setOutlineThickness(2.f);
	textbox3->setPrimaryColor(sf::Color::Red);
	textbox3->setSecondaryColor(sf::Color::Cyan);
	textbox3->setPosition({ getRenderer()->getSize().x / 2.f - textbox3->getSize().x / 2.f, 400 });
}

DemoState::~DemoState()
{
	m_Sound.play();
	while (m_Sound.getStatus() == sf::Sound::Status::Playing);
}

void DemoState::onEvent()
{
	for (sf::Event event; pollEvent(event);)
	{
		getWindow().handleEvent(event);
		m_GuiManager.handleEvent(event);
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			PEACH_TRACE("KeyPressedEvent: {}", sf::Keyboard::getDescription(event.key.scancode).toAnsiString());

			switch (event.key.code)
			{
			case sf::Keyboard::B:
				int x = getRenderer()->getSize().x;
				int y = getRenderer()->getSize().y;
				PEACH_TRACE("Window Size: {}, {}", x, y);
				break;
			}
			break;
		}
	}
}

void DemoState::onUpdate()
{
	m_GuiManager.update();
}

void DemoState::onRender()
{
	getWindow().setMouseCursor(m_GuiManager.getCursor());

	getRenderer()->setView(getRenderer()->getView());

	getRenderer()->clear(sf::Color::White);

	m_GuiManager.render(getRenderer());

	getWindow().display();
}
