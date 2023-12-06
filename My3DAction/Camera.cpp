#include "Camera.h"

/**
* @brief Camera�̃R���X�g���N�^
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


// �f�X�g���N�^
Camera::~Camera()
{
}


/**
* @brief �J�������상�\�b�h
* @note  
*/
void Camera::CameraController()
{
	// �J�����̐����p�x����ɉ�]
	if (CheckHitKey(KEY_INPUT_S))
	{
		CameraVAngle += CAMERA_ANGLE_SPEED;
		// ����𒴂����烊�Z�b�g
		if (CameraVAngle >= MAX_VERTICAL_ANGLE)
		{
			CameraVAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_X))
	{
		CameraVAngle -= CAMERA_ANGLE_SPEED;
		// �����𒴂����烊�Z�b�g
		if (CameraVAngle <= MIN_VERTICAL_ANGLE)
		{
			CameraVAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x���E�ɉ�]
	if (CheckHitKey(KEY_INPUT_C))
	{
		CameraHAngle += CAMERA_ANGLE_SPEED;
		// 360�x�𒴂����ꍇ�ł����m�Ȋp�x��ۂ悤��
		if (CameraHAngle >= MAX_HORIZONTAL_ANGLE)
		{
			CameraHAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_Z))
	{
		CameraHAngle -= CAMERA_ANGLE_SPEED;
		// 360�x�𒴂����ꍇ�ł����m�Ȋp�x��ۂ悤��
		if (CameraHAngle <= MIN_HORIZONTAL_ANGLE)
		{
			CameraHAngle += CAMERA_FULL_CIRCLE_DEGREES;
		}
	}

}


/**
* @brief �v���C���[�̈ʒu�Z�o���\�b�h
* @note  �J�����̊p�x�ɍ��킹��̂�Camera�N���X�Œ�`
*/
VECTOR Camera::MoveAlongHAngle(VECTOR move_vec, VECTOR player_pos)
{
	VECTOR TempMoveVector;

	// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z
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
* @brief �ʒu�Z�o���\�b�h
* @note  
*/
void Camera::SetCameraPositionAndDirection(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR HorizontalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR CameraLookAtPos;		// �����_�̈ʒu

	// �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
	CameraLookAtPos = player_pos;
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


/**
* @brief �J���������p�x���擾���ĕԂ�
* @note
*/
float Camera::GetCameraHorizontalAngle()
{
	return CameraHAngle;
}


/**
* @brief �J���������p�x���擾���ĕԂ�
* @note
*/
float Camera::GetCameraVerticalAngle()
{
	return CameraVAngle;
}