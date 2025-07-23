#include "peachpch.h"
#include "AppState.h"

namespace Peach
{
	AppState::AppState(Ref<AppData> data, const std::string& name)
		: m_Data(data), m_DebugName(name)
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

	Ref<AppData> AppState::getAppData() const
	{
		if (auto data = m_Data.lock())
		{
			return data;
		}

		PEACH_CORE_ERROR("AppState::getData(), Ritornato valore nullo");
		return nullptr;
	}

	Peach::Window& AppState::getWindow() const
	{
		return *getAppData()->window;
	}

	void AppState::removeState() const
	{
		getAppData()->machine.removeState();
	}

	const Peach::Texture& AppState::getTexture(const std::string& key) const
	{
		return getAsset<Peach::Texture>(key);
	}

	const Peach::Font& AppState::getFont(const std::string& key) const
	{
		return getAsset<Peach::Font>(key);
	}

	const Peach::Sound& AppState::getSound(const std::string& key) const
	{
		return getAsset<Peach::Sound>(key);
	}

}
