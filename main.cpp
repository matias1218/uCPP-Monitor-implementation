#include <uC++.h>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <unistd.h>
#include "header.h"
#include "BoundedBuffer.cpp"
#include "ReadRGB.cpp"
#include "ConvertToGray.cpp"
#include "ConvertToBin.cpp"
#include "NearlyBlack.cpp"
#include "WriteRGB.cpp"

using namespace std;
int main(int argc, char  *argv[]){



	char param;
	char *cantImages1 = NULL;
	char *binaryUmbral1 = NULL;
	char *nearlyBlackUmbral1 = NULL;
	int flag1 = 0;
  	int cantImages;
  	int binaryUmbral;
  	int nearlyBlackUmbral;

	  // ------------------------------ Bloque de GETOPT() --------------------------------------//

	/**El bucle se realiza mientras el resultado sea -1, ya que este es el valor que se retorna cuando ya se han leído todos los parámetros.
	 *Los parámetros de la función getopt() son los siguientes:
	 *Primer parámetro: Cantidad de parámetros ingresados por la consola. Viene dado por el valor del parámetro argc del main.
	 *Segundo parámetro: Son los valores de los parámetros (en forma de Strings) ingresados por la consola. Viene dado por el parámetro argv del main.
	 *Tercer parámetro: Es el formato de lectura de parámetros considerado en la consola. Para este ejemplo se usan tres parámetros, los cuales son
	  c, u, n y b los cuales son separados por dos puntos (:) indicando que cada uno debe tener un valor al ingresarlos por consola.
	 *Se debe considerar que el valor que toma la variable optarg (la cual viene incluída por defecto en la librería unistd.h) es el valor
	 que tiene cada parámetro ingresado por consola, por lo que al recorrer estos parámetros, tomarán respectivamente los valores dados para
	 c, u, n y b.
	*/
	while((param = getopt(argc, argv, "c:u:n:b")) != -1){
		switch(param){
			case 'c':
		        if(atoi(optarg) == 0){
		          	printf("FORMAT ERROR IN -c ARGUMENT\n");
		          	exit(1);
		        }
		        else{
		          	cantImages1 = optarg;
		        }
				break;
			case 'u':
		        if(atoi(optarg) == 0){
		          	printf("FORMAT ERROR IN -u ARGUMENT\n");
		          	exit(1);
		        }
		        else{
		          	binaryUmbral1 = optarg;
		        }
				break;
			case 'n':
		        if(atoi(optarg) == 0){
		          	printf("FORMAT ERROR IN -n ARGUMENT\n");
		          	exit(1);
		        }
		        else{
		          	nearlyBlackUmbral1  = optarg;
		        }	
				break;
			case 'b':
				flag1 = 1;
				break;
			
		}
	}

	  //------------------------------ Bloque de verificacion de entradas -----------------------//

	if(cantImages1 == NULL){
	    printf("NOT VALUE IN -c ARGUMENT\n");
	    exit(1);
    }
	else{
		if(binaryUmbral1 == NULL){
			printf("NOT VALUE IN -u ARGUMENT\n");
	        exit(1);
	    }
	    else{
	    	if(nearlyBlackUmbral1 == NULL){
	    		printf("NOT VALUE IN -n ARGUMENT\n");
	        	exit(1);
	      	}
	      	else{
	        	cantImages= atoi(cantImages1);
	        	binaryUmbral= atoi(binaryUmbral1);
	        	nearlyBlackUmbral= atoi(nearlyBlackUmbral1);
	        	if(cantImages < 0){
	          		printf("INVALID AMOUNT OF IMAGES\n");
	          		exit(1);
	        	}
	        	else{
	          		if(binaryUmbral < 0 || binaryUmbral > 255){
	            		printf("INVALID PIXEL VALUE\n");
	            		exit(1);
	          		}
	          		else{
	            		if(nearlyBlackUmbral < 0 || nearlyBlackUmbral > 100){
	              			printf("INVALID RATIO VALUE\n");
	              			exit(1);
	            		}
	          		}
	        	}
	      	}
	    }
	}


	srand (time(NULL));
	// inicializacion de monitores
	BoundedBuffer buf1(20); // Monitor 1 que posee 20 elementos
	BoundedBuffer buf2(20); // Monitor 2
	BoundedBuffer buf3(20); // Monitor 3
	BoundedBuffer buf4(20); // Monitor 4
	// creacion de los objetos para cada proceso
	ReadRGB *read = new ReadRGB(buf1,cantImages,binaryUmbral,nearlyBlackUmbral,flag1);
	ConvertToGray *gray = new ConvertToGray(buf1,buf2);
	ConvertToBin *bin = new ConvertToBin(buf2,buf3);
	NearlyBlack *nearly = new NearlyBlack(buf3,buf4);
	WriteRGB *Write = new WriteRGB(buf4);
	// eliminacion de los procesos
	msge exit;
	exit.finish = 1;
	delete read;
	buf1.insert(exit);
	delete gray;
	buf2.insert(exit);
	delete bin;
	buf3.insert(exit);
	delete nearly;
	buf4.insert(exit);
	
	delete Write;
	return 0;
}