#include "Header.h"
#include "Object.h"

void Object::Update(float deltaTime)
{
	if (bRigidbody)
	{
		velocity += force * 10;
		force = { 0, 0 };
		pos += velocity * deltaTime;

		if (abs(velocity.x) >= 100)
			velocity.x -= (bGround ? 10 : 4) * velocity.x / abs(velocity.x) * min(abs(velocity.x), 100) * deltaTime;
		else
			velocity.x = 0;

		if (abs(velocity.y) >= 100)
			velocity.y -= (bGround ? 10 : 4) * velocity.y / abs(velocity.y) * min(abs(velocity.y), 100) * deltaTime;
		else
			velocity.y = 0;

	}
}

void Object::Render()
{
#ifdef _DEBUG
	if (bCollider)
	{
		for (auto body : bodies)
		{
			D3DXMATRIX matrix;
			D3DXMatrixTranslation(&matrix, pos.x, pos.y, 0.0f);

			if (body.type == Collider::TYPE::AABB)
			{
				Game::GetInstance().DrawLine(body.aabb.min, D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.max.x, body.aabb.min.y), body.aabb.max, matrix, body.color);
				Game::GetInstance().DrawLine(body.aabb.max, D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), matrix, body.color);
				Game::GetInstance().DrawLine(D3DXVECTOR2(body.aabb.min.x, body.aabb.max.y), body.aabb.min, matrix, body.color);
			}
		}
	}

#endif // DEBUG

}

void Object::OnCollision(Collider& coll)
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

	std::sort(objects.begin(), objects.end(), [](const Object* lhs, const Object* rhs) -> bool { return lhs->layer < rhs->layer; });

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

void ObjectManager::Collision()
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
	for (auto& object : objects)
		object->Render();
}
