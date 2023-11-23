///*
//* @file	 My3DAction.h
//* @brief
//*
//*
//*/
//#include "DxLib.h"
//#include "Constants.h"
//#include "Model.h"
//#include "Player.h"
//#include "Selector.h"
//#include "Enums.h"
//
//// インスタンス生成
////Selector selectorObject;
////int GamePhase = selectorObject.eGamePhase;
//
////// デバッグ用Titleメソッド
////void drawTitle()
////{
////    DrawString(100, 100, "Title", GetColor(255, 255, 255));
////
////    if (CheckHitKey(KEY_INPUT_B))
////    {
////        m_eGamePhase = GAMEPHASE_GAME;
////    }
////
////}
////
////float enemy_anim_timer = 0.f;
////float player_anim_timer = 0.f;
////int enemy_anim_no = 1;
////int player_anim_no = 1;
////// ここでアニメーション管理
////void drawGame()
////{
////    // インスタンス作成
////    Model modelObject;
////    // モデルセットメソッド呼び出し
////    modelObject.ModelSet();
////    // 敵モデルのハンドルを取得
////    int enemy_handle = modelObject.enemyHandle;
////    // プレイヤーモデルのハンドルを取得
////    int player_handle = modelObject.playerHandle;
////    //int anim_no = modelObject.anim_no;
////    //int anim_timer = modelObject.anim_timer;
////
////    // アニメーションの設定
////    MV1AttachAnim(enemy_handle, 0);
////    MV1AttachAnim(player_handle, 0);
////    VECTOR pos = VGet(0.f, 0.f, 30.f);
////
////    // アニメーションの再生時間の取得
////    float anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, 0);
////    float anim_player_time = MV1GetAnimTotalTime(player_handle, 0);
////
////    if (enemy_anim_no != 0)
////    {
////        enemy_anim_no = 0;
////        enemy_anim_timer = 0;
////        // アニメーションにかかる時間を取得
////        anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
////        // アニメーションをデタッチ
////        MV1DetachAnim(enemy_handle, 0);
////        // アニメーションをアタッチ
////        MV1AttachAnim(enemy_handle, enemy_anim_no);
////    }
////
////    if (player_anim_no != 0)
////    {
////        player_anim_no = 0;
////        player_anim_timer = 0;
////        // アニメーションにかかる時間を取得
////        anim_player_time = MV1GetAnimTotalTime(player_handle, player_anim_no);
////            // アニメーションをデタッチ
////            MV1DetachAnim(player_handle, 0);
////        // アニメーションをアタッチ
////        MV1AttachAnim(player_handle, player_anim_no);
////    }
////
////    // 画面に映る位置に３Ｄモデルを移動
////    MV1SetPosition(enemy_handle, VGet(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z));
////    MV1SetPosition(player_handle, VGet(PLAYER_POS_X, PLAYER_POS_Y, PLAYER_POS_Z));
////
////    
////    //for (float i = 0.f; i <= anim_enemy_time; i += 1.f)
////    //{
////    //    anim_timer = i;
////
////    //    if (anim_timer >= anim_enemy_time)
////    //    {
////    //        anim_timer = 0.0f;
////    //    }
////
////    //}
////
////    enemy_anim_timer += 60 / 36.0f;
////    // enemy ------------------------------------
////    // アニメーション時間を過ぎたらリセット
////    if (enemy_anim_timer >= anim_enemy_time)
////    {
////        enemy_anim_timer = 0.0f;
////    }
////    // アニメーションセット
////    MV1SetAttachAnimTime(enemy_handle, 0, enemy_anim_timer);
////    // モデルの大きさ変更
////    MV1SetScale(enemy_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
////    // ３Ｄモデルの描画
////    MV1DrawModel(enemy_handle);
////    
////
////    // player ------------------------------------
////    // アニメーション時間を過ぎたらリセット
////    //if (anim_timer >= anim_player_time)
////    //{
////    //    anim_timer = 0.0f;
////    //}
////    //// アニメーションセット
////    //MV1SetAttachAnimTime(player_handle, 0, anim_timer);
////    //// モデルの大きさ変更
////    //MV1SetScale(player_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
////    //// ３Ｄモデルの描画
////    //MV1DrawModel(player_handle);
////
////
////    if (CheckHitKey(KEY_INPUT_SPACE))
////    {
////        m_eGamePhase = GAMEPHASE_END;
////        // モデルハンドルの削除
////        MV1DeleteModel(enemy_handle);
////        MV1DeleteModel(player_handle);
////    }
////
////}
////
////
////// デバッグ用Endメソッド
////void drawEnd()
////{
////    DrawString(100, 100, "End", GetColor(255, 255, 255));
////    
////    if (CheckHitKey(KEY_INPUT_N))
////    {
////         m_eGamePhase = GAMEPHASE_TITLE;
////    }
////
////}
//
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//    ChangeWindowMode(TRUE);     // ウィンドウモードに設定
//    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLOR);    // ウィンドウ設定
//
//    // ＤＸライブラリの初期化
//    if (DxLib_Init() < 0)
//    {
//        // エラーが発生したら直ちに終了
//        return -1;
//    }
//
//    SetDrawScreen(DX_SCREEN_BACK);	// 描画対象を裏のキャンバスに指定
//
//    // カメラの描画距離   SetCameraNearFar(最短距離,最長距離)
//    SetCameraNearFar(0.f, 1000.f);
//
//
//    /*********************
//         初期化部分
//    *********************/
//
//    // Phase初期化
//    //GamePhase = GAMEPHASE_TITLE;
//
//    // インスタンス作成
//    Model modelObject;
//    // モデルセットメソッド呼び出し
//    modelObject.ModelSet();
//    // 敵モデルのハンドルを取得
//    int enemy_handle = modelObject.enemyHandle;
//    //int player_handle = modelObject.playerHandle;
//
//    // アニメーションをアタッチ
//    MV1AttachAnim(enemy_handle, eEnemy::Idle);
//    //MV1AttachAnim(player_handle, ePlayer::Idle);
//
//    float enemy_anim_timer = 0.f;
//    //float player_anim_timer = 0.f;
//
//    // アニメーションの再生時間の取得
//    float anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, 0);
//    //float anim_player_time = MV1GetAnimTotalTime(player_handle, 0);
//
//    int enemy_anim_no = 0;
//    //int player_anim_no = 0;
//
//    // 座標セット用変数宣言・初期化
//    VECTOR EPosition = VGet(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z);
//
//    //
//    float EAngle = 0;
//
//    /**************************
//          メッセージループ
//    **************************/
//
//    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
//    {
//
//        // カメラの描画位置と見る位置を指定
//        SetCameraPositionAndTargetAndUpVec(
//            VGet(0.f, 0.f, 0.f),    // カメラ座標
//            VGet(0.f, 0.f, 1.f),    // カメラの見る位置
//            VGet(0.f, 1.f, 0.f)     // 固定
//        );
//        // カメラの位置と向きを設定     遠くから
//        //SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 1200.0f, -2000.0f), VGet(0.0f, 400.0f, 0.0f));
//
//        // 背景の色変更　灰色
//        SetBackgroundColor(128, 128, 128);
//
//        // enemy ================================================================================================
//        // I => Runモーション(2)
//        if (CheckHitKey(KEY_INPUT_I))
//        {
//            if (enemy_anim_no != eEnemy::Run)
//            {
//                enemy_anim_no = eEnemy::Run;
//                enemy_anim_timer = 0;
//                // アニメーションにかかる時間を取得
//                anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
//                // アニメーションをデタッチ
//                MV1DetachAnim(enemy_handle, 0);
//                // アニメーションをアタッチ
//                MV1AttachAnim(enemy_handle, enemy_anim_no);
//                // 手前移動
//                if (enemy_anim_no == eEnemy::Run)
//                {
//                    EAngle = 0.f;
//                    EPosition.z -= ENEMY_MOVE_SPEED;
//                }
//            }
//        }
//        else
//        {
//            // アニメーションがないとき、Idleモーション(1)
//            if (enemy_anim_no != eEnemy::Idle)
//            {
//                enemy_anim_no = eEnemy::Idle;
//                enemy_anim_timer = 0;
//                // アニメーションにかかる時間を取得
//                anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
//                // アニメーションをデタッチ
//                MV1DetachAnim(enemy_handle, 0);
//                // アニメーションをアタッチ
//                MV1AttachAnim(enemy_handle, enemy_anim_no);
//            }
//        }
//
//        // enemy ================================================================================================
//        enemy_anim_timer += ENEMY_ANIM_F_INCREMENT;
//        // アニメーション時間を過ぎたらリセット
//        if (enemy_anim_timer >= anim_enemy_time)
//        {
//            enemy_anim_timer = 0.0f;
//        }
//        // アニメーションセット
//        MV1SetAttachAnimTime(enemy_handle, 0, enemy_anim_timer);
//
//
//        // player ================================================================================================
//
//        // 引数で挑戦
//
//        //player_anim_timer += PLAYER_ANIM_F_INCREMENT;
//        //// アニメーション時間を過ぎたらリセット
//        //if (player_anim_timer >= anim_player_time)
//        //{
//        //    anim_player_time = 0.0f;
//        //}
//        //MV1SetAttachAnimTime(player_handle, 0, player_anim_timer);
//
//
//
//        ClearDrawScreen();
//
//
//        //switch (m_eGamePhase)
//        //{
//        //case GAMEPHASE_TITLE:
//        //    drawTitle();
//        //    break;
//        //case GAMEPHASE_GAME:
//        //    drawGame();
//        //    break;
//        //case GAMEPHASE_END:
//        //    drawEnd();
//        //    break;
//        //default: break;
//        //}
//
//
//        // 画面に映る位置に3Dモデルを移動
//        MV1SetPosition(enemy_handle, EPosition);
//        //MV1SetPosition(player_handle, PPosition);
//
//        // モデルの大きさ変更
//        MV1SetScale(enemy_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
//        //MV1SetScale(player_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
//
//        // モデルの回転
//        MV1SetRotationXYZ(enemy_handle, VGet(0.f, EAngle * DX_PI_F / 180.f, 0.f));
//        //MV1SetRotationXYZ(player_handle, VGet(0.f, PAngle * DX_PI_F / 180.f, 0.f));
//
//        // ３Ｄモデルの描画
//        MV1DrawModel(enemy_handle);
//        //MV1DrawModel(player_handle);
//
//
//        //WaitTimer(FLAME_TIME);
//
//        //ClearDrawScreen();
//
//        // フリップ関数
//        ScreenFlip();
//
//
//    }
//
//    // DXライブラリの後始末
//    DxLib_End();
//
//    // ソフトの終了
//    return 0;
//}