#pragma once

class Object
{
public:
	int layer = 0;
	bool destroy = false;
	bool bCollider = false;
	D3DXVECTOR2 pos = { 0, 0 };
	std::vector<Collider> bodies;

	bool bCamera = true;

	bool bRigidbody = false;
	bool bGround = false;

	float gravity = 9.8f;
	float groundPosY = 0.0f;
	D3DXVECTOR2 force = { 0, 0 };
	D3DXVECTOR2 velocity = { 0, 0 };

	virtual ~Object();
	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coll);
};

class ObjectManager
{
public:
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;

public:
	~ObjectManager();
	void AddObject(Object* addObject);
	void Update(float deltaTime);
	void Collision();
	void Render();
};
