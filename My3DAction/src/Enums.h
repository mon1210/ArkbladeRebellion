/*
* @file		Enums.h
* @brief	eunm変数宣言用ヘッダファイル
* @note		クラス名と被るためnamespaceにはプレフィクス付与
*/
#pragma once

// ゲームの状態を表す
enum class GamePhase 
{
	GAMEPHASE_INIT = 0,
	GAMEPHASE_RESET = 1,
	GAMEPHASE_TITLE = 0x010,
	GAMEPHASE_GAME = 0x100,
	GAMEPHASE_GAMEOVER = 0x200
};

// シーンの状態を管理
enum class GameSceneResultCode 
{
	GAMESCENE_DEFAULT = 0,
	GAMESCENE_END_OK = 1,
	GAMESCENE_END_TIMEOUT = 2,
	GAMESCENE_END_FAILURE = 3
};

// タイトルの状態を表す
enum class TitlePhase 
{
	TITLE_INIT = 0,
	TITLE_RUN = 1,
	TITLE_FADE = 2,
	TITLE_DONE = 3
};

// ステージの状態を表す
enum class StagePhase 
{
	STAGE_INIT = 0,
	STAGE_RUN = 1,
	STAGE_PAUSE = 2,
	STAGE_FADE = 3,
	STAGE_DONE = 4,
};

// モデルの種類
enum class ModelType
{
	Default = -1,			// -1代入用
	Player,
	PlayerWithSword,	// 武器を持ったプレイヤー
	Enemy,
	Tile				// 床

};

// プレイヤーモデルのアニメーション番号
namespace ePlayer
{
	enum class AnimationNum
	{
		Default = -1,	// -1代入用
		Idle = 1,
		Run,
		NoMoveRoll,		// その場で
		Roll,
		SpeedRoll,		// 素早い
		Damage = 9,
		Drinking,		// 回復
		Dying, 
	};
}

// 武器を持ったプレイヤーモデルのアニメーション番号
namespace ePlayerWS
{
	enum class AnimationNum
	{
		Default = -1,	// -1代入用
		Idle = 0,
		Slash1,			// 攻撃 一段目
		Slash2,			// 二段目
		Slash3,			// 三段目
	};
}

// エネミーモデルのアニメーション番号
namespace eEnemy
{
	enum class AnimationNum
	{
		Default = -1,	// -1代入用
		Idle = 1,
		Run,
		Swiping,		// 攻撃
		Damage,
		Dying
	};
}

// プレイヤーの状態を表す
enum class PlayerState
{
	Default = -1,		// -1代入用
	Idle,
	Move,
	Roll,
	Attack,
	Damage,
	Healing,
	Death

};

// エネミーの状態を表す
enum class EnemyState
{
	Default = -1,	// -1代入用
	Wait,
	Move, 
	Chase,
	Attack,
	Damage,
	Death,

};

// Radarに映るPointの種類
namespace eRadar
{
	enum class PointType
	{
		Default = -1,	// -1代入用
		Enemy,
	};
}
