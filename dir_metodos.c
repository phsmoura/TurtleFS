#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "globais.c"

#ifndef DIR_METODOS_H
#define DIR_METODOS_H

void cria_raiz(char *diretorio, const char *nome_raiz, const char *lbl_raiz){
	int tamanho = 2 * strlen(lbl_raiz) * strlen(nome_raiz);
	char *escreve_bloco = malloc(sizeof(char) * tamanho);

	// retira lixo de memoria do vetor
	for (i = 0; i < tamanho; i++){
		escreve_bloco[i] = '\0';
	}

	strcat(escreve_bloco, lbl_raiz);
	strcat(escreve_bloco, lbl_raiz);
	strcat(escreve_bloco, nome_raiz);

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb+");

	for (i = 0; escreve_bloco[i] != '\0'; i++){
		fwrite(&escreve_bloco[i], sizeof(char),1,f_bin);
	}
	fwrite(&escreve_bloco[i], sizeof(char),1,f_bin);
	
	free(escreve_bloco);
	fclose(f_bin);
}

void cria_diretorio(char *diretorio, char *nome_diretorio, const char *lbl_atual_dir, char* lbl_aux, int *bloco_livre){
	char* bloco = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * blk_size);

	// retira lixo de memoria do vetor
	for (i = 0; i < blk_size; i++){
		bloco[i] = '\0';
		escreve_bloco[i] = '\0';
	}

	// limita tamanho max do nome do diretorio
	if (nome_diretorio[blk_size - 7] != '\0'){
		nome_diretorio[blk_size - 6] = '\0';
	}

	strcat(escreve_bloco, lbl_atual_dir);
	strcat(escreve_bloco, lbl_aux);
	strcat(escreve_bloco, nome_diretorio);
	

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb+");

	for (i = 0; i < blk_qtd; i++){

		if (bloco_livre[0] == i){
			for (j = 0; escreve_bloco[j] != '\0'; j++){
				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
			}
			// escreve \0
			fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
			break;
		}
		else {
			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_bin);
			}
		}
	}

	printf("\n\tDiretorio criado com sucesso!\n\n");

	free(bloco);
	free(escreve_bloco);
	fclose(f_bin);
}

void remove_diretorio(char *diretorio, char *nome_diretorio, const char *lbl_atual_dir){
	char* bloco = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * blk_size);
	char* nome = malloc(sizeof(char) * blk_size);
	char* lbl_aux_del = malloc(sizeof(char) * pmax);
	char* dir_encontrado = malloc(sizeof(char) * pmax);
	int deleta_linha = 0;

	for (i = 0; i < blk_size; i++){
		escreve_bloco[i] = c_nulo;
	}

	FILE *f_bin;
	f_bin = fopen (diretorio, "rb");

	k = 0;

	for (i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			bloco[j] = '\0';
			nome[j] = '\0';
		}

		// retira lixo de memoria do vetor
		for (j = 0; j < pmax; j++){
			lbl_aux_del[j] = '\0';
			dir_encontrado[j] = '\0';
		}
		lbl_aux_del[pmax] = '\0';
		dir_encontrado[pmax] = '\0';

		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_bin);
		}

		for (j = 0; j < pmax; j++){
			lbl_aux_del[j] = bloco[j];
		}

		for (j = 0; j < pmax; j++){
			dir_encontrado[j] = bloco[j + 3];
		}

		for (j = 0; j < blk_size; j++){
			nome[j] = bloco[j + 6];
		}

		if (strcmp(lbl_aux_del, lbl_atual_dir) == 0){

			if(strcmp(nome, nome_diretorio) == 0){

				deleta_linha = i;
				k++;
			}
		}
	}

	fclose(f_bin);

	if (k > 1){
		free(bloco);
		free(escreve_bloco);
		free(nome);
		free(lbl_aux_del);
		printf("\n\tHa arquivos ou diretorios dentro deste diretorio."
			"\n\tDelete-os primeiro!\n\n");
		return;
	}

	if (deleta_linha == 0){
		free(bloco);
		free(escreve_bloco);
		free(nome);
		free(lbl_aux_del);
		free(dir_encontrado);
		printf("\n\tDiretorio inexistente!\n\n");
		return;
	}

	f_bin = fopen (diretorio, "rb+");

	for (i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			bloco[j] = '\0';
		}

		if(i == deleta_linha){
			for (j = 0; j < blk_size; j++){
				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
			}
		}
		else {
			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_bin);
			}
		}
	}
	
	fclose(f_bin);
	free(bloco);
	free(escreve_bloco);
	free(nome);
	free(lbl_aux_del);
	free(dir_encontrado);

	printf("\n\tDiretorio removido com sucesso!\n\n");
}

