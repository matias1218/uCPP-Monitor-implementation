
using namespace std;
#ifndef CONSUMER_WRITERGB_CPP
#define CONSUMER_WRITERGB_CPP
_Task WriteRGB {
        BoundedBuffer &Buffer; // sched. interno o externo
    public:
        WriteRGB( BoundedBuffer &buf ) : Buffer( buf ) {}

        /*  Funcion que escribe en disco una imagen con extensión ".bmp" de 32 bits. Para este caso, la imagen binarizada
            ENTRADAS: - Una lista enlazada para guardar la informacion de la imagen.
                      - El archivo de salida.
                      - La informacion de los pixeles de una imagen.
                      - La cabecera de informacion de la imagen.
                      - La cabecera del fichero de la imagen procesada.
            SALIDA:   - Salida vacía.
        */
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
          
        }
    private:
    void main() {
        msge item;
        char bufOut[32] = { 0 };
        const char *nameOut = "salida_";

        // se realiza el ciclo infinito que tendra a la hebra constantemente consultando e insertando en los buffers
        for (int i = 1 ;; i++) {
            // se extrae un nodo de imagen del buffer
            item = Buffer.remove();

            // verificador para terminar el ciclo
            if(item.finish == 1 || item.fileNotFound == 1){
                if(item.fileNotFound == 1){
                  cout<<"Archivo no encontrado, finalizando..." << endl;
                }
                break;
            }
            FILE *save;
            sprintf(bufOut, "%s%d.bmp", nameOut, i);
            save = fopen(bufOut, "wb");

            // se escribe la imagen en disco
            writes(save,item.img,item.info,item.header);
            yield( rand() % 20 );
        }
    }
};
#endif