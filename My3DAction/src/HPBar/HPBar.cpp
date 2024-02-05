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
void HPBar::update()
{
	// Player -------------
	// HP�o�[�̕\���䗦��HP�ȏ�̎�
	if (playerHpRatio > pGame->GetPlayer()->GetHp()) {
		playerHpRatio -= HP_CHANGE_AMOUNT;
	}
	// HP�o�[�̕\���䗦��HP�ȉ��̎�
	else if (playerHpRatio < pGame->GetPlayer()->GetHp()) {
		playerHpRatio += HP_CHANGE_AMOUNT;
	}

	// Enemy --------------
	if (enemyHpRatio > pGame->GetEnemy()->GetHp()) {
		enemyHpRatio -= HP_CHANGE_AMOUNT;
	}
	else if (enemyHpRatio < pGame->GetEnemy()->GetHp()) {
		enemyHpRatio += HP_CHANGE_AMOUNT;
	}
}


/*
* @brief �`�惁�\�b�h
* @note  �̗͒ቺ�Ńo�[�̐F�ύX
*/
void HPBar::draw()
{
	// HP�̊��������߂�
	float Ratio = playerHpRatio / MAX_HP;

	// �o�[�̐F�w��
	int BarColor = GREEN;
	// �̗͒ቺ�Ńo�[�̐F�ύX
	if (pGame->GetPlayer()->GetHp() <= LOW_HP) { BarColor = RED; }

	// HP�o�[�`��	�����Ɋ����������đ�����\��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + static_cast<int>(HP_BAR_WIDTH * Ratio), HP_BAR_POS_Y + HP_BAR_HEIGHT,
			BarColor, TRUE);
	// �������킩��₷���悤�ɉ����`��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH, HP_BAR_POS_Y + HP_BAR_HEIGHT, 
			WHITE, FALSE);

	// Enemy ----------------------------------
	float EHPRatio = enemyHpRatio / ENEMY_MAX_HP;
	// HP�o�[�`��	�����Ɋ����������đ�����\��
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + static_cast<int>(ENEMY_HP_BAR_WIDTH * EHPRatio), ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		RED, TRUE);
	// �������킩��₷���悤�ɉ����`��
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + ENEMY_HP_BAR_WIDTH, ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		BLACK, FALSE);
	// Enemy ���O�\��
	DrawString(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y - ENEMY_NAME_POS_Y, "Enemy:", BLACK);
}