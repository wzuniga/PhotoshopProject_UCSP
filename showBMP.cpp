/*
 *  showBMP.c
 *
 *  Nina Amenta, May 2004
 *  No copyright - free to good home!
 *
 */

//
#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>
#ifndef readBMP
    #include "readBMP.h"
    #define readBMP
#endif

#include "lib/utils.cpp"
#include "convolution/convolution.cpp"
#include "colorspace/colorTransform.cpp"
#include "fourier/dft.cpp"

/* ascii code for the escape key */
#define ESCAPE 27

int window;  // id of glut window
Image *image; // data structure for image
int n,m; // width and height
int typeImage = GL_RGB;

void getImage() {
    
    // allocate space for image data structure
    image = (Image *) malloc(sizeof(Image));
    if (image == NULL) {
		printf("Error allocating space for image");
		exit(0);
    }

	char path[] = "./img/cow.bmp";

    if (!ImageLoad(path, image)) {
		exit(1);
    }
	
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);

	//glDrawPixels(image->sizeX,image->sizeY,GL_LUMINANCE, GL_UNSIGNED_BYTE, image->data);
	glDrawPixels(image->sizeX, image->sizeY, typeImage, GL_UNSIGNED_BYTE, image->data);
	/* Put additional OpenGL drawing commands here */

	glFlush();
}


void myreshape(int h, int w)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,h,w);
}

int main(int argc, char **argv)
{
	
	getImage();

	Image * gray =  rgb2Gray(image);
	//image = gray;
	//typeImage = GL_LUMINANCE;

	n = image->sizeX;
	m = image->sizeY;
	
	unsigned char filter = 3;
    //printf("Aplicando Combolucion %i \n", filter);
    //applyCombolutionIMG(image, filter);
    //applyRGB2HSV(image);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize(n, m);
	glutInitWindowPosition(0,0);
	glutCreateWindow("image");
	glutReshapeFunc(myreshape);
	glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0); 
	glutMainLoop();
	return(0);
}
