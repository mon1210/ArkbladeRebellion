// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲームの背景を管理するクラスと関連データを定義
#include "BG.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"
// プレイヤーキャラクターとその関連情報を定義したクラスと定数/列挙型の定義
#include "Player.h"
// 敵キャラクターセットアップと管理に関するクラスとデータの定義
#include "Enemy.h"
// 
#include "camera.h"
// 
#include "Model.h"
// 
#include "Grid.h"
// 
#include "Collider.h"
// 定数値を定めたヘッダファイル
#include "Constants.h"


/**
* @brief Stageのコンストラクタ
*/
Stage::Stage(Selector *pSystem)
{
	System = pSystem;
	pModel = NULL;
	pCamera = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;
	pCollider = NULL;

	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;
	tileHandle = 0;

	pModel = new Model();
	pCamera = new Camera();
	pCollider = new Collider();
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pBG = new BG();
	pGrid = new Grid();

	pModel->LoadModel();
	pBG->setTileModel(pModel->GetTileModel());
	pPlayer->setPlayerModel(pModel->GetPlayerModel());
	pEnemy->setEnemyModel(pModel->GetEnemyModel());
	pEnemy->setTileModel(pBG->GetModelHandle());
	pCollider->setTileModel(pBG->GetModelHandle());


}


// デストラクタ
Stage::~Stage()
{
	SAFE_DELETE(pCollider);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModel);
}


/**
* @brief アニメーション(1フレーム)の実行
* @note 処理の順番は オブジェクトを move してから各々 collide を取って、必要なら各座標を調整する
* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
*/
GameSceneResultCode Stage::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		// Tileに当たり判定付与
		tileHandle = pBG->GetModelHandle();
		MV1SetupCollInfo(
			tileHandle = 0,		// 当たり判定を設定するモデルのハンドル
			-1,					// 対象となるモデルのフレーム番号(-1は全て)	
			32,					// X軸の空間分割数
			32,					// Y軸の空間分割数
			32					// Z軸の空間分割数
		);
		pEnemy->InitAnimation();
		Phase = STAGE_RUN;
		break;

	case STAGE_RUN:
		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(0x50))		 // P 
		{
			if (!bPause) 
			{
				Phase = STAGE_PAUSE;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		if (pPlayer)
		{
			if (!pPlayer->move())
			{
				Phase = STAGE_FADE;
				Timer = 0;
				break;
			}


		}
		break;
		// --------------------- STAGE_RUN END --------------------- //

	case STAGE_PAUSE:
		//	ポーズ画面呼び出し
		if (GetAsyncKeyState(0x50))		// P
		{
			if (!bPause) 
			{
				Phase = STAGE_RUN;
				bPause = true;
				break;
			}
		}
		else 
		{
			bPause = false;
		}

		break;

	case STAGE_FADE:
		if (Timer++ < STAGE_FADE_TIMER)
		{
			break;
		}
		Phase = STAGE_DONE;
		break;

	case STAGE_DONE:
		return GAMESCENE_END_OK;

	}

	return GAMESCENE_DEFAULT;
}


/**
* @brief 描画処理
* @note  現在のマップと次のマップを動かしながら描画することで移動しているように見せる
*/
void Stage::draw()
{
	switch (Phase)
	{
		default:
			if (pBG)
				pBG->draw();
			if (pGrid)
				pGrid->Draw();
			if (pPlayer)
				pPlayer->draw();
			if (pCamera) {
				pCamera->CameraController();
				pCamera->SetCameraPositionAndDirection(pPlayer->GetPlayerPos());
				pPlayer->setPlayerNewPos(pCamera->MoveAlongHAngle(pPlayer->GetPlayerMoveVec(), pPlayer->GetPlayerPos()));
			}			
			if (pEnemy) {
				pEnemy->Update();
				pEnemy->setPlayerPos(pPlayer->GetPlayerPos());
			}
				
			//if (m_pUI)
			//	m_pUI->draw(pRenderTarget);
			break;
	}

	switch (Phase)
	{
	case STAGE_FADE:
	case STAGE_DONE:
	{
		// フェードアウト処理
	}
		break;
	default:
		break;
	}

}

Collider *Stage::GetCollider()
{
	return pCollider;
}
