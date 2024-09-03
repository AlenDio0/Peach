#include "peachpch.h"
#include "State.h"

namespace Peach
{
	State::State(DataRef state, std::string name)
		: m_Data(state), m_DebugName(name)
	{

		PEACH_CORE_TRACE("Stato \"{}\" inizializzato", m_DebugName);
	}

	State::~State()
	{
		PEACH_CORE_TRACE("Stato \"{}\" distrutto", m_DebugName);
	}

	void State::onAdd()
	{
		PEACH_CORE_TRACE("Stato \"{}\" in aggiunta", m_DebugName);
	}

	void State::onRemove()
	{
		PEACH_CORE_TRACE("Stato \"{}\" in rimozione", m_DebugName);
	}

	std::string State::getName() const
	{
		return m_DebugName;
	}
}
