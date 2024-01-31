#include "OBBCollider.h"


/**
* @brief OBBColliderのコンストラクタ
* @note  引数の値を基に、OBBColliderを作成
* @param[in] scale_			拡縮値
* @param[in] rotate_		回転値
* @param[in] translate_		移動値
*/
OBBCollider::OBBCollider(VECTOR scale_, VECTOR rotate_, VECTOR translate_)
{
	// 拡縮行列を設定
	scaleMatrix = MGetIdent();
	CreateScalingMatrix(&scaleMatrix, scale_.x, scale_.y, scale_.z);

	// 回転行列を設定
	VECTOR rotate_rad = VScale(rotate_, DX_PI / 180.f);
	rotateMatrix = MGetIdent();
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);

	// 移動行列を設定
	translateMatrix = MGetIdent();
	CreateTranslationMatrix(&translateMatrix, translate_.x, translate_.y, translate_.z);

	// 更新
	update();
}


// デストラクタ
OBBCollider::~OBBCollider()
{
}


/**
* @brief scaleMatrix変更用メソッド
*/
void OBBCollider::changeScaleMatrix(VECTOR& scale_)
{
	// 初期化
	scaleMatrix = MGetIdent();
	// 拡縮行列作成し、代入
	CreateScalingMatrix(&scaleMatrix, scale_.x, scale_.y, scale_.z);
	// 更新
	update();
}


/**
* @brief rotateMatrix変更用メソッド
*/
void OBBCollider::changeRotateMatrix(VECTOR& rotate_)
{
	// x, y, z成分をそれぞれ弧度法に変換して保存
	VECTOR rotate_rad = VScale(rotate_, DX_PI / 180.f);
	// 初期化
	rotateMatrix = MGetIdent();
	// 回転行列を作成し、代入
	CreateRotationXYZMatrix(&rotateMatrix, rotate_rad.x, rotate_rad.y, rotate_rad.z);
	// 更新
	update();
}


/**
* @brief translateMatrix変更用メソッド
*/
void OBBCollider::changeTranslateMatrix(VECTOR& translate_)
{
	// 初期化
	translateMatrix = MGetIdent();
	// 移動行列を作成し、代入
	CreateTranslationMatrix(&translateMatrix, translate_.x, translate_.y, translate_.z);
	// 更新
	update();
}


/**
* @brief parentMatrixセット用メソッド
*/
void OBBCollider::setParentMatrix(MATRIX parent_)
{
	parentMatrix = parent_;

	update();
}


/**
* @brief OBBからローカル軸を取得
*/
void OBBCollider::GetAxis(Axis& axis)
{
	GetAxis(axis.x, axis.y, axis.z);
}


/**
* @brief OBBからローカル軸を取得
*/
void OBBCollider::GetAxis(VECTOR& x_axis, VECTOR& y_axis, VECTOR& z_axis)
{
	MATRIX mat = rotateMatrix;
	// 回転行列から各軸の方向ベクトルを取得
	x_axis = VGet(mat.m[0][0], mat.m[0][1], mat.m[0][2]);
	y_axis = VGet(mat.m[1][0], mat.m[1][1], mat.m[1][2]);
	z_axis = VGet(mat.m[2][0], mat.m[2][1], mat.m[2][2]);
}


/**
* @brief 更新メソッド
*/
void OBBCollider::update()
{
	// 中心から八つの頂点に対しての座標を定義    時計回り
	// 辺の長さ1なので半分の0.5で計算
	const VECTOR VERTICES[] = {
		{ -0.5f,  0.5f, -0.5f},   // x:左　y:上　z:手前   [0]
		{  0.5f,  0.5f, -0.5f},   // x:右　y:上　z:手前   [1]
		{  0.5f, -0.5f, -0.5f},   // x:右　y:下　z:手前   [2]
		{ -0.5f, -0.5f, -0.5f},   // x:左　y:下　z:手前   [3]

		{ -0.5f,  0.5f,  0.5f},   // x:左　y:上　z:奥     [4]
		{  0.5f,  0.5f,  0.5f},   // x:右　y:上　z:奥     [5]
		{  0.5f, -0.5f,  0.5f},   // x:右　y:下　z:奥     [6]
		{ -0.5f, -0.5f,  0.5f},   // x:左　y:下　z:奥     [7]
	};

	// 初期化
	transformMatrix = MGetIdent();

	// 以下 変換処理 =====================================================
	
	// ①拡縮行列を乗算
	transformMatrix = MMult(transformMatrix, scaleMatrix);
	// ②回転行列を乗算
	transformMatrix = MMult(transformMatrix, rotateMatrix);
	// ③移動行列を乗算
	transformMatrix = MMult(transformMatrix, translateMatrix);
	// 親の変換行列を乗算
	transformMatrix = MMult(transformMatrix, parentMatrix);

	// 以上 変換処理 =====================================================

	// 8つの各頂点に変換を反映し、座標変更
	for (int i = 0; i < MAX_VERTICES; i++) 
	{
		//「VTransform」行列によって座標を作ってくれる
		currentVertices[i] = VTransform(VERTICES[i], transformMatrix);
	}

}


#ifdef _DEBUG
/**
* @brief 描画メソッド
*/
void OBBCollider::draw()
{
	// currentVerticesを使って立方体を書く
	std::vector<std::pair<VECTOR, VECTOR>> vertice_list =
	{
		// 0->1 1->2 2->3 3->0  矩形1
		{currentVertices[0],currentVertices[1] },
		{currentVertices[1],currentVertices[2] },
		{currentVertices[2],currentVertices[3] },
		{currentVertices[3],currentVertices[0] },

		// 4->5 5->6 6->7 7->4  矩形2　矩形1と対面
		{currentVertices[4],currentVertices[5] },
		{currentVertices[5],currentVertices[6] },
		{currentVertices[6],currentVertices[7] },
		{currentVertices[7],currentVertices[4] },

		// 0->4 1->5 2->6 3->7  矩形1から2のベクトル
		{currentVertices[0],currentVertices[4] },
		{currentVertices[1],currentVertices[5] },
		{currentVertices[2],currentVertices[6] },
		{currentVertices[3],currentVertices[7] },
	};

	// list分回す
	for (const auto& pair : vertice_list)
	{
		// キーワード二つを取り出し、ラインを表示
		DrawLine3D(pair.first, pair.second, WHITE);
	}

}

#endif // _DEBUG