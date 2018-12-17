#include <QTextStream>
#include <QFileDialog>
# include <math.h>
# include <iostream>
# include <fstream>
# include <string.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "stdio.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    connect(ui->readBMP, SIGNAL (pressed()),this, SLOT (on_read_pressed()));
    connect(ui->convolution, SIGNAL (pressed()),this, SLOT (on_convolution_pressed()));
    connect(ui->polinomial, SIGNAL (pressed()),this, SLOT (on_polinomial_pressed()));

    //ui->graphicView->setMatrix(pix.);
}

MainWindow::~MainWindow()
{
    delete ui;
}

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

unsigned char* ImgLoad(const char *filename, int *W, int *H) {
    FILE *file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;             // number of bits per pixel (must be 24)
    unsigned char temp;

    if ((file = fopen(filename, "rb"))==NULL)
    {
        printf("File Not Found : %s\n",filename);
        return nullptr;
    }

    fseek(file, 18, SEEK_CUR);

    int sizeX = endianReadInt(file);
    int sizeY = endianReadInt(file);

    size = sizeX * sizeY * 3;

    if (!(planes=endianReadShort(file))) {
        printf("Error lectura de %s.\n", filename);
        return nullptr;
    }
    if (planes != 1) {
        printf("Planes de %s no es 1: %u\n", filename, planes);
        return nullptr;
    }

    if (!(bpp = endianReadShort(file))) {
        printf("Error leyendo bpp de %s.\n", filename);
        return nullptr;
    }
    if (bpp != 24) {
        printf("Bpp de %s no es 24: %u\n", filename, bpp);
        return nullptr;
    }

    fseek(file, 24, SEEK_CUR);

    unsigned char* data = (unsigned char *) malloc(size);
    if (data == NULL) {
        printf("Error de creado de memoria: ");
        return nullptr;
    }

    if ((i = fread(data, size, 1, file)) != 1) {
        printf("Error de lectura de: %s.\n", filename);
        return nullptr;
    }

    for (i=0;i<size;i+=3) {
        temp = data[i];
        data[i] = data[i+2];
        data[i+2] = temp;
    }

    *H = sizeX;
    *W = sizeY;

    return data;
}

void getCombMatrixMean(int* matrix, int filter){
    int init = (filter - 1) / -2;
    for(int i=0; i < filter; i++)
        matrix[i] = init++;
}

void charArrToQImage(unsigned char *data, QImage *image, int widgt_map, int height_map, int type){
    if(type == QImage::Format_RGB888){
    for(int x = 0; x < widgt_map; x++){
        int r = 0;
        for(int y = 0; y < height_map; y++){
            int st = (y*widgt_map + x)*3;

            image->setPixelColor((x), height_map - y- 1, QColor(data[ st],data[st +1],data[st +2]));
            r++;

        }
    }
    }
    else if (QImage::Format_Grayscale8){
        for(int x = 0; x < widgt_map; x++){
            for(int y = 0; y < height_map; y++){
                int st = (y*widgt_map + x);

                image->setPixelColor((x), height_map - y- 1, QColor(data[ st],data[st ],data[st ]));
            }
        }
    }
}

void MainWindow::on_read_pressed()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "/Users/wzuniga/Maestria/Semestre II/Imagenes/PhotoshopProject_UCSP/img", tr("Images (*.bmp)"));

    charMap = ImgLoad(filename.toStdString().c_str(), &height_map, &widgt_map);

    if(charMap != nullptr){
        QImage image(widgt_map, height_map, QImage::Format_RGB888);

        charArrToQImage(charMap, &image, widgt_map, height_map, QImage::Format_RGB888);
        pixelMap = QPixmap::fromImage(image);

        ui->label->setPixmap(pixelMap);

    }else{
        QTextStream(stdout) << "Error de lectura bpp:" << endl;
    }

}


void MainWindow::on_convolution_pressed()
{
    if(charMap != nullptr){
        unsigned char* combMat = (unsigned char *) malloc(widgt_map * height_map * 3);
        int filter = ui->filterSize->text().toInt();
        int matrix[filter];
        getCombMatrixMean(matrix, filter);
        char tmp = 0;
        int H = height_map;
        int W = widgt_map;
        for(long i = 0; i < H; i++){
            for(long e = 0; e < W; e++){
                unsigned char sum_red = 0, sum_green = 0, sum_blue = 0;
                for(int a=0; a < filter; a++){
                    for(int b=0; b < filter; b++){
                        int x = i + matrix[a];
                        int y = e + matrix[b];
                        if(!(x < 0) && !(y < 0) && !(y > W) && !(x > H)){
                            int st = (H * y + x ) * 3;
                            unsigned char ttl = filter*filter;
                            sum_red += charMap[st] / ttl;
                            sum_green += charMap[st + 1] / ttl;
                            sum_blue += charMap[st + 2] / ttl;
                        }
                    }
                }
                combMat[ (H * e + i ) * 3     ] = sum_red   ;
                combMat[((H * e + i ) * 3) + 1] = sum_green ;
                combMat[((H * e + i ) * 3) + 2] = sum_blue  ;
            }
            tmp++;
        }

        QImage image(widgt_map, height_map, QImage::Format_RGB888);
        charArrToQImage(combMat, &image, widgt_map, height_map, QImage::Format_RGB888);

        pixelMap = QPixmap::fromImage(image);

        ui->imgConvo->setPixmap(pixelMap);
        ui->outputAlg->setText("Convolution");
    }
}

