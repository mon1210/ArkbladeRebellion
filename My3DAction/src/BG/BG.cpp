#include "BG.h"

//  マクロ定義
#undef SAFE_RELEASE
#undef SAFE_DELETE
#undef SAFE_DELETE_ARRAY
#define SAFE_RELEASE(o) if (o){ (o)->Release(); o = NULL; }
#define SAFE_DELETE(o)  if (o){ delete (o); o = NULL; }
#define SAFE_DELETE_ARRAY(o) if (o){ delete [] (o); o = NULL; }


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