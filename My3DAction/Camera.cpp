/*
*
*
*
*/
#include "camera.h"

/*
*
* 
*/
Camera::Camera()
{
	cameraPos = VGet(0.f, 0.f, 0.f);
	playerPos = VGet(0.f, 0.f, 0.f);
	CameraHAngle = 0.0f;
	CameraVAngle = 40.0f;
	SinParam = 0.f;
	CosParam = 0.f;
}


//
Camera::~Camera()
{

}


// 
void Camera::FollowCamera(VECTOR pos)
{
	// 3Dオブジェクトの座標を取得
	playerPos = pos;

	// カメラの位置を3Dオブジェクトの後ろに設定
	SetCameraPositionAndTarget_UpVecY(cameraPos, playerPos);

}


// 
void Camera::CameraController()
{
	// ZCSXキーでカメラの操作
	if (CheckHitKey(KEY_INPUT_C))
	{
		CameraHAngle += CAMERA_ANGLE_SPEED;
		if (CameraHAngle >= 180.0f)
		{
			CameraHAngle -= 360.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_Z))
	{
		CameraHAngle -= CAMERA_ANGLE_SPEED;
		if (CameraHAngle <= -180.0f)
		{
			CameraHAngle += 360.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_S))
	{
		CameraVAngle += CAMERA_ANGLE_SPEED;
		if (CameraVAngle >= 80.0f)
		{
			CameraVAngle = 80.0f;
		}
	}

	if (CheckHitKey(KEY_INPUT_X))
	{
		CameraVAngle -= CAMERA_ANGLE_SPEED;
		if (CameraVAngle <= 0.0f)
		{
			CameraVAngle = 0.0f;
		}
	}
}


// 
VECTOR Camera::MoveAlongHAngle(VECTOR moveVec, VECTOR pPlayerPos)
{
	VECTOR TempMoveVector;

	// カメラの角度に合わせて移動ベクトルを回転してから加算
	SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
	TempMoveVector.x = moveVec.x * CosParam - moveVec.z * SinParam;
	TempMoveVector.y = 0.0f;
	TempMoveVector.z = moveVec.x * SinParam + moveVec.z * CosParam;

	playerPos = VAdd(pPlayerPos, TempMoveVector);

	return playerPos;
}


// 
void Camera::SetCameraPositionAndDirection(VECTOR pPlayerPos)
{
	VECTOR VerticalAnglePos;
	VECTOR HorizontalAnglePos;
	VECTOR CameraLookAtPos;

	// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
	CameraLookAtPos = pPlayerPos;
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