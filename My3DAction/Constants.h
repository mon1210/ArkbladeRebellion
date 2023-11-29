/**
* @file		Constants.h
* @brief	�萔���߂��w�b�_�t�@�C��
* @note		�}�W�b�N�i���o�[�̍폜
*/
#pragma once
#include "DxLib.h"

// �΂ߓ��͗p�̊e���̔{��( sin( 45��) )
#define VECTOR_SCALING	0.70710678118f
// 
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 

// �ȉ�BG�p�萔====================================================================================================== //
const float BG_SCALE_FACTOR = 1.0f;				// �w�i�`��̍ۂ̊g�嗦

// �ȏ�BG�p�萔====================================================================================================== //



// �ȉ�Camera�p�萔================================================================================================== //
const float CAMERA_ANGLE_SPEED = 1.f;			// �J�����̃A���O���ύX���x
const float CAMERA_LOOK_AT_HEIGHT = 100.f;		// �J��������������_����v���C���[�܂ł̍���
const float CAMERA_LOOK_AT_DISTANCE = 800.f;	// �J�����ƒ����_�̋���
const float MAX_VERTICAL_ANGLE = 80.f;			// ���������ɑ΂���A���O���ύX�̍ő�l
const float MIN_VERTICAL_ANGLE = 0.f;			// ���������ɑ΂���A���O���ύX�̍ŏ��l
const float MAX_HORIZONTAL_ANGLE = 180.f;		// ���������ɑ΂���A���O���ύX�̍ő�l
const float MIN_HORIZONTAL_ANGLE = -180.f;		// ���������ɑ΂���A���O���ύX�̍ŏ��l
const float FULL_CIRCLE_DEGREES = 360.f;		// ���S�ȉ~�̊p�x
// �ȏ�Camera�p�萔================================================================================================== //


// �ȉ�Enemy�p�萔=================================================================================================== //
const float ENEMY_POS_X = 300.f;				// �G�l�~�[�̏���X���W
const float ENEMY_POS_Y = 0.f;					// �G�l�~�[�̏���Y���W -280
const float ENEMY_POS_Z = 900.f;				// �G�l�~�[�̏���Z���W
const float ENEMY_START_ROTATE_Y = 0.f;			// �G�l�~�[�̏�����]Y
const float ENEMY_ANIM_F_INCREMENT = 0.25f;		// �G�l�~�[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float ENEMY_MOVE_SPEED = 2.f;				// �G�l�~�[�̈ړ�����
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
//const float DEG_TO_RAD = DX_PI_F / 180.f;		// �x�����烉�W�A���ւ̕ύX�p�萔
//const float FLAME_TIME = 1.f / 60.f;			// 
// �ȏ�My3DAction�p�萔============================================================================================== //


// �ȉ�Player�p�萔================================================================================================== //
const float PLAYER_POS_X = 0.f;					// �v���C���[�̏���X���W
const float PLAYER_POS_Y = 0.f;					// �v���C���[�̏���Y���W -250
const float PLAYER_POS_Z = 600.f;				// �v���C���[�̏���Z���W
const float PLAYER_START_ROTATE_Y = 180.f;		// �v���C���[�̏�����]Y
const float PLAYER_ANIM_F_INCREMENT = 0.2f;		// �v���C���[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float PLAYER_MOVE_SPEED = 10.f;			// �v���C���[�̈ړ�����
const float PLAYER_ROLL_DISTANCE = 5.f;			// �v���C���[�̑O�]���̈ړ�����
const float PLAYER_ROLL_ANIM_F_INCREMENT = 0.3f;// �v���C���[�̑O�]���̈ړ�����
const float MODEL_SCALE = 1.5f;					// 3D���f���̊g�嗦
// �ȏ�Player�p�萔================================================================================================== //


// �ȉ�Stage�p�萔=================================================================================================== //
const int STAGE_FADE_TIMER = 120;				// �}�b�v�t�F�[�h�A�E�g��Phase�ҋ@�p 
// �ȏ�Stage�p�萔=================================================================================================== //


// �ȉ�Title�p�萔=================================================================================================== //
const int TITLE_TIMER_INIT = 0;					// �^�C�g���J�n���̃^�C�}�[�����l
const int TITLE_DONE_TIME = 0;					// �^�C�g���t�F�[�h�A�E�g�J�n���̏������l
const int TITLE_FADEOUT_TIME = 30;				// �^�C�g���t�F�[�h�A�E�g�ɗv���鎞��
const int TITLE_LOOP_FRAME = 1516;				// �^�C�g�����[�v����
const int TITLE_LOOP_HALF_FRAME = 758;			// �����̔���(�Ȃ߂炩�ȕ`�惋�[�v)
const int CENTER = 2;							// ��ʂ̃Z���^�[�w��p
const int VERTICAL_SHIFT_AMOUNT = 40;			// PressSpace����ɃV�t�g����
const int TEXT_OPACITY_TIMER = 150;				// PressSpace�̓����x�𑪂鐔�l
const int DARK_THRESHOLD = 60;					// ���̐��l�ȉ��͂��񂾂񓧖�
const int LIGHT_THRESHOLD = 90;					// ���̐��l�ȏ�͂��񂾂�N��
const int DARK_START_OPACITY = 2;				// ���񂾂񓧖��ɂȂ鏉���l
const float MAX_OPACITY = 1.0f;					// �����x�̍ő�l
const float PER_FLOAT = 60.f;					// �t���[���l��
const float DARK_THRESHOLD_FLAME = 30;			// �����ƑN���l�̍�
const float TITLE_MARGIN_ABOVE = 120.f;			// �^�C�g������ɗ]�����J����
const float TITLE_SCALE_FACTOR = 1.0f;			// �^�C�g���`��̊g�嗦
const float TITLE_BLACKOUT_TIME = 30.0f;		// �^�C�g���̃t�F�[�h�A�E�g����ʂ��Â�����
// �ȏ�Title�p�萔=================================================================================================== //
