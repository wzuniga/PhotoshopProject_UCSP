#ifndef readBMP
    #include "readBMP.h"
    #include <cmath>
    #include <math.h> 
    #define readBMP
#endif

void applyDFT(Image *imagen){
    int size = imagen->sizeX * imagen->sizeY / 2;
    for(int k = 0; k < imagen->sizeX; k++){
        for(int l = 0; l < imagen->sizeY; l++){

            for(int i = 0; i < imagen->sizeX; i++){
                for(int j = 0; j < imagen->sizeY; j++){
                
                    double temp = imagen->data[(imagen->sizeX * i + j )] * cos( 180 * size * (k*i+l*j) );
                }
            }
        }
    }
    return;
}