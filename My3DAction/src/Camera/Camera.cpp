#include "Camera.h"

/**
* @brief Camera�̃R���X�g���N�^
*/
Camera::Camera(Game *Game)
{
	pGame = Game;
}


// �f�X�g���N�^
Camera::~Camera()
{
}


/**
* @brief �J�����̍X�V
*/
void Camera::update()
{
	// ���상�\�b�h
	control();

	if (pGame)
	{
		// �J�����̈ʒu�Z�o
		setPosition(pGame->GetPlayer()->GetPos());

		// ���[�_�[�̒��S�����̍��W�ƌ����ɐݒ�
		float Rad = static_cast<float>(hAngle * (DX_PI / 180.0f));
		float HAngleRadX = -sinf(Rad);
		float HAngleRadZ = cosf(Rad);
		pGame->GetRadar()->addCenter(position.x, position.z + RADAR_CENTER_OFFSET, HAngleRadX, HAngleRadZ);
	}

}


/**
* @brief �J�������상�\�b�h
*/
void Camera::control()
{
	// �J�����̐����p�x����ɉ�]
	if (CheckHitKey(KEY_INPUT_I))
	{
		vAngle += CAMERA_ANGLE_SPEED;
		// ����𒴂����烊�Z�b�g
		if (vAngle >= MAX_VERTICAL_ANGLE)
		{
			vAngle = MAX_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_K))
	{
		vAngle -= CAMERA_ANGLE_SPEED;
		// �����𒴂����烊�Z�b�g
		if (vAngle <= MIN_VERTICAL_ANGLE)
		{
			vAngle = MIN_VERTICAL_ANGLE;
		}
	}
	// �J�����̐����p�x���E�ɉ�]
	if (CheckHitKey(KEY_INPUT_L))
	{
		hAngle += CAMERA_ANGLE_SPEED;
		// 360�x�𒴂����ꍇ�ł����m�Ȋp�x��ۂ悤��
		if (hAngle >= MAX_HORIZONTAL_ANGLE)
		{
			hAngle -= CAMERA_FULL_CIRCLE_DEGREES;
		}
	}
	// �J�����̐����p�x�����ɉ�]
	if (CheckHitKey(KEY_INPUT_J))
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
	VECTOR NewPlayerPos;

	// �J�����̊p�x�ɍ��킹�Ĉړ��x�N�g������]���Ă�����Z

	// �J�����̐����p�x�ɑ΂���sin, cos�l���Z�o
	float SinParam = sin(hAngle / 180.0f * DX_PI_F);
	float CosParam = cos(hAngle / 180.0f * DX_PI_F);
	// �ړ��x�N�g���𐅕������ɉ�]���ĕۑ�
	NewPlayerPos.x = move_vec.x * CosParam - move_vec.z * SinParam;
	NewPlayerPos.y = 0.0f;	// �㉺�͖���
	NewPlayerPos.z = move_vec.x * SinParam + move_vec.z * CosParam;

	NewPlayerPos = VAdd(player_pos, NewPlayerPos);

	return NewPlayerPos;
}


/**
* @brief �ʒu�Z�o���\�b�h
*/
void Camera::setPosition(VECTOR player_pos)
{
	VECTOR VerticalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR HorizontalAnglePos;	// �����p�x�𔽉f�����ʒu
	VECTOR CameraLookAtPos;		// �����_�̈ʒu

	// �����_�̓L�����N�^�[���f���̍��W���� CAMERA_LOOK_AT_HEIGHT �����������ʒu
	CameraLookAtPos = player_pos;
	CameraLookAtPos.y += CAMERA_LOOK_AT_HEIGHT;

	// �J�����̈ʒu�̓J�����̐����p�x�Ɛ����p�x����Z�o

	// �ŏ��ɐ����p�x�𔽉f�����ʒu���Z�o
	float SinParam = sin(vAngle / 180.0f * DX_PI_F);
	float CosParam = cos(vAngle / 180.0f * DX_PI_F);
	VerticalAnglePos.x = 0.0f;
	VerticalAnglePos.y = SinParam * CAMERA_LOOK_AT_DISTANCE;
	VerticalAnglePos.z = -CosParam * CAMERA_LOOK_AT_DISTANCE;

	// ���ɐ����p�x�𔽉f�����ʒu���Z�o
	SinParam = sin(hAngle / 180.0f * DX_PI_F);
	CosParam = cos(hAngle / 180.0f * DX_PI_F);
	HorizontalAnglePos.x = CosParam * VerticalAnglePos.x - SinParam * VerticalAnglePos.z;
	HorizontalAnglePos.y = VerticalAnglePos.y;
	HorizontalAnglePos.z = SinParam * VerticalAnglePos.x + CosParam * VerticalAnglePos.z;

	// �Z�o�������W�ɒ����_�̈ʒu�����Z�������̂��J�����̈ʒu
	position = VAdd(HorizontalAnglePos, CameraLookAtPos);

	// �J�����̐ݒ�ɔ��f����
	SetCameraPositionAndTarget_UpVecY(position, CameraLookAtPos);

}


/**
* @brief �J���������p�x���擾���ĕԂ�
*/
float Camera::GetHorizontalAngle()
{
	return hAngle;
}
