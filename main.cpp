#include <Novice.h>
#include"Exmath.h"

const char kWindowTitle[] = "LE2C_サクマ_シン_MT4";

const int kColmunWidth = 60;
const int kColmunHeight = 50;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

using namespace KamataEngine;

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

	Vector3 v1{ 1.0f, 3.0f, -5.0f };
	Vector3 v2{ 4.0f, -1.0f, 2.0f };
	

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
		Vector3 from0 = Normalize(Vector3{ 1.0f, 0.7f, 0.5f });
		Vector3 to0 = { -from0.x,-from0.y, -from0.z };
		Vector3 from1 = Normalize(Vector3{ -0.6f, 0.9f, 0.2f });
		Vector3 to1 = Normalize(Vector3{ 0.4f, 0.7f, -0.5f });
		Matrix4x4 rotateMatrix0 = DirectionToDirection(Normalize(Vector3{ 1.0f, 0.0f, 0.0f }), Normalize(Vector3{ -1.0f, 0.0f, 0.0f }));
		Matrix4x4 rotateMatrix1 = DirectionToDirection(from0, to0);
		Matrix4x4 rotateMatrix2 = DirectionToDirection(from1, to1);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		MatrixScreenPrintf(0, 0, rotateMatrix0, "rotateMatrix0");
		MatrixScreenPrintf(0, kColmunHeight * 5, rotateMatrix1, "rotateMatrix1");
		MatrixScreenPrintf(0, kColmunHeight * 10, rotateMatrix2, "rotateMatrix2");
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
