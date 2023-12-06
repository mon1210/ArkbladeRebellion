// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"


/**
* @brief Stageのコンストラクタ
*/
Stage::Stage(Selector *pSystem)
{
	System = pSystem;
	pModel = NULL;
	pCamera = NULL;
	pCollider = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;

	Phase = STAGE_INIT;
	bPause = true;
	Timer = 0;
	tileHandle = 0;

	// インスタンス化
	pModel = new Model();
	pCamera = new Camera();
	pCollider = new Collider();	// 必ずPlayerより上に書く
	pPlayer = new Player(this);
	pEnemy = new Enemy();
	pBG = new BG();
	pGrid = new Grid();

	// モデルセット
	pModel->LoadModel();
	pBG->setTileModel(pModel->GetTileModel());
	pPlayer->setPlayerModel(pModel->GetPlayerModel());
	pEnemy->setEnemyModel(pModel->GetEnemyModel());
	pEnemy->setTileModel(pBG->GetModelHandle());
	pCollider->setTileModel(pBG->GetModelHandle());
	tileHandle = pBG->GetModelHandle();
}


/**
* @brief デストラクタ
* @note	 すべてのポインタをここでDelete
*/
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
* @note 
* @return GAMESCENE_DEFAULT: 継続 / GAMESCENE_END_FAILURE: ゲームオーバー
*/
GameSceneResultCode Stage::move()
{
	switch (Phase)
	{
	case STAGE_INIT:
		pCollider->InitCollision(tileHandle);
		pEnemy->InitAnimation();	// phase分けはEnemyのみなので
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
* @note  毎フレーム実行される
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
				pCamera->SetCameraPositionAndDirection(pPlayer->GetPlayerPos());	//カメラの位置・角度設定 
				if (pPlayer) {
					pPlayer->setCameraHAngle(pCamera->GetCameraHorizontalAngle());	// カメラの水平角度取得
					pPlayer->setPlayerNewPos(pCamera->MoveAlongHAngle
						(pPlayer->GetPlayerMoveVec(), pPlayer->GetPlayerPos()));	// プレイヤーの座標設定
				}
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


/**
* @brief Colliderを取得して返す
*/
Collider *Stage::GetCollider()
{
	return pCollider;
}
