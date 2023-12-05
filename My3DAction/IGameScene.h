/**
* @file IGameScene.h
* @brief �V�[���̊��N���X IGameScene �̐錾
*/
#pragma once
/*
*�����w�b�_�t�@�C����������C���N���[�h����邱�Ƃɂ�����h�����߂̃v���v���Z�b�T�e�N�j�b�N
*/

enum GameSceneResultCode;

class IGameScene
{
public:
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	virtual void draw() = 0;
};

