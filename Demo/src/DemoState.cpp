#include "DemoState.h"

#include <Peach/Gui/Button.h>
#include <Peach/Gui/Checkbox.h>
#include <Peach/Gui/TextBox.h>
#include <Peach/System/Timer.h>

#include "GameState.h"

DemoState::DemoState(Peach::Ref<Peach::AppData> data)
	: AppState(data, "Demo")
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
	m_TextBox = m_GuiManager.add(textbox3);

	m_RemovedSound = getAssetRef<Peach::Sound>("removed");

	getTexture("example");

	button1->setOutlineThickness(3.f);
	button1->setLabelStyle(sf::Text::Bold);
	button1->setPosition({ (getWindow().getSize().x - button1->getSize().x) / 2.f, 100 });
	button1->addCallback(sf::Event::MouseButtonPressed,
		[&](Peach::GuiObject* obj, sf::Event event) {
			auto& buttonEvent = event.mouseButton;
			if (buttonEvent.button != sf::Mouse::Button::Left)
			{
				return;
			}

			if (obj->isCursorOn(buttonEvent))
			{
				PEACH_INFO("RIMPIAZZA");
				addState<DemoState>(true);
			}
		}
	);

	button2->setOutlineThickness(3.f);
	button2->setLabelStyle(sf::Text::Italic);
	button2->setPosition({ (getWindow().getSize().x - button2->getSize().x) / 2.f, 165 });
	button2->addCallback(sf::Event::MouseButtonPressed,
		[&](Peach::GuiObject* obj, sf::Event event) {
			auto& buttonEvent = event.mouseButton;
			if (buttonEvent.button != sf::Mouse::Button::Left)
			{
				return;
			}

			if (obj->isCursorOn(buttonEvent))
			{
				PEACH_INFO("GIOCA");
				addState<GameState>(false);
			}
		}
	);

	box1->setAppearance({ 3.f, {}, sf::Color::Blue, sf::Color(128, 128, 128, 50) });
	box1->setPosition({ 150.f, 40.f });

	textbox1->setPolicy(isalnum);
	textbox1->setAppearance({ 2.f, sf::Color::Black, sf::Color::Black, sf::Color::White });
	textbox1->setPosition({ (getWindow().getSize().x - textbox1->getSize().x) / 2.f, 250 });
	textbox1->addCallback(sf::Event::KeyPressed,
		[&](Peach::GuiObject* obj, sf::Event event) {
			auto& keyEvent = event.key;
			if (keyEvent.code != sf::Keyboard::Add)
			{
				return;
			}

			if (auto textbox = dynamic_cast<Peach::TextBox*>(obj))
			{
				if (!textbox->isSelected())
				{
					return;
				}

				textbox->setLength(textbox->getBuffLength() - 2);
			}
		}
	);

	textbox2->setPolicy(isdigit, false);
	textbox2->setAppearance({ 2.f, sf::Color::Magenta, sf::Color::Green, sf::Color::White });
	textbox2->setPosition({ (getWindow().getSize().x - textbox2->getSize().x) / 2.f, 325 });

	textbox3->setPolicy([](int c) { return c > ' ' && c <= '~'; });
	textbox3->setAppearance({ 2.f, sf::Color::Red, sf::Color::Cyan, sf::Color::White });
	textbox3->setPosition({ (getWindow().getSize().x - textbox3->getSize().x) / 2.f, 400 });

	m_Input.addBind(sf::Keyboard::A,
		[&](sf::Event::KeyEvent) {
			if (auto textbox = m_GuiManager.getObject<Peach::TextBox>(m_InsertPin).lock())
			{
				PEACH_INFO("PIN: {}", textbox->getBuff());
			}
		}, "Stampa il PIN");

	m_Input.addBind(sf::Keyboard::B,
		[&](sf::Event::KeyEvent) {
			if (auto textbox = m_GuiManager.getObject<Peach::TextBox>(m_TextBox).lock())
			{
				PEACH_INFO("isPalindrome: {}", ([&]() {
					Peach::ScopeTimer timer("palindrome");

					const std::string& str = textbox->getBuff();
					for (size_t i = 0; i < str.size() / 2; i++)
						if (str[i] != str[(str.size() - 1) - i])
							return false;

					return true;
					})());
			}
		}, "Stampa il PIN");
}

DemoState::~DemoState()
{
	sf::Sound sound(*m_RemovedSound.get());
	sound.play();
	while (sound.getStatus() == sf::Sound::Status::Playing);
}

void DemoState::onEvent(const sf::Event& event)
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

void DemoState::onUpdate(const float deltaTime)
{
	static Peach::Timer timer;
	if (timer.elapsedTimeSec() > 0.5f)
	{
		timer.reset();
		getWindow().setTitle("FPS: " + std::to_string((int)(1 / deltaTime)));
	}

	m_GuiManager.update(deltaTime);

}

void DemoState::onRender()
{
	getWindow().setMouseCursor(m_GuiManager.getCursor());

	getWindow().clear(sf::Color::White);

	m_GuiManager.render(getWindow());

	getWindow().display();
}
