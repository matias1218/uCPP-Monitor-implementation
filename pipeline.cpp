#include <uC++.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
using namespace std;

typedef struct bmpFileHeader
{
  /* 2 bytes de identificación */
  uint32_t size;        /* Tamaño del archivo */
  uint16_t resv1;       /* Reservado */
  uint16_t resv2;       /* Reservado */
  uint32_t offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader
{
  uint32_t headersize;      /* Tamaño de la cabecera */
  uint32_t width;       /* Ancho */
  uint32_t height;      /* Alto */
  uint16_t planes;          /* Planos de color (Siempre 1) */
  uint16_t bpp;             /* bits por pixel */
  uint32_t compress;        /* compresión */
  uint32_t imgsize;     /* tamaño de los datos de imagen */
  uint32_t bpmx;        /* Resolución X en bits por metro */
  uint32_t bpmy;        /* Resolución Y en bits por metro */
  uint32_t colors;      /* colors used en la paleta */
  uint32_t imxtcolors;      /* Colores importantes. 0 si son todos */
  uint32_t v1;      /* Colores importantes. 0 si son todos */
  uint32_t v2;      /* Colores importantes. 0 si son todos */
  uint32_t v3;      /* Colores importantes. 0 si son todos */
  uint32_t v4;      /* Colores importantes. 0 si son todos */
  uint32_t v5;      /* Colores importantes. 0 si son todos */
  uint32_t v6;      /* Colores importantes. 0 si son todos */
  uint32_t v7;      /* Colores importantes. 0 si son todos */
  uint32_t v8;      /* Colores importantes. 0 si son todos */
  uint32_t v9;      /* Colores importantes. 0 si son todos */
  uint32_t v10;      /* Colores importantes. 0 si son todos */
  uint32_t v11;      /* Colores importantes. 0 si son todos */
  uint32_t v12;      /* Colores importantes. 0 si son todos */
  uint32_t v13;      /* Colores importantes. 0 si son todos */
  uint32_t v14;      /* Colores importantes. 0 si son todos */
  uint32_t v15;      /* Colores importantes. 0 si son todos */
  uint32_t v16;      /* Colores importantes. 0 si son todos */
  uint32_t v17;      /* Colores importantes. 0 si son todos */
  uint32_t v18;      /* Colores importantes. 0 si son todos */
  uint32_t v19;      /* Colores importantes. 0 si son todos */
  uint32_t v20;      /* Colores importantes. 0 si son todos */
  uint32_t v21;      /* Colores importantes. 0 si son todos */     
} bmpInfoHeader;





unsigned char *readRGB(FILE* file, bmpInfoHeader* bInfoHeader,bmpFileHeader* header){
    
    //bmpFileHeader header;     /* cabecera */
    unsigned char *imgdata;   /* datos de imagen */
    uint16_t type;        /* 2 bytes identificativos */


     /* Leemos los dos primeros bytes */
    fread(&type, sizeof(uint16_t), 1, file);
    if (type !=0x4D42){        /* Comprobamos el formato */
        fclose(file);
        return NULL;
    }

    /* Leemos la cabecera de fichero completa */
    fread(header, sizeof(bmpFileHeader), 1, file);

    /* Leemos la cabecera de información completa */
    fread(bInfoHeader, sizeof(bmpInfoHeader), 1, file);

    /* Reservamos memoria para la imagen, ¿cuánta?
     Tanto como indique imgsize */
    imgdata=(unsigned char*)malloc(bInfoHeader->imgsize);

    /* Nos situamos en el sitio donde empiezan los datos de imagen,
    nos lo indica el offset de la cabecera de fichero*/
    fseek(file, header->offset, SEEK_SET);

    /* Leemos los datos de imagen, tantos bytes como imgsize */
    fread(imgdata, bInfoHeader->imgsize,1, file);

    /* Cerramos */
    fclose(file);

    return imgdata;
}
void writes(FILE* out,unsigned char* img,bmpInfoHeader* bInfoHeader, bmpFileHeader* bmpFile){

  // se asigna el valor predeterminado para archivos con extension ".bmp"
  uint16_t type = 0x4D42; 
  fwrite(&type,sizeof(uint16_t),1,out);

  // Se lee la cabecera de fichero completa
  fwrite(bmpFile, sizeof(bmpFileHeader), 1, out);

  // se lee la cabecera de información completa
  fwrite(bInfoHeader, sizeof(bmpInfoHeader), 1, out);

  // escritura de la informacion de la imagen
  fwrite(img,bInfoHeader->imgsize, 1, out);
  fclose(out);
}


void uMain::main(){
	
	FILE *file;
	FILE *save;
	bmpInfoHeader* info = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
	bmpFileHeader* header = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
	unsigned char *img;
	file = fopen("image_1.bmp", "rb");
	save = fopen("salida.bmp", "wb");
	img = readRGB(file,info,header);
	writes(save,img,info,header);



}