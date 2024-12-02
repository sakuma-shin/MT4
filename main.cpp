#include <Novice.h>
#include"Exmath.h"

const char kWindowTitle[] = "LE2C_サクマ_シン_MT4";

const int kColumnWidth = 60;
const int kColumnHeight = 50;
const int kWindowWidth = 1280;
const int kWindowHeight = 720;


void VectorScreenPrintf(int x, int y, const KamataEngine::Vector3& v, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", v.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", v.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", v.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const KamataEngine::Matrix4x4& matrix, const char* a) {
	Novice::ScreenPrintf(x, y, "%s", a);
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(
				x + (column + 1) * kColumnWidth, y + (row + 1) * kColumnHeight, "%0.03f", matrix.m[row][column]);
		}
	}
}

void QuaternionScreenPrintf(int x, int y, Quaternion quaternion, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%.02f", quaternion.w);
	Novice::ScreenPrintf(x + kColumnWidth * 4, y, label);
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
		Quaternion rotation0 = makeRotateAxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = makeRotateAxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		QuaternionScreenPrintf(0, kColumnHeight * 0, interpolate0, " : interpolate0");
		QuaternionScreenPrintf(0, kColumnHeight * 1, interpolate1, " : interpolate1");
		QuaternionScreenPrintf(0, kColumnHeight * 2, interpolate2, " : interpolate2");
		QuaternionScreenPrintf(0, kColumnHeight * 3, interpolate3, " : interpolate3");
		QuaternionScreenPrintf(0, kColumnHeight * 4, interpolate4, " : interpolate4");


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
