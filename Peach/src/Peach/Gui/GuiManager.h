#pragma once

#include "GuiObject.h"

#include "Peach/System/Manager.h"

namespace Peach
{
	class PEACH_API GuiManager : public Manager<GuiObject>
	{
	public:
		GuiManager();
		virtual ~GuiManager() override;

		const sf::Cursor& getCursor() const;

		virtual void handleEvent(const sf::Event& event) override;
		virtual void update(const float deltaTime) override;
		virtual void render(sf::RenderTarget& target) const override;
	private:
		static inline sf::Vector2i m_MousePosition;
	};
}
