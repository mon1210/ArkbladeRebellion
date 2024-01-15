#include "Camera.h"

/**
* @brief Cameraのコンストラクタ
*/
Camera::Camera(Game *Game_)
{
	pGame = Game_;
}


// デストラクタ
Camera::~Camera()
{
}


/**
* @brief カメラの更新
*/
void Camera::update()
{
	// 操作メソッド
	control();

	// カメラの位置算出
	if (pGame)
		setPosition(pGame->GetPlayer()->GetPos());

}


/**
* @brief カメラ操作メソッド
*/
void Camera::control()
{
	// カメラの垂直角度を上に回転
	if (CheckHitKey(KEY_INPUT_I))
	{
		vAngle += CAMERA_ANGLE_SPEED;
		// 上限を超えたらリセット
		if (vAngle >= MAX_VERTICAL_ANGLE)
		{
			vAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// カメラの垂直角度を下に回転
	if (CheckHitKey(KEY_INPUT_K))
	{
		vAngle -= CAMERA_ANGLE_SPEED;
		// 下限を超えたらリセット
		if (vAngle <= MIN_VERTICAL_ANGLE)
		{
			vAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// カメラの水平角度を右に回転
	if (CheckHitKey(KEY_INPUT_L))
	{
		hAngle += CAMERA_ANGLE_SPEED;
		// 360度を超えた場合でも正確な角度を保つように
		if (hAngle >= MAX_HORIZONTAL_ANGLE)
		{
			hAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// カメラの水平角度を左に回転
	if (CheckHitKey(KEY_INPUT_J))
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
	VECTOR NewPlayerPos;

	// カメラの角度に合わせて移動ベクトルを回転してから加算

	// カメラの水平角度に対するsin, cos値を算出
	float sinParam = sin(hAngle / 180.0f * DX_PI_F);
	float cosParam = cos(hAngle / 180.0f * DX_PI_F);
	// 移動ベクトルを水平方向に回転して保存
	NewPlayerPos.x = move_vec.x * cosParam - move_vec.z * sinParam;
	NewPlayerPos.y = 0.0f;	// 上下は無視
	NewPlayerPos.z = move_vec.x * sinParam + move_vec.z * cosParam;

	NewPlayerPos = VAdd(player_pos, NewPlayerPos);

	return NewPlayerPos;
}


/**
* @brief 位置算出メソッド
*/
void Camera::setPosition(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// 垂直角度を反映した位置
	VECTOR HorizontalAnglePos;	// 水平角度を反映した位置
	VECTOR CameraLookAtPos;		// 注視点の位置

	// 注視点はキャラクターモデルの座標から CAMERA_LOOK_AT_HEIGHT 分だけ高い位置
	CameraLookAtPos = player_pos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// カメラの位置はカメラの水平角度と垂直角度から算出

	// 最初に垂直角度を反映した位置を算出
	float sinParam = sin(vAngle / 180.0f * DX_PI_F);
	float cosParam = cos(vAngle / 180.0f * DX_PI_F);
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
float Camera::GetHorizontalAngle()
{
	return hAngle;
}
