/**
* @file		Constants.h
* @brief	定数を定めたヘッダファイル
* @note		マジックナンバーの削除
*/
#pragma once
#include "DxLib.h"


// 以下BG用定数====================================================================================================== //
// 以上BG用定数====================================================================================================== //


// 以下Camera用定数================================================================================================== //
const float CAMERA_ANGLE_SPEED = 1.f;			// カメラのアングル変更速度
const float CAMERA_LOOK_AT_HEIGHT = 100.f;		// カメラが注視する点からプレイヤーまでの高さ
const float CAMERA_LOOK_AT_DISTANCE = 800.f;	// カメラと注視点の距離
const float MAX_VERTICAL_ANGLE = 80.f;			// 垂直方向に対するアングル変更の最大値
const float MIN_VERTICAL_ANGLE = 0.f;			// 垂直方向に対するアングル変更の最小値
const float MAX_HORIZONTAL_ANGLE = 180.f;		// 水平方向に対するアングル変更の最大値
const float MIN_HORIZONTAL_ANGLE = -180.f;		// 垂直方向に対するアングル変更の最小値
const float CAMERA_FULL_CIRCLE_DEGREES = 360.f;	// 完全な円の角度
// 以上Camera用定数================================================================================================== //


// 以下Collision用定数=============================================================================================== //
const int SPATIAL_PARTITION = 32;				// 空間分割数
const float CHARA_HEIGHT = 250.f;				// 当たり判定の大きさ
const float CHARA_HIT_PUSH_POWER = 20.f;		// 当たった際に押し戻される力
const float PLAYER_CAP_RADIUS = 55.f;			// プレイヤーの当たり判定カプセルの半径
const float ENEMY_CAP_RADIUS = 100.f;			// エネミーの当たり判定カプセルの半径
const float CAP_HEIGHT = 215.f;					// カプセルの高さ
// 以上Collision用定数=============================================================================================== //


// 以下Enemy用定数=================================================================================================== //
const int TIME_TO_TRANSITION = 240;				// エネミーの行動遷移タイマー
const int FULL_CIRCLE_DEGREES = 360;			// 完全な円の角度 rand() % のあとにはint型しかダメなのでCameraと分ける
const float ENEMY_START_POS_X = 300.f;			// エネミーの初期X座標
const float ENEMY_START_POS_Y = 0.f;			// エネミーの初期Y座標 -280
const float ENEMY_START_POS_Z = 900.f;			// エネミーの初期Z座標
const float ENEMY_START_ROTATE_Y = 0.f;			// エネミーの初期回転Y
const float ENEMY_ANIM_F_INCREMENT = 0.25f;		// エネミーの毎フレームごとのアニメーションの増加数
const float ENEMY_MOVE_SPEED = 2.f;				// エネミーの移動距離
const float ENEMY_VIEW_RADIUS = 1500.f;			// エネミーの視野円の半径
// 以上Enemy用定数=================================================================================================== //
 

// 以下Grid用定数==================================================================================================== //
const int LINE_NUM = 50;						// 線の本数
const float LINE_AREA_SIZE = 10000.f;			// 線を描画するエリアサイズ
const float GRID_LINE_START_POSITION = 0.0f;	// 線の描画開始位置
// 以上Grid用定数==================================================================================================== //


// 以下My3DAction用定数============================================================================================== //
const int WINDOW_WIDTH = 640;					// ウィンドウ横幅	test
const int WINDOW_HEIGHT = 480;					// ウィンドウ縦幅	test
const int WINDOW_COLOR = 32;					// ウィンドウカラー	test
const int WINDOW_BG_COLOR_OFFSET = 1;			// 背景色をカスタマイズするためのオフセット
const int WINDOW_POS_Y = 0;						// 生成時Y座標
const int WINDOW_WIDTH_SIZE = 640;				// ウィンドウの横幅
const int WINDOW_HEIGHT_SIZE = 480;				// ウィンドウの縦幅
const double DOUBLE_ONE = 1.0;					// 倍精度浮動小数点数リテラル
const float CAMERA_FAR_DISTANCE = 5000.f;		// カメラの可視最長距離
// 以上My3DAction用定数============================================================================================== //


// 以下OBBCollider用定数============================================================================================= //
const int MAX_VERTICES = 8;						// 頂点のIndex最大値　立方体の頂点なので8
// 以上OBBCollider用定数============================================================================================= //


