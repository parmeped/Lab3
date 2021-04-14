#include<stdio.h>
#include<stdlib.h>

int main() {

  int LOTE = 10;
  FILE *fp;

  // Produciendo
  if ((fp = fopen("productos.txt", "w")) == NULL) {
    printf("\nNo se puede abrir el archivo!");
  }
  else {
    printf("Produciendo...\n");
    int i = 0;
    while (i  < LOTE) {
      fprintf(fp, "PRODUCTO-%02d\n", i);      
      i++;
    }
  }

  fclose(fp);

  // Consumiendo  
  printf("Consumiendo\n");
  FILE *fp2;
  char producto[20];

  if ((fp2 = fopen("productos.txt", "r")) == NULL) {
    printf("\nNo se puede abrir el archivo!");
  } 
  else {
    while (!feof(fp2)) {
      fscanf(fp2, "%s\n", producto);
      printf("Consumiendo producto: %s \n", producto);
    }
  }
  fclose(fp2);
}
