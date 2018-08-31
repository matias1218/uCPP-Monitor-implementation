#include "BoundedBuffer.cpp"
#include <iostream>
using namespace std;
#ifndef CONSUMER_PRODUCER_NEARLYBLACK_CPP
#define CONSUMER_PRODUCER_NEARLYBLACK_CPP
_Task NearlyBlack {
        BoundedBuffer &BufferIN; // sched. interno o externo
        BoundedBuffer &BufferOUT; // sched. interno o externo
    public:
        NearlyBlack(BoundedBuffer &bufIN, BoundedBuffer &bufOUT) : BufferIN(bufIN), BufferOUT(bufOUT) {}

        /*  Funcion que analiza y concluye si una imagen es "cercana a negro". 
            ENTRADAS: - La informacion de los pixeles de una imagen.
                      - La cabecera de informacion de la imagen.
                      - El valor en porcentaje a comparar de pixeles negros en una imagen.
                      - Una bandera que indica si la informacion de la clasificacion de la imagen se muestra o no en pantalla.
            SALIDA:   - Un entero especificando si la imagen es cercana a negro o no.
        */
        int isNearlyBlackOrNot(unsigned char* imgdata, bmpInfoHeader* bInfoHeader, int rate){

            
          int i=0,j=0;
          int cantOnes= 0;
          int cantZeros=0;
          int cantPIxels= bInfoHeader->imgsize/4;
          while(i<cantPIxels){
         
              if (imgdata[j] == 255){
                  cantOnes++;
              }
              else{
                  cantZeros++;
              }
              j+=4;
              i++;
          }
            
          float zerosProportions = ((float)cantZeros/cantPIxels)*100; 
          if (zerosProportions >= rate)
          {
            // si nearly black
            return 1;
          }
          else{
            // no nearly black
            return 0;
          }
        }
    private:
    void main() {
        msge item;
        char bufOut[32] = { 0 };
        const char *nameOut = "image_";
        int flagShow = 0;
        for ( ;; ) {
             // se extrae un nodo de imagen desde el buffer (consumidor)
            item = BufferIN.remove();

            // verificacion de termino de ciclo
            if(item.finish == 1 || item.fileNotFound == 1){
                BufferOUT.insert( item );
                break;
            }

            if(flagShow == 0 && item.flag == 1){
                printf("|        image        |    nearly black    |\n");
                printf("|---------------------|--------------------|\n");
                // -----o------- 
                flagShow = 1;
              }

            if(item.flag == 1){
                int value = isNearlyBlackOrNot(item.img, item.info, item.ratio);
                sprintf(bufOut, "%s%d.bmp", nameOut, item.imagenActual);
                if(value == 1 ){
                    printf("|   %14s    |        yes         |\n",bufOut );
                }
                else{
                    printf("|   %14s    |        no          |\n",bufOut );
                }
            }

            // se inserta una imagen en el buffer de imagen (productor)
            BufferOUT.insert( item );


            yield( rand() % 20 );


        }
    }
};
#endif