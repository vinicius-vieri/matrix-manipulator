//Projeto/Prova 2 Programacao Estruturada  - Prof. Igor Malheiros
//Yhasmim de Souza Tigre                   - mat.: 20210026966
//Vinicius Vieri Bezerra de Lima           - mat.: 20210027364

#ifndef matrix_h
#define matrix_h

//Definição da estrutura da matriz
struct matrix{
	int* data;
	int n_rows;
	int n_cols;
	int stride_rows;
	int stride_cols;
	int offset;
};

//estrutura de dados para matriz
typedef struct matrix Matrix;

//funções para criação da matriz
Matrix create_matrix(int *data, int n_rows, int n_cols); //feito
Matrix zeros_matrix(int n_rows, int n_cols); //feito 
Matrix full_matrix(int n_rows, int n_cols, int value); //feito 
Matrix i_matrix(int n); //feito
Matrix tile_matrix(Matrix matrix, int reps); //feito

//funções para acessar elementos
int get_element(Matrix matrix, int ri, int ci); //feito
void put_element(Matrix matrix, int ri, int ci, int elem); //feito
void print_matrix(Matrix matrix); //feito

//funções de manipulação de dimensões
Matrix transpose(Matrix matrix);//feito
Matrix reshape(Matrix matrix, int new_n_rows, int new_n_cols);//feito
Matrix slice(Matrix a_matrix, int rs, int re, int cs, int ce);//feito

//funções de agregação
int min(Matrix matrix); //feito
int max(Matrix matrix); //feito
int argmin(Matrix matrix); //feito
int argmax(Matrix matrix); //feito

//definição da estrutura da matrix_1 
typedef struct{
	int* data;
	int n_rows;
	int n_cols;
	int stride_rows;
	int stride_cols;
	int offset;
} matrix_1;

//definição da estrutura da matrix_2 
typedef struct{
	int* data;
	int n_rows;
	int n_cols;
	int stride_rows;
	int stride_cols;
	int offset;
} matrix_2;

//definição da estrutura da a_matrix 
typedef struct{
	int* data;
	int n_rows;
	int n_cols;
	int stride_rows;
	int stride_cols;
	int offset;
} a_matrix;

//funções de operações aritméticas
Matrix add(Matrix matrix_1, Matrix matrix_2);//feito
Matrix sub(Matrix matrix_1, Matrix matrix_2);//feito
Matrix division(Matrix matrix_1, Matrix matrix_2);//feito
Matrix mul(Matrix matrix_1, Matrix matrix_2);//feito

#endif