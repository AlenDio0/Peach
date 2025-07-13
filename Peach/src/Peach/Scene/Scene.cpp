#include "peachpch.h"
#include "Scene.h"

#include "Entity.h"
#include "World.h"

namespace Peach
{
	Scene::Scene()
	{
		PEACH_CORE_TRACE("Scene costruito");
	}

	Scene::Scene(std::filesystem::path mapFile, const Peach::Texture& mapTexture)
		: m_World(MakeScope<World>(this, mapFile, mapTexture))
	{
		PEACH_CORE_TRACE("Scene costruito");
	}

	Scene::~Scene()
	{
		PEACH_CORE_TRACE("Scene distrutto");
	}

	Entity Scene::createEntity(std::string_view tag)
	{
		Entity entity(m_Registry.create(), this);

		if (!tag.empty())
		{
			entity.addComponent<TagComponent>(tag);
		}

		return entity;
	}

	Entity Scene::getEntity(std::string_view tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto entity : view)
		{
			auto& tagComp = view.get<TagComponent>(entity);
			if (tagComp == tag)
			{
				return Entity(entity, this);
			}
		}

		return Entity();
	}

	void Scene::update(const float deltaTime)
	{
		auto view = m_Registry.view<UpdateComponent>();
		for (auto entity : view)
		{
			auto& update = view.get<UpdateComponent>(entity).update;

			if (update)
			{
				update(Entity(entity, this), deltaTime);
			}
		}
	}

	void Scene::render(sf::RenderTarget& target)
	{
		{
			std::vector<SpriteComponent> sprites;
			auto view = m_Registry.view<TransformComponent, SpriteComponent>();
			for (auto [entity, transform, spriteComp] : view.each())
			{
				auto& sprite = spriteComp.sprite;

				sprite.setPosition(transform.position);
				sprite.setScale(transform.scale);

				sprites.push_back(spriteComp);
			}

			std::sort(sprites.begin(), sprites.end(),
				[](SpriteComponent& a, SpriteComponent& b) {
					return a.priority < b.priority;
				});
			for (auto& [sprite, priority] : sprites)
			{
				target.draw(sprite);
			}
		}

		{
			auto view = m_Registry.view<TransformComponent, TextComponent>();
			for (auto [entity, transform, textComp] : view.each())
			{
				textComp.text.setPosition(transform.position + textComp.offset);

				target.draw(textComp.text);
			}
		}
	}

	void Scene::renderHitbox(sf::RenderTarget& target, sf::Color color, float thickness)
	{
		auto view = m_Registry.view<TransformComponent, HitboxComponent>();
		for (auto [entity, transform, hitbox] : view.each())
		{
			auto& box = hitbox.box;

			sf::RectangleShape shape(box.size);
			shape.setPosition(transform.position + box.position);
			shape.setFillColor(sf::Color::Transparent);
			shape.setOutlineColor(color);
			shape.setOutlineThickness(thickness);

			target.draw(shape);
		}
	}
}
