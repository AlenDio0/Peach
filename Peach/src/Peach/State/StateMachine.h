#pragma once

#include "State.h"

#include <memory>
#include <stack>

namespace Peach
{
	class PEACH_API StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		const Scope<State>& getCurrentState() const;

		void update();

		void addState(Scope<State> newState, bool replacing);
		void removeState();

		void clear();
	private:
		std::stack<Scope<State>> m_States;
		Scope<State> m_NewState;

		bool m_IsAdding;
		bool m_IsReplacing;
		bool m_IsRemoving;

		void onAdding();
		void onRemoving();
	};
}
