#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "singleLineBrush.h"

extern float frand();

SingleLineBrush::SingleLineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void SingleLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();
	

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize( (float)size );

	BrushMove( source, target );
}

void SingleLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	//スライダーつけたあと

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	//SetColorAlpha( source, alpha );
	SetColor( source );
	glBegin(GL_LINE_STRIP);
	glVertex2d( target.x - 10, target.y );
	glVertex2d( target.x + 10, target.y );
	glEnd();
}

void SingleLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
	glDisable(GL_BLEND);

}

