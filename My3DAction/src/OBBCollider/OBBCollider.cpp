#include "OBBCollider.h"


// �R���X�g���N�^
OBBCollider::OBBCollider(VECTOR scale, VECTOR rotate, VECTOR translate)
{
	// �g�k�s���ݒ�
	scaleMatrix = MGetIdent();
	CreateScalingMatrix(&scaleMatrix, scale.x, scale.y, scale.z);

	// ��]�s���ݒ�
	VECTOR rotate_rad = VScale(rotate, DX_PI / 180.f);
	rotateMatrix = MGetIdent();
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);

	// �ړ��s���ݒ�
	translateMatrix = MGetIdent();
	CreateTranslationMatrix(&translateMatrix, translate.x, translate.y, translate.z);

	// �X�V
	update();
}


// �f�X�g���N�^
OBBCollider::~OBBCollider()
{
}


// scaleMatrix�ύX�p���\�b�h
void OBBCollider::changeScaleMatrix(VECTOR& scale)
{
	// ������
	scaleMatrix = MGetIdent();
	// �g�k�s��쐬���A���
	CreateScalingMatrix(&scaleMatrix, scale.x, scale.y, scale.z);
	// �X�V
	update();
}


// rotateMatrix�ύX�p���\�b�h
void OBBCollider::changeRotateMatrix(VECTOR& rotate)
{
	// x, y, z���������ꂼ��ʓx�@�ɕϊ����ĕۑ�
	VECTOR rotate_rad = VScale(rotate, DX_PI / 180.f);
	// ������
	rotateMatrix = MGetIdent();
	// ��]�s����쐬���A���
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);
	// �X�V
	update();
}


// translateMatrix�ύX�p���\�b�h
void OBBCollider::changeTranslateMatrix(VECTOR& translate)
{
	// ������
	translateMatrix = MGetIdent();
	// �ړ��s����쐬���A���
	CreateTranslationMatrix(&translateMatrix, translate.x, translate.y, translate.z);
	// �X�V
	update();
}


// parentMatrix�Z�b�g�p���\�b�h
void OBBCollider::setParentMatrix(MATRIX parent)
{
	parentMatrix = parent;

	update();
}


/* 
	OBB���烍�[�J�������擾
	�֐��̃I�[�o�[���[�h
*/ 
void OBBCollider::GetAxis(Axis& axis)
{
	GetAxis(axis.x, axis.y, axis.z);
}


// OBB���烍�[�J�������擾
void OBBCollider::GetAxis(VECTOR& x_axis, VECTOR& y_axis, VECTOR& z_axis)
{
	MATRIX mat = rotateMatrix;
	// ��]�s�񂩂�e���̕����x�N�g�����擾
	x_axis = VGet(mat.m[0][0], mat.m[0][1], mat.m[0][2]);
	y_axis = VGet(mat.m[1][0], mat.m[1][1], mat.m[1][2]);
	z_axis = VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]);
}


// �X�V���\�b�h
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


// �`�惁�\�b�h
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
