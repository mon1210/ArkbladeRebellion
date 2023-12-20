/**
* @file IGameScene.h
* @brief シーンの基底クラス IGameScene の宣言
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

