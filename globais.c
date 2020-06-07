#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef VARIAVEIS_PADRAO_H
#define VARIAVEIS_PADRAO_H

// controlam diretorio
char diretorio [] = "/home/pedro/Documents/repos/turtlefs/hds/"; 
const char reseta_dir [] = "/home/pedro/Documents/repos/turtlefs/hds/";

// tamanho e quantidade de blocos
const int blk_size = 32;
const int blk_qtd = 1000;

// caractere usadas para hd
const char c_nulo = '\\';
const char c_any = '+';
const char extensao[] = ".hdv";
const char dir_raiz[] = "raiz";
const char primeiro_dir[] = "DAA";

// tamanho do vetor
const int max = 50;
const int max2 = 100;
const int max3 = 150;
const int pmax = 3;

// contadores
int i,j,k,p,q; 

bool verifica_hd(char nome_hd[]){

	FILE *f_hdv;
	f_hdv = fopen(diretorio, "rb");

	if (f_hdv == NULL){
		strcpy(diretorio, reseta_dir);
		puts("\n\tHD nao existe!\n");
        return false;
	}

	fclose(f_hdv);
	return true;
}

int* conta_blocos_livres(char *diretorio, int *bloco_livre){
	char* bloco = malloc(sizeof(char) * blk_size);

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb");

	// retira lixo de memoria
	for (i = 0; i < blk_qtd; i++){
		bloco_livre[i] = -1;
	}

	k = 0;

	for (i = 0; i < blk_qtd; i++){
		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_bin);
		}

		if (bloco[0] == c_nulo){
			bloco_livre[k] = i;
			k++;
		}
	}

	// for (j = 0; j < blk_qtd; j++){
	// 	printf("livre: %d ", *(bloco_livre + j));
	// }
	// printf("\n\n");

	free (bloco);
	fclose(f_bin);
	return bloco_livre;
}

char *define_lbl_arq(char *atual_arq){
	if (strcmp(atual_arq, "---") == 0){
		strcpy(atual_arq, "CAA");
	}

	else
		if (atual_arq[2] != 'Z'){
			atual_arq[2] = atual_arq[2] + 1;
		}

	else 
		if (atual_arq[2] == 'Z' && atual_arq[1] < 'Z'){
			atual_arq[2] = 'A';
			atual_arq[1] = atual_arq[1] + 1;
	}

	return atual_arq;
}

char *encontra_lbl_arq(char *diretorio){
	char *bloco = malloc(sizeof(char) * blk_size);
	
	char *lbl_arq = malloc(sizeof(char) * pmax);
	strcpy(lbl_arq, "---");

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb");

	if (f_bin == NULL){
		free(bloco);
		free(lbl_arq);
        return "---";
	}

	for (i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_bin);
		}

		if (bloco[0] != c_nulo && bloco[3] == 'C'){

			lbl_arq[0] = bloco[3];

			if (bloco[4] > lbl_arq[1]){
				lbl_arq[1] = bloco[4];
			}

			if (bloco[5] > lbl_arq[2]){
				lbl_arq[2]= bloco[5];
			}
		}
	}

	free(bloco);
	fclose(f_bin);

	// evita que lixo de memoria entre no vetor
	lbl_arq[pmax] = '\0';
	
	return lbl_arq;
}

char *encontra_lbl_dir(char *diretorio){
	char *bloco = malloc(sizeof(char) * blk_size);
	char *lbl_dir = malloc(sizeof(char) * pmax);

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb");

	if (f_bin == NULL){
		free(bloco);
		free(lbl_dir);
        return "DAA";
	}

	for (i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_bin);
		}

		if (bloco[0] != c_nulo && bloco[3] == 'D'){

			lbl_dir[0] = bloco[3];

			if (bloco[4] > lbl_dir[1]){
				lbl_dir[1] = bloco[4];
			}

			if (bloco[5] > lbl_dir[2]){
				lbl_dir[2]= bloco[5];
			}
		}
	}

	free(bloco);
	fclose(f_bin);

	// evita que lixo de memoria entre no vetor
	lbl_dir[pmax] = '\0';
	
	return lbl_dir;
}

char *soma_lbl_dir(char *lbl_dir){
	if (lbl_dir[2] != 'Z'){
		lbl_dir[2] = lbl_dir[2] + 1;
	}

	else 
		if (lbl_dir[2] == 'Z' && lbl_dir[1] < 'Z'){
			lbl_dir[2] = 'A';
			lbl_dir[1] = lbl_dir[1] + 1;
	}

	return lbl_dir;
}

char *decrementa_lbl_dir(char *lbl_dir){
	if (lbl_dir[2] != 'A'){
		lbl_dir[2] = lbl_dir[2] - 1;
	}

	else 
		if (lbl_dir[2] == 'A' && lbl_dir[1] > 'A'){
			lbl_dir[2] = 'Z';
			lbl_dir[1] = lbl_dir[1] - 1;
	}

	return lbl_dir;
}

#endif