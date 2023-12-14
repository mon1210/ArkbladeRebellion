#include "Camera.h"

/**
* @brief Cameraのコンストラクタ
*/
Camera::Camera()
{
	position = VGet(0.f, 0.f, 0.f);
	playerPos = VGet(0.f, 0.f, 0.f);

	hAngle = 0.f;
	vAngle = 40.f;
	sinParam = 0.f;
	cosParam = 0.f;

}


// デストラクタ
Camera::~Camera()
{
}


/**
* @brief カメラ操作メソッド
*/
void Camera::controller()
{
	// カメラの垂直角度を上に回転
	if (CheckHitKey(KEY_INPUT_S))
	{
		vAngle += CAMERA_ANGLE_SPEED;
		// 上限を超えたらリセット
		if (vAngle >= MAX_VERTICAL_ANGLE)
		{
			vAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// カメラの垂直角度を下に回転
	if (CheckHitKey(KEY_INPUT_X))
	{
		vAngle -= CAMERA_ANGLE_SPEED;
		// 下限を超えたらリセット
		if (vAngle <= MIN_VERTICAL_ANGLE)
		{
			vAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// カメラの水平角度を右に回転
	if (CheckHitKey(KEY_INPUT_C))
	{
		hAngle += CAMERA_ANGLE_SPEED;
		// 360度を超えた場合でも正確な角度を保つように
		if (hAngle >= MAX_HORIZONTAL_ANGLE)
		{
			hAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// カメラの水平角度を左に回転
	if (CheckHitKey(KEY_INPUT_Z))
	{
		hAngle -= CAMERA_ANGLE_SPEED;
		// 360度を超えた場合でも正確な角度を保つように
		if (hAngle <= MIN_HORIZONTAL_ANGLE)
		{
			hAngle += CAMERA_FULL_CIRCLE_DEGREES;
		}
	}

}


/**
* @brief プレイヤーの位置算出メソッド
* @note  カメラの角度に合わせるのでCameraクラスで定義
*/
VECTOR Camera::moveAlongHAngle(VECTOR move_vec, VECTOR player_pos)
{
	VECTOR TempMoveVector;

	// カメラの角度に合わせて移動ベクトルを回転してから加算

	// カメラの水平角度に対するsin, cos値を算出
	sinParam = sin(hAngle / 180.0f * DX_PI_F);
	cosParam = cos(hAngle / 180.0f * DX_PI_F);
	// 移動ベクトルを水平方向に回転して保存
	TempMoveVector.x = move_vec.x * cosParam - move_vec.z * sinParam;
	TempMoveVector.y = 0.0f;	// 上下は無視
	TempMoveVector.z = move_vec.x * sinParam + move_vec.z * cosParam;

	playerPos = VAdd(player_pos, TempMoveVector);

	// pCollider->Chara_Collision(&playerPos, pEnemy, &TempMoveVector);

	return playerPos;
}


/**
* @brief 位置算出メソッド
*/
void Camera::setPositionAndDirection(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// 垂直角度を反映した位置
	VECTOR HorizontalAnglePos;	// 水平角度を反映した位置
	VECTOR CameraLookAtPos;		// 注視点の位置

	// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
	CameraLookAtPos = player_pos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// カメラの位置はカメラの水平角度と垂直角度から算出

	// 最初に垂直角度を反映した位置を算出
	sinParam = sin(vAngle / 180.0f * DX_PI_F);
	cosParam = cos(vAngle / 180.0f * DX_PI_F);
	VerticalAnglePos.x = 0.0f;
	VerticalAnglePos.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
	VerticalAnglePos.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

	// 次に水平角度を反映した位置を算出
	sinParam = sin(hAngle / 180.0f * DX_PI_F);
	cosParam = cos(hAngle / 180.0f * DX_PI_F);
	HorizontalAnglePos.x = cosParam * VerticalAnglePos.x - sinParam * VerticalAnglePos.z;
	HorizontalAnglePos.y = VerticalAnglePos.y;
	HorizontalAnglePos.z = sinParam * VerticalAnglePos.x + cosParam * VerticalAnglePos.z;

	// 算出した座標に注視点の位置を加算したものがカメラの位置
	position = VAdd(HorizontalAnglePos, CameraLookAtPos);

	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(position, CameraLookAtPos);

}


/**
* @brief カメラ水平角度を取得して返す
*/
float Camera::getHorizontalAngle()
{
	return hAngle;
}


/**
* @brief カメラ垂直角度を取得して返す
*/
float Camera::getVerticalAngle()
{
	return vAngle;
}