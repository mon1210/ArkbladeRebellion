/**
* @file IGameScene.h
* @brief シーンの基底クラス IGameScene の宣言
*/
#pragma once
/*
*同じヘッダファイルが複数回インクルードされることによる問題を防ぐためのプリプロセッサテクニック
*/
#define __IGAMESCENE_H__

enum GameSceneResultCode;

class IGameScene
{
public:
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	virtual void draw() = 0;
};

