/*
 *  readBMP.h
 *
 *  Created by Nina Amenta on Sun May 23 2004.
 *  Free to good home!
 *
 */


/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    unsigned char *data;
};
typedef struct Image Image;

/* Function that reads in the image; first param is filename, second is image struct */
/* As side effect, sets w and h */
int ImageLoad(char* filename, Image* image);

typedef void (*ButtonCallback)();

struct Button 
{
	int   x;							/* top left x coord of the button */
	int   y;							/* top left y coord of the button */
	int   w;							/* the width of the button */
	int   h;							/* the height of the button */
	int	  state;						/* the state, 1 if pressed, 0 otherwise */
	int	  highlighted;					/* is the mouse cursor over the control? */
	char* label;						/* the text label of the button */
	ButtonCallback callbackFunction;	/* A pointer to a function to call if the button is pressed */
};
typedef struct Button Button;



void applyCombolutionIMG(Image *image, unsigned char filter);

void applyRGB2HSV(Image *image);

void rgb2hsv_pixel(unsigned char &src_r, unsigned char &src_g, unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v);