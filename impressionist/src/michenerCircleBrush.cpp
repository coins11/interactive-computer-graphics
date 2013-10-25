//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "michenerCircleBrush.h"

extern float frand();

MichenerCircleBrush::MichenerCircleBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void MichenerCircleBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void MichenerCircleBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;
	int size = pDoc->getSize();

	//スライダーつけたあと

	if ( pDoc == NULL ) {
		printf( "MichenerCircleBrush::BrushMove  document is NULL\n" );
		return;
	}

	//SetColorAlpha( source, alpha );
	SetColor( source );
	glBegin( GL_POINTS );
	Circle(target.x, target.y, size / 2);
	glEnd();
}

void MichenerCircleBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

void MichenerCircleBrush::Swap( int* x, int* y )
{
	int t;

	t = *x;
	*x = *y;
	*y = t;
}

void MichenerCircleBrush::Plot8( int x, int y, int x0, int y0 )
{
	for (int i = 0; i < 2; i++) {
		glVertex2i(x  + x0,  y + y0);
		glVertex2i(x  + x0, -y + y0);
		glVertex2i(-x + x0,  y + y0);
		glVertex2i(-x + x0, -y + y0);
		Swap(&x, &y);
	}
}

void MichenerCircleBrush::Circle( int x0, int y0, int r )
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;

	Plot8(x, y, x0, y0);

	for (; x < y; x++) {
		if (d < 0) {
			d += 4 * x + 6;
		} else {
			d += 4 * (x - y) + 10;
			y--;
		}

		Plot8(x, y, x0, y0);
	}
}
