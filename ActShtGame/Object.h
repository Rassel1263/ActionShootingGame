#pragma once

class Collider;
class Object
{
public:
	bool destroy = false;
	bool bCollider = false;
	int layer = 0;
	D3DXVECTOR2 pos = { 0, 0 };
	std::vector<Collider> bodies;

	bool bRigidbody = false;
	bool bGround = false;

	float gravity = 9.8f;
	float groundPosY = 0.0f;
	D3DXVECTOR3 force = { 0, 0, 0 };
	D3DXVECTOR3 velocity = { 0, 0, 0 };

	virtual ~Object();

	virtual void Update(float deltaTime);
	virtual void Render();
	virtual void OnCollision(Collider& coli);
};

class ObjectManager
{
private:
	std::vector<Object*> objects;
	std::vector<Object*> addObjects;

public:
	virtual ~ObjectManager();
	void AddObject(Object* addObject);
	void Update(float deltaTime);
	void OnCollision();
	void Render();
	void UIRender();
};

