#pragma once

#include "Peach/Core.h"
#include "IState.h"

#include "Peach/Data.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API State : public IState
	{
	public:
		State(Ref<Data> data, const std::string& name = "State");
		virtual ~State();

		virtual void onAdd();
		virtual void onRemove();
		virtual void onEvent() {}
		virtual void onUpdate() {}
		virtual void onRender() {}

		const std::string& getName() const;
	protected:
		Ref<Data> m_Data;
	protected:
		Peach::Window& getWindow() const;
		bool pollEvent(sf::Event& event) const;
		sf::RenderTarget* getRenderer() const;

		template<typename T>
		void addState(bool replacing = false) const { m_Data->machine.addState(MakeRef<T>(m_Data), replacing); }
		void removeState() const;

		template<typename T>
		const T& getAsset(const AssetKey& key) const { return *m_Data->assets.getAsset<T>(key); }
		const Peach::Texture& getTexture(const AssetKey& key) const;
		const Peach::Font& getFont(const AssetKey& key) const;
		const Peach::Sound& getSound(const AssetKey& key) const;
	private:
		std::string m_DebugName;
	};
}
