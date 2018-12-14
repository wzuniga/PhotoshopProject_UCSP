void getCombMatrix(int* matrix, int filter){
    int init = (filter - 1) / -2;
    for(int i=0; i < filter; i++)
        matrix[i] = init++;
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
                    }
                }
            }

            combMat[ (image->sizeX * e + i ) * 3     ] = sum_red   ;
            combMat[((image->sizeX * e + i ) * 3) + 1] = sum_green ;
            combMat[((image->sizeX * e + i ) * 3) + 2] = sum_blue  ;
        }
        tmp++;
    }
    image->data = combMat;
}
