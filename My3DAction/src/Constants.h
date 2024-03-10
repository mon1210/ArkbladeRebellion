/**
* @file		Constants.h
* @brief	定数 の宣言
* @note		マジックナンバーの削除
*/
#pragma once
#include "DxLib.h"


// 以下BG用定数======================================================================================================== //
// 以上BG用定数======================================================================================================== //


// 以下Camera用定数==================================================================================================== //

//! カメラのアングル変更速度
const float CAMERA_ANGLE_SPEED = 1.f;
//! カメラが注視する点からプレイヤーまでの高さ
const float CAMERA_LOOK_AT_HEIGHT = 100.f;
//! カメラと注視点の距離
const float CAMERA_LOOK_AT_DISTANCE = 800.f;
//! 垂直方向に対するアングル変更の最大値
const float MAX_VERTICAL_ANGLE = 80.f;
//! 垂直方向に対するアングル変更の最小値
const float MIN_VERTICAL_ANGLE = 0.f;
//! 水平方向に対するアングル変更の最大値
const float MAX_HORIZONTAL_ANGLE = 180.f;
//! 垂直方向に対するアングル変更の最小値
const float MIN_HORIZONTAL_ANGLE = -180.f;
//! 完全な円の角度
const float CAMERA_FULL_CIRCLE_DEGREES = 360.f;
//! RadarPointがRadarの中心に来るように補正する値
const float RADAR_CENTER_OFFSET = 350.f;

// 以上Camera用定数==================================================================================================== //


// 以下Collision用定数================================================================================================= //

//! 空間分割数
const int SPATIAL_PARTITION = 32;
//! 頂点リストのサイズ
const int VERTICES_LIST_SIZE = 2;
//! OBBの頂点の数
const int OBB_VERTICES = 8;
//! 当たり判定の大きさ
const float CHARA_HEIGHT = 250.f;
//! 当たった際に押し戻される力
const float CHARA_HIT_PUSH_POWER = 20.f;
//! プレイヤーの当たり判定カプセルの半径
const float PLAYER_CAP_RADIUS = 55.f;
//! エネミーの当たり判定カプセルの半径
const float ENEMY_CAP_RADIUS = 180.f;
//! カプセルの高さ
const float CAP_HEIGHT = 215.f;
//! エネミーのカプセルの高さ
const float ENEMY_CAP_HEIGHT = 300.f;
//! 最小値初期化のための限りなく大きな値
const float MAX_INITIAL_VALUE = 10000.f;
//! 最大値初期化のための限りなく小さな値
const float MIN_INITIAL_VALUE = -10000.f;

// 以上Collision用定数================================================================================================= //


// 以下DrawDebugKey用定数============================================================================================== //

//! デバッグ用キー表示座標X
const int DRAW_DEBUG_KEY_POS_X = 30;
//! OBB表示用キー表示座標Y
const int DRAW_OBB_KEY_POS_Y = 230;
//! 当たり判定カプセル表示用キー表示座標Y
const int DRAW_CAP_KEY_POS_Y = 250;

// 以上DrawDebugKey用定数============================================================================================== //


// 以下Enemy用定数===================================================================================================== //

