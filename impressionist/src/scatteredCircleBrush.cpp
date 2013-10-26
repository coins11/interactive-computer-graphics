//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredCircleBrush.h"
#include <math.h>

extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void ScatteredCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int size = pDoc->getSize();
	float alpha = pDoc->getAlpha();
	float Ax,Ay;


	//スライダーつけたあと

	if ( pDoc == NULL ) {
		printf( "ScatteredCircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	SetColorAlpha( source, alpha );
	for(int i=0; i<10; i++){
		Ax=target.x-size/2+rand()%size;
		Ay=target.y-size/2+rand()%size;
		DrawCircle( Ax, Ay );
	}
}

void ScatteredCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

void ScatteredCircleBrush::DrawCircle ( float x, float y )
{
	float Ax, Ay;
	int div=36;
	float radius=1.0;
	const double PI = 3.141592653589793238462;

	glBegin(GL_POLYGON);
	for (int i = 0; i < div; i++) {
		Ax = x + radius*cos(2*PI*i/div);
		Ay = y + radius*sin(2*PI*i/div);
		glVertex2f(Ax,Ay);
	}
	glEnd();
}
