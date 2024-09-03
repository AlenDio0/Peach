#pragma once
#include <Peach/Data.h>
#include <Peach/State.h>

class DemoState : public Peach::State
{
public:
	DemoState(Peach::DataRef data);
	~DemoState() = default;

	void onEvent() override;
	void onUpdate() override;
	void onRender() override;
private:
	sf::CircleShape m_Circle;
};
