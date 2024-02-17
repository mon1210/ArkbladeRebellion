#include "HealCounter.h"


// �R���X�g���N�^
HealCounter::HealCounter(Game *Game)
{
    pGame = Game;
}


// �f�X�g���N�^
HealCounter::~HealCounter()
{
}


// �`�惁�\�b�h
void HealCounter::draw()
{
    DrawFormatString(HEAL_COUNT_POS_X, HEAL_COUNT_POS_Y, color, "heal : %d", pGame->GetPlayer()->GetHealCount());
}


// �X�V���\�b�h
void HealCounter::update()
{
    if (pGame->GetPlayer()->GetHealCount() == 0) 
    {
        // 0�̎��͐�
        color = RED; 
    } 
    else
    {
        color = GREEN;
    }

}