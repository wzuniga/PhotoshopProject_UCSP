/*
 *  readBMP.c
 *
 *  Created by Nina Amenta on Sun May 23 2004.
 *  Free to good home!
 *
 */

#include <stdio.h>      // Header file for standard file i/o.
#include <stdlib.h>     // Header file for malloc/free.
#include <math.h>
#include "readBMP.h"

#define btoa(x) ((x)?"true":"false")

#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))
/* Simple BMP reading code, should be adaptable to many
systems. Originally from Windows, ported to Linux, now works on my Mac
OS system.

NOTE!! only reads 24-bit RGB, single plane, uncompressed, unencoded
BMP, not all BMPs. BMPs saved by xv should be fine. */

//
// This code was created by Jeff Molofee '99 
//  (www.demonews.com/hosted/nehe)
// Ported to Linux/GLUT by Richard Campbell '99
// Code and comments for adaptation to big endian/little endian systems 
// Nina Amenta '04
//

/* Reads a long 32 bit integer; comment out one or the other shifting line below, 
whichever makes your system work right. */
unsigned int endianReadInt(FILE* file) {
    unsigned char  b[4]; 
    unsigned int i;

    if ( fread( b, 1, 4, file) < 4 )
        return 0;
    /* LITTLE VS BIG ENDIAN LINES - comment out one or the other */
    i = (b[3]<<24) | (b[2]<<16) | (b[1]<<8) | b[0]; // big endian
    //i = (b[0]<<24) | (b[1]<<16) | (b[2]<<8) | b[3]; // little endian
    return i;
}

/* Reads a 16 bit integer; comment out one or the other shifting line below, 
whichever makes your system work right. */
unsigned short int endianReadShort(FILE* file) {
    unsigned char  b[2]; 
    unsigned short s;

    if ( fread( b, 1, 2, file) < 2 )
        return 0;
    /* LITTLE VS BIG ENDIAN LINES - comment out one or the other */
    s = (b[1]<<8) | b[0]; // big endian
    //s = (b[0]<<8) | b[1]; // little endian
    return s;
}


// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.  
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size;                 // size of the image in bytes.
    unsigned long i;                    // standard counter.
    unsigned short int planes;          // number of planes in image (must be 1) 
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    unsigned char temp;                          // temporary color storage for bgr-rgb conversion.

    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL)
    {
	    printf("File Not Found : %s\n",filename);
	    return 0;
    }
    
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);

    // read the width
    //printf("Endian INT WIDTH: %d \n", endianReadInt(file));
    //printf("Endian INT Height: %d \n", endianReadInt(file));
    if (!(image->sizeX = endianReadInt(file))) {
	    printf("Error reading width from %s.\n", filename);
	    return 0;
    }
    printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height 
    if (!(image->sizeY = endianReadInt(file))) {
	    printf("Error reading height from %s.\n", filename);
	    return 0;
    }
    printf("Height of %s: %lu\n", filename, image->sizeY);
    

    
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image->sizeX * image->sizeY * 3;

    // read the planes
    if (!(planes=endianReadShort(file))) {
	    printf("Error reading planes from %s.\n", filename);
	    return 0;
    }
    if (planes != 1) {
	    printf("Planes from %s is not 1: %u\n", filename, planes);
	    return 0;
    }

    // read the bits per pixel
    if (!(bpp = endianReadShort(file))) {
	    printf("Error reading bpp from %s.\n", filename);
	    return 0;
    }
    if (bpp != 24) {
	    printf("Bpp from %s is not 24: %u\n", filename, bpp);
	    return 0;
    }
	
    // seek past the rest of the bitmap header.
    fseek(file, 24, SEEK_CUR);

    // read the data. 
    image->data = (unsigned char *) malloc(size);
    if (image->data == NULL) {
	    printf("Error allocating memory for color-corrected image data");
	    return 0;	
    }

    if ((i = fread(image->data, size, 1, file)) != 1) {
	    printf("Error reading image data from %s.\n", filename);
	    return 0;
    }

    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
	    temp = image->data[i];
	    image->data[i] = image->data[i+2];
	    image->data[i+2] = temp;
    }
    
    unsigned char filter = 3;
    printf("Aplicando Combolucion %i \n", filter);
    //applyCombolutionIMG(image, filter);
    applyRGB2HSV(image);
    // we're done.
    return 1;
}


