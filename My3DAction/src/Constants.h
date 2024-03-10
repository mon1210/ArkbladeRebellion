/**
* @file		Constants.h
* @brief	�萔 �̐錾
* @note		�}�W�b�N�i���o�[�̍폜
*/
#pragma once
#include "DxLib.h"


// �ȉ�BG�p�萔======================================================================================================== //
// �ȏ�BG�p�萔======================================================================================================== //


// �ȉ�Camera�p�萔==================================================================================================== //

//! �J�����̃A���O���ύX���x
const float CAMERA_ANGLE_SPEED = 1.f;
//! �J��������������_����v���C���[�܂ł̍���
const float CAMERA_LOOK_AT_HEIGHT = 100.f;
//! �J�����ƒ����_�̋���
const float CAMERA_LOOK_AT_DISTANCE = 800.f;
//! ���������ɑ΂���A���O���ύX�̍ő�l
const float MAX_VERTICAL_ANGLE = 80.f;
//! ���������ɑ΂���A���O���ύX�̍ŏ��l
const float MIN_VERTICAL_ANGLE = 0.f;
//! ���������ɑ΂���A���O���ύX�̍ő�l
const float MAX_HORIZONTAL_ANGLE = 180.f;
//! ���������ɑ΂���A���O���ύX�̍ŏ��l
const float MIN_HORIZONTAL_ANGLE = -180.f;
//! ���S�ȉ~�̊p�x
const float CAMERA_FULL_CIRCLE_DEGREES = 360.f;
//! RadarPoint��Radar�̒��S�ɗ���悤�ɕ␳����l
const float RADAR_CENTER_OFFSET = 350.f;

// �ȏ�Camera�p�萔==================================================================================================== //


// �ȉ�Collision�p�萔================================================================================================= //

//! ��ԕ�����
const int SPATIAL_PARTITION = 32;
//! ���_���X�g�̃T�C�Y
const int VERTICES_LIST_SIZE = 2;
//! OBB�̒��_�̐�
const int OBB_VERTICES = 8;
//! �����蔻��̑傫��
const float CHARA_HEIGHT = 250.f;
//! ���������ۂɉ����߂�����
const float CHARA_HIT_PUSH_POWER = 20.f;
//! �v���C���[�̓����蔻��J�v�Z���̔��a
const float PLAYER_CAP_RADIUS = 55.f;
//! �G�l�~�[�̓����蔻��J�v�Z���̔��a
const float ENEMY_CAP_RADIUS = 180.f;
//! �J�v�Z���̍���
const float CAP_HEIGHT = 215.f;
//! �G�l�~�[�̃J�v�Z���̍���
const float ENEMY_CAP_HEIGHT = 300.f;
//! �ŏ��l�������̂��߂̌���Ȃ��傫�Ȓl
const float MAX_INITIAL_VALUE = 10000.f;
//! �ő�l�������̂��߂̌���Ȃ������Ȓl
const float MIN_INITIAL_VALUE = -10000.f;

// �ȏ�Collision�p�萔================================================================================================= //


// �ȉ�DrawDebugKey�p�萔============================================================================================== //

//! �f�o�b�O�p�L�[�\�����WX
const int DRAW_DEBUG_KEY_POS_X = 30;
//! OBB�\���p�L�[�\�����WY
const int DRAW_OBB_KEY_POS_Y = 230;
//! �����蔻��J�v�Z���\���p�L�[�\�����WY
const int DRAW_CAP_KEY_POS_Y = 250;

// �ȏ�DrawDebugKey�p�萔============================================================================================== //


// �ȉ�Enemy�p�萔===================================================================================================== //

