/**
* @file IGameScene.h
* @brief シーンの基底クラス IGameScene の宣言
*/
#pragma once

enum class GameSceneResultCode;

class IGameScene
{
public:
	/**
	* @brief 純粋仮想デストラクタの実体
	* @note  デストラクタだけは用意しなければ、サブクラスがデストラクタを呼べない
	*/
	virtual ~IGameScene() = 0;
	virtual GameSceneResultCode move() = 0;
	virtual void draw() = 0;
};

