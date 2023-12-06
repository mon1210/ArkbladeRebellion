#include "Camera.h"

/**
* @brief Cameraのコンストラクタ
* 
*/
Camera::Camera()
{
	cameraPos = VGet(0.f, 0.f, 0.f);
	playerPos = VGet(0.f, 0.f, 0.f);

	CameraHAngle = 0.f;
	CameraVAngle = 40.f;
	SinParam = 0.f;
	CosParam = 0.f;

}


// デストラクタ
Camera::~Camera()
{
}


/**
* @brief カメラ操作メソッド
* @note  
*/
void Camera::CameraController()
{
	// カメラの垂直角度を上に回転
	if (CheckHitKey(KEY_INPUT_S))
	{
		CameraVAngle += CAMERA_ANGLE_SPEED;
		// 上限を超えたらリセット
		if (CameraVAngle >= MAX_VERTICAL_ANGLE)
		{
			CameraVAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// カメラの垂直角度を下に回転
	if (CheckHitKey(KEY_INPUT_X))
	{
		CameraVAngle -= CAMERA_ANGLE_SPEED;
		// 下限を超えたらリセット
		if (CameraVAngle <= MIN_VERTICAL_ANGLE)
		{
			CameraVAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// カメラの水平角度を右に回転
	if (CheckHitKey(KEY_INPUT_C))
	{
		CameraHAngle += CAMERA_ANGLE_SPEED;
		// 360度を超えた場合でも正確な角度を保つように
		if (CameraHAngle >= MAX_HORIZONTAL_ANGLE)
		{
			CameraHAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// カメラの水平角度を左に回転
	if (CheckHitKey(KEY_INPUT_Z))
	{
		CameraHAngle -= CAMERA_ANGLE_SPEED;
		// 360度を超えた場合でも正確な角度を保つように
		if (CameraHAngle <= MIN_HORIZONTAL_ANGLE)
		{
			CameraHAngle += CAMERA_FULL_CIRCLE_DEGREES;
		}
	}

}


/**
* @brief プレイヤーの位置算出メソッド
* @note  カメラの角度に合わせるのでCameraクラスで定義
*/
VECTOR Camera::MoveAlongHAngle(VECTOR move_vec, VECTOR player_pos)
{
	VECTOR TempMoveVector;

	// カメラの角度に合わせて移動ベクトルを回転してから加算
	SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
	TempMoveVector.x = move_vec.x * CosParam - move_vec.z * SinParam;
	TempMoveVector.y = 0.0f;
	TempMoveVector.z = move_vec.x * SinParam + move_vec.z * CosParam;

	playerPos = VAdd(player_pos, TempMoveVector);

	// pCollider->Chara_Collision(&playerPos, pEnemy, &TempMoveVector);

	return playerPos;
}


/**
* @brief 位置算出メソッド
* @note  
*/
void Camera::SetCameraPositionAndDirection(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// 垂直角度を反映した位置
	VECTOR HorizontalAnglePos;	// 水平角度を反映した位置
	VECTOR CameraLookAtPos;		// 注視点の位置

	// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
	CameraLookAtPos = player_pos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// カメラの位置はカメラの水平角度と垂直角度から算出

	// 最初に垂直角度を反映した位置を算出
	SinParam = sin(CameraVAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraVAngle / 180.0f * DX_PI_F);
	VerticalAnglePos.x = 0.0f;
	VerticalAnglePos.y = SinParam * CAMERA_LOOK_AT_DISTANCE;
	VerticalAnglePos.z = -CosParam * CAMERA_LOOK_AT_DISTANCE;

	// 次に水平角度を反映した位置を算出
	SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
	HorizontalAnglePos.x = CosParam * VerticalAnglePos.x - SinParam * VerticalAnglePos.z;
	HorizontalAnglePos.y = VerticalAnglePos.y;
	HorizontalAnglePos.z = SinParam * VerticalAnglePos.x + CosParam * VerticalAnglePos.z;

	// 算出した座標に注視点の位置を加算したものがカメラの位置
	cameraPos = VAdd(HorizontalAnglePos, CameraLookAtPos);

	// カメラの設定に反映する
	SetCameraPositionAndTarget_UpVecY(cameraPos, CameraLookAtPos);

}


/**
* @brief カメラ水平角度を取得して返す
* @note
*/
float Camera::GetCameraHorizontalAngle()
{
	return CameraHAngle;
}


/**
* @brief カメラ垂直角度を取得して返す
* @note
*/
float Camera::GetCameraVerticalAngle()
{
	return CameraVAngle;
}