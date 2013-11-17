#include "controller.h"
#include "model.h"

void SetController( ModelerControl* controls )
{
	// フレーム番号の制御用スライダ
    controls[FRAME_CONTROLS] = ModelerControl( "Frame Number", 0, (float)max_frame_count, 1, 0 );

    // 〜〜〜スライダを追加〜〜〜
	controls[X_POSITION] = ModelerControl( "X-Position", -20.0f, 20.0f, 0.1f, 0.0f );
}
