#include "HealCounter.h"


/**
* @brief HPCounter�̃R���X�g���N�^
*/
HealCounter::HealCounter(Game *Game_)
{
    pGame = Game_;
}


// �f�X�g���N�^
HealCounter::~HealCounter()
{
}


/**
* @brief �`�惁�\�b�h
*/
void HealCounter::draw()
{
    DrawFormatString(HEAL_COUNT_POS_X, HEAL_COUNT_POS_Y, color, "heal : %d", pGame->GetPlayer()->GetHealCount());
}


/**
* @brief �X�V���\�b�h
* @note  �c��񐔂ɍ��킹�ĐF�ύX
*/
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