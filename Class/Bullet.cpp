#include "Bullet.h"
#include "Class/Common/Render.h"

void Bullet::Init() {
	physics.Init();
	transform.pos = { 0.0f,0.0f };
	transform.size = { 16.0f,16.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;

	moveSpeed = 12.0f;

	camera = nullptr;

	isActive = false;
}

void Bullet::Update() {
	if (isActive) {
		transform.pos.y += moveSpeed;

		if (!camera->IsInScreen(transform.pos, transform.size)) {
			isActive = false;
		}
	}
}

void Bullet::Draw() {
	if (isActive) {
		Render::DrawEllipse(transform.pos, transform.size, transform.angle, *camera, WHITE, kFillModeSolid);
	}
}

void Bullet::SetCamera(Camera* set) {
	camera = set;
}
