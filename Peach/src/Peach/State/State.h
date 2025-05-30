#pragma once

#include "Peach/Core.h"
#include "IState.h"

#include "Peach/Data.h"

#include <SFML/Graphics.hpp>
#include <string>

namespace Peach
{
	class PEACH_API State : public IState
	{
	public:
		State(Ref<Data> data, const std::string& name = "State");
		virtual ~State();

		virtual void onAdd();
		virtual void onRemove();
		virtual void onEvent() {}
		virtual void onUpdate() {}
		virtual void onRender() {}

		const std::string& getName() const;
	protected:
		Ref<Data> m_Data;
	protected:
		void addState(IState* newstate, bool replacing);
		void removeState();

		template<typename T>
		T& getAsset(const AssetKey& key)
		{
			return m_Data->assets.getAsset<T>(key);
		}
	private:
		std::string m_DebugName;
	};
}
