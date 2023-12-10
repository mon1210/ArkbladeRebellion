// Windowsアプリケーション開発用の共通ヘッダファイル
#include "stdafx.h"
// ゲーム内のステージ関連クラスと列挙型の定義
#include "Stage.h"


/**
* @brief Stageのコンストラクタ
*/
Stage::Stage()
{
	pModel = NULL;
	pCamera = NULL;
	pCollision = NULL;
	pPlayer = NULL;
	pEnemy = NULL;
	pBG = NULL;
	pGrid = NULL;
	pRadar = NULL;

	Phase = STAGE_INIT;

	bPause = true;

	Timer = 0;
	tileHandle = 0;

	// インスタンス化
	pModel = new Model();
	pCamera = new Camera();
	pCollision = new Collision();	// 必ずPlayerより上に書く
	pRadar = new Radar();		// 必ずPlayerより上に書く
	pPlayer = new Player(this);
	pEnemy = new Enemy(this);
	pBG = new BG();
	pGrid = new Grid();

	// モデルセット
	pModel->loadModel();
	pBG->setTileModel(pModel->getTileModel());
	pPlayer->setPlayerModel(pModel->getPlayerModel());
	pEnemy->setEnemyModel(pModel->getEnemyModel());
	pEnemy->setTileModel(pBG->getModelHandle());
	pCollision->setTileModel(pBG->getModelHandle());
	tileHandle = pBG->getModelHandle();
}


/**
* @brief デストラクタ
* @note	 すべてのポインタをここでDelete
*/
Stage::~Stage()
{
	SAFE_DELETE(pCollision);
	SAFE_DELETE(pGrid);
	SAFE_DELETE(pBG);
	SAFE_DELETE(pEnemy);
	SAFE_DELETE(pPlayer);
	SAFE_DELETE(pCamera);
	SAFE_DELETE(pModel);
	SAFE_DELETE(pRadar);
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
		pCollision->initCollision(tileHandle);
		pEnemy->initAnimation();	// phase分けはEnemyのみなので
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
			if (pRadar)
				pRadar->listReset();	// Pointリスト初期化
			if (pBG)
				pBG->draw();
			if (pGrid)
				pGrid->draw();
			if (pPlayer)
				pPlayer->draw();
			if (pCamera) {
				pCamera->controller();
				pCamera->setPositionAndDirection(pPlayer->getPlayerPos());			//カメラの位置・角度設定 
				if (pPlayer) {
					pPlayer->setCameraHAngle(pCamera->getHorizontalAngle());		// カメラの水平角度取得
					pPlayer->setPlayerNewPos(pCamera->moveAlongHAngle
						(pPlayer->getPlayerMoveVec(), pPlayer->getPlayerPos()));	// プレイヤーの座標設定
				}
			}			
			if (pEnemy) {
				pEnemy->update();
				pEnemy->setPlayerPos(pPlayer->getPlayerPos());
			}
			if (pRadar)
				pRadar->draw();
				
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
* @brief Collisionを取得して返す
*/
Collision *Stage::GetCollision()
{
	return pCollision;
}


/**
* @brief Radarを取得して返す
*/
Radar* Stage::GetRadar()
{
	return pRadar;
}