void renomeia_diretorio(char *diretorio, char *nome_diretorio, char *novo_nome, const char *lbl_atual_dir){
	char* bloco = malloc(sizeof(char) * blk_size);
	char* nome_encontrado = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * blk_size);
	char* dir_encontrado = malloc(sizeof(char) * pmax);
	char* lbl_dir = malloc(sizeof(char) * pmax);

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb");

	for (p = 0; p < blk_qtd; p++){

		// retira lixo
		for (i = 0; i < blk_size; i++){
			bloco[i] = '\0';
			nome_encontrado[i] = '\0';
		}

		// retira lixo
		for (i = 0; i < pmax + 1; i++){
			dir_encontrado[i] = '\0';
			lbl_dir[i] = '\0';
		}

		for (i = 0; i < blk_size; i++){
			fread(&bloco[i],sizeof(char),1,f_bin);
		}

		for (i = 0; i < pmax; i++){
			dir_encontrado[i] = bloco[i];
		}

		for (i = 0; i < pmax; i++){
			lbl_dir[i] = bloco[i + 3];
		}

		for (i = 0; i < blk_size - 6; i++){
			nome_encontrado[i] =  bloco[i+6];
		}

		if (strcmp(lbl_atual_dir, dir_encontrado) == 0){
			if (strcmp(nome_diretorio, nome_encontrado) == 0){
				break;
			}
		}
	}

	fclose(f_bin);

	if (p >= blk_qtd){
		free(bloco);
		free(dir_encontrado);
		free(lbl_dir);
		free(nome_encontrado);
		free(escreve_bloco);
		
		printf("\n\tEste diretorio nao existe neste diterorio!\n\n");
		return;
	}

	f_bin = fopen(diretorio, "rb+");

	// retira lixo
	for (i = 0; i < blk_size; i++){
		escreve_bloco[i] = '\0';
	}

	strcat(escreve_bloco, lbl_atual_dir);
	strcat(escreve_bloco, lbl_dir);
	strcat(escreve_bloco, novo_nome);

	for (i = 0; escreve_bloco[i] != '\0'; i++);

	for (j = i + 1; j< blk_size; j++){
		escreve_bloco[j] = '\\';
	}

	for (i = 0; i < blk_qtd; i++){

		// retira lixo
		for (j = 0; j < blk_size; j++){
			bloco[i] = '\0';
		}

		if (i == p){
			for (j = 0; j < blk_size; j++){
				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
			}
		}

		else {
			for (j = 0; j < blk_size; j++){
				fread(&bloco[i],sizeof(char),1,f_bin);
			}
		}
	}

	fclose(f_bin);

	free(bloco);
	free(dir_encontrado);
	free(lbl_dir);
	free(nome_encontrado);
	free(escreve_bloco);

	printf("\n\tDiretorio %s renomeado com sucesso!\n\n", nome_diretorio);
}

char* navega_diretorio(char *diretorio, char *nome_diretorio, char *lbl_atual_dir){
	char* lbl_dir = malloc(sizeof(char) * pmax);

	if (strcmp(nome_diretorio, "..") == 0){
		// retira lixo
		for (i = 0; i < pmax + 1; i++){
			lbl_dir[i] = '\0';
		}

		strcpy(lbl_dir, decrementa_lbl_dir(lbl_atual_dir));
		return lbl_dir;
	}

	char* bloco = malloc(sizeof(char) * blk_size);
	char* nome_encontrado = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * blk_size);
	char* dir_encontrado = malloc(sizeof(char) * pmax);
	

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb");

	for (p = 0; p < blk_qtd; p++){

		// retira lixo
		for (i = 0; i < blk_size; i++){
			bloco[i] = '\0';
			nome_encontrado[i] = '\0';
		}

		// retira lixo
		for (i = 0; i < pmax + 1; i++){
			dir_encontrado[i] = '\0';
			lbl_dir[i] = '\0';
		}

		for (i = 0; i < blk_size; i++){
			fread(&bloco[i],sizeof(char),1,f_bin);
		}

		for (i = 0; i < pmax; i++){
			dir_encontrado[i] = bloco[i];
		}

		for (i = 0; i < pmax; i++){
			lbl_dir[i] = bloco[i + 3];
		}

		for (i = 0; i < blk_size - 6; i++){
			nome_encontrado[i] =  bloco[i+6];
		}

		if (strcmp(lbl_atual_dir, dir_encontrado) == 0){
			if (strcmp(nome_diretorio, nome_encontrado) == 0){
				break;
			}
		}
	}

	fclose(f_bin);

	if (p >= blk_qtd){
		free(bloco);
		free(dir_encontrado);
		free(lbl_dir);
		free(nome_encontrado);
		free(escreve_bloco);
		
		printf("\n\tEste diretorio nao existe neste diterorio!\n\n");
		return lbl_atual_dir;
	}

	free(bloco);
	free(dir_encontrado);
	free(nome_encontrado);
	free(escreve_bloco);

	return lbl_dir;
}

#endif