#include "Exmath.h"

using namespace KamataEngine;

Vector3 operator+(const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
Vector3 operator-(const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
Vector3 operator*(float s, const Vector3& v) { return Multiply(s, v); }
Vector3 operator*(const Vector3& v, float s) { return s * v; }
Vector3 operator/(const Vector3& v, float s) { return Multiply(1.0f / s, v); }
Matrix4x4 operator+(const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
Matrix4x4 operator-(const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

Vector3 operator-(const Vector3& v) { return{ -v.x,-v.y,-v.z }; }
Vector3 operator+(const Vector3& v) { return v; }

Quaternion operator*(const Quaternion& q1, const Quaternion& q2)
{
	return Quaternion(q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z);
}



//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;

	return result;
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;

	return result;
}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;

	return result;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result;
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return result;
}


//長さ
float Length(const Vector3& v) {
	float result;
	result = v.x * v.x + v.y * v.y + v.z * v.z;
	result = sqrtf(result);

	return result;
}

//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result;

	float length = Length(v);
	result.x = v.x / length;
	result.y = v.y / length;
	result.z = v.z / length;

	return result;
}



//加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] + m2.m[i][j];
		}
	}

	return result;
}

//減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m1.m[i][j] - m2.m[i][j];
		}
	}

	return result;
}

