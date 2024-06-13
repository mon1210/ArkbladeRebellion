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
	DrawString(DRAW_DEBUG_KEY_POS_X, DRAW_OBB_KEY_POS_Y, "OBB表示：L_SHIFT", GREEN);
	// 当たり判定カプセル描画キーを表示
	DrawString(DRAW_DEBUG_KEY_POS_X, DRAW_CAP_KEY_POS_Y, "当たり判定カプセル表示：Q", GREEN);
}