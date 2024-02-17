/**
* @file IGameScene.h
* @brief �V�[���̊��N���X IGameScene �̐錾
*/
#pragma once

enum class GameSceneResultCode;

class IGameScene
{
public:
	/**
	* @brief �������z�f�X�g���N�^�̎���
	* @note  �f�X�g���N�^�����͗p�ӂ��Ȃ���΁A�T�u�N���X���f�X�g���N�^���ĂׂȂ�
	*/
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	virtual void draw() = 0;
};

