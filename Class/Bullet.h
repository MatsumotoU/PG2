#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Camera.h"

class Bullet :public GameObject
{
public:

	void Init()override;
	void Update()override;
	void Draw()override;

	void SetCamera(Camera* set);

private:
	
	Camera* camera;
	float moveSpeed;
};

