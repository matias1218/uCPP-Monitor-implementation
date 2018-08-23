
using namespace std;
#ifndef CONSUMER_WRITERGB_CPP
#define CONSUMER_WRITERGB_CPP
_Task WriteRGB {
        BoundedBuffer &Buffer; // sched. interno o externo
    public:
        WriteRGB( BoundedBuffer &buf ) : Buffer( buf ) {}
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
        for (int i = 1 ;; i++) {
            item = Buffer.remove();
            if(item.finish == 1){
                break;
            }
            FILE *save;
            sprintf(bufOut, "%s%d.bmp", nameOut, i);
            save = fopen(bufOut, "wb");
            writes(save,item.img,item.info,item.header);
            yield( rand() % 20 );
        }
    }
};
#endif