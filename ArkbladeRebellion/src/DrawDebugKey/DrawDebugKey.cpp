#include "DrawDebugKey.h"

// �R���X�g���N�^
DrawDebugKey::DrawDebugKey()
{
}

// �f�X�g���N�^
DrawDebugKey::~DrawDebugKey()
{
}

// �`�惁�\�b�h
void DrawDebugKey::draw()
{
	// OBB�`��L�[��\��
	DrawString(DRAW_DEBUG_KEY_POS_X, DRAW_OBB_KEY_POS_Y, "OBB�\���FL_SHIFT", GREEN);
	// �����蔻��J�v�Z���`��L�[��\��
	DrawString(DRAW_DEBUG_KEY_POS_X, DRAW_CAP_KEY_POS_Y, "�����蔻��J�v�Z���\���FQ", GREEN);
}