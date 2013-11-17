#include "model.h"
#include "animator.h"
#include "controller.h"

int max_frame_count = 500;

Model::Model( int x, int y, int w, int h, char* label ) : ModelerView( x, y, w, h, label )
{
	//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
	//第3週課題
	//---------------------------------------------------------------------

	// フレーム番号の初期化
	frame_count = 0;

	//---------------------------------------------------------------------
	// 初期化
	//---------------------------------------------------------------------

	// 〜〜〜変数を初期化〜〜〜


	//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
}

// 自動アニメーションの設定
void Model::SetAutomaticAnimation()
{
	//-----------------------------------------------------------------
	// アニメーション
	//-----------------------------------------------------------------

	// 〜〜〜プログラムを記述〜〜〜

	//-----------------------------------------------------------------
}

// 手動アニメーションの設定
void Model::SetManualAnimation()
{
	//-----------------------------------------------------------------
	// アニメーション
	//-----------------------------------------------------------------

	// 〜〜〜プログラムを記述〜〜〜

	//-----------------------------------------------------------------
}

//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜


// 描画の前処理
void Model::BeginPaint()
{
	// 半透明処理を有効化
	glEnable( GL_BLEND );
	// 混合方法の指定
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

// 描画の後処理
void Model::EndPaint()
{
	// 半透明処理を無効化
	glDisable( GL_BLEND );
}


// オブジェクトの描画
void Model::draw()
{
	//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜
	//第3週課題
	//---------------------------------------------------------------------
	// 自動アニメーションの処理
	if ( IsAutomaticAnimation() && frame_count<max_frame_count ) {
		// フレーム番号の更新
		SetSliderValue( FRAME_CONTROLS, ++frame_count );
		// 自動アニメーション
		SetAutomaticAnimation();
	}
	// 手動アニメーションの処理
	else {
		// フレーム番号を取得
		frame_count = (int)GetSliderValue( FRAME_CONTROLS );
		// 手動アニメーション
		SetManualAnimation();            
	}
	//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜


	// スーパークラスの描画メソッドをコール（必須）
	ModelerView::draw();


	// 描画開始
	BeginPaint();

	//---------------------------------------------------------------------
	// オブジェクトを描画
	//---------------------------------------------------------------------

	//drawSomeCylinder();
	setDiffuseColor( 0, 1, 0 );
	setAmbientColor( 0, 1, 0 );
	setSpecularColor( 1, 0, 0 );
	glPushMatrix();
	glTranslated( (double)GetSliderValue(X_POSITION),0.,0. );
	drawCone(10, 10, 100, 10);
	glPopMatrix();
	// 〜〜〜プログラムを記述〜〜

	//---------------------------------------------------------------------

	// 描画終了
	EndPaint();
}
