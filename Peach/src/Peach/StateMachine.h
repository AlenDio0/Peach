#pragma once

#include "Core.h"

#include "IState.h"

#include <memory>
#include <stack>

namespace Peach
{
	typedef std::shared_ptr<IState> IStateRef;

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
		std::stack<IStateRef> m_States;
		IStateRef m_NewState;

		bool m_IsAdding;
		bool m_IsReplacing;
		bool m_IsRemoving;

		void onAdding();
		void onRemoving();
	};
}
