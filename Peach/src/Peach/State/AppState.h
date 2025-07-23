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

		virtual bool isWaitEvent() const override { return false; }
		virtual const std::string& getName() const override;
	protected:
		Ref<AppData> getAppData() const;

		Window& getWindow() const;

		template<typename T>
		void addState(bool replacing = false) const { getAppData()->machine.addState(MakeScope<T>(getAppData()), replacing); }
		void removeState() const;

		template<typename T>
		Ref<T> getAssetRef(const std::string& key) const { return getAppData()->assets.getAsset<T>(key); }
		template<typename T>
		const T& getAsset(const std::string& key) const { return *getAssetRef<T>(key).get(); }

		const Peach::Texture& getTexture(const std::string& key) const;
		const Peach::Font& getFont(const std::string& key) const;
		const Peach::Sound& getSound(const std::string& key) const;
	private:
		std::weak_ptr<AppData> m_Data;

		std::string m_DebugName;
	};
}