//! エネミーの行動遷移タイマー
const int TIME_TO_TRANSITION = 240;
//! 完全な円の角度 rand() % のあとにはint型しかダメなのでCameraと分ける
const int FULL_CIRCLE_DEGREES = 360;
//! 左手のフレーム番号
const int ENEMY_LEFT_HAND_FRAME = 18;
//! エネミーの初期X座標
const float ENEMY_START_POS_X = 300.f;
//! エネミーの初期Y座標
const float ENEMY_START_POS_Y = 0.f;
//! エネミーの初期Z座標
const float ENEMY_START_POS_Z = 900.f;
//! エネミーの初期回転Y
const float ENEMY_START_ROTATE_Y = 0.f;
//! エネミーの3Dモデルの拡大率
const float ENEMY_MODEL_SCALE = 2.5f; 
//! エネミーの毎フレームごとのアニメーションの増加数
const float ENEMY_ANIM_F_INCREMENT = 0.35f;
//! エネミーの移動距離
const float ENEMY_MOVE_SPEED = 5.f;
//! エネミーの視野円の半径
const float ENEMY_VIEW_RADIUS = 1500.f;
//! エネミーの最大HP
const float ENEMY_MAX_HP = 250.f;
//! エネミーの体の当たり判定OBBの移動値Y　座標Yに加算する
const float ENEMY_OBB_TRANS_Y = 250.f;
//! プレイヤーの攻撃力　エネミークラスで使用するのでここで定義
const float PLAYER_ATTACK = 0.5f;
//! 体の当たり判定OBBの拡縮値
const VECTOR ENEMY_OBB_SCALE = VGet(200.f, 450.f, 200.f);
//! 体の当たり判定OBBの回転値
const VECTOR ENEMY_OBB_ANGLE = VGet(0.f, ENEMY_START_ROTATE_Y, 0.f);
//! 体の当たり判定OBBの移動値
const VECTOR ENEMY_OBB_TRANS = VGet(ENEMY_START_POS_X, ENEMY_START_POS_Y + ENEMY_OBB_TRANS_Y, ENEMY_START_POS_Z);
//! 手の当たり判定OBBの拡縮値
const VECTOR HAND_OBB_SCALE = VGet(35.f, 30.f, 20.f);
//! 手の当たり判定OBBの回転値
const VECTOR HAND_OBB_ANGLE = VGet(0.f, 6.4f, 89.f);
//! 手の当たり判定OBBの移動値
const VECTOR HAND_OBB_TRANS = VGet(1.f, 19.f, -3.f);

// 以上Enemy用定数===================================================================================================== //
 

// 以下Grid用定数====================================================================================================== //

//! 線の本数
const int LINE_NUM = 50;
//! 線を描画するエリアサイズ
const float LINE_AREA_SIZE = 10000.f;
//! 線の描画開始位置
const float GRID_LINE_START_POSITION = 0.0f;

// 以上Grid用定数====================================================================================================== //


// 以下Main用定数====================================================================================================== //

//! ウィンドウ横幅
const int WINDOW_WIDTH = 640;
//! ウィンドウ縦幅
const int WINDOW_HEIGHT = 480;
//! ウィンドウカラー
const int WINDOW_COLOR = 32;
//! カメラの可視最長距離
const float CAMERA_FAR_DISTANCE = 5000.f;

// 以上Main用定数====================================================================================================== //


// 以下OBBCollider用定数=============================================================================================== //

//! 頂点のIndex最大値　立方体の頂点なので8
const int MAX_VERTICES = 8;

// 以上OBBCollider用定数=============================================================================================== //


// 以下Player用定数==================================================================================================== //

//! Rollのクールタイム
const int MAX_ROLL_COOL_TIME = 500;
//! 最大回復回数
const int MAX_HEAL_COUNT = 8;
//! 回復回数を表示するX座標
const int HEAL_COUNT_POS_X = 530;
//! 回復回数を表示するY座標
const int HEAL_COUNT_POS_Y = 40;
//! 右手のフレーム番号
const int PLAYER_RIGHT_HAND_FRAME = 41;
//! プレイヤーの初期X座標
const float PLAYER_START_POS_X = 0.f;
//! プレイヤーの初期Y座標
const float PLAYER_START_POS_Y = 0.f;
//! プレイヤーの初期Z座標
const float PLAYER_START_POS_Z = 600.f;
//! プレイヤーの初期回転Y
const float PLAYER_START_ROTATE_Y = 180.f;
//! プレイヤーの毎フレームごとのアニメーションの増加数
const float PLAYER_ANIM_F_INCREMENT = 0.35f;
//! プレイヤーの移動距離
const float PLAYER_MOVE_SPEED = 14.f;
//! プレイヤーの前転時の移動距離
const float PLAYER_ROLL_SPEED = 8.f;
//! プレイヤー前進時の回転角度
const float FORWARD_ROTATION_ANGLE = 180.f;
//! プレイヤー右移動時の回転角度
const float RIGHT_ROTATION_ANGLE = -90.f;
//! プレイヤー左移動時の回転角度
const float LEFT_ROTATION_ANGLE = 90.f;
//! プレイヤー後移動時の回転角度
const float BACK_ROTATION_ANGLE = 0.f;
//! プレイヤー後退時の回転角度
const float BACKWARD_ROTATION_ANGLE = 0.f;
//! 3Dモデルの拡大率
const float MODEL_SCALE = 1.5f;
//! 最大HP
const float MAX_HP = 200.f;
//! 一度の回復量
const float HEALING_VALUE = 20.f;
//! プレイヤーの体の当たり判定OBBの移動値Y　座標Yに加算する
const float PLAYER_OBB_TRANS_Y = 130.f;
//! エネミーの攻撃力　プレイヤークラスで使用するのでここで定義
const float ENEMY_ATTACK = 0.5f;
//! 体の当たり判定OBBの拡縮値
const VECTOR PLAYER_OBB_SCALE = VGet(100.f, 250.f, 100.f);
//! 体の当たり判定OBBの回転値
const VECTOR PLAYER_OBB_ANGLE = VGet(0.f, PLAYER_START_ROTATE_Y, 0.f);
//! 体の当たり判定OBBの移動値
const VECTOR PLAYER_OBB_TRANS = VGet(PLAYER_START_POS_X, PLAYER_START_POS_Y + PLAYER_OBB_TRANS_Y, PLAYER_START_POS_Z);
//! 剣の当たり判定OBBの拡縮値
const VECTOR SWORD_OBB_SCALE = VGet(105.f, 15.f, 10.f);
//! 剣の当たり判定OBBの回転値
const VECTOR SWORD_OBB_ANGLE = VGet(18.f, -7.6f, 32.f);
//! 剣の当たり判定OBBの移動値
const VECTOR SWORD_OBB_TRANS = VGet(58.f, 42.f, 2.f);

