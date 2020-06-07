#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "globais.c"

#ifndef HD_METODOS_H
#define HD_METODOS_H

void cria_hd(char nome_hd[]){
	char c = c_any;

	strcat(diretorio, nome_hd);

	FILE *f_hdv;
	f_hdv = fopen(diretorio , "wb");

	if (f_hdv == NULL){
		strcpy(diretorio, reseta_dir);
		puts("\n\tErro na criacao do HD!\n");
        return;
	}

	for (i = 0; i < blk_size * blk_qtd; i++){
		fwrite(&c,sizeof(char),1,f_hdv);
	}

	fclose(f_hdv);
	strcpy(diretorio, reseta_dir);
	puts("\n\tHD criado com sucesso!\n");
}

void formata_hd(char nome_hd[]){
	char c = c_nulo; 

	strcat(diretorio, nome_hd);

	FILE *f_hdv;
	f_hdv = fopen(diretorio, "wb");

	if (f_hdv == NULL){
		strcpy(diretorio, reseta_dir);
		puts("\n\tHD nao existe!\n");
        return;
	}

	for (i = 0; i < blk_size * blk_qtd; i++){
		fwrite(&c,sizeof(char),1,f_hdv);
	}

	fclose(f_hdv);

	strcpy(diretorio, reseta_dir);
	puts("\n\tHD formatado com sucesso!\n");
}

void type_hd(char nome_hd[]){
	char *bloco = malloc(sizeof(char)*blk_size);

	strcat(diretorio, nome_hd);

	FILE *f_hdv;
	f_hdv = fopen(diretorio , "rb");

	if (f_hdv == NULL){
		strcpy(diretorio, reseta_dir);
		free(bloco);
        puts("\n\tHD nao existe!\n");
        return;
	}

	printf("\n\t");

	for (i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			bloco[j] = '\0';
		}
		
		// loop abaixo le bloco
		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_hdv);
		}

		if (bloco[0] == c_any){
			puts("HD nao esta formatado!\n");
			strcpy(diretorio, reseta_dir);
			return;
		}

		if (bloco[0] != c_nulo){
			// loop abaixo imprime em hexadecimal
			for(j = 0; j < blk_size; j++){
			// for(j = 0;  bloco[j] != c_nulo; j++){
				if (bloco[j] == c_nulo){
					break;
				}
				printf("%x ", *(bloco + j));
			}

			printf("\n\t");	

			// loop abaixo imprime caractere
			for(j = 0; j < blk_size; j++){
			// for(j = 0; bloco[j] != c_nulo; j++){
				if (bloco[j] == c_nulo){
					break;
				}
				printf("%c  ", *(bloco + j));
			}
			printf("\n\t");
		}		
	}

	free(bloco);
	fclose(f_hdv);
	
	printf("\n");
	strcpy(diretorio, reseta_dir);
}

void lista_hds(){
	char* comando_ls = malloc(sizeof(char) * max3);

	for (i = 0; i < max3; i++){
		comando_ls[i] = '\0';
	}

	strcat(comando_ls, "ls ");
	strcat(comando_ls, reseta_dir);

	printf("\n");
	system(comando_ls);
	printf("\n");

	free(comando_ls);
}

void status_hd(char* nome_hd, int* bloco_livre){
	int total_bytes = blk_qtd * blk_size;
	int bytes_livres = 0, bytes_ocupados;

	for (i = 0; i < blk_qtd; i++){
		if (bloco_livre[i] >= 0){
			bytes_livres++;
		}
	}

	bytes_livres *= blk_size;

	bytes_ocupados = total_bytes - bytes_livres;

	printf("\n\tEspaco total: %d bytes"
		"\n\tEspaco livre: %d bytes"
		"\n\tEspaco ocupado: %d bytes\n\n", total_bytes, bytes_livres, bytes_ocupados);
}

void remove_hd(char* nome_hd){
	char* comando_rm = malloc(sizeof(char) * max3);

	for (i = 0; i < max3; i++){
		comando_rm[i] = '\0';
	}

	strcat(comando_rm, "rm ");
	strcat(comando_rm, nome_hd);

	system(comando_rm);
	printf("\n\tHD removido com sucesso!\n\n");
	free(comando_rm);
}

#endif