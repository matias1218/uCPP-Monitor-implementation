#include "BoundedBuffer.cpp"
#include <iostream>
using namespace std;
#ifndef CONSUMER_PRODUCER_CONVERTTOBIN_CPP
#define CONSUMER_PRODUCER_CONVERTTOBIN_CPP
_Task ConvertToBin {
        BoundedBuffer &BufferIN; // sched. interno o externo
        BoundedBuffer &BufferOUT; // sched. interno o externo
    public:
        ConvertToBin( BoundedBuffer &bufIN, BoundedBuffer &bufOUT) : BufferIN(bufIN), BufferOUT(bufOUT) {}

        /*  Funcion que convierte una imagen a su modo binario. 
            ENTRADAS: - La informacion de los pixeles de una imagen.
                      - La cabecera de informacion de la imagen.
                      - El umbral en valor pixel, el cual define cuales pixeles deben ser transformados a blanco o negro.
            SALIDA:   - La informacion de la imagen (pixeles) binarizada.
        */
        unsigned char *convertToBinary(unsigned char* imgdata, bmpInfoHeader* bInfoHeader, int umbral){

            unsigned char* blackWhite = (unsigned char*)malloc(sizeof(unsigned char)*bInfoHeader->imgsize);

            int count = 0;
            int i=0;
            while(count<bInfoHeader->imgsize/4){
                if (imgdata[i] > umbral){
                    blackWhite[i] = 255;
                    blackWhite[i+1] = 255;
                    blackWhite[i+2] = 255;
                    blackWhite[i+3] = 255;
                }
                else{
                    blackWhite[i] = 0;
                    blackWhite[i+1] = 0;
                    blackWhite[i+2] = 0;
                    blackWhite[i+3] = 255;
                }
                i+=4;
                count++;
            }
            return blackWhite;
        }
    private:
    void main() {
        msge item;
        unsigned char *binary;
        for (int i = 1;;i++) {

            // se extrae un nodo de imagen desde el buffer (consumidor)
            item = BufferIN.remove();
             // verificacion de termino de ciclo
            if(item.finish == 1 || item.fileNotFound == 1){
                BufferOUT.insert( item );
                break;
            }
            binary = convertToBinary(item.img,item.info,item.umbral);
            item.img = binary;

            // se inserta una imagen en el buffer de imagen (productor)
            BufferOUT.insert( item );
            yield( rand() % 20 );
        }
    }
};
#endif