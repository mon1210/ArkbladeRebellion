#include "HPBar.h"


/*
* @brief HPBarのコンストラクタ
*/
HPBar::HPBar(Game* Game_)
{
	pGame = Game_;
}


// デストラクタ
HPBar::~HPBar()
{
}


/*
* @brief 変動処理
* @note  滑らかなHPの増減を実装
*/
void HPBar::update()
{
	// HPバーの表示比率がHP以上の時
	if (hpRatio > pGame->GetPlayer()->GetHp()) {
		hpRatio -= HP_CHANGE_AMOUNT;
	}
	// HPバーの表示比率がHP以下の時
	else if (hpRatio < pGame->GetPlayer()->GetHp()) {
		hpRatio += HP_CHANGE_AMOUNT;
	}
}


/*
* @brief 描画メソッド
* @note  
*/
void HPBar::draw()
{
	// HPの割合を求める
	float Ratio = hpRatio / MAX_HP;

	// バーの色指定
	int BarColor = GREEN;
	// 体力低下でバーの色変更
	if (pGame->GetPlayer()->GetHp() <= LOW_HP) { BarColor = RED; }

	// HPバー描画	横幅に割合をかけて増減を表現
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + (HP_BAR_WIDTH * Ratio), HP_BAR_POS_Y + HP_BAR_HEIGHT,
			BarColor, TRUE);
	// 増減がわかりやすいように縁も描画
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH, HP_BAR_POS_Y + HP_BAR_HEIGHT, 
			WHITE, FALSE);
}