typedef struct bmpFileHeader{
  /* 2 bytes de identificación */
  uint32_t size;        /* Tamaño del archivo */
  uint16_t resv1;       /* Reservado */
  uint16_t resv2;       /* Reservado */
  uint32_t offset;      /* Offset hasta hasta los datos de imagen */
} bmpFileHeader;

typedef struct bmpInfoHeader{
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

typedef struct msge {
  bmpFileHeader *header;
  bmpInfoHeader *info;
  int totalImages; //cantidad de imagenes a procesar
  int imagenActual; //numero de la imagen procesada n>=1
  int umbral; // parametro de pixel para escala de grises
  int ratio; // porcentaje de oscuridad
  int flag; // flag para mostrar por pantalla
  int finish; // flag para terminar los procesos
  unsigned char *img; // datos de la imagen actual
} msge;