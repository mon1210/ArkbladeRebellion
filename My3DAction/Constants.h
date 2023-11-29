/**
* @file		Constants.h
* @brief	定数を定めたヘッダファイル
* @note		マジックナンバーの削除
*/
#pragma once
#include "DxLib.h"

// 斜め入力用の各軸の倍率( sin( 45°) )
#define VECTOR_SCALING	0.70710678118f
// 
#define PadInput GetJoypadInputState( DX_INPUT_KEY_PAD1 ) 

// 以下BG用定数====================================================================================================== //
const float BG_SCALE_FACTOR = 1.0f;				// 背景描画の際の拡大率

// 以上BG用定数====================================================================================================== //



// 以下Camera用定数================================================================================================== //
const float CAMERA_ANGLE_SPEED = 1.f;			// カメラのアングル変更速度
const float CAMERA_LOOK_AT_HEIGHT = 100.f;		// カメラが注視する点からプレイヤーまでの高さ
const float CAMERA_LOOK_AT_DISTANCE = 800.f;	// カメラと注視点の距離
const float MAX_VERTICAL_ANGLE = 80.f;			// 垂直方向に対するアングル変更の最大値
const float MIN_VERTICAL_ANGLE = 0.f;			// 垂直方向に対するアングル変更の最小値
const float MAX_HORIZONTAL_ANGLE = 180.f;		// 水平方向に対するアングル変更の最大値
const float MIN_HORIZONTAL_ANGLE = -180.f;		// 垂直方向に対するアングル変更の最小値
const float FULL_CIRCLE_DEGREES = 360.f;		// 完全な円の角度
// 以上Camera用定数================================================================================================== //


// 以下Enemy用定数=================================================================================================== //
const float ENEMY_POS_X = 300.f;				// エネミーの初期X座標
const float ENEMY_POS_Y = 0.f;					// エネミーの初期Y座標 -280
const float ENEMY_POS_Z = 900.f;				// エネミーの初期Z座標
const float ENEMY_START_ROTATE_Y = 0.f;			// エネミーの初期回転Y
const float ENEMY_ANIM_F_INCREMENT = 0.25f;		// エネミーの毎フレームごとのアニメーションの増加数
const float ENEMY_MOVE_SPEED = 2.f;				// エネミーの移動距離
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
//const float DEG_TO_RAD = DX_PI_F / 180.f;		// 度数からラジアンへの変更用定数
//const float FLAME_TIME = 1.f / 60.f;			// 
// 以上My3DAction用定数============================================================================================== //


// 以下Player用定数================================================================================================== //
const float PLAYER_POS_X = 0.f;					// プレイヤーの初期X座標
const float PLAYER_POS_Y = 0.f;					// プレイヤーの初期Y座標 -250
const float PLAYER_POS_Z = 600.f;				// プレイヤーの初期Z座標
const float PLAYER_START_ROTATE_Y = 180.f;		// プレイヤーの初期回転Y
const float PLAYER_ANIM_F_INCREMENT = 0.2f;		// プレイヤーの毎フレームごとのアニメーションの増加数
const float PLAYER_MOVE_SPEED = 10.f;			// プレイヤーの移動距離
const float PLAYER_ROLL_DISTANCE = 5.f;			// プレイヤーの前転時の移動距離
const float PLAYER_ROLL_ANIM_F_INCREMENT = 0.3f;// プレイヤーの前転時の移動距離
const float MODEL_SCALE = 1.5f;					// 3Dモデルの拡大率
// 以上Player用定数================================================================================================== //


// 以下Stage用定数=================================================================================================== //
const int STAGE_FADE_TIMER = 120;				// マップフェードアウト時Phase待機用 
// 以上Stage用定数=================================================================================================== //


// 以下Title用定数=================================================================================================== //
const int TITLE_TIMER_INIT = 0;					// タイトル開始時のタイマー初期値
const int TITLE_DONE_TIME = 0;					// タイトルフェードアウト開始時の初期化値
const int TITLE_FADEOUT_TIME = 30;				// タイトルフェードアウトに要する時間
const int TITLE_LOOP_FRAME = 1516;				// タイトルループ周期
const int TITLE_LOOP_HALF_FRAME = 758;			// 周期の半分(なめらかな描画ループ)
const int CENTER = 2;							// 画面のセンター指定用
const int VERTICAL_SHIFT_AMOUNT = 40;			// PressSpaceを上にシフトする
const int TEXT_OPACITY_TIMER = 150;				// PressSpaceの透明度を測る数値
const int DARK_THRESHOLD = 60;					// この数値以下はだんだん透明
const int LIGHT_THRESHOLD = 90;					// この数値以上はだんだん鮮明
const int DARK_START_OPACITY = 2;				// だんだん透明になる初期値
const float MAX_OPACITY = 1.0f;					// 透明度の最大値
const float PER_FLOAT = 60.f;					// フレーム値に
const float DARK_THRESHOLD_FLAME = 30;			// 透明と鮮明値の差
const float TITLE_MARGIN_ABOVE = 120.f;			// タイトルを上に余白を開ける
const float TITLE_SCALE_FACTOR = 1.0f;			// タイトル描画の拡大率
const float TITLE_BLACKOUT_TIME = 30.0f;		// タイトルのフェードアウト時画面が暗い時間
// 以上Title用定数=================================================================================================== //
