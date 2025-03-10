#include "peachpch.h"
#include "AppState.h"

namespace Peach
{
	AppState::AppState(Ref<Data> state, const std::string& name)
		: m_Data(state), m_DebugName(name)
	{
		PEACH_CORE_TRACE("AppState \"{}\" costruito", m_DebugName);
	}

	AppState::~AppState()
	{
		PEACH_CORE_TRACE("AppState \"{}\" distrutto", m_DebugName);
	}

	const std::string& AppState::getName() const
	{
		return m_DebugName;
	}

	Peach::Window& AppState::getWindow() const
	{
		if (auto data = m_Data.lock())
		{
			return data->window;
		}

		throw std::runtime_error("Data inaccessibile");
	}

	sf::RenderTarget& AppState::getRenderer() const
	{
		return getWindow().getRenderer();
	}

	void AppState::removeState() const
	{
		if (auto data = m_Data.lock())
		{
			data->machine.removeState();
			return;
		}

		PEACH_CORE_ERROR("AppState::removeState(), Impossibile rimuovere AppState [Data inaccessibile]");
	}

	const Peach::Texture& AppState::getTexture(const AssetKey& key) const
	{
		return getAsset<Peach::Texture>(key);
	}

	const Peach::Font& AppState::getFont(const AssetKey& key) const
	{
		return getAsset<Peach::Font>(key);
	}

	const Peach::Sound& AppState::getSound(const AssetKey& key) const
	{
		return getAsset<Peach::Sound>(key);
	}

}
