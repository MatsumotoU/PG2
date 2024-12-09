#include <Novice.h>
#include "Class/Common/Render.h"
#include "Class/Common/InputManager.h"
#include "Class/Common/Collision2D.h"

#include "Class/Player.h"
#include "Class/Bullet.h"
#include "Class/Enemy.h"

const char kWindowTitle[] = "LC1A_22_マツモトユウタ_静的メンバ変数";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	InputManager* input = InputManager::GetInstance();

	Camera mainCamera;
	mainCamera.Init();

	Player player;
	player.Init();
	player.SetCamera(&mainCamera);

	Bullet playerBullet[16];
	for (int i = 0; i < 16; i++) {
		playerBullet[i].Init();
		playerBullet[i].SetCamera(&mainCamera);
	}

	Enemy enemyes[2];
	for (int i = 0; i < 2; i++) {
		enemyes[i].Init();
		enemyes[i].SetCamera(&mainCamera);
	}
	enemyes[0].SetPos({ 200.0f,300.0f });
	enemyes[1].SetPos({ -200.0f,150.0f });

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		input->Update();

		// オブジェクト更新
		mainCamera.Update();
		player.Update();
		for (int i = 0; i < 16; i++) {
			playerBullet[i].Update();
		}
		for (int i = 0; i < 2; i++) {
			enemyes[i].Update();
		}

		// プレイヤー射撃処理
		if (player.GetIsShot()) {
			for (int i = 0; i < 16; i++) {
				if (!playerBullet[i].GetIsActive()) {
					playerBullet[i].SetIsActive(true);
					playerBullet[i].SetPos(player.GetPos());
					player.SetIsShot(false);
					player.SetShotCoolDown(6);
					break;
				}
			}
		}

		// 敵と弾丸の当たり判定
		for (int e = 0; e < 2; e++) {
			if (enemyes[e].GetIsActive()) {

				for (int b = 0; b < 16; b++) {
					if (playerBullet[b].GetIsActive()) {
						
						if (IsHitCollisionEllipse(
							enemyes[e].GetPos(), playerBullet[b].GetPos(),
							enemyes[e].GetSize().x * 0.5f, playerBullet[b].GetSize().x * 0.5f)) {

							enemyes[e].isAlive = false;
						}
					}
				}
			}
		}

		// 敵のリスポーン
		if (input->GetTriger(DIK_R)) {
			enemyes[0].isAlive = true;
		}
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// デバッグ描画
		Novice::ScreenPrintf(0, 0, "enemyA isAlive = %d", enemyes[0].isAlive);
		Novice::ScreenPrintf(0, 20, "enemyB isAlive = %d", enemyes[1].isAlive);
		Novice::ScreenPrintf(0, 40, "WASD : player Move");
		Novice::ScreenPrintf(0, 60, "shot : SPACE");
		Novice::ScreenPrintf(0, 80, "enemy respawn : R");

		// オブジェクト描画
		for (int i = 0; i < 2; i++) {
			enemyes[i].Draw();
		}
		for (int i = 0; i < 16; i++) {
			playerBullet[i].Draw();
		}
		player.Draw();

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