// 以下Player用定数================================================================================================== //
const int MAX_ROLL_COOL_TIME = 500;				// Rollのクールタイム
const int MAX_HEAL_COUNT = 8;					// 最大回復回数
const int HEAL_COUNT_POS_X = 530;				// 回復回数を表示するX座標
const int HEAL_COUNT_POS_Y = 40;				// 回復回数を表示するY座標
const float PLAYER_START_POS_X = 0.f;			// プレイヤーの初期X座標
const float PLAYER_START_POS_Y = 0.f;			// プレイヤーの初期Y座標 -250
const float PLAYER_START_POS_Z = 600.f;			// プレイヤーの初期Z座標
const float PLAYER_START_ROTATE_Y = 180.f;		// プレイヤーの初期回転Y
const float PLAYER_ANIM_F_INCREMENT = 0.25f;	// プレイヤーの毎フレームごとのアニメーションの増加数
const float PLAYER_MOVE_SPEED = 10.f;			// プレイヤーの移動距離
const float PLAYER_ROLL_DISTANCE = 5.f;			// プレイヤーの前転時の移動距離
const float PLAYER_ROLL_ANIM_F_INCREMENT = 0.3f;// プレイヤーの前転時の移動距離
const float FORWARD_ROTATION_ANGLE = 180.f;		// プレイヤー前進時の回転角度
const float RIGHT_ROTATION_ANGLE = -90.f;		// プレイヤー右移動時の回転角度
const float LEFT_ROTATION_ANGLE = 90.f;			// プレイヤー左移動時の回転角度
const float BACK_ROTATION_ANGLE = 0.f;			// プレイヤー後移動時の回転角度
const float BACKWARD_ROTATION_ANGLE = 0.f;		// プレイヤー後退時の回転角度
const float MODEL_SCALE = 1.5f;					// 3Dモデルの拡大率
const float MAX_HP = 100.f;						// 最大HP
const float HEALING_VALUE = 20.f;				// 一度の回復量
// 以上Player用定数================================================================================================== //


// 以上Radar用定数================================================================================================== //
// 以上Radar用定数================================================================================================== //


// 以上RadarPoint用定数============================================================================================== //
const float RADAR_DETECTION_RANGE = 2000.f;		// Radarの索敵範囲
const float RADAR_POINT_RADIUS = 5.f;			// Pointの半径
// 以上RadarPoint用定数============================================================================================== //


// 以下SceneManager用定数============================================================================================ //
const int MAX_OPACITY = 255;					// 完全に不透明(完全に見える)
const float FRAME = 60.f;						// フレーム値
// 以下SceneManager用定数============================================================================================ //


// 以下Stage用定数=================================================================================================== //
const int STAGE_FADE_TIMER = 120;				// マップフェードアウト時Phase待機用 
// 以上Stage用定数=================================================================================================== //


// 以下Title用定数=================================================================================================== //
const int TITLE_TIMER_INIT = 0;					// タイトル開始時のタイマー初期値
const int TITLE_DONE_TIME = 0;					// タイトルフェードアウト開始時の初期化値
const int TITLE_FADEOUT_TIME = 30;				// タイトルフェードアウトに要する時間
const int TITLE_LOOP_FRAME = 1516;				// タイトルループ周期
const int TITLE_LOOP_HALF_FRAME = 758;			// 周期の半分(なめらかな描画ループ)
const int TITLE_POS_X = 0;						// TitleのX座標
const int TITLE_POS_Y = 0;						// TitleのY座標
const int TITLE_PS_POS_X = 20;					// PressSpaceのX座標
const int TITLE_PS_POS_Y = 240;					// PressSpaceのY座標
// 以上Title用定数=================================================================================================== //


// 以下UI用定数====================================================================================================== //
const int LOW_HP = 30;							// この数値以下でゲージの色変更
const int HP_BAR_POS_X = 250;					// HPバーのX座標
const int HP_BAR_POS_Y = 20;					// HPバーのY座標
const int HP_BAR_WIDTH = 350;					// HPバーの横幅
const int HP_BAR_HEIGHT = 13;					// HPバーの高さ
const float HP_CHANGE_AMOUNT = 0.5f;			// HPの変化量　バーの増減速度
// 以上UI用定数====================================================================================================== //


// 以下Color====================================================================================================== //
const int BLACK = GetColor(	 0,	  0,   0);		// 黒
const int WHITE = GetColor(255, 255, 255);		// 白
const int RED	= GetColor(255,   0,   0);		// 赤
const int GREEN = GetColor(  0, 255,   0);		// 緑
#ifdef _DEBUG
const int BLUE  = GetColor(  0,   0, 255);		// 青
#endif
// 以上Color====================================================================================================== //
