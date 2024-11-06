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

	Peach::Checkbox* box1 = new Peach::Checkbox({ 32.f, 32.f }, getTexture("check"));

	Peach::TextBox* textbox1 = new Peach::TextBox({ 300.f, 70.f }, getFont("consola"), "Placeholder", false);
	Peach::TextBox* textbox2 = new Peach::TextBox({ 300.f, 50.f }, getFont("consola"), "PIN", false);
	Peach::TextBox* textbox3 = new Peach::TextBox({ 300.f, 25.f }, getFont("consola"), "Text", false);

	m_GuiManager.add(button1);
	m_GuiManager.add(button2);
	m_GuiManager.add(box1);
	m_GuiManager.add(textbox1);
	m_InsertPin = m_GuiManager.add(textbox2);
	m_GuiManager.add(textbox3);

	m_Sound.setBuffer(getSound("removed"));

	getTexture("invalid key example");

	button1->setOutlineThickness(3.f);
	button1->setLabelStyle(sf::Text::Bold);
	button1->setPosition({ (getRenderer()->getSize().x - button1->getSize().x) / 2.f, 100 });
	button1->addCallback
	(
		[&]() {
			PEACH_INFO("RIMPIAZZA");
			addState<DemoState>(true);
		}
	);

	button2->setOutlineThickness(3.f);
	button2->setLabelStyle(sf::Text::Italic);
	button2->setPosition({ (getRenderer()->getSize().x - button2->getSize().x) / 2.f, 165 });
	button2->addCallback
	(
		[&]() {
			PEACH_INFO("GIOCA");
			addState<GameState>(false);
		}
	);

	box1->setAppearance({ 3.f, {}, sf::Color::Blue, sf::Color(128, 128, 128, 50) });
	box1->setPosition({ 150.f, 40.f });

	textbox1->setRestriction(isalnum);
	textbox1->setAppearance({ 2.f, sf::Color::Black, sf::Color::Black, sf::Color::White });
	textbox1->setPosition({ (getRenderer()->getSize().x - textbox1->getSize().x) / 2.f, 250 });

	textbox2->setRestriction(isdigit, false);
	textbox2->setAppearance({ 2.f, sf::Color::Magenta, sf::Color::Green, sf::Color::White });
	textbox2->setPosition({ (getRenderer()->getSize().x - textbox2->getSize().x) / 2.f, 325 });

	textbox3->setRestriction([](char c) { return c > ' ' && c <= '~'; });
	textbox3->setAppearance({ 2.f, sf::Color::Red, sf::Color::Cyan, sf::Color::White });
	textbox3->setPosition({ (getRenderer()->getSize().x - textbox3->getSize().x) / 2.f, 400 });

	m_Input.bind(sf::Keyboard::A,
		[&]() {
			auto textbox = m_GuiManager.getGuiObject<Peach::TextBox>(m_InsertPin);
			PEACH_INFO("PIN: {}", textbox->getBuff());
		}, "Stampa nella console la stringa scritta in PIN", true
	);
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
		m_Input.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			PEACH_TRACE("KeyPressedEvent: {}", sf::Keyboard::getDescription(event.key.scancode).toAnsiString());
			break;
		}
	}
}

void DemoState::onUpdate()
{
	m_GuiManager.update();
	m_Input.update();
}

void DemoState::onRender()
{
	getWindow().setMouseCursor(m_GuiManager.getCursor());

	getRenderer()->setView(getRenderer()->getView());

	getRenderer()->clear(sf::Color::White);

	m_GuiManager.render(getRenderer());

	getWindow().display();
}
