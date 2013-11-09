//=============================================================================
// �t�@�C��: model.h
//=============================================================================
// ���f���̐ݒ�E�`��𐧌�
//=============================================================================

#ifndef __MODEL_H__
#define __MODEL_H__

// �w�b�_�t�@�C���̃C���N���[�h
#include "animator.h"
#include <math.h>

// �t���[���ԍ��̍ő�l
int max_frame_count = 500;

//
// �v���~�e�B�u
//

static void drawDumpling()
{
	// ����`��
	glPushMatrix();
	  glTranslated( -5, 0, 0 );
	  glRotated( 90, 0, 1, 0 );
	  drawCylinder( 5, 0.2, 0.2 );
	glPopMatrix();

	// �c�q��`��
	for ( int i=0; i<3; i++ ) {
	  glPushMatrix();
	    glTranslated( 2*i-2, 0, 0 );
	    drawSphere( 1.2 );
	  glPopMatrix();
	}
}

static void drawTriangle(Vec3d A, Vec3d B, Vec3d C)
{
	// �@���x�N�g���̌v�Z
	Vec3d N = ( A-C) ^ ( B-C );

	// �|���S���̕`��
	glBegin( GL_TRIANGLES );
	  glNormal3d( N[0], N[1], N[2] );
	  glVertex3d( A[0], A[1], A[2] );
	  glVertex3d( B[0], B[1], B[2] );
	  glVertex3d( C[0], C[1], C[2] );
	glEnd();
}