// 以上Player用定数==================================================================================================== //


// 以上Radar用定数===================================================================================================== //
// 以上Radar用定数===================================================================================================== //


// 以上RadarPoint用定数================================================================================================ //

//! Pointの半径
const int RADAR_POINT_RADIUS = 5;
//! Radarの索敵範囲
const float RADAR_DETECTION_RANGE = 3000.f;

// 以上RadarPoint用定数================================================================================================ //


// 以下SceneManager用定数============================================================================================== //

//! 完全に不透明(完全に見える)
const int MAX_OPACITY = 255;
//! フレーム値
const float FRAME = 60.f;

// 以下SceneManager用定数============================================================================================== //


// 以下Stage用定数===================================================================================================== //

//! マップフェードアウト時Phase待機用
const int STAGE_FADE_TIMER = 80;

// 以上Stage用定数===================================================================================================== //


// 以下Title用定数===================================================================================================== //

//! タイトルフェードアウト開始時の初期化値
const int TITLE_DONE_TIME = 0;
//! タイトルフェードアウトに要する時間
const int TITLE_FADEOUT_TIME = 75;
//! TitleのX座標
const int TITLE_POS_X = 0;
//! TitleのY座標
const int TITLE_POS_Y = 0;
//! PressSpaceのX座標
const int TITLE_PS_POS_X = 20;
//! PressSpaceのY座標
const int TITLE_PS_POS_Y = 240;

// 以上Title用定数===================================================================================================== //


// 以下HPBar用定数===================================================================================================== //

//! この数値以下でゲージの色変更
const int LOW_HP = 80;
//! HPバーのX座標
const int HP_BAR_POS_X = 250;
//! HPバーのY座標
const int HP_BAR_POS_Y = 20;
//! HPバーの横幅
const int HP_BAR_WIDTH = 350;
//! HPバーの高さ
const int HP_BAR_HEIGHT = 13;
//! エネミーのHPバーのX座標
const int ENEMY_HP_BAR_POS_X = 50;
//! エネミーのHPバーのY座標
const int ENEMY_HP_BAR_POS_Y = 370;
//! エネミーのHPバーの横幅
const int ENEMY_HP_BAR_WIDTH = 525;
//! エネミーのHPバーの高さ
const int ENEMY_HP_BAR_HEIGHT = 25;
//! エネミーの名前表示Y座標
const int ENEMY_NAME_POS_Y = 20;
//! HPの変化量　バーの増減速度
const float HP_CHANGE_AMOUNT = 1.f;

// 以上HPBar用定数===================================================================================================== //


// 以下Color=========================================================================================================== //

//! 黒
const unsigned int BLACK = GetColor(  0,   0,   0);
//! 白
const unsigned int WHITE = GetColor(255, 255, 255);
//! 赤
const unsigned int RED	 = GetColor(255,   0,   0);
//! 緑
const unsigned int GREEN = GetColor(  0, 255,   0);
#ifdef _DEBUG
//! 青
const unsigned int BLUE  = GetColor(  0,   0, 255);
#endif

// 以上Color=========================================================================================================== //
