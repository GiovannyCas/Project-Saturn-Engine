#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <queue>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <bitset>
#include <array>
#include <map>


class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}


template <typename T> inline ComponentID getComponentTypeID() noexcept
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}


constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;


using ComponentArray = std::array<Component*, maxComponents>;


class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};

class Entity
{
private:
	bool active = true;
	Manager& manager;
	
	ComponentBitset componentBitset;
	GroupBitset groupBitset;
	ComponentArray componentArray;

	std::vector<std::unique_ptr<Component>> components;

public:
	Entity(Manager& m_Manager) : manager(m_Manager)
	{

	}

	void update()
	{
		for (auto& c : components)
		{
			c->update();
		}
	}

	void draw()
	{
		for (auto& c : components)
		{
			c->draw();
		}
	}

	bool isActive() const
	{
		return active;
	}

	void destory()
	{
		active = false;
	}

	bool hasGroup(Group m_Group)
	{
		return groupBitset[m_Group];
	}

	void addGroup(Group m_Group)
	{
		groupBitset[m_Group] = true;
		//manager.AddToGroup(this, m_Group);
	}
	void delGroup(Group m_Group)
	{
		groupBitset[m_Group] = false;
	}

	template<typename T> bool hasComponent() const
	{
		return componentBitset[getComponentTypeID<T>];
	}

	template<typename T, typename... TArgs>
	T& addCompnent(TArgs&&... m_Args)
	{
		T* c(new T(std::forward<TArgs>(m_Args)...));
		c->entity = this;

		std::unique_ptr<Component> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitset[getComponentTypeID<T>()] = true;
		
		c->init();
		
		return *c;
	}

	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update()
	{
		for (auto& e : entities)
		{
			e->update();
		}
	}

	void draw()
	{
		for (auto& e : entities)
		{
			e->draw();
		}
	}

	void refresh()
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(std::remove_if(std::begin(v), 
				std::end(v), [i](Entity* m_Entity)
				{
					return !m_Entity->isActive() || !m_Entity->hasGroup(i);
				}), std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& m_Entity)
			{
				return !m_Entity->isActive();
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* m_Entity, Group m_Group)
	{
		//groupedEntities[m_Group].emplace_back(m_Entity);
	}

	std::vector<Entity*>& getGroup(Group m_Group)
	{
		return groupedEntities[m_Group];
	}

	int GetSizeOfEntities()
	{
		return entities.size();
	}

	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;

	}

	~Manager()
	{
		//for (int i = 0; i < entities.size(); i++)
		//{
		//	if (entities[i].get()) 
		//	{
		//		//entities[i].release();
		//	}

		//}

		
	}
};