//積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	return result;
}

Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 result;

	// 行列の余因子行列を計算
	result.m[0][0] = m.m[1][1] * m.m[2][2] * m.m[3][3] + m.m[1][2] * m.m[2][3] * m.m[3][1] + m.m[1][3] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][3] * m.m[3][2] - m.m[1][2] * m.m[2][1] * m.m[3][3] - m.m[1][3] * m.m[2][2] * m.m[3][1];
	result.m[0][1] = m.m[0][1] * m.m[2][3] * m.m[3][2] + m.m[0][2] * m.m[2][1] * m.m[3][3] + m.m[0][3] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][2] * m.m[3][3] - m.m[0][2] * m.m[2][3] * m.m[3][1] - m.m[0][3] * m.m[2][1] * m.m[3][2];
	result.m[0][2] = m.m[0][1] * m.m[1][2] * m.m[3][3] + m.m[0][2] * m.m[1][3] * m.m[3][1] + m.m[0][3] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][3] * m.m[3][2] - m.m[0][2] * m.m[1][1] * m.m[3][3] - m.m[0][3] * m.m[1][2] * m.m[3][1];
	result.m[0][3] = m.m[0][1] * m.m[1][3] * m.m[2][2] + m.m[0][2] * m.m[1][1] * m.m[2][3] + m.m[0][3] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][2] * m.m[2][3] - m.m[0][2] * m.m[1][3] * m.m[2][1] - m.m[0][3] * m.m[1][1] * m.m[2][2];

	result.m[1][0] = m.m[1][0] * m.m[2][3] * m.m[3][2] + m.m[1][2] * m.m[2][0] * m.m[3][3] + m.m[1][3] * m.m[2][2] * m.m[3][0] - m.m[1][0] * m.m[2][2] * m.m[3][3] - m.m[1][2] * m.m[2][3] * m.m[3][0] - m.m[1][3] * m.m[2][0] * m.m[3][2];
	result.m[1][1] = m.m[0][0] * m.m[2][2] * m.m[3][3] + m.m[0][2] * m.m[2][3] * m.m[3][0] + m.m[0][3] * m.m[2][0] * m.m[3][2] - m.m[0][0] * m.m[2][3] * m.m[3][2] - m.m[0][2] * m.m[2][0] * m.m[3][3] - m.m[0][3] * m.m[2][2] * m.m[3][0];
	result.m[1][2] = m.m[0][0] * m.m[1][3] * m.m[3][2] + m.m[0][2] * m.m[1][0] * m.m[3][3] + m.m[0][3] * m.m[1][2] * m.m[3][0] - m.m[0][0] * m.m[1][2] * m.m[3][3] - m.m[0][2] * m.m[1][3] * m.m[3][0] - m.m[0][3] * m.m[1][0] * m.m[3][2];
	result.m[1][3] = m.m[0][0] * m.m[1][2] * m.m[2][3] + m.m[0][2] * m.m[1][3] * m.m[2][0] + m.m[0][3] * m.m[1][0] * m.m[2][2] - m.m[0][0] * m.m[1][3] * m.m[2][2] - m.m[0][2] * m.m[1][0] * m.m[2][3] - m.m[0][3] * m.m[1][2] * m.m[2][0];

	result.m[2][0] = m.m[1][0] * m.m[2][1] * m.m[3][3] + m.m[1][1] * m.m[2][3] * m.m[3][0] + m.m[1][3] * m.m[2][0] * m.m[3][1] - m.m[1][0] * m.m[2][3] * m.m[3][1] - m.m[1][1] * m.m[2][0] * m.m[3][3] - m.m[1][3] * m.m[2][1] * m.m[3][0];
	result.m[2][1] = m.m[0][0] * m.m[2][3] * m.m[3][1] + m.m[0][1] * m.m[2][0] * m.m[3][3] + m.m[0][3] * m.m[2][1] * m.m[3][0] - m.m[0][0] * m.m[2][1] * m.m[3][3] - m.m[0][1] * m.m[2][3] * m.m[3][0] - m.m[0][3] * m.m[2][0] * m.m[3][1];
	result.m[2][2] = m.m[0][0] * m.m[1][1] * m.m[3][3] + m.m[0][1] * m.m[1][3] * m.m[3][0] + m.m[0][3] * m.m[1][0] * m.m[3][1] - m.m[0][0] * m.m[1][3] * m.m[3][1] - m.m[0][1] * m.m[1][0] * m.m[3][3] - m.m[0][3] * m.m[1][1] * m.m[3][0];
	result.m[2][3] = m.m[0][0] * m.m[1][3] * m.m[2][1] + m.m[0][1] * m.m[1][0] * m.m[2][3] + m.m[0][3] * m.m[1][1] * m.m[2][0] - m.m[0][0] * m.m[1][1] * m.m[2][3] - m.m[0][1] * m.m[1][3] * m.m[2][0] - m.m[0][3] * m.m[1][0] * m.m[2][1];

	result.m[3][0] = m.m[1][0] * m.m[2][2] * m.m[3][1] + m.m[1][1] * m.m[2][0] * m.m[3][2] + m.m[1][2] * m.m[2][1] * m.m[3][0] - m.m[1][0] * m.m[2][1] * m.m[3][2] - m.m[1][1] * m.m[2][2] * m.m[3][0] - m.m[1][2] * m.m[2][0] * m.m[3][1];
	result.m[3][1] = m.m[0][0] * m.m[2][1] * m.m[3][2] + m.m[0][1] * m.m[2][2] * m.m[3][0] + m.m[0][2] * m.m[2][0] * m.m[3][1] - m.m[0][0] * m.m[2][2] * m.m[3][1] - m.m[0][1] * m.m[2][0] * m.m[3][2] - m.m[0][2] * m.m[2][1] * m.m[3][0];
	result.m[3][2] = m.m[0][0] * m.m[1][2] * m.m[3][1] + m.m[0][1] * m.m[1][0] * m.m[3][2] + m.m[0][2] * m.m[1][1] * m.m[3][0] - m.m[0][0] * m.m[1][1] * m.m[3][2] - m.m[0][1] * m.m[1][2] * m.m[3][0] - m.m[0][2] * m.m[1][0] * m.m[3][1];
	result.m[3][3] = m.m[0][0] * m.m[1][1] * m.m[2][2] + m.m[0][1] * m.m[1][2] * m.m[2][0] + m.m[0][2] * m.m[1][0] * m.m[2][1] - m.m[0][0] * m.m[1][2] * m.m[2][1] - m.m[0][1] * m.m[1][0] * m.m[2][2] - m.m[0][2] * m.m[1][1] * m.m[2][0];

	// 行列式を計算
	float dete = m.m[0][0] * result.m[0][0] + m.m[0][1] * result.m[1][0] + m.m[0][2] * result.m[2][0] + m.m[0][3] * result.m[3][0];


	if (dete == 0) {

		return result;
	}

	// 行列の逆行列を計算
	float factor = 1.0f / dete;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] *= factor;
		}
	}

	return result;
}
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 result;

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = m.m[j][i];
		}
	}

	return result;
}

