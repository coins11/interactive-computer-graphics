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
	float a = GetSliderValue(FOLD_ANGLE);
	angle = std::make_tuple(a, a, a, a, a);
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

	//drawSomeCylinder();
	setDiffuseColor( 0, 1, 0 );
	setAmbientColor( 0, 1, 0 );
	setSpecularColor( 1, 0, 0 );

	//drawFoldingBox(3, angle);
	//drawTorus(5, 10, 60, 100);
	drawIcosahedron();

	EndPaint();
}
