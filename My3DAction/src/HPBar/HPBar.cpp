#include "HPBar.h"


/*
* @brief HPBar�̃R���X�g���N�^
*/
HPBar::HPBar(Game* Game_)
{
	pGame = Game_;
}


// �f�X�g���N�^
HPBar::~HPBar()
{
}


/*
* @brief �ϓ�����
* @note  ���炩��HP�̑���������
*/
void HPBar::move()
{
	// HP�o�[�̕\���䗦��HP�ȏ�̎�
	if (hpRatio > pGame->GetPlayer()->GetHp()) {
		hpRatio -= HP_CHANGE_AMOUNT;
	}
	// HP�o�[�̕\���䗦��HP�ȉ��̎�
	else if (hpRatio < pGame->GetPlayer()->GetHp()) {
		hpRatio += HP_CHANGE_AMOUNT;
	}
}


/*
* @brief �`�惁�\�b�h
* @note  
*/
void HPBar::draw()
{
	// HP�̊��������߂�
	float Ratio = hpRatio / MAX_HP;
	// HP�o�[�`��	�����Ɋ����������đ�����\��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + (HP_BAR_WIDTH * Ratio), HP_BAR_POS_Y + HP_BAR_HEIGHT,
			GREEN, TRUE);
	// �������킩��₷���悤�ɉ����`��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH, HP_BAR_POS_Y + HP_BAR_HEIGHT, 
			WHITE, FALSE);
}