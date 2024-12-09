#include "Enemy.h"
#include "Class/Common/Render.h"

int Enemy::isAlive = true;

void Enemy::Init() {
	physics.Init();
	transform.pos = { 0.0f,0.0f };
	transform.size = { 24.0f,24.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;

	moveSpeed = 4.0f;

	camera = nullptr;

	isActive = true;
}

void Enemy::Update() {

	transform.pos.x += moveSpeed;

	if (transform.pos.x - transform.size.x <= -640.0f || 
		transform.pos.x + transform.size.x >= 640.0f) {

		moveSpeed *= -1.0f;
	}

}

void Enemy::Draw() {

	if (isAlive) {
		Render::DrawEllipse(transform.pos, transform.size, transform.angle, *camera, RED, kFillModeSolid);
	}
}

void Enemy::SetCamera(Camera* set) {
	camera = set;
}
