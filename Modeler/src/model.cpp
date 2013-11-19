#include "model.h"
#include "animator.h"
#include "controller.h"
#include <cmath>
#include <iostream>

int max_frame_count = 500;

Model::Model( int x, int y, int w, int h, char* label ) : ModelerView( x, y, w, h, label )
{
	frame_count = 0;
	angle = std::make_tuple(0, 0, 0, 0, 0);
}

void Model::SetAutomaticAnimation()
{
	float a = frame_count * 90 / max_frame_count;

	angle = std::make_tuple(a, a, a, a, a);
}

void Model::SetManualAnimation()
{
	angle = std::make_tuple(
			GetSliderValue(FOLD_ANGLE1),
			GetSliderValue(FOLD_ANGLE2),
			GetSliderValue(FOLD_ANGLE3),
			GetSliderValue(FOLD_ANGLE4),
			GetSliderValue(FOLD_ANGLE5));
}

void Model::BeginPaint()
{
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void Model::EndPaint()
{
	glDisable( GL_BLEND );
}

void Model::draw()
{
	if ( IsAutomaticAnimation() && frame_count<max_frame_count ) {
		SetSliderValue( FRAME_CONTROLS, ++frame_count );
		SetAutomaticAnimation();
	}
	else {
		frame_count = (int)GetSliderValue( FRAME_CONTROLS );
		SetManualAnimation(); 
	}

	ModelerView::draw();

	BeginPaint();

	setDiffuseColor( 0, 1, 0 );
	setAmbientColor( 0, 1, 0 );
	setSpecularColor( 1, 0, 0 );
	drawFoldingBox(3, angle);

	EndPaint();
}
