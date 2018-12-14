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

void applyCombolutionIMG(Image *image, unsigned char filter);

void applyRGB2HSV(Image *image);

void rgb2hsv_pixel(unsigned char &src_r, unsigned char &src_g, unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v);

