#include "peachpch.h"
#include "StateMachine.h"

namespace Peach
{
	StateMachine::StateMachine()
		: m_NewState(NULL), m_IsAdding(false), m_IsReplacing(false), m_IsRemoving(false)
	{
		PEACH_CORE_TRACE("StateMachine costruito");
	}

	StateMachine::~StateMachine()
	{
		PEACH_CORE_TRACE("StateMachine distrutto");
	}

	IStateRef StateMachine::getCurrentState() const
	{
		if (m_States.empty())
		{
			PEACH_CORE_ERROR("StateMachine::getCurrentState(), StateStack e' vuoto");
			return NULL;
		}
		else if (!m_States.top())
		{
			PEACH_CORE_ERROR("StateMachine::getCurrentState(), State attuale e' nullo");
			return NULL;
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

	void StateMachine::addState(IStateRef newState, bool isReplacing)
	{
		PEACH_CORE_INFO("StateMachine::addState(newState: {}, isReplacing: {})", newState ? "EXISTS" : "NULL", isReplacing);

		if (!newState)
		{
			PEACH_CORE_ERROR("StateMachine::addState(...), Impossibile aggiungere uno State nullo");

			return;
		}

		m_NewState = std::move(newState);

		m_IsAdding = true;
		m_IsReplacing = isReplacing;
	}

	void StateMachine::removeState()
	{
		m_IsRemoving = true;

		PEACH_CORE_INFO("StateMachine::removeState(), [currentState: {}]", getCurrentState() ? "EXISTS" : "NULL");
	}

	void StateMachine::onAdding()
	{
		PEACH_CORE_INFO("StateMachine::onAdding(), Tentativo di aggiungere State in corso [isReplacing: {}]", m_IsReplacing);

		if (!m_NewState)
		{
			PEACH_CORE_ERROR("StateMachine::onAdding(), Impossibile aggiungere uno State nullo");

			return;
		}

		if (m_IsReplacing && !m_States.empty())
		{
			PEACH_CORE_INFO("StateMachine::onAdding(), Tentativo di rimpiazzo dello State \"{}\" riuscito", getCurrentState()->getName());

			m_States.pop();
		}
		else if (m_IsReplacing)
		{
			PEACH_CORE_WARN("StateMachine::onAdding(), Impossibile rimpiazzare, StateStack vuoto");
		}

		PEACH_CORE_INFO("StateMachine::onAdding(), Aggiungendo State \"{}\"", m_NewState->getName());

		m_States.push(std::move(m_NewState));
		getCurrentState()->onAdd();

		PEACH_CORE_INFO("StateMachine::onAdding(), Aggiunto State \"{}\" con successo", getCurrentState()->getName());
	}

	void StateMachine::onRemoving()
	{
		PEACH_CORE_INFO("StateMachine::onRemoving(), Tentativo di rimozione stato in corso");

		if (m_States.empty())
		{
			if (m_IsAdding)
			{
				PEACH_CORE_WARN("StateMachine::onRemoving(), Rimosso il nuovo State \"{}\", StateStack vuoto", m_NewState->getName());

				m_IsAdding = false;
				m_IsReplacing = false;
				m_NewState = NULL;
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
