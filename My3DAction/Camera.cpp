#include "Camera.h"

/**
* @brief Camera�̃R���X�g���N�^
* 
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


// �f�X�g���N�^
Camera::~Camera()
{
}


/**
* @brief �J�������상�\�b�h
* @note  
*/
void Camera::controller()
{
	// �J�����̐����p�x����ɉ�]
	if (CheckHitKey(KEY_INPUT_S))
	{
		vAngle += CAMERA_ANGLE_SPEED;
		// ����𒴂����烊�Z�b�g
		if (vAngle >= MAX_VERTICAL_ANGLE)
		{
			vAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_X))
	{
		vAngle -= CAMERA_ANGLE_SPEED;
		// �����𒴂����烊�Z�b�g
		if (vAngle <= MIN_VERTICAL_ANGLE)
		{
			vAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x���E�ɉ�]
	if (CheckHitKey(KEY_INPUT_C))
	{
		hAngle += CAMERA_ANGLE_SPEED;
		// 360�x�𒴂����ꍇ�ł����m�Ȋp�x��ۂ悤��
		if (hAngle >= MAX_HORIZONTAL_ANGLE)
		{
			hAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_Z))
	{
		hAngle -= CAMERA_ANGLE_SPEED;
		// 360�x�𒴂����ꍇ�ł����m�Ȋp�x��ۂ悤��
		if (hAngle <= MIN_HORIZONTAL_ANGLE)
		{
			hAngle += CAMERA_FULL_CIRCLE_DEGREES;
		}
	}

}


/**
* @brief �v���C���[�̈ʒu�Z�o���\�b�h
* @note  �J�����̊p�x�ɍ��킹��̂�Camera�N���X�Œ�`
*/
VECTOR Camera::moveAlongHAngle(VECTOR move_vec, VECTOR player_pos)
{
	VECTOR TempMoveVector;

	// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z
	sinParam = sin(hAngle / 180.0f * DX_PI_F);
	cosParam = cos(hAngle / 180.0f * DX_PI_F);
	TempMoveVector.x = move_vec.x * cosParam - move_vec.z * sinParam;
	TempMoveVector.y = 0.0f;
	TempMoveVector.z = move_vec.x * sinParam + move_vec.z * cosParam;

	playerPos = VAdd(player_pos, TempMoveVector);

	// pCollider->Chara_Collision(&playerPos, pEnemy, &TempMoveVector);

	return playerPos;
}


/**
* @brief �ʒu�Z�o���\�b�h
* @note  
*/
void Camera::setPositionAndDirection(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR HorizontalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR CameraLookAtPos;		// �����_�̈ʒu

	// �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
	CameraLookAtPos = player_pos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

	// �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
	sinParam = sin(vAngle / 180.0f * DX_PI_F);
	cosParam = cos(vAngle / 180.0f * DX_PI_F);
	VerticalAnglePos.x = 0.0f;
	VerticalAnglePos.y = sinParam * CAMERA_LOOK_AT_DISTANCE;
	VerticalAnglePos.z = -cosParam * CAMERA_LOOK_AT_DISTANCE;

	// ���ɐ����p�x�𔽉f�����ʒu���Z�o
	sinParam = sin(hAngle / 180.0f * DX_PI_F);
	cosParam = cos(hAngle / 180.0f * DX_PI_F);
	HorizontalAnglePos.x = cosParam * VerticalAnglePos.x - sinParam * VerticalAnglePos.z;
	HorizontalAnglePos.y = VerticalAnglePos.y;
	HorizontalAnglePos.z = sinParam * VerticalAnglePos.x + cosParam * VerticalAnglePos.z;

	// �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	position = VAdd(HorizontalAnglePos, CameraLookAtPos);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(position, CameraLookAtPos);

}


/**
* @brief �J���������p�x���擾���ĕԂ�
* @note
*/
float Camera::getHorizontalAngle()
{
	return hAngle;
}


/**
* @brief �J���������p�x���擾���ĕԂ�
* @note
*/
float Camera::getVerticalAngle()
{
	return vAngle;
}