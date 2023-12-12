/**
* @file IGameScene.h
* @brief �V�[���̊��N���X IGameScene �̐錾
*/
#pragma once

enum GameSceneResultCode;

class IGameScene
{
public:
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	virtual void draw() = 0;
};

