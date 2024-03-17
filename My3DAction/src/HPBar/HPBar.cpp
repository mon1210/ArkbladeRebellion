#include "HPBar.h"


// �R���X�g���N�^
HPBar::HPBar(Game* Game)
{
	pGame = Game;
}


// �f�X�g���N�^
HPBar::~HPBar()
{
}


// �ϓ�����
void HPBar::update()
{
	// Player -------------
	// HP�o�[�̕\���䗦��HP�ȏ�̎�
	if (currnetPlayerHp > pGame->GetPlayer()->GetHp()) {
		currnetPlayerHp--;
	}
	// HP�o�[�̕\���䗦��HP�ȉ��̎�
	else if (currnetPlayerHp < pGame->GetPlayer()->GetHp()) {
		currnetPlayerHp++;
	}

	// Enemy --------------
	if (currnetEnemyHp > pGame->GetEnemy()->GetHp()) {
		currnetEnemyHp--;
	}
	else if (currnetEnemyHp < pGame->GetEnemy()->GetHp()) {
		currnetEnemyHp++;
	}
}


// �`�惁�\�b�h
void HPBar::draw()
{
	// HP�̊��������߂�
	float Ratio = currnetPlayerHp / MAX_HP;

	// �o�[�̐F�w��
	int BarColor = GREEN;
	// �̗͒ቺ�Ńo�[�̐F�ύX
	if (pGame->GetPlayer()->GetHp() <= LOW_HP) { BarColor = RED; }

	// HP�o�[�`��	�����Ɋ����������đ�����\��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH * Ratio, HP_BAR_POS_Y + HP_BAR_HEIGHT,
			BarColor, TRUE);
	// �������킩��₷���悤�ɉ����`��
	DrawBox(HP_BAR_POS_X, HP_BAR_POS_Y,
			HP_BAR_POS_X + HP_BAR_WIDTH, HP_BAR_POS_Y + HP_BAR_HEIGHT, 
			WHITE, FALSE);

	// Enemy ----------------------------------
	float EnemyHPRatio = currnetEnemyHp / ENEMY_MAX_HP;
	// HP�o�[�`��	�����Ɋ����������đ�����\��
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + ENEMY_HP_BAR_WIDTH * EnemyHPRatio, ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		RED, TRUE);
	// �������킩��₷���悤�ɉ����`��
	DrawBox(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y,
		ENEMY_HP_BAR_POS_X + ENEMY_HP_BAR_WIDTH, ENEMY_HP_BAR_POS_Y + ENEMY_HP_BAR_HEIGHT,
		BLACK, FALSE);
	// Enemy ���O�\��
	DrawString(ENEMY_HP_BAR_POS_X, ENEMY_HP_BAR_POS_Y - ENEMY_NAME_POS_Y, "Enemy:", BLACK);
}