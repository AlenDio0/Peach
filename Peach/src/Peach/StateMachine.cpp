#include "peachpch.h"
#include "StateMachine.h"

namespace Peach
{
	StateMachine::StateMachine()
		: m_NewState(NULL), m_IsAdding(false), m_IsReplacing(false), m_IsRemoving(false)
	{
		PEACH_CORE_TRACE("StateMachine inizializzato");
	}

	StateMachine::~StateMachine()
	{
		PEACH_CORE_TRACE("StateMachine distrutto");
	}

	IStateRef& StateMachine::getCurrentState() const
	{
		if (m_States.empty())
		{
			PEACH_CORE_FATAL("StateMachine::getCurrentState() [Lo stack degli stati è vuoto]");
		}
		else if (!m_States.top())
		{
			PEACH_CORE_FATAL("StateMachine::getCurrentState() [Stato attuale nullo]");
		}

		return static_cast<IStateRef>(m_States.top());
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

	void StateMachine::addState(IStateRef newState, bool isReplacing)
	{
		PEACH_CORE_INFO("StateMachine::addState(newState: {}, isReplacing: {})", newState ? "EXISTS" : "NULL", isReplacing);

		if (!newState)
		{
			PEACH_CORE_ERROR("Tentativo di aggiungere stato fallito");

			return;
		}

		m_NewState = std::move(newState);

		m_IsAdding = true;
		m_IsReplacing = isReplacing;
	}

	void StateMachine::removeState()
	{
		m_IsRemoving = true;

		PEACH_CORE_INFO("StateMachine::removeState() [currentState: {}]", getCurrentState() ? "EXISTS" : "NULL");
	}

	void StateMachine::onAdding()
	{
		PEACH_CORE_INFO("StateMachine::onAdding() [Tentativo di aggiungere stato in corso, isReplacing: {}]", m_IsReplacing);

		if (!m_NewState)
		{
			PEACH_CORE_ERROR("StateMachine::onAdding() [Tentativo di aggiungere stato fallito]");

			return;
		}

		if (m_IsReplacing && !m_States.empty())
		{
			PEACH_CORE_INFO("StateMachine::onAdding() [Tentativo di rimpiazzo dello stato \"{}\" riuscito]", getCurrentState()->getName());

			m_States.pop();
		}
		else if (m_IsReplacing)
		{
			PEACH_CORE_WARN("StateMachine::onAdding() [Tentativo di rimpiazzo impossibile]");
		}

		PEACH_CORE_INFO("StateMachine::onAdding() [Tentativo di aggiungere stato \"{}\" in corso]", m_NewState->getName());

		m_States.push(std::move(m_NewState));
		getCurrentState()->onAdd();

		PEACH_CORE_INFO("StateMachine::onAdding() [Tentativo di aggiungere stato \"{}\" riuscito]", getCurrentState()->getName());
	}

	void StateMachine::onRemoving()
	{
		PEACH_CORE_INFO("StateMachine::onRemoving() [Tentativo di rimozione stato in corso]");

		if (m_States.empty())
		{
			if (m_IsAdding)
			{
				PEACH_CORE_WARN("StateMachine::onRemoving() [Tentativo di rimozione ha causato la rimozione del nuovo stato \"{}]\"", m_NewState->getName());

				m_IsAdding = false;
				m_IsReplacing = false;
				m_NewState = NULL;
			}
			else
			{
				PEACH_CORE_ERROR("StateMachine::onRemoving() [Tentativo di rimozione stato fallito]");
			}

			return;
		}

		PEACH_CORE_INFO("StateMachine::onRemoving() [Tentativo di rimozione stato \"{}\" riuscito]", getCurrentState()->getName());

		getCurrentState()->onRemove();
		m_States.pop();
	}
}