//単位行列を作成
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 result;

	result.m[0][0] = 1.0f;
	result.m[0][1] = 0.0f;
	result.m[0][2] = 0.0f;
	result.m[0][3] = 0.0f;

	result.m[1][0] = 0.0f;
	result.m[1][1] = 1.0f;
	result.m[1][2] = 0.0f;
	result.m[1][3] = 0.0f;

	result.m[2][0] = 0.0f;
	result.m[2][1] = 0.0f;
	result.m[2][2] = 1.0f;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;
}




//平行移動行列
Matrix4x4 MakeTraslateMatrix(const Vector3& translate) {
	Matrix4x4 result;
	// 単位行列で初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			} else {
				result.m[i][j] = 0.0f;
			}
		}
	}

	// 平行移動の値をセット
	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

//拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	Matrix4x4 result;

	// 単位行列で初期化
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (i == j) {
				result.m[i][j] = 1.0f;
			} else {
				result.m[i][j] = 0.0f;
			}
		}
	}

	// スケールの値をセット
	result.m[0][0] = scale.x; // x軸方向の拡大縮小
	result.m[1][1] = scale.y; // y軸方向の拡大縮小
	result.m[2][2] = scale.z; // z軸方向の拡大縮小

	return result;
}


//座標変換
Vector3 TransForm(const Vector3& vector3, const Matrix4x4& mrix) {
	Vector3 result;

	result.x = vector3.x * mrix.m[0][0] + vector3.y * mrix.m[1][0] +
		vector3.z * mrix.m[2][0] + mrix.m[3][0]; // x成分の変換

	result.y = vector3.x * mrix.m[0][1] + vector3.y * mrix.m[1][1] +
		vector3.z * mrix.m[2][1] + mrix.m[3][1]; // y成分の変換

	result.z = vector3.x * mrix.m[0][2] + vector3.y * mrix.m[1][2] +
		vector3.z * mrix.m[2][2] + mrix.m[3][2]; // z成分の変換

	float length = vector3.x * mrix.m[0][3] + vector3.y * mrix.m[1][3] + vector3.z * mrix.m[2][3] + mrix.m[3][3];
	if (length != 0.0f) {
		result.x /= length;
		result.y /= length;
		result.z /= length;
	}
	return result;
}

//1.X軸回転行列
Matrix4x4 MakeRotateXMatrix(float radian) {
	Matrix4x4 result;
	float cos = cosf(radian);
	float sin = sinf(radian);

	result.m[0][0] = 1.0f; result.m[0][1] = 0.0f; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f; result.m[1][1] = cos;  result.m[1][2] = sin;  result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f; result.m[2][1] = -sin; result.m[2][2] = cos;  result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;
	return result;
}

//2.Y軸回転行列
Matrix4x4 MakeRotateYMatrix(float radian) {
	Matrix4x4 result;
	float cos = cosf(radian);
	float sin = sinf(radian);

	result.m[0][0] = cos; result.m[0][1] = 0.0f; result.m[0][2] = -sin; result.m[0][3] = 0.0f;
	result.m[1][0] = 0.0f; result.m[1][1] = 1.0f;  result.m[1][2] = 0.0f;  result.m[1][3] = 0.0f;
	result.m[2][0] = sin; result.m[2][1] = 0.0f; result.m[2][2] = cos;  result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;
	return result;
}

