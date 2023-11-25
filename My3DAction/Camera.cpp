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
	// 3D�I�u�W�F�N�g�̍��W���擾
	playerPos = pos;

	// �J�����̈ʒu��3D�I�u�W�F�N�g�̌��ɐݒ�
	SetCameraPositionAndTarget_UpVecY(cameraPos, playerPos);

}


// 
void Camera::CameraController()
{
	// ZCSX�L�[�ŃJ�����̑���
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

	// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z
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

	// �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
	CameraLookAtPos = pPlayerPos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

	// �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
	SinParam = sin(CameraVAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraVAngle / 180.0f * DX_PI_F);
	VerticalAnglePos.x = 0.0f;
	VerticalAnglePos.y = SinParam * CAMERA_LOOK_AT_DISTANCE;
	VerticalAnglePos.z = -CosParam * CAMERA_LOOK_AT_DISTANCE;

	// ���ɐ����p�x�𔽉f�����ʒu���Z�o
	SinParam = sin(CameraHAngle / 180.0f * DX_PI_F);
	CosParam = cos(CameraHAngle / 180.0f * DX_PI_F);
	HorizontalAnglePos.x = CosParam * VerticalAnglePos.x - SinParam * VerticalAnglePos.z;
	HorizontalAnglePos.y = VerticalAnglePos.y;
	HorizontalAnglePos.z = SinParam * VerticalAnglePos.x + CosParam * VerticalAnglePos.z;

	// �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	cameraPos = VAdd(HorizontalAnglePos, CameraLookAtPos);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(cameraPos, CameraLookAtPos);

}