/**
* @file		OBBCollider.h
* @brief	�N���X OBBCollider �̐錾
*/
#pragma once
#include "DxLib.h"
#include <vector>
#include "..\Axis.h"
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
	* @param[in] scale			�g�k�l
	* @param[in] rotate			��]�l
	* @param[in] translate		�ړ��l
	*/
	OBBCollider(VECTOR scale, VECTOR rotate, VECTOR translate);

	// �f�X�g���N�^
	~OBBCollider();

	/**
	* @brief scaleMatrix�ύX�p���\�b�h
	*/
	void changeScaleMatrix(VECTOR& scale);

	/**
	* @brief rotateMatrix�ύX�p���\�b�h
	*/
	void changeRotateMatrix(VECTOR& rotate);

	/**
	* @brief translateMatrix�ύX�p���\�b�h
	*/
	void changeTranslateMatrix(VECTOR& translate);

	/**
	* @brief parentMatrix�Z�b�g�p���\�b�h
	*/
	void setParentMatrix(MATRIX parent);

	// �ȉ��擾�p�萔===================================================================== //
	/**
	* @brief OBB���烍�[�J�������擾
	*/
	void GetAxis(Axis& axis);
	void GetAxis(VECTOR& x_axis, VECTOR& y_axis, VECTOR& z_axis);
	// �ȏ�擾�p�萔===================================================================== //
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

public:
	// ���݂̒��_���W
	VECTOR currentVertices[MAX_VERTICES] = { VGet(0.f, 0.f, 0.f) };

private:
	// MGetIdent()�@MATRIX�N���X�̃R���X�g���N�^�ŁA�ϐ������������Ă���
	MATRIX scaleMatrix		= MGetIdent();	// �g�k�s��
	MATRIX rotateMatrix		= MGetIdent();	// ��]�s��
	MATRIX translateMatrix	= MGetIdent();	// ���s�ړ��s��
	MATRIX parentMatrix		= MGetIdent();	// �e�̕ϊ��s��

	MATRIX transformMatrix	= MGetIdent();	// �ϊ��s��@��L�̍s����܂Ƃ߂ĕۑ�����
};