/**
* @file		Constants.h
* @brief	�萔���߂��w�b�_�t�@�C��
* @note		�}�W�b�N�i���o�[�̍폜
*/
#pragma once
#include "DxLib.h"


// �ȉ�BG�p�萔====================================================================================================== //
// �ȏ�BG�p�萔====================================================================================================== //


// �ȉ�Camera�p�萔================================================================================================== //
const float CAMERA_ANGLE_SPEED = 1.f;			// �J�����̃A���O���ύX���x
const float CAMERA_LOOK_AT_HEIGHT = 100.f;		// �J��������������_����v���C���[�܂ł̍���
const float CAMERA_LOOK_AT_DISTANCE = 800.f;	// �J�����ƒ����_�̋���
const float MAX_VERTICAL_ANGLE = 80.f;			// ���������ɑ΂���A���O���ύX�̍ő�l
const float MIN_VERTICAL_ANGLE = 0.f;			// ���������ɑ΂���A���O���ύX�̍ŏ��l
const float MAX_HORIZONTAL_ANGLE = 180.f;		// ���������ɑ΂���A���O���ύX�̍ő�l
const float MIN_HORIZONTAL_ANGLE = -180.f;		// ���������ɑ΂���A���O���ύX�̍ŏ��l
const float CAMERA_FULL_CIRCLE_DEGREES = 360.f;	// ���S�ȉ~�̊p�x
// �ȏ�Camera�p�萔================================================================================================== //


// �ȉ�Collision�p�萔=============================================================================================== //
const int SPATIAL_PARTITION = 32;				// ��ԕ�����
const float CHARA_HEIGHT = 250.f;				// �����蔻��̑傫��
const float CHARA_HIT_PUSH_POWER = 20.f;		// ���������ۂɉ����߂�����
const float PLAYER_CAP_RADIUS = 55.f;			// �v���C���[�̓����蔻��J�v�Z���̔��a
const float ENEMY_CAP_RADIUS = 100.f;			// �G�l�~�[�̓����蔻��J�v�Z���̔��a
const float CAP_HEIGHT = 215.f;					// �J�v�Z���̍���
// �ȏ�Collision�p�萔=============================================================================================== //


// �ȉ�Enemy�p�萔=================================================================================================== //
const int TIME_TO_TRANSITION = 240;				// �G�l�~�[�̍s���J�ڃ^�C�}�[
const int FULL_CIRCLE_DEGREES = 360;			// ���S�ȉ~�̊p�x rand() % �̂��Ƃɂ�int�^�����_���Ȃ̂�Camera�ƕ�����
const float ENEMY_START_POS_X = 300.f;			// �G�l�~�[�̏���X���W
const float ENEMY_START_POS_Y = 0.f;			// �G�l�~�[�̏���Y���W -280
const float ENEMY_START_POS_Z = 900.f;			// �G�l�~�[�̏���Z���W
const float ENEMY_START_ROTATE_Y = 0.f;			// �G�l�~�[�̏�����]Y
const float ENEMY_ANIM_F_INCREMENT = 0.25f;		// �G�l�~�[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float ENEMY_MOVE_SPEED = 2.f;				// �G�l�~�[�̈ړ�����
const float ENEMY_VIEW_RADIUS = 1500.f;			// �G�l�~�[�̎���~�̔��a
// �ȏ�Enemy�p�萔=================================================================================================== //
 

// �ȉ�Grid�p�萔==================================================================================================== //
const int LINE_NUM = 50;						// ���̖{��
const float LINE_AREA_SIZE = 10000.f;			// ����`�悷��G���A�T�C�Y
const float GRID_LINE_START_POSITION = 0.0f;	// ���̕`��J�n�ʒu
// �ȏ�Grid�p�萔==================================================================================================== //


// �ȉ�My3DAction�p�萔============================================================================================== //
const int WINDOW_WIDTH = 640;					// �E�B���h�E����	test
const int WINDOW_HEIGHT = 480;					// �E�B���h�E�c��	test
const int WINDOW_COLOR = 32;					// �E�B���h�E�J���[	test
const int WINDOW_BG_COLOR_OFFSET = 1;			// �w�i�F���J�X�^�}�C�Y���邽�߂̃I�t�Z�b�g
const int WINDOW_POS_Y = 0;						// ������Y���W
const int WINDOW_WIDTH_SIZE = 640;				// �E�B���h�E�̉���
const int WINDOW_HEIGHT_SIZE = 480;				// �E�B���h�E�̏c��
const double DOUBLE_ONE = 1.0;					// �{���x���������_�����e����
const float CAMERA_FAR_DISTANCE = 5000.f;		// �J�����̉��Œ�����
// �ȏ�My3DAction�p�萔============================================================================================== //


// �ȉ�OBBCollider�p�萔============================================================================================= //
const int MAX_VERTICES = 8;						// ���_��Index�ő�l�@�����̂̒��_�Ȃ̂�8
// �ȏ�OBBCollider�p�萔============================================================================================= //


