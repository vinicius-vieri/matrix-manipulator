//Projeto/Prova 2 Programacao Estruturada  - Prof. Igor Malheiros
//Yhasmim de Souza Tigre                   - mat.: 20210026966
//Vinicius Vieri Bezerra de Lima           - mat.: 20210027364

#ifndef MATRIX_C
#define MATRIX_C

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

//----------------------------------------------------------//

//FUNÇÕES PARA CRIAÇÃO DE MATRIZES

//FUNÇÃO PARA CRIAR A MATRIZ
Matrix create_matrix(int *data, int n_rows, int n_cols){
  Matrix m;
  m.data = data;
  m.n_rows = n_rows;
  m.n_cols = n_cols;
  m.stride_rows = n_cols;
  m.stride_cols = 1;
  m.offset = 0;
  return m;
}

//FUNÇÃO PARA PREENCHER A  MATRIZ COM ZEROS
Matrix zeros_matrix(int n_rows, int n_cols){

  return full_matrix(n_rows, n_cols, 0);
}

//FUNÇÃO PARA PREENCHER A MATRIZ COM VALOR ESPECIFICO
Matrix full_matrix(int n_rows, int n_cols, int value){
  
  int *data = malloc(sizeof(int)* (n_rows * n_cols));
  int length = n_rows * n_cols;

  //Preenche o array data com value de acordo com o length
  for(int i = 0; i < length; i++){
    data[i] = value;
  }

  Matrix full = create_matrix(data, n_rows, n_cols);
  return full;
}

//FUNÇÃO DE MATRIZ IDENTIDADE
Matrix i_matrix(int n){

  //calculando a quantidade de elementos da matriz
  int *data = malloc(sizeof(int)* (n * n));
  int length = n * n;


  //percorrendo a matriz e verificando quais índices são iguais para atribuir 1
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){ // aqui são pra percorrer
      int indice = (i * n) + j;
      if(i == j){ //se os índices forem iguais, data recebe 1
        data[indice] = 1; 
      } 
      else{ //se os índices não forem iguais, data recebe 0
        data[indice] = 0; 
      }   
    }
  }

  Matrix i = create_matrix(data, n, n);
  return i;
}

//FUNÇÃO QUE MULTPLICA O CONTEUDO DA MATRIZ
Matrix tile_matrix(Matrix matrix, int reps){
  int quant_elem = matrix.n_cols * matrix.n_rows;
  int m = 0, count = 0;
  int new_cols = 0;
  //alocando espaço de memoria para repetição
  int *data = malloc(sizeof(int) * (quant_elem * reps));

  for(int i = 0; i < matrix.n_rows; i++){
    for(int j = 0; j < reps; j++){
      for(int p = 0; p < matrix.n_cols; p++){
        data[m] = matrix.data[p + (count *matrix.stride_rows)];
        m++;
      }      
    }
    count++;
  }
 
  new_cols = matrix.n_cols * reps;
  Matrix matrix_tile = create_matrix(data, matrix.n_rows, new_cols);
  return matrix_tile;
}


//----------------------------------------------------------//

//FUNÇÕES PARA ACESSAR ELEMENTOS

//FUNÇÃO QUE PEGA UM ELEMENTO ESPECIFICO DA MATRIZ
int get_element(Matrix matrix, int ri, int ci){
  return matrix.data[ri * matrix.n_cols + ci];
}

//FUNÇÃO QUE PARA SUBSTITUIR EM UMA POSIÇÃO ESPECIFICA DA MATRIZ
void put_element(Matrix matrix, int ri, int ci, int elem){
  matrix.data[ri * matrix.n_cols + ci] = elem;
}

//FUNÇÃO QUE PRINTA OS ELEMENTOS DA MATRIZ
void print_matrix(Matrix matrix){
  int* content = matrix.data;
  int length = matrix.n_rows * matrix.n_cols;
  int stride_rows = matrix.stride_rows;
  
  // aqui ele conta e percorre
  int contador = 0;
  for(int i = 0; i < length; i++){
    printf("%i ", matrix.data[i]);
    contador++;

    //verificando se a linha chegou ao final
    if(contador == matrix.n_cols){
      printf("\n");

      //reinicia o contador para zero
      contador = 0;
    }
  }
}


//----------------------------------------------------------//

//FUNÇÕES DE AGREGAÇÃO 

//FUNÇÃO QUE RETORNA O MENOR VALOR DA MATRIZ
int min(Matrix matrix) {
  int* data = matrix.data;
  int qtd_elementos = matrix.n_rows * matrix.n_cols;
	//calculando a quantidade de elementos da matriz
    
  int menor = data[0]; //atribuindo o primeiro valor da matriz
  for(int i = 1; i < qtd_elementos; i++){
    if(data[i] < menor){ //comparando e capturando o menor elemento da matriz
      menor = data[i];
    }
  }
  return menor;
}

//FUNÇÃO QUE RETORNA O MAIOR VALOR DA MATRIZ
int max(Matrix matrix){
	int* data = matrix.data;
  int qtd_elementos = matrix.n_rows * matrix.n_cols; //calculando a quantidade de elementos da matriz
    
  int maior = data[0];  //atribuindo o primeiro valor da matriz
  for(int i = 1; i < qtd_elementos; i++){
    if(data[i] > maior){ //comparando e capturando o maior elemento da matriz
      maior = data[i];
    }
  }  
  return maior;
}

