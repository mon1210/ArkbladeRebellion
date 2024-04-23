#include "HealCounter.h"


// コンストラクタ
HealCounter::HealCounter(Game *Game)
{
    pGame = Game;
}


// デストラクタ
HealCounter::~HealCounter()
{
}


// 描画メソッド
void HealCounter::draw()
{
    DrawFormatString(HEAL_COUNT_POS_X, HEAL_COUNT_POS_Y, color, "heal : %d", pGame->GetPlayer()->GetHealCount());
}


// 更新メソッド
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