// �ȉ�Player�p�萔================================================================================================== //
const int MAX_ROLL_COOL_TIME = 500;				// Roll�̃N�[���^�C��
const int MAX_HEAL_COUNT = 8;					// �ő�񕜉�
const int HEAL_COUNT_POS_X = 530;				// �񕜉񐔂�\������X���W
const int HEAL_COUNT_POS_Y = 40;				// �񕜉񐔂�\������Y���W
const float PLAYER_START_POS_X = 0.f;			// �v���C���[�̏���X���W
const float PLAYER_START_POS_Y = 0.f;			// �v���C���[�̏���Y���W -250
const float PLAYER_START_POS_Z = 600.f;			// �v���C���[�̏���Z���W
const float PLAYER_START_ROTATE_Y = 180.f;		// �v���C���[�̏�����]Y
const float PLAYER_ANIM_F_INCREMENT = 0.25f;	// �v���C���[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float PLAYER_MOVE_SPEED = 10.f;			// �v���C���[�̈ړ�����
const float PLAYER_ROLL_DISTANCE = 5.f;			// �v���C���[�̑O�]���̈ړ�����
const float PLAYER_ROLL_ANIM_F_INCREMENT = 0.3f;// �v���C���[�̑O�]���̈ړ�����
const float FORWARD_ROTATION_ANGLE = 180.f;		// �v���C���[�O�i���̉�]�p�x
const float RIGHT_ROTATION_ANGLE = -90.f;		// �v���C���[�E�ړ����̉�]�p�x
const float LEFT_ROTATION_ANGLE = 90.f;			// �v���C���[���ړ����̉�]�p�x
const float BACK_ROTATION_ANGLE = 0.f;			// �v���C���[��ړ����̉�]�p�x
const float BACKWARD_ROTATION_ANGLE = 0.f;		// �v���C���[��ގ��̉�]�p�x
const float MODEL_SCALE = 1.5f;					// 3D���f���̊g�嗦
const float MAX_HP = 100.f;						// �ő�HP
const float HEALING_VALUE = 20.f;				// ��x�̉񕜗�
// �ȏ�Player�p�萔================================================================================================== //


// �ȏ�Radar�p�萔================================================================================================== //
// �ȏ�Radar�p�萔================================================================================================== //


// �ȏ�RadarPoint�p�萔============================================================================================== //
const float RADAR_DETECTION_RANGE = 2000.f;		// Radar�̍��G�͈�
const float RADAR_POINT_RADIUS = 5.f;			// Point�̔��a
// �ȏ�RadarPoint�p�萔============================================================================================== //


// �ȉ�SceneManager�p�萔============================================================================================ //
const int MAX_OPACITY = 255;					// ���S�ɕs����(���S�Ɍ�����)
const float FRAME = 60.f;						// �t���[���l
// �ȉ�SceneManager�p�萔============================================================================================ //


// �ȉ�Stage�p�萔=================================================================================================== //
const int STAGE_FADE_TIMER = 120;				// �}�b�v�t�F�[�h�A�E�g��Phase�ҋ@�p 
// �ȏ�Stage�p�萔=================================================================================================== //


// �ȉ�Title�p�萔=================================================================================================== //
const int TITLE_TIMER_INIT = 0;					// �^�C�g���J�n���̃^�C�}�[�����l
const int TITLE_DONE_TIME = 0;					// �^�C�g���t�F�[�h�A�E�g�J�n���̏������l
const int TITLE_FADEOUT_TIME = 30;				// �^�C�g���t�F�[�h�A�E�g�ɗv���鎞��
const int TITLE_LOOP_FRAME = 1516;				// �^�C�g�����[�v����
const int TITLE_LOOP_HALF_FRAME = 758;			// �����̔���(�Ȃ߂炩�ȕ`�惋�[�v)
const int TITLE_POS_X = 0;						// Title��X���W
const int TITLE_POS_Y = 0;						// Title��Y���W
const int TITLE_PS_POS_X = 20;					// PressSpace��X���W
const int TITLE_PS_POS_Y = 240;					// PressSpace��Y���W
// �ȏ�Title�p�萔=================================================================================================== //


// �ȉ�UI�p�萔====================================================================================================== //
const int LOW_HP = 30;							// ���̐��l�ȉ��ŃQ�[�W�̐F�ύX
const int HP_BAR_POS_X = 250;					// HP�o�[��X���W
const int HP_BAR_POS_Y = 20;					// HP�o�[��Y���W
const int HP_BAR_WIDTH = 350;					// HP�o�[�̉���
const int HP_BAR_HEIGHT = 13;					// HP�o�[�̍���
const float HP_CHANGE_AMOUNT = 0.5f;			// HP�̕ω��ʁ@�o�[�̑������x
// �ȏ�UI�p�萔====================================================================================================== //


// �ȉ�Color====================================================================================================== //
const int BLACK = GetColor(	 0,	  0,   0);		// ��
const int WHITE = GetColor(255, 255, 255);		// ��
const int RED	= GetColor(255,   0,   0);		// ��
const int GREEN = GetColor(  0, 255,   0);		// ��
#ifdef _DEBUG
const int BLUE  = GetColor(  0,   0, 255);		// ��
#endif
// �ȏ�Color====================================================================================================== //
