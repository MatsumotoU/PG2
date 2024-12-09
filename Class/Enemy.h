#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Camera.h"

class Enemy:public GameObject
{
public:

	static int isAlive;

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);

private:

	Camera* camera;
	float moveSpeed;
};