//FUNÇÃO QUE RETORNA O INDICE DE MENOR VALOR DA MATRIZ
int argmin(Matrix matrix){
  int* data = matrix.data;
  int qtd_elementos = matrix.n_rows * matrix.n_cols; //calculando a quantidade de elementos da matriz
  int indice = 0;
    
  int menor = data[0];
  for(int i = 1; i < qtd_elementos; i++){ //percorrendo
    if(data[i] < menor){ //comparando e capturando o índice do maior elemento da matriz
      menor = data[i];
      indice = i; //atribuindo para o retorno
    }
  }  
  return indice;
}

//FUNÇÃO QUE RETORNA O INDICE DE MAIOR VALOR DA MATRIZ
int argmax(Matrix matrix){
  int* data = matrix.data;
  int qtd_elementos = matrix.n_rows * matrix.n_cols;  //calculando a quantidade de elementos da matriz
  int indice = 0;
  
  int maior = data[0];
  for(int i = 1; i < qtd_elementos; i++){
    if(data[i] > maior){ //comparando e capturando o índice do menor elemento da matriz
      maior = data[i];
      indice = i; //atribuindo para o retorno
    }
  }    
  return indice;
}


//----------------------------------------------------------//

//FUNÇÕES DE MANIPULAÇÃO DE DIMENSÕES

//FUNÇÃO QUE RETORNA MATRIZ TRANSPOSTA
Matrix transpose(Matrix matrix){
  int n_rows = matrix.n_rows;
  int n_cols = matrix.n_cols;
  int count = 1, reset = 0;
  
  //Matrix transposta = create_matrix(data3, matrix.n_rows, matrix.n_cols);
  int* data = malloc(sizeof(int) * (matrix.n_rows * matrix.n_cols));//alocando espaço para nova matriz

  for(int i = 0, j = 0; i < matrix.n_rows * matrix.n_cols; i++){
    data[i] = matrix.data[j];//i irá percorrer a nova data, enquanto j percorre a antiga
    j += matrix.stride_rows; //pular a linha
    count++; 
    if(count > matrix.n_rows){//reseta o contador de colunas
      count = 1;
      reset++;
      j = count;
    }
  }

  //criando uma matriz para receber a transposta
  Matrix transposta = create_matrix(data, matrix.n_rows, matrix.n_cols);
  return transposta;
}


//FUNÇÃO QUE ALTERA AS DIMENSÕES DA MATRIZ
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols){
  
  //criando a matriz para a nova dimensão
  Matrix matrix_dim = create_matrix(matrix.data, new_n_rows, new_n_cols);
  return matrix_dim;
}


//FUNÇÃO QUE RETORNA UM "RECORTE" DA MATRIZ ORIGINAL
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce){
  
  int rows_final = re - rs; //numero de novas linhas
  int cols_final = ce - cs; //numero de novas colunas
  int quant_final = rows_final * cols_final; //quantidade de novos elementos 
  int k = 0, m = 0; 
  int* data = (malloc(sizeof(int) * quant_final));

  for(int i = 0; i < a_matrix.n_rows; i++){
    for(int j = 0; j < a_matrix.n_cols; j++){//percorrendo as linhas e colunas
      if(i >= rs && i < re){
        if(j >= cs && j < ce){//lendo os indices corretos
          data[k] = a_matrix.data[m];//atribuindo valores dentro dos limites estabelecidos na chamada ao data
          k = k + 1;                    
        }
      }
      m = m + 1;
    }
  }

  Matrix recorte = create_matrix(data, rows_final, cols_final);
  return recorte;
}


//----------------------------------------------------------//

//FUNÇÕES DE OPERAÇÕES ARITMÉTICAS

//FUNÇÃO DE SOMA
Matrix add(Matrix matrix_1, Matrix matrix_2){
    
  int* data3 = malloc(sizeof(int) * (matrix_1.n_rows * matrix_1.n_cols)); //alocando espaço para nova matriz

  for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){ 
    data3[i] = matrix_1.data[i] + matrix_2.data[i];
  }

  //criando a matriz soma
  Matrix matrix_soma = create_matrix(data3, matrix_1.n_rows, matrix_1.n_cols);
  return matrix_soma;
}

//FUNÇÃO DE SUBTRAÇÃO
Matrix sub(Matrix matrix_1, Matrix matrix_2){
     
  int* data3 = malloc(sizeof(int) * (matrix_1.n_rows * matrix_1.n_cols)); //alocando espaço para nova matriz

  for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){ 
    data3[i] = matrix_1.data[i] - matrix_2.data[i];
  }

  //criando a matriz soma
  Matrix matrix_sub = create_matrix(data3, matrix_1.n_rows, matrix_1.n_cols);
  return matrix_sub;
}

//FUNÇÃO DE DIVISÃO
Matrix division(Matrix matrix_1, Matrix matrix_2){
     
  int* data3 = malloc(sizeof(int) * (matrix_1.n_rows * matrix_1.n_cols)); //alocando espaço para nova matriz

  for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){ 
    data3[i] = matrix_1.data[i] / matrix_2.data[i];
  }

  //criando a matriz soma
  Matrix matrix_div = create_matrix(data3, matrix_1.n_rows, matrix_1.n_cols);
  return matrix_div;
}

//FUNÇÃO DE MULTIPLICAÇÃO
Matrix mul(Matrix matrix_1, Matrix matrix_2){
     
  int* data3 = malloc(sizeof(int) * (matrix_1.n_rows * matrix_1.n_cols)); //alocando espaço para nova matriz

  for(int i = 0; i < matrix_1.n_rows * matrix_1.n_cols; i++){ 
    data3[i] = matrix_1.data[i] * matrix_2.data[i];
  }

  //criando a matriz soma
  Matrix matrix_multi = create_matrix(data3, matrix_1.n_rows, matrix_1.n_cols);
  return matrix_multi;
}

#endif