/*
Self Operation
*/
void getCombMatrix(int* matrix, int filter){
    int init = (filter - 1) / -2;
    for(int i=0; i < filter; i++){
        matrix[i] = init++;
        printf(" %d ", matrix[i]);
    }
}

void applyCombolutionIMG(Image *image, unsigned char filter){
    unsigned char* combMat = (unsigned char *) malloc(image->sizeX * image->sizeY * 3);
    int matrix[filter];
    getCombMatrix(matrix, filter);
    char tmp = 0;
    for(long i = 0; i <= image->sizeX; i++){
        for(long e = 0; e <= image->sizeY; e++){
            unsigned char sum_red = 0, sum_green = 0, sum_blue = 0;
            for(int a=0; a < filter; a++){
                for(int b=0; b < filter; b++){
                    int x = i + matrix[a];
                    int y = e + matrix[b];
                    if(!(x < 0) && !(y < 0) && !(y >= image->sizeY+2) && !(x >= image->sizeX+2)){
                        int st = (image->sizeX * y + x ) * 3;
                        unsigned char ttl = filter*filter;
                        sum_red += image->data[st] / ttl;
                        sum_green += image->data[st + 1] / ttl;
                        sum_blue += image->data[st + 2] / ttl;
                        
                        if( i == 100 && e == 100)
                            printf("i= %d, e=%d, x=%d, y=%d val=%d vald=%d st=%d\n",i,e,x,y, image->data[st], image->data[st]/ttl, st);
                    }
                }
            }

            combMat[ (image->sizeX * e + i ) * 3     ] = sum_red   ;
            combMat[((image->sizeX * e + i ) * 3) + 1] = sum_green ;
            combMat[((image->sizeX * e + i ) * 3) + 2] = sum_blue  ;
            if( i == 100 && e == 100)
                printf("S = %d\n", image->data[((image->sizeY * i + e ) * 3) + 1]);
            if( i == 100 && e == 100)
                printf("S = %d\n", combMat[((image->sizeY * i + e ) * 3) + 1]);
        }
        tmp++;
    }
    image->data = combMat;
}

void applyRGB2HSV(Image *image){
    unsigned char* combMat = (unsigned char *) malloc(image->sizeX * image->sizeY * 3);
    unsigned char* img = image->data;
    for(long i = 0; i <= image->sizeX * image->sizeY * 3; i+=3){
        rgb2hsv_pixel(img[i], img[i+1], img[i+2], combMat[i], combMat[i+1], combMat[i+2]);
        //printf("%d %d %d", combMat[i], combMat[i+1], combMat[i+2]);
    }
    image->data = combMat;
}

void rgb2hsv_pixel(unsigned char &src_r, unsigned char &src_g, unsigned char &src_b, unsigned char &dst_h, unsigned char &dst_s, unsigned char &dst_v)
{
    float r = src_r / 255.0f;
    float g = src_g / 255.0f;
    float b = src_b / 255.0f;

    float h, s, v; // h:0-360.0, s:0.0-1.0, v:0.0-1.0

    float max = max_f(r, g, b);
    float min = min_f(r, g, b);

    v = max;

    if (max == 0.0f) {
        s = 0;
        h = 0;
    }
    else if (max - min == 0.0f) {
        s = 0;
        h = 0;
    }
    else {
        s = (max - min) / max;

        if (max == r) {
            h = 60 * ((g - b) / (max - min)) + 0;
        }
        else if (max == g) {
            h = 60 * ((b - r) / (max - min)) + 120;
        }
        else {
            h = 60 * ((r - g) / (max - min)) + 240;
        }
    }

    if (h < 0) h += 360.0f;

    dst_h = (unsigned char)(h / 2);   // dst_h : 0-180
    dst_s = (unsigned char)(s * 255); // dst_s : 0-255
    dst_v = (unsigned char)(v * 255); // dst_v : 0-255
}
