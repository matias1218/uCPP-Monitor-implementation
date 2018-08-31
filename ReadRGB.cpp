
using namespace std;
#ifndef PRODUCER_READRGB_CPP
#define PRODUCER_READRGB_CPP
_Task ReadRGB {
        BoundedBuffer &Buffer; // sched. interno o externo
        int cantImages;
        int umbral;
        int flag;
        int ratio;
    public:
        ReadRGB( BoundedBuffer &buf , int &cantImages, int &umbral, int &ratio, int &flag) : Buffer( buf ) {
            this->cantImages = cantImages;
            this->umbral = umbral;
            this->flag = flag;
            this->ratio = ratio;
        }
        
        /*  Funcion que lee un archivo de imagen y extrae la informacion de los pixeles para poder ser manipulados. 
            ENTRADAS: - Un archivo de tipo ".bmp".
                      - La cabecera de informacion de la imagen.
                      - La cabecera del fichero de la imagen procesada.
            SALIDA:   - La informacion de la imagen de un archivo de imagen ".bmp".
        */

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
    private:
    void main() {
        char bufIn[32] = { 0 };
        const char *nameIn = "image_";
        for ( ;; ) {
            for (int i = 1; i <= cantImages; i += 1) {
                FILE *file;
                bmpInfoHeader* info = (bmpInfoHeader*)malloc(sizeof(bmpInfoHeader));
                bmpFileHeader* header = (bmpFileHeader*)malloc(sizeof(bmpFileHeader));
                unsigned char *img;
                sprintf(bufIn, "%s%d.bmp", nameIn, i);
                file = fopen(bufIn, "rb");
                msge message;
                if (file==NULL)
                {
                    //cout<<"Archivo no encontrado, finalizando..." << endl;
                    message.fileNotFound = 1;
                    Buffer.insert( message );
                    break;
                }
                img = readRGB(file,info,header);

                // se crea un nodo mensaje para guardar en el buffer
                
                message.header = header;
                message.info = info;
                message.totalImages = cantImages; //cantidad de imagenes a procesar
                message.imagenActual = i;
                message.ratio = ratio;
                message.umbral = umbral;
                message.flag = flag;
                message.finish = 0;
                //int imagenActual; //numero de la imagen procesada n>=1
                //int umbral; // parametro de pixel para escala de grises
                //int ratio; // porcentaje de oscuridad
                //int flag; // flag para mostrar por pantalla
                message.img = img; // datos de la imagen actual


                yield( rand() % 20 ); // duerma un rato

                // se inserta el nodo en el buffer
                Buffer.insert( message );

                

            }

            break;
        }
    }
};
#endif