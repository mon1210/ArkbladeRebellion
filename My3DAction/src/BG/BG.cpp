#include "BG.h"

/**
* @brief BGのコンストラクタ
*/
BG::BG(Game *Game_)
{
	if (Game_)
		tileHandle = Game_->GetModelManager()->GetHandle(ModelType::Tile);
}


// デストラクタ
BG::~BG()
{
}


/**
* @brief 床モデルを取得して返す
*/
int BG::GetModelHandle()
{
	return tileHandle;
}


/**
* @brief 描画メソッド
* @note  画面上に見えている部分のみ描画
*/
void BG::draw() 
{
	// 3Dモデルに座標をセット
	MV1SetPosition(tileHandle, position);

	// 3Dモデルの描画
	MV1DrawModel(tileHandle);

}