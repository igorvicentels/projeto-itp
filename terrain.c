#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "funcs.h"
#include "io.h"

int main(int argc, char* argv[]) {
  int* vetor; // Vetor para armazenar altura de cada barra
  int max_var = 2; // Variavel com a variação maxima da altitude (inicializada com com um valor padrão)
  char arquivo[64]; // Variável com o nome do arquivo de imagem a ser gerado
  int dimx = 1280; // Lagura da imagem
  int dimy = 720; // Altura da imagem
  int max_alt; // Altura máxima para as barras das extremidades
  int min_alt; // Altura minima para as barras das extremidades

  // Atribui um nome padrão para a imagem a ser gerada
  sprintf(arquivo, "%s", "terreno.ppm");

  // Lê os parametros de entrada da linha de comando (veriação da altura, nome do arquivo gerado e dimensões da imagem)
  for (int i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
      max_var = atoi(argv[i + 1]);
      i++;
    }
    if (strcmp(argv[i], "-o") == 0) {
      sprintf(arquivo, "%s.ppm", argv[i + 1]);
      i++;
    }
    if (strcmp(argv[i], "-s") == 0) {
      dimx = atoi(argv[i + 1]);
      dimy = atoi(argv[i + 1]) * 9 / 16;
      i++;
    }
  }

  vetor = malloc(sizeof(int) * dimx);
  
  // Gera o seed
  /* srand(time(NULL)); */
  srand(4);
  
  // Calcula o valor das alturas dos vetores das pontas
  max_alt = (int) dimy * 0.8;
  min_alt = (int) dimy * 0.3;
  do {
    vetor[0] = rand() % max_alt;
  } while (vetor[0] < min_alt);
  do {
    vetor[dimx - 1] = rand() % max_alt;
  } while (vetor[dimx - 1] < min_alt);
  

  //prints de teste
  printf("dimx: %d\n", dimx);
  printf("dimy: %d\n", dimy);
  printf("max_alt: %d\n", max_alt);
  printf("max_var: %d\n", max_var);
  printf("arquivo: %s\n", arquivo);
  printf("vetor[0]: %d\n", vetor[0]);
  printf("vetor[dimx - 1]: %d\n", vetor[dimx - 1]);

  // Calcula valores do vetor das alturas
  gera_terreno(vetor, 0, dimx - 1, max_var);

  // Gera arquivo de imagem
  cria_imagem(dimx, dimy, vetor, arquivo);

  return 0;
}