double Power2(unsigned char value, int p){
    if(p == 0 ) return 1.0;
    return (double)value*Power2(value, p - 1);
}

void MainWindow::on_polinomial_pressed()
{
    int size = height_map*widgt_map*3;
    unsigned char * data = new unsigned char[size];
    for(int i = 0; i < size; i++){
        double temp = 0;
        temp += ui->spinBox_1->text().toInt() * Power2(charMap[i], 2);
        temp += ui->spinBox_2->text().toInt() * Power2(charMap[i], 1);
        temp += ui->spinBox_3->text().toInt() * Power2(charMap[i], 0);
        int response = (int) temp;
        data[i] = (unsigned char)(response > 255 ? 255 : (response < 0 ? 0:response));
    }

    QImage image(widgt_map, height_map, QImage::Format_RGB888);
    charArrToQImage(data, &image, widgt_map, height_map, QImage::Format_RGB888);
    pixelMap = QPixmap::fromImage(image);

    ui->imgConvo->setPixmap(pixelMap);
    ui->outputAlg->setText("Polinomial Filter");
}

void MainWindow::on_dft_pressed()
{

    int szGray = widgt_map*height_map;

    double Rp = 0.2;
    double Gp = 0.7;
    double Bp = 0.1;

    unsigned char * grayscale = new unsigned char[szGray];
    for(int i = 0, k = 0; i < szGray*3; i+=3, k++){
        double val= Rp*(double)charMap[i] + Gp*(double)charMap[i+1] + Bp*(double)charMap[i+2];
        grayscale[k] = (unsigned char)val;
    }

    double *PkbReal = new double[widgt_map*height_map];
    double *PkbIm = new double[widgt_map*height_map];
    int k, b, a, l;
#pragma omp parallel for num_threads(4) shared(PkbReal, PkbIm) collapse(2) private(k, b, a)
    for(k = 0; k < height_map; k++){
        for(b = 0; b < widgt_map; b++){
            double sumReal = 0.0;
            double sumIm = 0.0;
            for(a = 0; a < height_map; a++){
                double theta = -2.0*3.1416*k*a/height_map;
                sumReal += (double)grayscale[b + widgt_map*a]*cosf(theta);
                sumIm += (double)grayscale[b + widgt_map*a]*sinf(theta);
            }
            PkbReal[b + widgt_map*k] = sumReal/(double)height_map;
            PkbIm[b + widgt_map*k] = sumIm/(double)height_map;
        }
    }
    unsigned char * real = new unsigned char[widgt_map*height_map];
#pragma omp parallel for num_threads(4) shared(Dft, PkbReal, PkbIm) collapse(2) private(k, l, b)
    for(k = 0; k < height_map; k++){
        for(l = 0; l < widgt_map; l++){
            double sumReal = 0.0;
            double sumIm = 0.0;
            for(b = 0; b < widgt_map; b++){
                double theta = -2.0*3.1416*l*b/widgt_map;
                sumReal += (double)PkbReal[b + k*widgt_map]*cosf(theta) - (double)PkbIm[b+k*widgt_map]*sinf(theta);
                sumIm += (double)PkbReal[b + k*widgt_map]*sinf(theta) + (double)PkbIm[b+k*widgt_map]*cos(theta);
            }
            sumReal = sumReal/widgt_map;
            sumIm += sumIm/widgt_map;
            sumReal = sqrtf(sumReal*sumReal + sumIm*sumIm);
            real[k*widgt_map + l] = (unsigned char) sumReal;
        }
    }

    int hmid = height_map/2, wmid = widgt_map/2;
#pragma omp parallel for num_trheads(4) collapse(2) private(hmid, wmid)
    for(int i = 0; i < wmid; i++){
        for(int j = 0; j < hmid; j++){
            unsigned char tmp = real[i + j*widgt_map];
            real[i + j*widgt_map] = real[widgt_map - wmid + i + (hmid+j)*widgt_map];
            real[widgt_map - wmid + i + (hmid+j)*widgt_map] = tmp;
        }
    }

#pragma omp parallel for num_trheads(4) collapse(2) private(hmid, wmid)
    for(int i = widgt_map - wmid; i < widgt_map; i++){
        for(int j = 0; j < hmid; j++){
            unsigned char tmp = real[i + j*widgt_map];
            real[i + j*widgt_map] = real[i - wmid + (hmid+j)*widgt_map];
            real[i - wmid + (hmid+j)*widgt_map] = tmp;
        }
    }


    QImage image(widgt_map, height_map, QImage::Format_Grayscale8);
    charArrToQImage(real, &image, widgt_map, height_map, QImage::Format_Grayscale8);
    pixelMap = QPixmap::fromImage(image);

    ui->imgConvo->setPixmap(pixelMap);
    ui->outputAlg->setText("Discrete Fourier Transform");
}
