#include "DxLib.h"
#include <vector>
#include "..\Constants.h"
#pragma once

/*	
	�ӂ̒���1�̗����̂����
	���S�_������A�������甪�̒��_�ɑ΂��čs��������邱�Ƃō��C���[�W
	���S�_�̒�`�͂��Ȃ�
*/

class OBBCollider
{
public:
	OBBCollider(VECTOR scale_, VECTOR rotate_, VECTOR translate_);	// �R���X�g���N�^�@�N���X���Ƃɒ�`���邱�Ƃō쐬����
	~OBBCollider();

	void changeScaleMatrix(VECTOR& scale_);							// scaleMatrix�ύX�p���\�b�h
	void changeRotateMatrix(VECTOR& rotate_);						// rotateMatrix�ύX�p���\�b�h
	void changeTranslateMatrix(VECTOR& translate_);					// translateMatrix�ύX�p���\�b�h
	void setParentMatrix(MATRIX parent_);							// parentMatrix�Z�b�g�p���\�b�h
private:
	void update();													// �X�V���\�b�h

#ifdef _DEBUG
public:
	void draw();													// �`�惁�\�b�h
#endif // _DEBUG

private:
	// ���݂̒��_���W
	VECTOR currentVertices[MAX_VERTICES]{};

	// MGetIdent()�@MATRIX�N���X�̃R���X�g���N�^�ŁA�ϐ������������Ă���
	MATRIX scaleMatrix	  { MGetIdent() };		// �g�k�s��
	MATRIX rotateMatrix	  { MGetIdent() };		// ��]�s��
	MATRIX translateMatrix{ MGetIdent() };		// ���s�ړ��s��
	MATRIX parentMatrix	  { MGetIdent() };		// �e�̕ϊ��s��

	MATRIX transformMatrix{ MGetIdent() };		// �ϊ��s��@��L�̍s����܂Ƃ߂ĕۑ�����
};