//! �G�l�~�[�̍s���J�ڃ^�C�}�[
const int TIME_TO_TRANSITION = 240;
//! ���S�ȉ~�̊p�x rand() % �̂��Ƃɂ�int�^�����_���Ȃ̂�Camera�ƕ�����
const int FULL_CIRCLE_DEGREES = 360;
//! ����̃t���[���ԍ�
const int ENEMY_LEFT_HAND_FRAME = 18;
//! �G�l�~�[�̏���X���W
const float ENEMY_START_POS_X = 300.f;
//! �G�l�~�[�̏���Y���W
const float ENEMY_START_POS_Y = 0.f;
//! �G�l�~�[�̏���Z���W
const float ENEMY_START_POS_Z = 900.f;
//! �G�l�~�[�̏�����]Y
const float ENEMY_START_ROTATE_Y = 0.f;
//! �G�l�~�[��3D���f���̊g�嗦
const float ENEMY_MODEL_SCALE = 2.5f; 
//! �G�l�~�[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float ENEMY_ANIM_F_INCREMENT = 0.35f;
//! �G�l�~�[�̈ړ�����
const float ENEMY_MOVE_SPEED = 5.f;
//! �G�l�~�[�̎���~�̔��a
const float ENEMY_VIEW_RADIUS = 1500.f;
//! �G�l�~�[�̍ő�HP
const float ENEMY_MAX_HP = 250.f;
//! �G�l�~�[�̑̂̓����蔻��OBB�̈ړ��lY�@���WY�ɉ��Z����
const float ENEMY_OBB_TRANS_Y = 250.f;
//! �v���C���[�̍U���́@�G�l�~�[�N���X�Ŏg�p����̂ł����Œ�`
const float PLAYER_ATTACK = 0.5f;
//! �̂̓����蔻��OBB�̊g�k�l
const VECTOR ENEMY_OBB_SCALE = VGet(200.f, 450.f, 200.f);
//! �̂̓����蔻��OBB�̉�]�l
const VECTOR ENEMY_OBB_ANGLE = VGet(0.f, ENEMY_START_ROTATE_Y, 0.f);
//! �̂̓����蔻��OBB�̈ړ��l
const VECTOR ENEMY_OBB_TRANS = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y + ENEMY_OBB_TRANS_Y, ENEMY_START_POS_Z);
//! ��̓����蔻��OBB�̊g�k�l
const VECTOR HAND_OBB_SCALE = VGet(35.f, 30.f, 20.f);
//! ��̓����蔻��OBB�̉�]�l
const VECTOR HAND_OBB_ANGLE = VGet(0.f, 6.4f, 89.f);
//! ��̓����蔻��OBB�̈ړ��l
const VECTOR HAND_OBB_TRANS = VGet(1.f, 19.f, -3.f);

// �ȏ�Enemy�p�萔===================================================================================================== //
 

// �ȉ�Grid�p�萔====================================================================================================== //

//! ���̖{��
const int LINE_NUM = 50;
//! ����`�悷��G���A�T�C�Y
const float LINE_AREA_SIZE = 10000.f;
//! ���̕`��J�n�ʒu
const float GRID_LINE_START_POSITION = 0.0f;

// �ȏ�Grid�p�萔====================================================================================================== //


// �ȉ�Main�p�萔====================================================================================================== //

//! �E�B���h�E����
const int WINDOW_WIDTH = 640;
//! �E�B���h�E�c��
const int WINDOW_HEIGHT = 480;
//! �E�B���h�E�J���[
const int WINDOW_COLOR = 32;
//! �J�����̉��Œ�����
const float CAMERA_FAR_DISTANCE = 5000.f;

// �ȏ�Main�p�萔====================================================================================================== //


// �ȉ�OBBCollider�p�萔=============================================================================================== //

//! ���_��Index�ő�l�@�����̂̒��_�Ȃ̂�8
const int MAX_VERTICES = 8;

// �ȏ�OBBCollider�p�萔=============================================================================================== //


// �ȉ�Player�p�萔==================================================================================================== //

//! Roll�̃N�[���^�C��
const int MAX_ROLL_COOL_TIME = 500;
//! �ő�񕜉�
const int MAX_HEAL_COUNT = 8;
//! �񕜉񐔂�\������X���W
const int HEAL_COUNT_POS_X = 530;
//! �񕜉񐔂�\������Y���W
const int HEAL_COUNT_POS_Y = 40;
//! �E��̃t���[���ԍ�
const int PLAYER_RIGHT_HAND_FRAME = 41;
//! �v���C���[�̏���X���W
const float PLAYER_START_POS_X = 0.f;
//! �v���C���[�̏���Y���W
const float PLAYER_START_POS_Y = 0.f;
//! �v���C���[�̏���Z���W
const float PLAYER_START_POS_Z = 600.f;
//! �v���C���[�̏�����]Y
const float PLAYER_START_ROTATE_Y = 180.f;
//! �v���C���[�̖��t���[�����Ƃ̃A�j���[�V�����̑�����
const float PLAYER_ANIM_F_INCREMENT = 0.35f;
//! �v���C���[�̈ړ�����
const float PLAYER_MOVE_SPEED = 14.f;
//! �v���C���[�̑O�]���̈ړ�����
const float PLAYER_ROLL_SPEED = 8.f;
//! �v���C���[�O�i���̉�]�p�x
const float FORWARD_ROTATION_ANGLE = 180.f;
//! �v���C���[�E�ړ����̉�]�p�x
const float RIGHT_ROTATION_ANGLE = -90.f;
//! �v���C���[���ړ����̉�]�p�x
const float LEFT_ROTATION_ANGLE = 90.f;
//! �v���C���[��ړ����̉�]�p�x
const float BACK_ROTATION_ANGLE = 0.f;
//! �v���C���[��ގ��̉�]�p�x
const float BACKWARD_ROTATION_ANGLE = 0.f;
//! 3D���f���̊g�嗦
const float MODEL_SCALE = 1.5f;
//! �ő�HP
const float MAX_HP = 200.f;
//! ��x�̉񕜗�
const float HEALING_VALUE = 20.f;
//! �v���C���[�̑̂̓����蔻��OBB�̈ړ��lY�@���WY�ɉ��Z����
const float PLAYER_OBB_TRANS_Y = 130.f;
//! �G�l�~�[�̍U���́@�v���C���[�N���X�Ŏg�p����̂ł����Œ�`
const float ENEMY_ATTACK = 0.5f;
//! �̂̓����蔻��OBB�̊g�k�l
const VECTOR PLAYER_OBB_SCALE = VGet(100.f, 250.f, 100.f);
//! �̂̓����蔻��OBB�̉�]�l
const VECTOR PLAYER_OBB_ANGLE = VGet(0.f, PLAYER_START_ROTATE_Y, 0.f);
//! �̂̓����蔻��OBB�̈ړ��l
const VECTOR PLAYER_OBB_TRANS = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y + PLAYER_OBB_TRANS_Y, PLAYER_START_POS_Z);
//! ���̓����蔻��OBB�̊g�k�l
const VECTOR SWORD_OBB_SCALE = VGet(105.f, 15.f, 10.f);
//! ���̓����蔻��OBB�̉�]�l
const VECTOR SWORD_OBB_ANGLE = VGet(18.f, -7.6f, 32.f);
//! ���̓����蔻��OBB�̈ړ��l
const VECTOR SWORD_OBB_TRANS = VGet(58.f, 42.f, 2.f);