//3.Z軸回転行列
Matrix4x4 MakeRotateZMatrix(float radian) {
	Matrix4x4 result;
	float cos = cosf(radian);
	float sin = sinf(radian);

	result.m[0][0] = cos; result.m[0][1] = sin; result.m[0][2] = 0.0f; result.m[0][3] = 0.0f;
	result.m[1][0] = -sin; result.m[1][1] = cos;  result.m[1][2] = 0.0f;  result.m[1][3] = 0.0f;
	result.m[2][0] = 0.0f; result.m[2][1] = 0.0f; result.m[2][2] = 1.0f;  result.m[2][3] = 0.0f;
	result.m[3][0] = 0.0f; result.m[3][1] = 0.0f; result.m[3][2] = 0.0f; result.m[3][3] = 1.0f;
	return result;
}

//回転行列の合成
Matrix4x4 RotateXYZMatrix(const Vector3& radian) {
	Matrix4x4 result = Multiply(MakeRotateXMatrix(radian.x), Multiply(MakeRotateYMatrix(radian.y), MakeRotateZMatrix(radian.z)));

	return result;
}

//3次元アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result;
	result.m[0][3] = 0.0f;
	result.m[1][3] = 0.0f;
	result.m[2][3] = 0.0f;
	result.m[3][3] = 1.0f;

	Matrix4x4 rotateM = RotateXYZMatrix(rotate);

	result.m[0][0] = scale.x * rotateM.m[0][0];
	result.m[0][1] = scale.x * rotateM.m[0][1];
	result.m[0][2] = scale.x * rotateM.m[0][2];

	result.m[1][0] = scale.y * rotateM.m[1][0];
	result.m[1][1] = scale.y * rotateM.m[1][1];
	result.m[1][2] = scale.y * rotateM.m[1][2];

	result.m[2][0] = scale.z * rotateM.m[2][0];
	result.m[2][1] = scale.z * rotateM.m[2][1];
	result.m[2][2] = scale.z * rotateM.m[2][2];

	result.m[3][0] = translate.x;
	result.m[3][1] = translate.y;
	result.m[3][2] = translate.z;

	return result;
}

//1.透視射影行列
Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	float conAs = 1.0f / tanf(fovY / 2.0f);
	Matrix4x4 result;
	result.m[0][0] = 1.0f / aspectRatio * conAs;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = conAs;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = farClip / (farClip - nearClip);
	result.m[2][3] = 1.0f;

	result.m[3][0] = 0;
	result.m[3][1] = 0;
	result.m[3][2] = -nearClip * farClip / (farClip - nearClip);
	result.m[3][3] = 0;

	return result;
}

//2.正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = 1.0f / (farClip - nearClip);
	result.m[2][3] = 0;

	result.m[3][0] = (left + right) / (left - right);
	result.m[3][1] = (top + bottom) / (bottom - top);
	result.m[3][2] = nearClip / (nearClip - farClip);
	result.m[3][3] = 1.0f;

	return result;
}

//3.ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 result;

	result.m[0][0] = width / 2.0f;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[0][3] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = -height / 2.0f;
	result.m[1][2] = 0;
	result.m[1][3] = 0;

	result.m[2][0] = 0;
	result.m[2][1] = 0;
	result.m[2][2] = maxDepth - minDepth;
	result.m[2][3] = 0;

	result.m[3][0] = left + width / 2.0f;
	result.m[3][1] = top + height / 2.0f;
	result.m[3][2] = minDepth;
	result.m[3][3] = 1.0f;

	return result;
}

// クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix) {
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdvision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdvision);

	for (uint32_t xIndex = 0; xIndex <= kSubdvision;++xIndex) {
		float x = -kGridHalfWidth + (xIndex * kGridEvery);
		unsigned int color = 0xAAAAAAFF;

		Vector3 start{ x,0.0f,-kGridHalfWidth };
		Vector3 end{ x,0.0f,kGridHalfWidth };

		Vector3 startScreen = TransForm(TransForm(start, viewProjectionMatrix), viewPortMatrix);
		Vector3 endScreen = TransForm(TransForm(end, viewProjectionMatrix), viewPortMatrix);

		if (x == 0.0f) {
			color = BLACK;
		}

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);
	}

	//左から右も同じように引く
	for (uint32_t zIndex = 0; zIndex <= kSubdvision;++zIndex) {
		float z = -kGridHalfWidth + (zIndex * kGridEvery);
		unsigned int color = 0xAAAAAAFF;

		Vector3 start{ -kGridHalfWidth ,0.0f,z };
		Vector3 end{ kGridHalfWidth ,0.0f,z };

		Vector3 startScreen = TransForm(TransForm(start, viewProjectionMatrix), viewPortMatrix);
		Vector3 endScreen = TransForm(TransForm(end, viewProjectionMatrix), viewPortMatrix);

		if (z == 0.0f) {
			color = BLACK;
		}

		Novice::DrawLine(int(startScreen.x), int(startScreen.y), int(endScreen.x), int(endScreen.y), color);
	}
}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, Matrix4x4& viewPortMatrix, uint32_t color) {
	float pi = float(M_PI);
	const uint32_t kSubdvision = 16;			//分割数
	const float kLonEvery = 2.0f * pi / kSubdvision;	//経度分割一つ分の角度
	const float kLatEvery = pi / kSubdvision;	//緯度分割一つ分の角度

	for (uint32_t latIndex = 0;latIndex < kSubdvision;++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;
		//経度の方に分割0~2π
		for (uint32_t lonIndex = 0;lonIndex < kSubdvision;++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			Vector3 a = {
				sphere.radius * (cosf(lat) * cosf(lon)) + sphere.center.x,//x
				sphere.radius * (sinf(lat)) + sphere.center.y,		//y
				sphere.radius * (cosf(lat) * sinf(lon)) + sphere.center.z//z
			};

			Vector3 b = {
				sphere.radius * cosf(lat + kLatEvery) * cosf(lon) + sphere.center.x,
				sphere.radius * sinf(lat + kLatEvery) + sphere.center.y,
				sphere.radius * cosf(lat + kLatEvery) * sinf(lon) + sphere.center.z
			};

			Vector3 c = {
				sphere.radius * cosf(lat) * cosf(lon + kLonEvery) + sphere.center.x,
				sphere.radius * sinf(lat) + sphere.center.y,
				sphere.radius * cosf(lat) * sinf(lon + kLonEvery) + sphere.center.z
			};




			Vector3 aScreen = TransForm(TransForm(a, viewProjectionMatrix), viewPortMatrix);
			Vector3 bScreen = TransForm(TransForm(b, viewProjectionMatrix), viewPortMatrix);
			Vector3 cScreen = TransForm(TransForm(c, viewProjectionMatrix), viewPortMatrix);


			//a,b,c,をスクリーン座標に変換


			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(bScreen.x), int(bScreen.y), color);
			Novice::DrawLine(int(aScreen.x), int(aScreen.y), int(cScreen.x), int(cScreen.y), color);

		}
	}
}


Vector3 Project(const Vector3& v1, const Vector3& v2) {
	float dotProduct = Dot(v1, v2);
	float lengthSquared = Length(v2) * Length(v2);
	float scalar = dotProduct / lengthSquared;
	return Multiply(scalar, v2);
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	Vector3 segmentToPoint = Subtract(point, segment.origin);
	Vector3 projection = Project(segmentToPoint, segment.diff);

	float projectionLengthSquared = Length(projection) * Length(projection);
	float segmentLengthSquared = Length(segment.diff) * Length(segment.diff);

	if (projectionLengthSquared <= segmentLengthSquared && Dot(projection, segment.diff) >= 0) {
		return Add(segment.origin, projection);
	} else {
		Vector3 endpoint = Add(segment.origin, segment.diff);
		Vector3 toEndpoint = Subtract(point, endpoint);
		if (Length(segmentToPoint) * Length(segmentToPoint) < Length(toEndpoint) * Length(toEndpoint)) {
			return segment.origin;
		} else {
			return endpoint;
		}
	}
}


