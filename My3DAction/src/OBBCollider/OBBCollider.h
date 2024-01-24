/**
* @file		OBBCollider.h
* @brief	�N���X OBBCollider �̐錾
*/
#pragma once
#include "DxLib.h"
#include <vector>
#include "..\Constants.h"

/*	
	�ӂ̒���1�̗����̂����
	���S�_������A�������甪�̒��_�ɑ΂��čs��������邱�Ƃō��C���[�W
	���S�_�̒�`�͂��Ȃ�
*/

class OBBCollider
{
public:
	/**
	* @brief OBBCollider�̃R���X�g���N�^
	* @note  �����̒l����ɁAOBBCollider���쐬
	* @param[in] scale_			�g�k�l
	* @param[in] rotate_		��]�l
	* @param[in] translate_		�ړ��l
	*/
	OBBCollider(VECTOR scale_, VECTOR rotate_, VECTOR translate_);
	~OBBCollider();
	/**
	* @brief scaleMatrix�ύX�p���\�b�h
	*/
	void changeScaleMatrix(VECTOR& scale_);
	/**
	* @brief rotateMatrix�ύX�p���\�b�h
	*/
	void changeRotateMatrix(VECTOR& rotate_);
	/**
	* @brief translateMatrix�ύX�p���\�b�h
	*/
	void changeTranslateMatrix(VECTOR& translate_);
	/**
	* @brief parentMatrix�Z�b�g�p���\�b�h
	*/
	void setParentMatrix(MATRIX parent_);
private:
	/**
	* @brief �X�V���\�b�h
	*/
	void update();

#ifdef _DEBUG
public:
	/**
	* @brief �`�惁�\�b�h
	*/
	void draw();
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