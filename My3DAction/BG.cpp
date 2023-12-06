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
BG::BG()
{
	tile_handle = 0;
	position = VGet(0.f, 0.f, 0.f);
}


// デストラクタ
BG::~BG()
{
}


/**
* @brief 床モデルセット
* @note
*/
void BG::setTileModel(int model)
{
	tile_handle = model;
}


/**
* @brief 床モデルを取得して返す
* @note
*/
int BG::GetModelHandle()
{
	return tile_handle;
}


/**
* @brief 描画メソッド
* @note  画面上に見えている部分のみ描画
*/
void BG::draw() 
{
	// 3Dモデルに座標をセット
	MV1SetPosition(tile_handle, position);

	// 3Dモデルの描画
	MV1DrawModel(tile_handle);

}