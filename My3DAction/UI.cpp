#include "UI.h"


/*
* @brief UI�̃R���X�g���N�^
*/
UI::UI(Game* Game_)
{
	pGame = Game_;
}


// �f�X�g���N�^
UI::~UI()
{
}


/*
* @brief �ϓ�����
* @note  ���炩��HP�̑���������
*/
void UI::move()
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
void UI::draw()
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