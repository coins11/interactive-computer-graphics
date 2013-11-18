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
	FRAME_CONTROLS,
	X_POSITION,
	FOLD_ANGLE,

    NUM_CONTROLS,   // コントローラ数（必ず末尾に追加）
};

extern void SetController( ModelerControl* controls );

// __CONTROLLER_H__
#endif