static void drawTorus(double R, double r)
{
	// �o�͂��郂�f���̊�{���
	int div_t   = 100;// t�̕�����
	int div_p   = 100;// p�̕�����

	// �ω�������p�����[�^(�}��ϐ�)
	// http://ja.wikipedia.org/wiki/%E3%83%88%E3%83%BC%E3%83%A9%E3%82%B9#.E3.83.89.E3.83.BC.E3.83.8A.E3.83.84.E5.9E.8B
	double t = 0;
	double p = 0;

	// �p�����[�^�̕ψ�
	double dt = 2*M_PI/(div_t);
	double dp = 2*M_PI/(div_p);

	int i,j;

	// ���W

	// ���W�̌v�Z
	Vec3d *ps = new Vec3d[div_t * div_p];
	int k = 0;
	for(i=0, t=0; i < div_t; i++, t+=dt) {
	  for(j=0, p=0; j < div_p; j++, p+=dp) {
	    double x = R * cos(t) + r * cos(p) * cos(t);
	    double y = R * sin(t) + r * cos(p) * sin(t);
	    double z = r * sin(p);
		ps[k++] = Vec3d(x,y,z);
	  }
	}

	// �ʂ̌v�Z
	for(i=0; i < div_t; i++) {
	  for(j=0; j < div_p; j++) {
	    int v0 = i*div_p + j;
	    int v1 = (i+1)%div_t*div_p + j;
	    int v2 = (i+1)%div_t*div_p + (j+1)%div_p;
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_p + (j+1)%div_p;
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

static void drawEllipsoid(double rx, double ry, double rz)
{
	// �o�͂��郂�f���̊�{���
	int div_phi   = 100;// �������̕�����
	int div_theta = 100;// �ƕ����̕�����

	// �ω�������p�����[�^
	// http://ja.wikipedia.org/wiki/%E6%A5%B5%E5%BA%A7%E6%A8%99%E7%B3%BB#.E7.90.83.E5.BA.A7.E6.A8.99_.28Spherical_Polar_Coordinates.29
	double phi = 0;
	double theta = 0;

	// �p�����[�^�̕ψ�
	double dtheta = M_PI/(div_theta);
	double dphi   = 2*M_PI/(div_phi);

	int i,j;

	// ���W�̌v�Z
	Vec3d *ps = new Vec3d[div_phi * (div_theta + 1)];
	int k = 0;
	for(i=0, theta=0; i <= div_theta; i++, theta+=dtheta) {
	  for(j=0, phi=0; j < div_phi; j++, phi+=dphi) {
	    double x = rx * sin(theta) * cos(phi);
	    double y = ry * sin(theta) * sin(phi);
	    double z = rz * cos(theta);
		ps[k++] = Vec3d(x,y,z);
	  }
	}

	// �ʂ̌v�Z
	for(i=0; i < div_theta; i++) {
	  for(j=0; j < div_phi; j++) {
	    int v0 = i*div_phi + j;
	    int v1 = (i+1)*div_phi + j;
	    int v2 = (i+1)*div_phi + (j+1)%div_phi;
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_phi + (j+1)%div_phi;
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

static double curve_cup(double z)
{
	return 2 + cos(M_PI * pow(z * 20.0, 1.7) * 0.01);
}

static void drawRevolution(double (*curve)(double))
{
	int i,j;

	// �o�͂��郂�f���̊�{���
	double height = 1;
	int div_z = 100;
	int div_phi = 100;

	double *r = new double[div_z+1];
	for(i=0; i<=div_z; i++) {
		//r[i] = 1 + cos(PI*i/div_z*2);
		//r[i] = 2 + cos(M_PI*pow(i * 20.0 / div_z, 1.7) * 0.01);
		r[i] = curve((double)i / div_z);
	}

	// �ω�������p�����[�^
	double z = -0.5 * height;
	double phi;

	// �p�����[�^�̕ψ�
	double dz   = height/div_z;
	double dphi = 2*M_PI/div_phi;

	// ���W�̌v�Z
	Vec3d *ps = new Vec3d[div_phi * (div_z + 1)];
	int k = 0;
	for(i=0; i <= div_z; i++, z+=dz) {
	  for(j=0, phi=0; j < div_phi; j++, phi+=dphi) {
	    double x = r[i] * sin(phi);
	    double y = r[i] * cos(phi);
	    //fprintf(fout, "v %f %f %f\n", x, -z, y);
		ps[k++] = Vec3d(x,-z,y);
	  }
	}

	// �ʂ̌v�Z
	for(i=0; i < div_z; i++) {
	  for(j=0; j < div_phi; j++) {
	    int v0 = i*div_phi + j;
	    int v1 = (i+1)*div_phi + j;
	    int v2 = (i+1)*div_phi + (j+1)%div_phi;
	    //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
		drawTriangle(ps[v0], ps[v1], ps[v2]);

	    //v0 = v0;
	    v1 = v2;
	    v2 = i*div_phi + (j+1)%div_phi;
	    //fprintf(fout, "f %d %d %d\n", v0+1, v1+1, v2+1);
		drawTriangle(ps[v0], ps[v1], ps[v2]);
	  }
	}

	delete[] ps;
}

double curve_body(double z)
{
	return abs(sin(z * M_PI * 2)) + pow(sin(z * M_PI), 2);
}

double curve_head(double z)
{
  return 
  pow(z, 0) * -0.00279909391803798 + 
  pow(z, 1) * 5.19175917413233 + 
  pow(z, 2) * -16.8718027194796 + 
  pow(z, 3) * 28.0849625347318 + 
  pow(z, 4) * -16.3769116011162 ;
}

// Model�N���X�̒�`�iModelerView�N���X���p���j
class Model : public ModelerView {
private:
    //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
	//��3�T�ۑ�
    //---------------------------------------------------------------------

	// �t���[���ԍ�
    int frame_count;

    //-------------------------------------------------------------------------
    // ����ϐ�
    //-------------------------------------------------------------------------

        // �`�`�`�ϐ���ǉ��`�`�`
	Vec3d center;
	Vec3d head;

    //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

public:
    // �R���X�g���N�^�i�X�[�p�[�N���X�̃R���X�g���N�^���Ăяo���j
    Model( int x, int y, int w, int h, char* label ) : ModelerView( x, y, w, h, label )
    {
        //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
		//��3�T�ۑ�
        //---------------------------------------------------------------------

        // �t���[���ԍ��̏�����
        frame_count = 0;

        //---------------------------------------------------------------------
        // ������
        //---------------------------------------------------------------------

            // �`�`�`�ϐ����������`�`�`
		head = Vec3d(10, -10, 10);

		//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
    }

    //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
	//��3�T�ۑ�
	//---------------------------------------------------------------------

    // �����A�j���[�V�����̐ݒ�
    void SetAutomaticAnimation()
    {
        //-----------------------------------------------------------------
        // �A�j���[�V����
        //-----------------------------------------------------------------

            // �`�`�`�v���O�������L�q�`�`�`

        //-----------------------------------------------------------------
    }

	// �蓮�A�j���[�V�����̐ݒ�
    void SetManualAnimation()
    {
        //-----------------------------------------------------------------
        // �A�j���[�V����
        //-----------------------------------------------------------------

            // �`�`�`�v���O�������L�q�`�`�`

		//-----------------------------------------------------------------
    }

    //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

    // �`��̑O����
    void BeginPaint()
    {
        // ������������L����
        glEnable( GL_BLEND );
        // �������@�̎w��
        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    }

    // �`��̌㏈��
    void EndPaint()
    {
        // �����������𖳌���
        glDisable( GL_BLEND );
    }

	void drawHead()
	{
		double R = 2.3;
		double dr = M_PI / 4;
		glPushMatrix();

			// ���Ă���
			for(int i = 0; i < 8; ++i)
			{
				glPushMatrix();
					glTranslated(R * sin(i * dr), R * cos(i * dr), 0);
					drawSphere(1);
				glPopMatrix();
			}

			// ���̖{��
			glTranslated(0, 0, -0.3);
			//glScaled(1, 1, 1.1);
			drawSphere(1.6);

			// ��
			glPushMatrix();
				glTranslated(-0.7, 0.3, -1.3);
				drawSphere(0.2);
			glPopMatrix();

			glPushMatrix();
				glTranslated(0.7, 0.3, -1.3);
				drawSphere(0.2);
			glPopMatrix();

			// ��
			glPushMatrix();
				glTranslated(-0.35, -0.6, -1.3);
				drawSphere(0.4);
			glPopMatrix();

			glPushMatrix();
				glTranslated(0.35, -0.6, -1.3);
				drawSphere(0.4);
			glPopMatrix();

			// �@
			glPushMatrix();
				glTranslated(0.0, -0.3, -1.5);
				drawSphere(0.25);
			glPopMatrix();

		glPopMatrix();
	}

	void drawBody()
	{
		glPushMatrix();
			glScaled(1, 5, 1);
			drawRevolution(&curve_body);
		glPopMatrix();
	}

  void drawLionBody()
  {
		glPushMatrix();
			glScaled(2, 5, 2);
      drawSphere(1);
		glPopMatrix();
  }

    // �I�u�W�F�N�g�̕`��
    void draw()
    {
		//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
		//��3�T�ۑ�
		//---------------------------------------------------------------------
        // �����A�j���[�V�����̏���
        if ( IsAutomaticAnimation() && frame_count<max_frame_count ) {
            // �t���[���ԍ��̍X�V
            SetSliderValue( FRAME_CONTROLS, ++frame_count );
            // �����A�j���[�V����
            SetAutomaticAnimation();
        }
        // �蓮�A�j���[�V�����̏���
        else {
            // �t���[���ԍ����擾
            frame_count = (int)GetSliderValue( FRAME_CONTROLS );
            // �蓮�A�j���[�V����
            SetManualAnimation();
        }
		//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

        // �X�[�p�[�N���X�̕`�惁�\�b�h���R�[���i�K�{�j
        ModelerView::draw();

        // �`��J�n
        BeginPaint();

        //---------------------------------------------------------------------
        // �I�u�W�F�N�g��`��
        //---------------------------------------------------------------------

        // �`�`�`�v���O�������L�q�`�`�`

        //drawDumpling();

        //drawTorus(4, 2);
        //drawEllipsoid(3, 4, 5);

        glScaled(1, 5, 1);
        drawRevolution(&curve_cup);

        //drawHead();
        //drawBody();

        //glScaled(1, 3, 1);
        //drawRevolution(&curve_head);
        //

        //drawLionBody();


		//---------------------------------------------------------------------

        // �`��I��
        EndPaint();
    }
};

// __MODEL_H__
#endif
