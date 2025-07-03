#pragma once

#include "State.h"

#include "Peach/Core/AppData.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API AppState : public State
	{
	public:
		AppState(Ref<AppData> data, const std::string& name = "AppState");
		virtual ~AppState() override;

		virtual void onAdd() override {}
		virtual void onRemove() override {}
		virtual void onEvent(const sf::Event& event) override {}
		virtual void onUpdate(const float deltaTime) override {}
		virtual void onRender() override {}

		virtual const std::string& getName() const override;
	protected:
		Peach::Window& getWindow() const;

		template<typename T>
		void addState(bool replacing = false) const
		{
			if (auto data = m_Data.lock())
			{
				data->machine.addState(MakeScope<T>(data), replacing);
				return;
			}

			PEACH_CORE_ERROR("AppState::addState(), Impossibile aggiungere AppState [AppData inaccessibile]");
		}
		void removeState() const;

		template<typename T>
		const T& getAsset(const AssetKey& key) const
		{
			if (auto data = m_Data.lock())
			{
				return *data->assets.getAsset<T>(key);
			}

			throw std::runtime_error("AppData inaccessibile");
		}
		const Peach::Texture& getTexture(const AssetKey& key) const;
		const Peach::Font& getFont(const AssetKey& key) const;
		const Peach::Sound& getSound(const AssetKey& key) const;
	protected:
		std::weak_ptr<AppData> m_Data;
	private:
		std::string m_DebugName;
	};
}
