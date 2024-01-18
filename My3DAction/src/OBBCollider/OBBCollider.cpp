#include "OBBCollider.h"


/**
* @brief OBBCollider�̃R���X�g���N�^
*/
OBBCollider::OBBCollider(VECTOR scale_, VECTOR rotate_, VECTOR translate_)
{
	// �g�k�s���ݒ�
	scaleMatrix = MGetIdent();
	CreateScalingMatrix(&scaleMatrix, scale_.x, scale_.y, scale_.z);

	// ��]�s���ݒ�
	VECTOR rotate_rad = VScale(rotate_, DX_PI / 180.f);
	rotateMatrix = MGetIdent();
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);

	// �ړ��s���ݒ�
	translateMatrix = MGetIdent();
	CreateTranslationMatrix(&translateMatrix, translate_.x, translate_.y, translate_.z);

	// �X�V
	update();
}


// �f�X�g���N�^
OBBCollider::~OBBCollider()
{
}


/**
* @brief scaleMatrix�ύX�p���\�b�h
*/
void OBBCollider::changeScaleMatrix(VECTOR& scale_)
{
	// ������
	scaleMatrix = MGetIdent();
	// �g�k�s��쐬���A���
	CreateScalingMatrix(&scaleMatrix, scale_.x, scale_.y, scale_.z);
	// �X�V
	update();
}


/**
* @brief rotateMatrix�ύX�p���\�b�h
*/
void OBBCollider::changeRotateMatrix(VECTOR& rotate_)
{
	// x, y, z���������ꂼ��ʓx�@�ɕϊ����ĕۑ�
	VECTOR rotate_rad = VScale(rotate_, DX_PI / 180.f);
	// ������
	rotateMatrix = MGetIdent();
	// ��]�s����쐬���A���
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);
	// �X�V
	update();
}


/**
* @brief translateMatrix�ύX�p���\�b�h
*/
void OBBCollider::changeTranslateMatrix(VECTOR& translate_)
{
	// ������
	translateMatrix = MGetIdent();
	// �ړ��s����쐬���A���
	CreateTranslationMatrix(&translateMatrix, translate_.x, translate_.y, translate_.z);
	// �X�V
	update();
}


/**
* @brief parentMatrix�Z�b�g�p���\�b�h
*/
void OBBCollider::setParentMatrix(MATRIX parent_)
{
	parentMatrix = parent_;

	update();
}


/**
* @brief �X�V���\�b�h
*/
void OBBCollider::update()
{
	// ���S���甪�̒��_�ɑ΂��Ă̍��W���`    ���v���
	// �ӂ̒���1�Ȃ̂Ŕ�����0.5�Ōv�Z
	const VECTOR VERTICES[] = {
		{ -0.5f,  0.5f, -0.5f},   // x:���@y:��@z:��O   [0]
		{  0.5f,  0.5f, -0.5f},   // x:�E�@y:��@z:��O   [1]
		{  0.5f, -0.5f, -0.5f},   // x:�E�@y:���@z:��O   [2]
		{ -0.5f, -0.5f, -0.5f},   // x:���@y:���@z:��O   [3]

		{ -0.5f,  0.5f,  0.5f},   // x:���@y:��@z:��     [4]
		{  0.5f,  0.5f,  0.5f},   // x:�E�@y:��@z:��     [5]
		{  0.5f, -0.5f,  0.5f},   // x:�E�@y:���@z:��     [6]
		{ -0.5f, -0.5f,  0.5f},   // x:���@y:���@z:��     [7]
	};

	// ������
	transformMatrix = MGetIdent();

	// �ȉ� �ϊ����� =====================================================
	
	// �@�g�k�s�����Z
	transformMatrix = MMult(transformMatrix, scaleMatrix);
	// �A��]�s�����Z
	transformMatrix = MMult(transformMatrix, rotateMatrix);
	// �B�ړ��s�����Z
	transformMatrix = MMult(transformMatrix, translateMatrix);
	// �e�̕ϊ��s�����Z
	transformMatrix = MMult(transformMatrix, parentMatrix);

	// �ȏ� �ϊ����� =====================================================

	// 8�̊e���_�ɕϊ��𔽉f���A���W�ύX
	for (int i = 0; i < MAX_VERTICES; i++) 
	{
		//�uVTransform�v�s��ɂ���č��W������Ă����
		currentVertices[i] = VTransform(VERTICES[i], transformMatrix);
	}

}


#ifdef _DEBUG
/**
* @brief �`�惁�\�b�h
*/
void OBBCollider::draw()
{
	// currentVertices���g���ė����̂�����
	std::vector<std::pair<VECTOR, VECTOR>> vertice_list =
	{
		// 0->1 1->2 2->3 3->0  ��`1
		{currentVertices[0],currentVertices[1] },
		{currentVertices[1],currentVertices[2] },
		{currentVertices[2],currentVertices[3] },
		{currentVertices[3],currentVertices[0] },

		// 4->5 5->6 6->7 7->4  ��`2�@��`1�ƑΖ�
		{currentVertices[4],currentVertices[5] },
		{currentVertices[5],currentVertices[6] },
		{currentVertices[6],currentVertices[7] },
		{currentVertices[7],currentVertices[4] },

		// 0->4 1->5 2->6 3->7  ��`1����2�̃x�N�g��
		{currentVertices[0],currentVertices[4] },
		{currentVertices[1],currentVertices[5] },
		{currentVertices[2],currentVertices[6] },
		{currentVertices[3],currentVertices[7] },
	};

	// list����
	for (const auto& pair : vertice_list)
	{
		// �L�[���[�h������o���A���C����\��
		DrawLine3D(pair.first, pair.second, WHITE);
	}

}

#endif // _DEBUG