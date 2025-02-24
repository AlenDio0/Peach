#include "peachpch.h"
#include "StateMachine.h"

namespace Peach
{
	StateMachine::StateMachine()
		: m_NewState(nullptr), m_IsAdding(false), m_IsReplacing(false), m_IsRemoving(false)
	{
		PEACH_CORE_TRACE("StateMachine costruito");
	}

	StateMachine::~StateMachine()
	{
		PEACH_CORE_TRACE("StateMachine distrutto");

		clear();
	}

	Ref<State> StateMachine::getCurrentState() const
	{
		if (m_States.empty())
		{
			PEACH_CORE_ERROR("StateMachine::getCurrentState(), StateStack e' vuoto");
			return nullptr;
		}
		else if (!m_States.top())
		{
			PEACH_CORE_ERROR("StateMachine::getCurrentState(), State attuale e' nullo");
			return nullptr;
		}

		return m_States.top();
	}

	void StateMachine::update()
	{
		if (m_IsRemoving)
		{
			onRemoving();

			m_IsRemoving = false;
		}

		if (m_IsAdding)
		{
			onAdding();

			m_IsAdding = false;
			m_IsReplacing = false;
		}
	}

	void StateMachine::addState(Ref<State> newstate, bool replacing)
	{
		PEACH_CORE_TRACE("StateMachine::addState(newState: {}, isReplacing: {})", newstate, replacing);

		if (!newstate)
		{
			PEACH_CORE_ERROR("StateMachine::addState(...), Impossibile aggiungere uno State nullo");

			return;
		}

		m_NewState = std::move(newstate);

		m_IsAdding = true;
		m_IsReplacing = replacing;
	}

	void StateMachine::removeState()
	{
		m_IsRemoving = true;

		PEACH_CORE_TRACE("StateMachine::removeState(), [currentState: {}]", getCurrentState());
	}

	void StateMachine::clear()
	{
		while (!m_States.empty())
		{
			m_States.pop();
		}
	}

	void StateMachine::onAdding()
	{
		PEACH_CORE_TRACE("StateMachine::onAdding(), Tentativo di aggiungere State in corso [isReplacing: {}]", m_IsReplacing);

		if (!m_NewState)
		{
			PEACH_CORE_ERROR("StateMachine::onAdding(), Impossibile aggiungere uno State nullo");

			return;
		}

		if (m_IsReplacing)
		{
			PEACH_CORE_TRACE("StateMachine::onAdding(), Tentativo di rimpiazzo dello State \"{}\" in corso", getCurrentState()->getName());

			onRemoving();
		}

		PEACH_CORE_TRACE("StateMachine::onAdding(), Aggiungendo State \"{}\"", m_NewState->getName());

		m_NewState->onAdd();
		m_States.push(std::move(m_NewState));

		PEACH_CORE_INFO("StateMachine::onAdding(), Aggiunto State \"{}\" con successo", getCurrentState()->getName());
	}

	void StateMachine::onRemoving()
	{
		PEACH_CORE_TRACE("StateMachine::onRemoving(), Tentativo di rimozione stato in corso");

		if (m_States.empty())
		{
			if (m_IsAdding)
			{
				PEACH_CORE_WARN("StateMachine::onRemoving(), Rimosso il nuovo State \"{}\", StateStack vuoto", m_NewState->getName());

				m_IsAdding = false;
				m_IsReplacing = false;
				m_NewState = nullptr;
			}
			else
			{
				PEACH_CORE_ERROR("StateMachine::onRemoving(), Impossibile rimuovere State, StateStack vuoto");
			}

			return;
		}

		PEACH_CORE_INFO("StateMachine::onRemoving(), Rimosso State \"{}\" con successo", getCurrentState()->getName());

		getCurrentState()->onRemove();
		m_States.pop();
	}
}
