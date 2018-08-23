#include "BoundedBuffer.cpp"
#include <iostream>
using namespace std;
#ifndef CONSUMER_PRODUCER_CONVERTTOGRAY_CPP
#define CONSUMER_PRODUCER_CONVERTTOGRAY_CPP
_Task ConvertToGray {
        BoundedBuffer &BufferIN; // sched. interno o externo
        BoundedBuffer &BufferOUT; // sched. interno o externo
    public:
        ConvertToGray(BoundedBuffer &bufIN, BoundedBuffer &bufOUT) : BufferIN(bufIN), BufferOUT(bufOUT){}
        unsigned char* convertToGray(unsigned char* imgdata, bmpInfoHeader* bInfoHeader){

		    unsigned char* gray = (unsigned char*)malloc(sizeof(unsigned char)*bInfoHeader->imgsize);
		    int count = 0;
		    int i=0;
		    int y;
		    while(count<bInfoHeader->imgsize/4){
		        y = imgdata[i+2]*0.3+imgdata[i+1]*0.59+imgdata[i]*0.11;
		        gray[i] = y;
		        gray[i+1] = y;
		        gray[i+2] = y;
		        gray[i+3] = 255;
		        i+=4;
		        count++;
		    }
		    return gray;
		}

    private:
    void main() {
        msge item;
        unsigned char *gray;
        for ( int i = 1;;i++ ) {
            item = BufferIN.remove();
            if(item.finish == 1){
                break;
            }
            gray = convertToGray(item.img,item.info);
            item.img = gray;
            BufferOUT.insert( item );
            yield( rand() % 20 );
        }
    }
};
#endif