#include "peachpch.h"
#include "State.h"

namespace Peach
{
	State::State(Ref<Data> state, const std::string& name)
		: m_Data(state), m_DebugName(name)
	{
		PEACH_CORE_TRACE("State \"{}\" costruito", m_DebugName);
	}

	State::~State()
	{
		PEACH_CORE_TRACE("State \"{}\" distrutto", m_DebugName);
	}

	void State::onAdd()
	{
		PEACH_CORE_TRACE("State \"{}\" in aggiunta", m_DebugName);
	}

	void State::onRemove()
	{
		PEACH_CORE_TRACE("State \"{}\" in rimozione", m_DebugName);
	}

	const std::string& State::getName() const
	{
		return m_DebugName;
	}

	Peach::Window& State::getWindow() const
	{
		if (auto data = m_Data.lock())
		{
			return data->window;
		}

		throw std::runtime_error("Data inaccessibile");
	}

	bool State::pollEvent(sf::Event& event) const
	{
		return getWindow().pollEvent(event);
	}

	sf::RenderTarget* State::getRenderer() const
	{
		return getWindow().getRenderer();
	}

	void State::removeState() const
	{
		if (auto data = m_Data.lock())
		{
			data->machine.removeState();
			return;
		}

		PEACH_CORE_ERROR("State::removeState(), Impossibile rimuovere State [Data inaccessibile]");
	}

	const Peach::Texture& State::getTexture(const AssetKey& key) const
	{
		return getAsset<Peach::Texture>(key);
	}

	const Peach::Font& State::getFont(const AssetKey& key) const
	{
		return getAsset<Peach::Font>(key);
	}

	const Peach::Sound& State::getSound(const AssetKey& key) const
	{
		return getAsset<Peach::Sound>(key);
	}

}
