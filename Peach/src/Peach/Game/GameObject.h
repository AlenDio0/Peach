#pragma once

#include "Peach/Core/Core.h"

#include "Components.h"
#include "Peach/Core/Log.h"

namespace Peach
{
	class PEACH_API GameObject
	{
	public:
		GameObject();
		GameObject(bool debuglog);
		virtual ~GameObject();

		template<typename T>
		std::weak_ptr<T> has() const
		{
			for (const auto& comp : m_Components)
			{
				auto component = std::dynamic_pointer_cast<T>(comp);
				if (component)
				{
					return component;
				}
			}

			return Ref<T>(nullptr);
		}

		template<typename T>
		std::weak_ptr<T> has()
		{
			for (auto& comp : m_Components)
			{
				auto component = std::dynamic_pointer_cast<T>(comp);
				if (component)
				{
					return component;
				}
			}

			return Ref<T>(nullptr);
		}

		template<typename T, typename... Args>
		void addComponent(Args&& ... args)
		{
			if (!has<T>().expired())
			{
				PEACH_CORE_WARN("GameObject::addComponent(), Componente gia' aggiunto");
				return;
			}

			m_Components.push_back(MakeRef<T>(std::forward<Args>(args)...));
		}

		virtual void update() {}
		virtual void render(sf::RenderTarget* target) const {}
	private:
		bool m_DebugLog;

		std::vector<Ref<Component>> m_Components;
	};
}
