#define min_f(a, b, c)  (fminf(a, fminf(b, c)))
#define max_f(a, b, c)  (fmaxf(a, fmaxf(b, c)))


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