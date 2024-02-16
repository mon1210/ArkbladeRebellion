#include "HPBar.h"


/*
* @brief HPBarのコンストラクタ
*/
HPBar::HPBar(Game* Game)
{
	pGame = Game;
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
	// Player -------------
	// HPバーの表示比率がHP以上の時
	if (currnetPlayerHp > pGame->GetPlayer()->GetHp()) {
		currnetPlayerHp -= HP_CHANGE_AMOUNT;
	}
	// HPバーの表示比率がHP以下の時
	else if (currnetPlayerHp < pGame->GetPlayer()->GetHp()) {
		currnetPlayerHp += HP_CHANGE_AMOUNT;
	}

	// Enemy --------------
	if (currnetEnemyHp > pGame->GetEnemy()->GetHp()) {
		currnetEnemyHp -= HP_CHANGE_AMOUNT;
	}
	else if (currnetEnemyHp < pGame->GetEnemy()->GetHp()) {
		currnetEnemyHp += HP_CHANGE_AMOUNT;
	}
}


/*
* @brief 描画メソッド
* @note  体力低下でバーの色変更
*/
void HPBar::draw()
{
	// HPの割合を求める
	float Ratio = currnetPlayerHp / MAX_HP;

	// バーの色指定
	int BarColor = GREEN;
	// 体力低下でバーの色変更
	if (pGame->GetPlayer()->GetHp() <= LOW_HP) { BarColor = RED; }

	// HPバー描画	横幅に割合をかけて増減を表現
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + static_cast<int>(HP_BAR_WIDTH * Ratio), HP_BAR_POS_Y + HP_BAR_HEIGHT,
			BarColor, TRUE);
	// 増減がわかりやすいように縁も描画
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH, HP_BAR_POS_Y + HP_BAR_HEIGHT, 
			WHITE, FALSE);

	// Enemy ----------------------------------
	float EHPRatio = currnetEnemyHp / ENEMY_MAX_HP;
	// HPバー描画	横幅に割合をかけて増減を表現
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + static_cast<int>(ENEMY_HP_BAR_WIDTH * EHPRatio), ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		RED, TRUE);
	// 増減がわかりやすいように縁も描画
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + ENEMY_HP_BAR_WIDTH, ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		BLACK, FALSE);
	// Enemy 名前表示
	DrawString(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y - ENEMY_NAME_POS_Y, "Enemy:", BLACK);
}