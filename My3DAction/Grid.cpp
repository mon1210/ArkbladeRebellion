
#include "Grid.h"


/**
* @brief Grid�̃R���X�g���N�^
*
*/
Grid::Grid()
{
    // Horizontal
    startHorizontal = VGet(0.f, 0.f, 0.f);
    endHorizontal = VGet(0.f, 0.f, 0.f);
    // Vertical
    startVertical = VGet(0.f, 0.f, 0.f);
    endVertical = VGet(0.f, 0.f, 0.f);
}


// �f�X�g���N�^
Grid::~Grid()
{
}


/**
* @brief �`��֐�
* @note  Stage::draw()�ŌĂяo��
*/
void Grid::Draw()
{
    // Z�o�b�t�@���g�p����
    SetUseZBufferFlag(TRUE);

    // �������̃O���b�h����`��     2.0f = �O���b�h���̊Ԋu
    startHorizontal = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    endHorizontal = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, LINE_AREA_SIZE / 2.0f);
    for (int i = 0; i <= LINE_NUM; i++)
    {
        DrawLine3D(startHorizontal, endHorizontal, GetColor(255, 255, 255));
        startHorizontal.x += LINE_AREA_SIZE / LINE_NUM;
        endHorizontal.x += LINE_AREA_SIZE / LINE_NUM;
    }

    // �c�����̃O���b�h����`��     2.0f = �O���b�h���̊Ԋu
    startVertical = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    endVertical = VGet(LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    for (int i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(startVertical, endVertical, GetColor(255, 255, 255));
        startVertical.z += LINE_AREA_SIZE / LINE_NUM;
        endVertical.z += LINE_AREA_SIZE / LINE_NUM;
    }

    // Z�o�b�t�@���g�p���Ȃ�
    SetUseZBufferFlag(FALSE);
}