// �ȏ�Player�p�萔==================================================================================================== //


// �ȏ�Radar�p�萔===================================================================================================== //
// �ȏ�Radar�p�萔===================================================================================================== //


// �ȏ�RadarPoint�p�萔================================================================================================ //

//! Point�̔��a
const int RADAR_POINT_RADIUS = 5;
//! Radar�̍��G�͈�
const float RADAR_DETECTION_RANGE = 3000.f;

// �ȏ�RadarPoint�p�萔================================================================================================ //


// �ȉ�SceneManager�p�萔============================================================================================== //

//! ���S�ɕs����(���S�Ɍ�����)
const int MAX_OPACITY = 255;
//! �t���[���l
const float FRAME = 60.f;

// �ȉ�SceneManager�p�萔============================================================================================== //


// �ȉ�Stage�p�萔===================================================================================================== //

//! �}�b�v�t�F�[�h�A�E�g��Phase�ҋ@�p
const int STAGE_FADE_TIMER = 80;

// �ȏ�Stage�p�萔===================================================================================================== //


// �ȉ�Title�p�萔===================================================================================================== //

//! �^�C�g���t�F�[�h�A�E�g�J�n���̏������l
const int TITLE_DONE_TIME = 0;
//! �^�C�g���t�F�[�h�A�E�g�ɗv���鎞��
const int TITLE_FADEOUT_TIME = 75;
//! Title��X���W
const int TITLE_POS_X = 0;
//! Title��Y���W
const int TITLE_POS_Y = 0;
//! PressSpace��X���W
const int TITLE_PS_POS_X = 20;
//! PressSpace��Y���W
const int TITLE_PS_POS_Y = 240;

// �ȏ�Title�p�萔===================================================================================================== //


// �ȉ�HPBar�p�萔===================================================================================================== //

//! ���̐��l�ȉ��ŃQ�[�W�̐F�ύX
const int LOW_HP = 80;
//! HP�o�[��X���W
const int HP_BAR_POS_X = 250;
//! HP�o�[��Y���W
const int HP_BAR_POS_Y = 20;
//! HP�o�[�̉���
const int HP_BAR_WIDTH = 350;
//! HP�o�[�̍���
const int HP_BAR_HEIGHT = 13;
//! �G�l�~�[��HP�o�[��X���W
const int ENEMY_HP_BAR_POS_X = 50;
//! �G�l�~�[��HP�o�[��Y���W
const int ENEMY_HP_BAR_POS_Y = 370;
//! �G�l�~�[��HP�o�[�̉���
const int ENEMY_HP_BAR_WIDTH = 525;
//! �G�l�~�[��HP�o�[�̍���
const int ENEMY_HP_BAR_HEIGHT = 25;
//! �G�l�~�[�̖��O�\��Y���W
const int ENEMY_NAME_POS_Y = 20;
//! HP�̕ω��ʁ@�o�[�̑������x
const float HP_CHANGE_AMOUNT = 1.f;

// �ȏ�HPBar�p�萔===================================================================================================== //


// �ȉ�Color=========================================================================================================== //

//! ��
const unsigned int BLACK = GetColor(  0,   0,   0);
//! ��
const unsigned int WHITE = GetColor(255, 255, 255);
//! ��
const unsigned int RED	 = GetColor(255,   0,   0);
//! ��
const unsigned int GREEN = GetColor(  0, 255,   0);
#ifdef _DEBUG
//! ��
const unsigned int BLUE  = GetColor(  0,   0, 255);
#endif

// �ȏ�Color=========================================================================================================== //
