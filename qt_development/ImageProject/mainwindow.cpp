#include <QTextStream>
#include <QFileDialog>

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

void charArrToQImage(unsigned char *data, QImage *image, int widgt_map, int height_map){
    for(int x = 0; x < widgt_map; x++){
        int r = 0;
        for(int y = 0; y < height_map; y++){
            int st = (y*widgt_map + x)*3;

            image->setPixelColor((x), height_map - y- 1, QColor(data[ st],data[st +1],data[st +2]));
            //if (x == 100 &&y == 100)
            //    QTextStream(stdout) << x << " " << y << " "<< st << endl;
            r++;

        }
    }
}

void MainWindow::on_read_pressed()
{

    QString filename = QFileDialog::getOpenFileName(this, tr("choose"), "/Users/wzuniga/Maestria/Semestre II/Imagenes/PhotoshopProject_UCSP/img", tr("Images (*.bmp)"));

    charMap = ImgLoad(filename.toStdString().c_str(), &height_map, &widgt_map);

    if(charMap != nullptr){
        QImage image(widgt_map, height_map, QImage::Format_RGB888);

        charArrToQImage(charMap, &image, widgt_map, height_map);
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
        QTextStream(stdout) << "Filter: " << filter << endl;
        char tmp = 0;
        int H = height_map;
        int W = widgt_map;
        QTextStream(stdout) << "H: " << H << " W: "<< W << endl;
        for(long i = 0; i < H; i++){
            QTextStream(stdout) << "i: " << i << endl;
            for(long e = 0; e < W; e++){
                QTextStream(stdout) << "e: " << e << endl;
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
                //QTextStream(stdout) << "Start Bucle " << (H * e + i ) * 3  << endl;
                combMat[ (H * e + i ) * 3     ] = sum_red   ;
                //QTextStream(stdout) << " Bucle " << 1  << endl;
                combMat[((H * e + i ) * 3) + 1] = sum_green ;
                //QTextStream(stdout) << " Bucle " << 2 << endl;
                combMat[((H * e + i ) * 3) + 2] = sum_blue  ;
                //QTextStream(stdout) << "Fin Bucle " << e << endl;
            }
            tmp++;
        }
        QTextStream(stdout) << "End Convolution" << endl;
        QImage image(widgt_map, height_map, QImage::Format_RGB888);
        charArrToQImage(combMat, &image, widgt_map, height_map);

        pixelMap = QPixmap::fromImage(image);

        ui->imgConvo->setPixmap(pixelMap);
        //image->data = combMat;
    }
}