// 法線に垂直なベクトルを求める関数
Vector3 Perpendicular(const Vector3& normal) {
	if (normal.x != 0 || normal.y != 0) {
		return { -normal.y, normal.x, 0 };
	} else {
		return { 0, -normal.z, normal.y };
	}
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	float cos = std::cos(angle);
	float sin = std::sin(angle);

	Matrix4x4 rotateMatrix = {};
	rotateMatrix.m[0][0] = axis.x * axis.x * (1 - cos) + cos;
	rotateMatrix.m[0][1] = axis.x * axis.y * (1 - cos) + axis.z * sin;
	rotateMatrix.m[0][2] = axis.x * axis.z * (1 - cos) - axis.y * sin;
	rotateMatrix.m[0][3] = 0.0f;

	rotateMatrix.m[1][0] = axis.x * axis.y*(1 - cos) - axis.z * sin;
	rotateMatrix.m[1][1] = axis.y * axis.y * (1 - cos) + cos;
	rotateMatrix.m[1][2] = axis.y * axis.z * (1 - cos) + axis.x * sin;
	rotateMatrix.m[1][3] = 0.0f;

	rotateMatrix.m[2][0] = axis.x * axis.z * (1 - cos) + axis.y * sin;
	rotateMatrix.m[2][1] = axis.y * axis.z * (1 - cos) - axis.x * sin;
	rotateMatrix.m[2][2] = axis.z * axis.z * (1 - cos) + cos;
	rotateMatrix.m[2][3] = 0.0f;

	rotateMatrix.m[3][0] = 0.0f;
	rotateMatrix.m[3][1] = 0.0f;
	rotateMatrix.m[3][2] = 0.0f;
	rotateMatrix.m[3][3] = 1.0f;

		return rotateMatrix;
}

// 平面の描画関数
void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	// 1. 平面の中心点を計算
	Vector3 center = Multiply(plane.distance, plane.normal);

	// 垂直ベクトルを格納する配列
	Vector3 perpendiculars[4];

	// 2. 法線に垂直なベクトルを求める
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));

	// 3. 逆ベクトルを求める
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };

	// 4. 法線とのクロス積を求める
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);

	// 5. 逆ベクトルを求める
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	// 6. 各頂点を計算し、変換
	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Multiply(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = TransForm(TransForm(point, viewProjectionMatrix), viewportMatrix);
	}

	// pointsをそれぞれ結んでDrawLineで矩形を描画する
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[2].x), int(points[2].y), color);
	Novice::DrawLine(int(points[0].x), int(points[0].y), int(points[3].x), int(points[3].y), color);;
	Novice::DrawLine(int(points[1].x), int(points[1].y), int(points[3].x), int(points[3].y), color);;

}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 vertices[3];

	for (uint32_t i = 0;i < 3;i++) {
		vertices[i] = TransForm(TransForm(triangle.vertices[i], viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawTriangle(
		int(vertices[0].x), int(vertices[0].y),
		int(vertices[1].x), int(vertices[1].y),
		int(vertices[2].x), int(vertices[2].y),
		color, kFillModeWireFrame
	);
}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 vertices[8];
	vertices[0] = aabb.min;
	vertices[1] = { aabb.max.x,aabb.min.y,aabb.min.z };
	vertices[2] = { aabb.min.x,aabb.min.y,aabb.max.z };
	vertices[3] = { aabb.max.x,aabb.min.y,aabb.max.z };
	vertices[4] = { aabb.min.x,aabb.max.y,aabb.min.z };
	vertices[5] = { aabb.max.x,aabb.max.y,aabb.min.z };
	vertices[6] = { aabb.min.x,aabb.max.y,aabb.max.z };
	vertices[7] = aabb.max;

	for (uint32_t i = 0;i < 8;i++) {
		vertices[i] = TransForm(TransForm(vertices[i], viewProjectionMatrix), viewportMatrix);
	}


	Novice::DrawLine(int(vertices[0].x), int(vertices[0].y), int(vertices[1].x), int(vertices[1].y), color);
	Novice::DrawLine(int(vertices[0].x), int(vertices[0].y), int(vertices[2].x), int(vertices[2].y), color);
	Novice::DrawLine(int(vertices[1].x), int(vertices[1].y), int(vertices[3].x), int(vertices[3].y), color);
	Novice::DrawLine(int(vertices[2].x), int(vertices[2].y), int(vertices[3].x), int(vertices[3].y), color);

	Novice::DrawLine(int(vertices[0].x), int(vertices[0].y), int(vertices[4].x), int(vertices[4].y), color);
	Novice::DrawLine(int(vertices[1].x), int(vertices[1].y), int(vertices[5].x), int(vertices[5].y), color);
	Novice::DrawLine(int(vertices[2].x), int(vertices[2].y), int(vertices[6].x), int(vertices[6].y), color);
	Novice::DrawLine(int(vertices[3].x), int(vertices[3].y), int(vertices[7].x), int(vertices[7].y), color);

	Novice::DrawLine(int(vertices[4].x), int(vertices[4].y), int(vertices[5].x), int(vertices[5].y), color);
	Novice::DrawLine(int(vertices[4].x), int(vertices[4].y), int(vertices[6].x), int(vertices[6].y), color);
	Novice::DrawLine(int(vertices[5].x), int(vertices[5].y), int(vertices[7].x), int(vertices[7].y), color);
	Novice::DrawLine(int(vertices[6].x), int(vertices[6].y), int(vertices[7].x), int(vertices[7].y), color);
}

// 線形補完を行う関数
Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	result.x = (1 - t) * v1.x + t * v2.x;
	result.y = (1 - t) * v1.y + t * v2.y;
	result.z = (1 - t) * v1.z + t * v2.z;
	return result;
}

