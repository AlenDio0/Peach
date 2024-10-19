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

	void State::addState(IState* newstate, bool replacing);
	{
		m_Data->machine.addState(MakeRef<IState>(newstate), replacing);
	}

	void State::removeState()
	{
		m_Data->machine.removeState();
	}
}
