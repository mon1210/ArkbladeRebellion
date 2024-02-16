#include "HealCounter.h"


/**
* @brief HealCounterのコンストラクタ
*/
HealCounter::HealCounter(Game *Game)
{
    pGame = Game;
}


// デストラクタ
HealCounter::~HealCounter()
{
}


/**
* @brief 描画メソッド
*/
void HealCounter::draw()
{
    DrawFormatString(HEAL_COUNT_POS_X, HEAL_COUNT_POS_Y, color, "heal : %d", pGame->GetPlayer()->GetHealCount());
}


/**
* @brief 更新メソッド
* @note  残り回数に合わせて色変更
*/
void HealCounter::update()
{
    if (pGame->GetPlayer()->GetHealCount() == 0) 
    {
        // 0の時は赤
        color = RED; 
    } 
    else
    {
        color = GREEN;
    }

}