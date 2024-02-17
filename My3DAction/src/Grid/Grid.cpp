#include "Grid.h"


// コンストラクタ
Grid::Grid()
{
}


// デストラクタ
Grid::~Grid()
{
}


// 描画メソッド
void Grid::draw()
{
    // Zバッファを使用する
    SetUseZBufferFlag(TRUE);

    // 横方向のグリッド線を描画     2.0f = グリッド線の間隔
    startHorizontal = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    endHorizontal = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, LINE_AREA_SIZE / 2.0f);
    for (int i = 0; i <= LINE_NUM; i++)
    {
        DrawLine3D(startHorizontal, endHorizontal, GetColor(255, 255, 255));
        startHorizontal.x += LINE_AREA_SIZE / LINE_NUM;
        endHorizontal.x += LINE_AREA_SIZE / LINE_NUM;
    }

    // 縦方向のグリッド線を描画     2.0f = グリッド線の間隔
    startVertical = VGet(-LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    endVertical = VGet(LINE_AREA_SIZE / 2.0f, GRID_LINE_START_POSITION, -LINE_AREA_SIZE / 2.0f);
    for (int i = 0; i < LINE_NUM; i++)
    {
        DrawLine3D(startVertical, endVertical, GetColor(255, 255, 255));
        startVertical.z += LINE_AREA_SIZE / LINE_NUM;
        endVertical.z += LINE_AREA_SIZE / LINE_NUM;
    }

    // Zバッファを使用しない
    SetUseZBufferFlag(FALSE);
}