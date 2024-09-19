#pragma once

#include "Core.h"

#include "IState.h"

#include <memory>
#include <stack>

namespace Peach
{
	using IStateRef = std::shared_ptr<IState>;
	using IStateStack = std::stack<IStateRef>;

	class PEACH_API StateMachine
	{
	public:
		StateMachine();
		~StateMachine();

		IStateRef& getCurrentState() const;

		void update();

		void addState(IStateRef newState, bool isReplacing);
		void removeState();
	private:
		IStateStack m_States;
		IStateRef m_NewState;

		bool m_IsAdding;
		bool m_IsReplacing;
		bool m_IsRemoving;

		void onAdding();
		void onRemoving();
	};
}
