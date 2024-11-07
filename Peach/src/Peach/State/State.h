#pragma once

#include "IState.h"

#include "Peach/Core/Data.h"
#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API State : public IState
	{
	public:
		State(Ref<Data> data, const std::string& name = "State");
		virtual ~State() override;

		virtual void onAdd() override;
		virtual void onRemove() override;
		virtual void onEvent() override {}
		virtual void onUpdate() override {}
		virtual void onRender() override {}

		virtual const std::string& getName() const override;
	protected:
		std::weak_ptr<Data> m_Data;
	protected:
		Peach::Window& getWindow() const;
		bool pollEvent(sf::Event& event) const;
		sf::RenderTarget* getRenderer() const;

		template<typename T>
		void addState(bool replacing = false) const
		{
			if (auto data = m_Data.lock())
			{
				data->machine.addState(MakeRef<T>(data), replacing);
				return;
			}

			PEACH_CORE_ERROR("State::addState(), Impossibile aggiungere State [Data inaccessibile]");
		}
		void removeState() const;

		template<typename T>
		const T& getAsset(const AssetKey& key) const
		{
			if (auto data = m_Data.lock())
			{
				return *data->assets.getAsset<T>(key);
			}

			throw std::runtime_error("Data inaccessibile");
		}
		const Peach::Texture& getTexture(const AssetKey& key) const;
		const Peach::Font& getFont(const AssetKey& key) const;
		const Peach::Sound& getSound(const AssetKey& key) const;
	private:
		std::string m_DebugName;
	};
}
