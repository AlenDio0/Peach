#pragma once

#include "Core.h"
#include "IState.h"

#include "Data.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API State : public IState
	{
	public:
		State(DataRef data, std::string name = "State");
		virtual ~State();

		virtual void onAdd();
		virtual void onRemove();
		virtual void onEvent() {}
		virtual void onUpdate() {}
		virtual void onRender() {}

		std::string getName() const;
	protected:
		DataRef m_Data;
	private:
		std::string m_DebugName;
	};
}
