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

		Ref<State> getCurrentState() const;

		void update();

		void addState(Ref<State> newstate, bool replacing);
		void removeState();

		void clear();
	private:
		std::stack<Ref<State>> m_States;
		Ref<State> m_NewState;

		bool m_IsAdding;
		bool m_IsReplacing;
		bool m_IsRemoving;

		void onAdding();
		void onRemoving();
	};
}
