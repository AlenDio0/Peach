#pragma once

#include "Peach/Core.h"

#include "IState.h"

#include <memory>
#include <stack>

namespace Peach
{
	class PEACH_API StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		Ref<IState> getCurrentState() const;

		void update();

		void addState(Ref<IState> newState, bool isReplacing);
		void removeState();
	private:
		std::stack<Ref<IState>> m_States;
		Ref<IState> m_NewState;

		bool m_IsAdding;
		bool m_IsReplacing;
		bool m_IsRemoving;

		void onAdding();
		void onRemoving();
	};
}
