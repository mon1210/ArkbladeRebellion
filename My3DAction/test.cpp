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
//// �C���X�^���X����
////Selector selectorObject;
////int GamePhase = selectorObject.eGamePhase;
//
////// �f�o�b�O�pTitle���\�b�h
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
////// �����ŃA�j���[�V�����Ǘ�
////void drawGame()
////{
////    // �C���X�^���X�쐬
////    Model modelObject;
////    // ���f���Z�b�g���\�b�h�Ăяo��
////    modelObject.ModelSet();
////    // �G���f���̃n���h�����擾
////    int enemy_handle = modelObject.enemyHandle;
////    // �v���C���[���f���̃n���h�����擾
////    int player_handle = modelObject.playerHandle;
////    //int anim_no = modelObject.anim_no;
////    //int anim_timer = modelObject.anim_timer;
////
////    // �A�j���[�V�����̐ݒ�
////    MV1AttachAnim(enemy_handle, 0);
////    MV1AttachAnim(player_handle, 0);
////    VECTOR pos = VGet(0.f, 0.f, 30.f);
////
////    // �A�j���[�V�����̍Đ����Ԃ̎擾
////    float anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, 0);
////    float anim_player_time = MV1GetAnimTotalTime(player_handle, 0);
////
////    if (enemy_anim_no != 0)
////    {
////        enemy_anim_no = 0;
////        enemy_anim_timer = 0;
////        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
////        anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
////        // �A�j���[�V�������f�^�b�`
////        MV1DetachAnim(enemy_handle, 0);
////        // �A�j���[�V�������A�^�b�`
////        MV1AttachAnim(enemy_handle, enemy_anim_no);
////    }
////
////    if (player_anim_no != 0)
////    {
////        player_anim_no = 0;
////        player_anim_timer = 0;
////        // �A�j���[�V�����ɂ����鎞�Ԃ��擾
////        anim_player_time = MV1GetAnimTotalTime(player_handle, player_anim_no);
////            // �A�j���[�V�������f�^�b�`
////            MV1DetachAnim(player_handle, 0);
////        // �A�j���[�V�������A�^�b�`
////        MV1AttachAnim(player_handle, player_anim_no);
////    }
////
////    // ��ʂɉf��ʒu�ɂR�c���f�����ړ�
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
////    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
////    if (enemy_anim_timer >= anim_enemy_time)
////    {
////        enemy_anim_timer = 0.0f;
////    }
////    // �A�j���[�V�����Z�b�g
////    MV1SetAttachAnimTime(enemy_handle, 0, enemy_anim_timer);
////    // ���f���̑傫���ύX
////    MV1SetScale(enemy_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
////    // �R�c���f���̕`��
////    MV1DrawModel(enemy_handle);
////    
////
////    // player ------------------------------------
////    // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
////    //if (anim_timer >= anim_player_time)
////    //{
////    //    anim_timer = 0.0f;
////    //}
////    //// �A�j���[�V�����Z�b�g
////    //MV1SetAttachAnimTime(player_handle, 0, anim_timer);
////    //// ���f���̑傫���ύX
////    //MV1SetScale(player_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
////    //// �R�c���f���̕`��
////    //MV1DrawModel(player_handle);
////
////
////    if (CheckHitKey(KEY_INPUT_SPACE))
////    {
////        m_eGamePhase = GAMEPHASE_END;
////        // ���f���n���h���̍폜
////        MV1DeleteModel(enemy_handle);
////        MV1DeleteModel(player_handle);
////    }
////
////}
////
////
////// �f�o�b�O�pEnd���\�b�h
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
//    ChangeWindowMode(TRUE);     // �E�B���h�E���[�h�ɐݒ�
//    SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_COLOR);    // �E�B���h�E�ݒ�
//
//    // �c�w���C�u�����̏�����
//    if (DxLib_Init() < 0)
//    {
//        // �G���[�����������璼���ɏI��
//        return -1;
//    }
//
//    SetDrawScreen(DX_SCREEN_BACK);	// �`��Ώۂ𗠂̃L�����o�X�Ɏw��
//
//    // �J�����̕`�拗��   SetCameraNearFar(�ŒZ����,�Œ�����)
//    SetCameraNearFar(0.f, 1000.f);
//
//
//    /*********************
//         ����������
//    *********************/
//
//    // Phase������
//    //GamePhase = GAMEPHASE_TITLE;
//
//    // �C���X�^���X�쐬
//    Model modelObject;
//    // ���f���Z�b�g���\�b�h�Ăяo��
//    modelObject.ModelSet();
//    // �G���f���̃n���h�����擾
//    int enemy_handle = modelObject.enemyHandle;
//    //int player_handle = modelObject.playerHandle;
//
//    // �A�j���[�V�������A�^�b�`
//    MV1AttachAnim(enemy_handle, eEnemy::Idle);
//    //MV1AttachAnim(player_handle, ePlayer::Idle);
//
//    float enemy_anim_timer = 0.f;
//    //float player_anim_timer = 0.f;
//
//    // �A�j���[�V�����̍Đ����Ԃ̎擾
//    float anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, 0);
//    //float anim_player_time = MV1GetAnimTotalTime(player_handle, 0);
//
//    int enemy_anim_no = 0;
//    //int player_anim_no = 0;
//
//    // ���W�Z�b�g�p�ϐ��錾�E������
//    VECTOR EPosition = VGet(ENEMY_POS_X, ENEMY_POS_Y, ENEMY_POS_Z);
//
//    //
//    float EAngle = 0;
//
//    /**************************
//          ���b�Z�[�W���[�v
//    **************************/
//
//    while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
//    {
//
//        // �J�����̕`��ʒu�ƌ���ʒu���w��
//        SetCameraPositionAndTargetAndUpVec(
//            VGet(0.f, 0.f, 0.f),    // �J�������W
//            VGet(0.f, 0.f, 1.f),    // �J�����̌���ʒu
//            VGet(0.f, 1.f, 0.f)     // �Œ�
//        );
//        // �J�����̈ʒu�ƌ�����ݒ�     ��������
//        //SetCameraPositionAndTarget_UpVecY(VGet(0.0f, 1200.0f, -2000.0f), VGet(0.0f, 400.0f, 0.0f));
//
//        // �w�i�̐F�ύX�@�D�F
//        SetBackgroundColor(128, 128, 128);
//
//        // enemy ================================================================================================
//        // I => Run���[�V����(2)
//        if (CheckHitKey(KEY_INPUT_I))
//        {
//            if (enemy_anim_no != eEnemy::Run)
//            {
//                enemy_anim_no = eEnemy::Run;
//                enemy_anim_timer = 0;
//                // �A�j���[�V�����ɂ����鎞�Ԃ��擾
//                anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
//                // �A�j���[�V�������f�^�b�`
//                MV1DetachAnim(enemy_handle, 0);
//                // �A�j���[�V�������A�^�b�`
//                MV1AttachAnim(enemy_handle, enemy_anim_no);
//                // ��O�ړ�
//                if (enemy_anim_no == eEnemy::Run)
//                {
//                    EAngle = 0.f;
//                    EPosition.z -= ENEMY_MOVE_SPEED;
//                }
//            }
//        }
//        else
//        {
//            // �A�j���[�V�������Ȃ��Ƃ��AIdle���[�V����(1)
//            if (enemy_anim_no != eEnemy::Idle)
//            {
//                enemy_anim_no = eEnemy::Idle;
//                enemy_anim_timer = 0;
//                // �A�j���[�V�����ɂ����鎞�Ԃ��擾
//                anim_enemy_time = MV1GetAnimTotalTime(enemy_handle, enemy_anim_no);
//                // �A�j���[�V�������f�^�b�`
//                MV1DetachAnim(enemy_handle, 0);
//                // �A�j���[�V�������A�^�b�`
//                MV1AttachAnim(enemy_handle, enemy_anim_no);
//            }
//        }
//
//        // enemy ================================================================================================
//        enemy_anim_timer += ENEMY_ANIM_F_INCREMENT;
//        // �A�j���[�V�������Ԃ��߂����烊�Z�b�g
//        if (enemy_anim_timer >= anim_enemy_time)
//        {
//            enemy_anim_timer = 0.0f;
//        }
//        // �A�j���[�V�����Z�b�g
//        MV1SetAttachAnimTime(enemy_handle, 0, enemy_anim_timer);
//
//
//        // player ================================================================================================
//
//        // �����Œ���
//
//        //player_anim_timer += PLAYER_ANIM_F_INCREMENT;
//        //// �A�j���[�V�������Ԃ��߂����烊�Z�b�g
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
//        // ��ʂɉf��ʒu��3D���f�����ړ�
//        MV1SetPosition(enemy_handle, EPosition);
//        //MV1SetPosition(player_handle, PPosition);
//
//        // ���f���̑傫���ύX
//        MV1SetScale(enemy_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
//        //MV1SetScale(player_handle, VGet(MODEL_SCALE, MODEL_SCALE, MODEL_SCALE));
//
//        // ���f���̉�]
//        MV1SetRotationXYZ(enemy_handle, VGet(0.f, EAngle * DX_PI_F / 180.f, 0.f));
//        //MV1SetRotationXYZ(player_handle, VGet(0.f, PAngle * DX_PI_F / 180.f, 0.f));
//
//        // �R�c���f���̕`��
//        MV1DrawModel(enemy_handle);
//        //MV1DrawModel(player_handle);
//
//
//        //WaitTimer(FLAME_TIME);
//
//        //ClearDrawScreen();
//
//        // �t���b�v�֐�
//        ScreenFlip();
//
//
//    }
//
//    // DX���C�u�����̌�n��
//    DxLib_End();
//
//    // �\�t�g�̏I��
//    return 0;
//}