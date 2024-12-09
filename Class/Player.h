#pragma once
#include "Class/Common/GameObject.h"
#include "Class/Common/Camera.h"
#include "Class/Common/InputManager.h"

class Player :public GameObject
{
public:
	void Init()override;
	void Update()override;
	void Draw()override;

	int GetIsShot();

	void SetIsShot(int set);
	void SetShotCoolDown(int set);
	void SetCamera(Camera* set);

private:

	Camera* camera;
	int isShot;
	int shotCoolDown;
	float moveSpeed;

	InputManager* input = InputManager::GetInstance();
};

