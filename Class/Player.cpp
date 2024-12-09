#include "Player.h"
#include "Class/Common/Render.h"

void Player::Init() {
	physics.Init();
	transform.pos = { 0.0f,0.0f };
	transform.size = { 32.0f,32.0f };
	transform.scale = { 1.0f,1.0f };
	transform.angle = 0.0f;

	moveSpeed = 8.0f;

	camera = nullptr;

	isActive = true;
}

void Player::Update() {

	// 移動処理
	transform.pos += input->GetControlDir() * moveSpeed;

	// 弾丸発射処理
	if (input->GetPress(DIK_SPACE)) {
		if (!isShot) {
			if (shotCoolDown <= 0) {
				isShot = true;
			}
		}
	}

	// 発射クールダウン処理
	if (shotCoolDown > 0) {
		shotCoolDown--;
	}

	camera->IsInScreen(transform.pos, transform.size);
}

void Player::Draw() {
	Render::DrawEllipse(transform.pos, transform.size, transform.angle, *camera, GREEN, kFillModeSolid);
}

int Player::GetIsShot() {
	return isShot;
}

void Player::SetIsShot(int set) {
	isShot = set;
}

void Player::SetShotCoolDown(int set) {
	shotCoolDown = set;
}

void Player::SetCamera(Camera* set) {
	camera = set;
}