// ベジエ曲線を描く関数
void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewPortMatrix, uint32_t color) {

	const int segments = 16; // ベジエ曲線の分割数
	for (int i = 0; i < segments; ++i) {
		float t1 = static_cast<float>(i) / segments;
		float t2 = static_cast<float>(i + 1) / segments;

		// t1とt2に対するベジエ曲線上の点を求める
		Vector3 p1 = Lerp(Lerp(controlPoint0, controlPoint1, t1), Lerp(controlPoint1, controlPoint2, t1), t1);
		Vector3 p2 = Lerp(Lerp(controlPoint0, controlPoint1, t2), Lerp(controlPoint1, controlPoint2, t2), t2);

		//座標変換
		Vector3 transformedP1 = TransForm(p1, viewProjectionMatrix);
		transformedP1 = TransForm(transformedP1, viewPortMatrix);
		Vector3 transformedP2 = TransForm(p2, viewProjectionMatrix);
		transformedP2 = TransForm(transformedP2, viewPortMatrix);

		// 線を描く
		Novice::DrawLine(static_cast<int>(transformedP1.x), static_cast<int>(transformedP1.y),
			static_cast<int>(transformedP2.x), static_cast<int>(transformedP2.y), color);
	}
}

//任意回転Quaternionの生成
Quaternion makeRotateAxisAngleQuaternion(const Vector3& axis, float angle) {

	Quaternion q;
	float halfAngle = angle / 2.0f;
	float sinHalfAngle = sin(halfAngle);

	q.w = cos(halfAngle);
	q.x = axis.x * sinHalfAngle;
	q.y = axis.y * sinHalfAngle;
	q.z = axis.z * sinHalfAngle;

	return q;

}

Quaternion Conjugate(const Quaternion& q) {
	return { -q.x, -q.y, -q.z, q.w };
}

//クォータニオンでベクトルを回転させる関数
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {

	Quaternion vectorQuat = { vector.x, vector.y, vector.z, 0.0f };

	Quaternion qv = quaternion * vectorQuat * Conjugate(quaternion);

	return { qv.x, qv.y, qv.z };
}


//Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {

	Matrix4x4 m;

	m.m[0][0] = 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
	m.m[0][1] = 2 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
	m.m[0][2] = 2 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
	m.m[0][3] = 0;

	m.m[1][0] = 2 * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
	m.m[1][1] = 1 - 2 * (quaternion.x * quaternion.x + quaternion.z * quaternion.z);
	m.m[1][2] = 2 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
	m.m[1][3] = 0;

	m.m[2][0] = 2 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);
	m.m[2][1] = 2 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);
	m.m[2][2] = 1 - 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
	m.m[2][3] = 0;

	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;

	return m;

}






