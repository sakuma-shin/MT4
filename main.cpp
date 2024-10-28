#include <Novice.h>
#include"Exmath.h"

const char kWindowTitle[] = "LE2C_サクマ_シン_MT3";

const int kColmunWidth = 60;
const int kColmunHeight = 50;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


void VectorScreenPrintf(int x, int y, const KamataEngine::Vector3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", v.x);
	Novice::ScreenPrintf(x + kColmunWidth, y, "%.02f", v.y);
	Novice::ScreenPrintf(x + kColmunWidth * 2, y, "%.02f", v.z);
	Novice::ScreenPrintf(x + kColmunWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const KamataEngine::Matrix4x4& matrix, const char* a) {
	Novice::ScreenPrintf(x, y, "%s", a);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + (column + 1) * kColmunWidth, y + (row + 1) * kColmunHeight, "%0.03f", matrix.m[row][column]);
		}
	}
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	KamataEngine::Vector3 axis = Normalize({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;
	KamataEngine::Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);
	

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, rotateMatrix, "rotateMatrix");
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
