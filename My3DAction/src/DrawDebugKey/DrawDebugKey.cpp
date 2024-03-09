#include "DrawDebugKey.h"

// コンストラクタ
DrawDebugKey::DrawDebugKey()
{
}

// デストラクタ
DrawDebugKey::~DrawDebugKey()
{
}

// 描画メソッド
void DrawDebugKey::draw()
{
	// OBB描画キーを表示
	DrawString(30, 230, "OBB表示：E", GREEN);
	// 当たり判定カプセル描画キーを表示
	DrawString(30, 250, "当たり判定カプセル表示：Q", GREEN);
}