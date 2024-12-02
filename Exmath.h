#pragma once
#include <Novice.h>
#define _USE_MATH_DEFINES
#include <cmath>
#include"math/Vector3.h"
#include"math/Matrix4x4.h"
#include<algorithm>

using namespace KamataEngine;


struct Sphere {
	KamataEngine::Vector3 center;
	float radius;
};

struct Line {
	KamataEngine::Vector3 origin;
	KamataEngine::Vector3 diff;
};

struct Ray {
	KamataEngine::Vector3 origin;
	KamataEngine::Vector3 diff;
};

struct Segment {
	KamataEngine::Vector3 origin;
	KamataEngine::Vector3 diff;
};

struct Plane {
	KamataEngine::Vector3 normal;// 法線
	float distance;//距離
};

struct Triangle {
	KamataEngine::Vector3 vertices[3];//頂点
};

struct AABB {
	KamataEngine::Vector3 min;//最小点
	KamataEngine::Vector3 max;//最小点

};

struct Quaternion {
	float x, y, z, w;
};

//加算
KamataEngine::Vector3 Add(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

//減算
KamataEngine::Vector3 Subtract(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

//スカラー倍
KamataEngine::Vector3 Multiply(float scalar, const KamataEngine::Vector3& v);

//内積
float Dot(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);


//長さ
float Length(const KamataEngine::Vector3& v);

//正規化
KamataEngine::Vector3 Normalize(const KamataEngine::Vector3& v);



//加算
KamataEngine::Matrix4x4 Add(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

//減算
KamataEngine::Matrix4x4 Subtract(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

//積
KamataEngine::Matrix4x4 Multiply(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

KamataEngine::Matrix4x4 Inverse(const KamataEngine::Matrix4x4& m);
//転置行列
KamataEngine::Matrix4x4 Transpose(const KamataEngine::Matrix4x4& m);

//単位行列を作成
KamataEngine::Matrix4x4 MakeIdentity4x4();



//平行移動行列
KamataEngine::Matrix4x4 MakeTraslateMatrix(const KamataEngine::Vector3& translate);

//拡大縮小行列
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);


//座標変換
KamataEngine::Vector3 TransForm(const KamataEngine::Vector3& vector3, const KamataEngine::Matrix4x4& matrix);

//1.X軸回転行列
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);

//2.Y軸回転行列
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);

//3.Z軸回転行列
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

//回転行列の合成
KamataEngine::Matrix4x4 RotateXYZMatrix(const KamataEngine::Vector3& radian);

//3次元アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

//1.透視射影行列
KamataEngine::Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//2.正射影行列
KamataEngine::Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//3.ビューポート変換行列
KamataEngine::Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

//クロス積
KamataEngine::Vector3 Cross(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

void DrawGrid(const KamataEngine::Matrix4x4& viewProjectionMatrix, const KamataEngine::Matrix4x4& viewPortMatrix);

void DrawSphere(const Sphere& sphere, const KamataEngine::Matrix4x4& viewProjectionMatrix, KamataEngine::Matrix4x4& viewportMatrix, uint32_t color);


KamataEngine::Vector3 Project(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);

KamataEngine::Vector3 ClosestPoint(const KamataEngine::Vector3& point, const Segment& segment);

// 平面の頂点を計算する関数
KamataEngine::Vector3 Perpendicular(const KamataEngine::Vector3& normal);

KamataEngine::Matrix4x4 MakeRotateAxisAngle(const KamataEngine::Vector3& axis, float angle);

void DrawPlane(const Plane& plane, const KamataEngine::Matrix4x4& viewProjectionMatrix, const KamataEngine::Matrix4x4& viewportMatrix, uint32_t color);

void DrawTriangle(const Triangle& triangle, const KamataEngine::Matrix4x4& viewProjectionMatrix, const KamataEngine::Matrix4x4& viewportMatrix, uint32_t color);

void DrawAABB(const AABB& aabb, const KamataEngine::Matrix4x4& viewProjectionMatrix, const KamataEngine::Matrix4x4& viewportMatrix, uint32_t color);

KamataEngine::Vector3 Lerp(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2, float t);

void DrawBezier(const KamataEngine::Vector3& controlPoint0, const KamataEngine::Vector3& controlPoint1, const KamataEngine::Vector3& controlPoint2,
	const KamataEngine::Matrix4x4& viewProjectionMatrix, const KamataEngine::Matrix4x4& viewPortMatrix, uint32_t color);

KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v1, const KamataEngine::Vector3& v2);
KamataEngine::Vector3 operator*(float s, const KamataEngine::Vector3& v);
KamataEngine::Vector3 operator*(const KamataEngine::Vector3& v, float s);
KamataEngine::Vector3 operator/(const KamataEngine::Vector3& v, float s);
KamataEngine::Matrix4x4 operator+(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);
KamataEngine::Matrix4x4 operator-(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);
KamataEngine::Matrix4x4 operator*(const KamataEngine::Matrix4x4& m1, const KamataEngine::Matrix4x4& m2);

KamataEngine::Vector3 operator-(const KamataEngine::Vector3& v);
KamataEngine::Vector3 operator+(const KamataEngine::Vector3& v);

Quaternion operator*(const Quaternion& q1, const Quaternion& q2);

Quaternion makeRotateAxisAngleQuaternion(const Vector3& axis, float angle);

Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);

Quaternion Conjugate(const Quaternion& q);

//クォータニオンでベクトルを回転させる関数
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);