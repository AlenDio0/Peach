#include <Peach.h>
#include "DemoState.h"

class DemoApp : public Peach::Application
{
public:
	DemoApp()
	{
		m_Data->window.create("Titolo", { 500, 500 });

		addState(Peach::IStateRef(new DemoState(m_Data)), false);
	}

	~DemoApp()
	{
	}
};

Peach::Application* Peach::CreateApplication()
{
	return new DemoApp();
}
