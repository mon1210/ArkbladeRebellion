#include "BG.h"


// コンストラクタ
BG::BG(Game *Game)
{
	if (Game)
		tileHandle = Game->GetModelManager()->GetHandle(ModelType::Tile);
}


// デストラクタ
BG::~BG()
{
}


// 床モデルを取得して返す
int BG::GetModelHandle()
{
	return tileHandle;
}


// 描画メソッド
void BG::draw() 
{
	// 3Dモデルに座標をセット
	MV1SetPosition(tileHandle, position);

	// 3Dモデルの描画
	MV1DrawModel(tileHandle);

}