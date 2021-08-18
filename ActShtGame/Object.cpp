#include "DXUT.h"
#include "Object.h"

Object::~Object()
{
}

void Object::Update(float deltaTime)
{
}

void Object::Render()
{
	for (auto& body : bodies)
	{
		if (bCollider)
		{
			D3DXMATRIX matrix;
			D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);

			if (body.type == Collider::Type::AABB)
			{
				D3DXVECTOR2 min = body.aabb.min;
				D3DXVECTOR2 max = body.aabb.max;
				Game::GetInstance().DrawLine(min, D3DXVECTOR2(max.x, min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(max.x, min.y), max, matrix, body.color);
				Game::GetInstance().DrawLine(max, D3DXVECTOR2(min.x, max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(min.x, max.y), min, matrix, body.color);
			}
		}
	}
}

void Object::OnCollision(Collider& coli)
{
}


ObjectManager::~ObjectManager()
{
	for (auto object : objects)
		SAFE_DELETE(object);

	for (auto addObject : addObjects)
		SAFE_DELETE(addObject);
}

void ObjectManager::AddObject(Object* addObject)
{
	addObjects.push_back(addObject);
}

void ObjectManager::Update(float deltaTime)
{
	objects.insert(objects.end(), addObjects.begin(), addObjects.end());
	addObjects.clear();

	std::sort(objects.begin(), objects.end(), [](const Object* lhs, const Object* rhs) -> bool {return lhs->layer < rhs->layer; });

	for (auto it = objects.begin(); it != objects.end();)
	{
		(*it)->Update(deltaTime);
		if ((*it)->destroy)
		{
			SAFE_DELETE(*it);
			it = objects.erase(it);
		}
		else
			++it;
	}
}

void ObjectManager::OnCollision()
{
	for (auto it = objects.begin(); it != objects.end(); ++it)
	{
		for (auto it2 = it + 1; it2 != objects.end(); ++it2)
		{
			for (auto body1 : (*it)->bodies)
			{
				for (auto body2 : (*it2)->bodies)
				{
					if (IntersectCollider(body1, body2))
					{
						(*it)->OnCollision(body2);
						(*it2)->OnCollision(body1);
					}
				}
			}
		}
	}
}

void ObjectManager::Render()
{
	for (auto object : objects)
		object->Render();
}

