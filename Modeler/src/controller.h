//=============================================================================
// ファイル: controller.h
//=============================================================================
// スライダコントローラの設定
//=============================================================================

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

// ヘッダファイルのインクルード
#include "modelerapp.h"

// コントローラ識別用の列挙子
enum CONTROLLERS {

	FRAME_CONTROLS,   // フレームコントローラ（変更しないこと)
	X_POSITION,
    // 〜〜〜列挙子を追加〜〜〜

    NUM_CONTROLS,   // コントローラ数（必ず末尾に追加）
};

extern void SetController( ModelerControl* controls );

// __CONTROLLER_H__
#endif
