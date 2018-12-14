#include <stdio.h> 
#include <stdlib.h>

Image * rgb2Gray(Image *image){
    Image * gray;
    gray = (Image *) malloc(sizeof(Image));
    int size = image->sizeX * image->sizeY;
    gray->sizeX = image->sizeX;
    gray->sizeY = image->sizeY;
    gray->data = (unsigned char *) malloc(size);

    for(int i = 0, e = 0; i < size*3; i+=3, e++){
        gray->data[e] = image->data[i]/3 + image->data[i+1]/7 + image->data[i+2]/2;
    }
    return gray;
}