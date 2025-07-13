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
		return createEntity(UUID(), tag);
	}

	Entity Scene::createEntity(UUID uuid, std::string_view tag)
	{
		Entity entity(m_Registry.create(), this);
		m_Entities[uuid] = entity;

		entity.addComponent<IDComponent>(uuid);
		if (!tag.empty())
		{
			entity.addComponent<TagComponent>(tag);
		}

		PEACH_CORE_TRACE("Scene::createEntity(uuid: {}, tag: {}), [entity: {}]", uuid, tag, (uint32_t)entity);
		return entity;
	}

	void Scene::destroyEntity(Entity entity)
	{
		PEACH_CORE_TRACE("Scene::destroyEntity(entity: {}), [uuid: {}, tag: {}]", (uint32_t)entity, entity.getUUID(), entity.getTag());

		m_Entities.erase(entity.getUUID());
		m_Registry.destroy(entity);
	}

	Entity Scene::getEntity(std::string_view tag)
	{
		auto view = m_Registry.view<TagComponent>();
		for (auto [entity, tagComp] : view.each())
		{
			if (tagComp.tag == tag)
			{
				return Entity(entity, this);
			}
		}

		PEACH_CORE_WARN("Scene::getEntity(tag: {}), Nessun Entity trovato con quel tag", tag);
		return Entity();
	}

	Entity Scene::getEntity(UUID uuid)
	{
		try
		{
			return Entity(m_Entities.at(uuid), this);
		}
		catch (const std::exception& e)
		{
			PEACH_CORE_ERROR("Scene::getEntity(uuid: {}), Catturata eccezione: {}", uuid, e.what());
			return Entity();
		}
	}

	void Scene::update(const float deltaTime)
	{
		auto view = m_Registry.view<UpdateComponent>();
		for (auto [entity, updateComp] : view.each())
		{
			if (updateComp.update)
			{
				updateComp.update(Entity(entity, this), deltaTime);
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
