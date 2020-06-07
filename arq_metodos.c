#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "globais.c"

#ifndef ARQ_METODOS_H
#define ARQ_METODOS_H

// int conta_bytes_ocupados(char *diretorio){
// 	char c;
// 	FILE *f_bin;
// 	f_bin = fopen(diretorio, "rb");
// 	if (f_bin == NULL){
//         return -1;
// 	}

// 	for (i = 1; i <= blk_qtd; i++){
// 		fread(&c,sizeof(char),1,f_bin);
// 		if (c != c_nulo){
// 			for(j = 0; j < blk_size; j++){
// 				fread(&c,sizeof(char),1,f_bin);
// 			}
// 		}
// 		if (c == c_nulo)
// 			break;			
// 	}
// 	fclose(f_bin);
// 	return i * j;
// }

// int cria_arquivo(char *diretorio, char *nome_arquivo, char *lbl_dir, char *lbl_arq){
// 	int tamanho = strlen(nome_arquivo) + 2 * strlen(lbl_dir);
// 	char c = '\0';
// 	char *escreve = malloc(sizeof(char) * tamanho);
	
// 	// retirando lixo de memoria do vetor
// 	for (i = 0; i < tamanho; i++)
// 		escreve[i] = '\0';

// 	// os 1os 3 bytes sao reservados para o ponteiro do diretorio
// 	strcat(escreve, lbl_dir);

// 	// os proximos 3 bytes para o ponteiro do arquivo
// 	strcat(escreve, lbl_arq);

// 	// o resto para o nome
// 	strcat(escreve, nome_arquivo);

// 	// conta bytes ocupados do HD
// 	int bytes_ocupados = conta_bytes_ocupados(diretorio);

// 	if (bytes_ocupados == -1){
// 		return -1;
// 	}

// 	FILE *f_bin;
// 	f_bin = fopen(diretorio, "rb+");

// 	for (k = 0; k < bytes_ocupados; k++)
// 		fread(&c,sizeof(char),1,f_bin);

// 	if (tamanho >= blk_size - 1){
// 		tamanho = blk_size - 1;
// 		escreve[tamanho] = '\0';
// 	}

// 	for (i = 0; i <= tamanho; i++){
// 		fwrite(&escreve[i],sizeof(char),1,f_bin);
// 	}

// 	fclose(f_bin);
// 	free(escreve);
// 	return 1;
// }

// char *conteudo_arquivo(char *diretorio, char *lbl_arq){
// 	char c;
// 	int bytes_ocupados;
// 	FILE *f_bin;

// 	int tamanho_escreve = max * 10;
// 	char *escreve = malloc(sizeof(char) * tamanho_escreve);

// 	int tamanho_conteudo = max * 10 + 2 * strlen(lbl_arq);
// 	char *conteudo = malloc(sizeof(char) * tamanho_conteudo);

// 	// retira lixo de memoria
// 	for (i = 0; i < tamanho_conteudo; i++){
// 		conteudo[i] = '\0';
// 	}

// 	// retira lixo de memoria
// 	for (i = 0; i < tamanho_escreve; i++){
// 		escreve[i] = '\0';
// 	}

// 	printf("Escreva o conteudo do arquivo:\n\n");
// 	fgets(escreve, tamanho_escreve, stdin);

// 	for (q = 0; escreve[q] != '\0'; q++);

// 	// retira o caractere line feed do vetor
// 	escreve[q - 1] = '\0';

// 	k = 0;

// 	while(q > 0){

// 		bytes_ocupados = conta_bytes_ocupados(diretorio);

// 		f_bin = fopen (diretorio, "rb+");

// 		// encontra espaco vazio
// 		for (p = 0; p < bytes_ocupados; p++)
// 			fread(&c,sizeof(char),1,f_bin);

// 		strcat(conteudo, lbl_arq);

// 		if(q < blk_size - 6){
// 			strcat(conteudo, lbl_arq);

// 			for (j = 6; escreve[k] != '\0'; j++){
// 				conteudo[j] = escreve[k];
// 				k++;
// 			}

// 			for (i = 0; conteudo[i] != '\0'; i++)
// 				fwrite(&conteudo[i],sizeof(char),1,f_bin);

// 			fwrite(&conteudo[i],sizeof(char),1,f_bin);
// 		}

// 		else{
// 			// soma ponteiro do arquivo
// 			strcpy(lbl_arq, define_lbl_arq(lbl_arq));

// 			// concatena ponteiro no conteudo
// 			strcat(conteudo, lbl_arq);

// 			for (j = 6; j < blk_size; j++){
// 				conteudo[j] = escreve[k];
// 				k++;
// 			}

// 			for (j = 0; j < blk_size; j++)
// 				fwrite(&conteudo[j],sizeof(char),1,f_bin);

// 			// reseta conteudo
// 			for (j = 0; j < tamanho_conteudo; j++){
// 				conteudo[j] = '\0';
// 			}
// 		}

// 		fclose(f_bin);
// 		q = q - (blk_size - 6);
// 	}

// 	free(conteudo);
// 	free(escreve);
// 	return lbl_arq;
// }

// char* cria_arquivo(char *diretorio, char *nome_arquivo, char *lbl_dir, char *lbl_arq, int *bloco_livre){
// 	// variaveis para nome do arquivo
// 	int tamanho_bloco = blk_size;
// 	char* escreve_bloco = malloc(sizeof(char) * tamanho_bloco);

// 	// variaveis para conteudo do arquivo
// 	char* escreve_conteudo_arq = malloc(sizeof(char) * max3);

// 	// retirando lixo de memoria do vetor
// 	for (i = 0; i < max3; i++){
// 		escreve_conteudo_arq[i] = '\0';
// 	}

// 	// captura conteudo do arquivo
// 	printf("Escreva o conteudo do arquivo:\n\n");
// 	fgets(escreve_conteudo_arq, max3, stdin);
// 	printf("\n");

// 	// printf("escreve_conteudo_arq: %s\n", escreve_conteudo_arq);

// 	if (strlen(escreve_conteudo_arq) >= max3){
// 		getchar();
// 	}

// 	// retira caractere line feed e conta caracteres capturados
// 	for (i = 0; escreve_conteudo_arq[i] != '\0'; i++);
// 	escreve_conteudo_arq[i-1] = '\0';

// 	int qtd_chars = i;
	
// 	char* bloco = malloc(sizeof(char) * blk_size);
// 	bool flag = false;

// 	FILE *f_bin;
// 	f_bin = fopen(diretorio, "rb+");

// 	k = 0;
// 	p = 0;

// 	for (i = 0; i < blk_qtd; i++){

// 		// retira lixo de memoria do vetor
// 		for (j = 0; j < tamanho_bloco; j++){
// 			escreve_bloco[j] = '\0';
// 		}

// 		if (bloco_livre[k] == i && flag == false){

// 			k++;
// 			flag = true;

// 			// os 1os 3 bytes sao reservados para o label do diretorio
// 			strcat(escreve_bloco, lbl_dir);

// 			// os proximos 3 bytes para o label do arquivo
// 			strcat(escreve_bloco, lbl_arq);

// 			// o resto para o nome
// 			strcat(escreve_bloco, nome_arquivo);
// 			escreve_bloco[31] = '\0';

// 			for (j = 0; escreve_bloco[j] != '\0'; j++){
// 				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
// 			}
// 			// escreve \0
// 			fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);

// 			tamanho_bloco -= j + 1;

// 			for (j = 0; j < tamanho_bloco; j++){
// 				fread(&bloco[j],sizeof(char),1,f_bin);
// 			}

// 			tamanho_bloco = blk_size;
// 		}

// 		else if (bloco_livre[k] == i  && flag == true){

// 			k++;

// 			if (qtd_chars < blk_size - 6){
// 				strcat(escreve_bloco, lbl_arq);
// 				strcat(escreve_bloco, lbl_arq);

// 				for (j = 6; j < blk_size; j++){
// 					escreve_bloco[j] = escreve_conteudo_arq[p];
// 					p++;
// 				}

// 				for (j = 0; escreve_bloco[j] != '\0'; j++){
// 					fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
// 				}
// 				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);

// 				// free(bloco);
// 				// free(escreve_bloco);
// 				// free(escreve_conteudo_arq);
// 				// fclose(f_bin);

// 				// return lbl_arq;
// 			}

// 			else{

// 				strcat(escreve_bloco, lbl_arq);

// 				strcpy(lbl_arq, define_lbl_arq(lbl_arq));

// 				strcat(escreve_bloco, lbl_arq);

// 				for (j = 6; j < blk_size; j++){
// 					escreve_bloco[j] = escreve_conteudo_arq[p];
// 					p++;
// 				}

// 				for (j = 0; j < blk_size; j++){
// 					fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
// 				}

// 				qtd_chars -= (blk_size - 6);
// 			}

// 		}

// 		else{
// 			for (j = 0; j < blk_size; j++){
// 				fread(&bloco[j],sizeof(char),1,f_bin);
// 			}
// 		}
// 	}	
// 	printf("\n\tArquivo criado com sucesso!\n\n");

// 	free(bloco);
// 	free(escreve_bloco);
// 	free(escreve_conteudo_arq);
// 	fclose(f_bin);

// 	return lbl_arq;
// }

int cria_arquivo(char *diretorio, char *nome_arquivo, char *lbl_dir, char *lbl_arq, int *bloco_livre){
	// variaveis para nome do arquivo
	int tamanho = strlen(nome_arquivo) + 2 * strlen(lbl_dir);
	char* bloco = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * tamanho);

	// retira lixo de memoria do vetor
	for (j = 0; j < tamanho; j++){
		escreve_bloco[j] = '\0';
	}

	// os 1os 3 bytes sao reservados para o label do diretorio
	strcat(escreve_bloco, lbl_dir);

	// os proximos 3 bytes para o label do arquivo
	strcat(escreve_bloco, lbl_arq);

	// o resto para o nome
	strcat(escreve_bloco, nome_arquivo);
	
	if (tamanho >= blk_size - 1){
		tamanho = blk_size - 1;
		escreve_bloco[tamanho - 1] = '\0';
	}

	// for (i = 0; i < tamanho; i++){
	// 	printf("%x ", escreve_bloco[i] );
	// }

	// printf("\n\n");

	// for (i = 0; i < tamanho; i++){
	// 	printf("%x ", nome_arquivo[i] );
	// }

	FILE *f_bin;
	f_bin = fopen(diretorio, "rb+");

	if (verifica_hd(diretorio) == false){
		free(bloco);
		free(escreve_bloco);
		return -1;
	}

	k=0;

	for (i = 0; i < blk_qtd; i++){
		if (bloco_livre[k] == i){
			for (j = 0; escreve_bloco[j] != '\0'; j++){
				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
			}
			// escreve \0
			fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);

			break;
		}
		else{
			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_bin);
			}
		}
	}

	fclose(f_bin);
	free(bloco);
	free(escreve_bloco);
	return 1;
}

char *conteudo_arquivo(char *diretorio, char *lbl_arq, int *bloco_livre){
	// variaveis para nome do arquivo
	char* escreve_bloco = malloc(sizeof(char) * blk_size);

	// variaveis para conteudo do arquivo
	char* escreve_conteudo_arq = malloc(sizeof(char) * max3);
	char* bloco = malloc(sizeof(char) * blk_size);

	// retirando lixo de memoria do vetor
	for (i = 0; i < max3; i++){
		escreve_conteudo_arq[i] = '\0';
	}

	// captura conteudo do arquivo
	printf("Escreva o conteudo do arquivo:\n\n");
	fgets(escreve_conteudo_arq, max3, stdin);
	printf("\n");

	// printf("escreve_conteudo_arq: %s\n", escreve_conteudo_arq);

	if (strlen(escreve_conteudo_arq) >= max3){
		getchar();
	}

	// retira caractere line feed e conta caracteres capturados
	for (i = 0; escreve_conteudo_arq[i] != '\0'; i++);
	escreve_conteudo_arq[i-1] = '\0';

	int qtd_chars = i;

	FILE *f_bin;
	f_bin = fopen (diretorio, "rb+");

	if (verifica_hd(diretorio) == false){
		free(escreve_bloco);
		free(escreve_conteudo_arq);
		free(bloco);
		return "---";
	}

	i = 0;
	k = 0;
	p = 0;

	while (qtd_chars > 0 || i < blk_qtd){

		// reseta conteudo
		for (j = 0; j < blk_size; j++){
			escreve_bloco[j] = '\0';
			bloco[j] = '\0';
		}

		strcat(escreve_bloco, lbl_arq);

		if (bloco_livre[p] == i){
			p++;
			if(qtd_chars < blk_size - 6){
				strcat(escreve_bloco, lbl_arq);

				for (j = 6; escreve_conteudo_arq[k] != '\0'; j++){
					escreve_bloco[j] = escreve_conteudo_arq[k];
					k++;
				}

				// escreve_bloco[j] = '\0';
				// printf("escreve_bloco: %s\n", escreve_bloco);
				// printf("escreve_conteudo_arq: %s\n", escreve_conteudo_arq);
				// printf("escreve_bloco em hexa:\n\t");
				// for (j = 0; escreve_bloco[j] != '\0'; j++){
				// 	printf("%x ", escreve_bloco[j]);
				// }
				// printf("\n\n");

				for (j = 0; escreve_bloco[j] != '\0'; j++){
					fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
				}

				fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);

				break;
			}
			else{
				// soma lbl do arquivo
				strcpy(lbl_arq, define_lbl_arq(lbl_arq));

				// concatena lbl no conteudo
				strcat(escreve_bloco, lbl_arq);

				for (j = 6; j < blk_size; j++){
					escreve_bloco[j] = escreve_conteudo_arq[k];
					k++;
				}

				// escreve_bloco[j] = '\0';
				// printf("escreve_bloco: %s\n", escreve_bloco);
				// printf("escreve_conteudo_arq: %s\n", escreve_conteudo_arq);
				// printf("escreve_bloco em hexa:\n\t");
				// for (j = 0; j < blk_size; j++){
				// 	printf("%x ", escreve_bloco[j]);
				// }
				// printf("\n\n");

				for (j = 0; j < blk_size; j++){
					fwrite(&escreve_bloco[j],sizeof(char),1,f_bin);
				}
			}
			qtd_chars = qtd_chars - (blk_size - 6);
		}
		else{
			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_bin);
			}
		}
		i++;
	}

	fclose(f_bin);
	free(escreve_bloco);
	free(escreve_conteudo_arq);
	free(bloco);
	return lbl_arq;
}

void type_arquivo(char* diretorio, char* nome_arquivo, char* lbl_dir){
	char* bloco = malloc(sizeof(char) * blk_size);
	char* dir_encontrado = malloc(sizeof(char) * pmax);
	char* arq_encontrado = malloc(sizeof(char) * pmax);
	char* nome_encontrado = malloc(sizeof(char) * blk_size);

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
			arq_encontrado[i] = '\0';
		}

		for (i = 0; i < blk_size; i++){
			fread(&bloco[i],sizeof(char),1,f_bin);
		}

		for (i = 0; i < pmax; i++){
			dir_encontrado[i] =  bloco[i];
		}

		for (i = 0; i < pmax; i++){
			arq_encontrado[i] =  bloco[i+3];
		}

		for (i = 0; i < blk_size - 6; i++){
			nome_encontrado[i] =  bloco[i+6];
		}

		if (strcmp(lbl_dir, dir_encontrado) == 0){

			// printf("dir_encontrado: %s\n", dir_encontrado);

			if (strcmp(nome_arquivo, nome_encontrado) == 0){
				// printf("nome_encontrado: %s\n", nome_encontrado);
				break;
			}
		}
	}

	if (p >= blk_qtd){
		fclose(f_bin);
		free(dir_encontrado);
		free(arq_encontrado);
		free(nome_encontrado);
		free(bloco);

		printf("\n\tEste arquivo nao existe neste diterorio\n\n");
		return;
	}

	char* arq_aux = malloc(sizeof(char) * pmax);

	while(p < blk_qtd){

		// retira lixo
		for (i = 0; i < blk_size; i++){
			bloco[i] = '\0';
		}

		// retira lixo
		for (i = 0; i < pmax + 1; i++){
			arq_aux[i] = '\0';
		}

		for (i = 0; i < blk_size; i++){
			fread(&bloco[i],sizeof(char),1,f_bin);
		}

		for (i = 0; i < pmax; i++){
			arq_aux[i] = bloco[i];
		}

		if (strcmp(arq_encontrado, arq_aux) == 0){
			printf("\n\t");
			for (i = 6; i < blk_size; i++){
				if (bloco[i] != c_nulo){
					printf("%c", bloco[i]);
				}
			}

			for (i = 0; i < pmax; i++){
				arq_encontrado[i] = bloco[i+3];
			}
		}
		p++;
	}

	printf("\n\n");

	fclose(f_bin);
	free(dir_encontrado);
	free(arq_encontrado);
	free(nome_encontrado);
	free(arq_aux);
	free(bloco);
}

void remove_arquivo(char *diretorio, char *nome_arquivo, char *lbl_dir){
	char *bloco = malloc(sizeof(char) * blk_size);
	char *aux_nome = malloc(sizeof(char) * (blk_size));
	char *aux_lbl = malloc(sizeof(char) * (pmax));
	char *aux_lbl_arq = malloc(sizeof(char) * (pmax));

	int tamanho = max * 3;
	int *del_linha = malloc(sizeof(int) * tamanho);

	// retira lixo de memoria
	for (i = 0; i < tamanho; i++){
		del_linha[i] = -1;
	}

	for (j = 0; j < pmax + 1; j++){
			aux_lbl[j] = '\0';
			aux_lbl_arq[j] = '\0';
	}
	

	FILE *f_bin;
	f_bin = fopen (diretorio, "rb");

	for(i = 0; i < blk_qtd; i++){

		for (j = 0; j < blk_size; j++){
			bloco[j] = '\0';
			aux_nome[j] = '\0';
		}

		for (j = 0; j < pmax; j++){
			aux_lbl[j] = '\0';
		}

		for (j = 0; j < blk_size; j++){
			fread(&bloco[j],sizeof(char),1,f_bin);
		}

		// printf("bloco: %s\n", bloco);

		if(bloco[3] != 'D'){

			for(j = 0; j < pmax; j++){
				aux_lbl[j] = bloco[j];
			}

			// printf("aux_lbl: %s\n", aux_lbl);

			for(j = 0; bloco[j + 6] != '\0'; j++){
				aux_nome[j] = bloco[j + 6];
			}

			// printf("aux_nome: %s\n", aux_nome);

			if (strcmp(aux_lbl, lbl_dir) == 0 && strcmp(aux_nome, nome_arquivo) == 0){
				for(j = 0; j < pmax; j++){
					aux_lbl[j] = bloco[j + 3];
				}

				// printf("achou aux_lbl: %s\n", aux_lbl);


				del_linha[0] = i;

				break;
			}
		}
	}

	// printf("saiu do for!!!\n\n");
	// printf("aux_lbl_arq: %s\n", aux_lbl_arq);

	/*if (i == blk_qtd){
		printf("Arquivo nao existe ou nao esta neste diretorio\n\n");
	}*/

	k = 1;
	if (del_linha[0] != -1){
		// printf("entrou no if!!!\n\n");
		while(i < blk_qtd){

			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_bin);
			}

			// printf("bloco: %s\n", bloco);

			for(j = 0; j < pmax; j++){
				aux_lbl_arq[j] = bloco[j];
			}

			// printf("aux_lbl_arq: %s\n", aux_lbl_arq);

			if (strcmp(aux_lbl, aux_lbl_arq) == 0){
				for(j = 0; j < pmax; j++){
					aux_lbl[j] = bloco[j + 3];
				}

				del_linha[k] = i + 1;

				k++;
			}
			
			i++;
		}
	} else {
		printf("\n\tArquivo nao existe ou nao esta neste diretorio\n\n");
		return;
	}

	fclose(f_bin);

	/*for (i = 0; i < tamanho; i++){
		if (del_linha[i] != -1){
			printf("linha: %d\n", *(del_linha + i));
		}
	}*/

	FILE *f_del;
	f_del = fopen (diretorio, "rb+");

	k = 0;
	for(i = 0; i < blk_qtd; i++){

		// printf("i: %d\n", i);
		// printf("del_linha: %d\n", *(del_linha + k));

		if(del_linha[k] == i){
			for (j = 0; j < blk_size; j++){
				fwrite(&c_nulo,sizeof(char),1,f_del);
			}
			k++;

		} else {
			for (j = 0; j < blk_size; j++){
				fread(&bloco[j],sizeof(char),1,f_del);
			}
		}

	}


	fclose(f_del);
	free(bloco);
	free(aux_nome);
	free(aux_lbl);
	free(aux_lbl_arq);
	free(del_linha);

	printf("\n\tArquivo removido com sucesso!\n\n");
}

void renomeia_arquivo(char *diretorio, char *nome_arquivo, char *novo_nome, char *lbl_dir){
	char* bloco = malloc(sizeof(char) * blk_size);
	char* dir_encontrado = malloc(sizeof(char) * pmax);
	char* arq_encontrado = malloc(sizeof(char) * pmax);
	char* nome_encontrado = malloc(sizeof(char) * blk_size);
	char* escreve_bloco = malloc(sizeof(char) * blk_size);

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
			arq_encontrado[i] = '\0';
		}

		for (i = 0; i < blk_size; i++){
			fread(&bloco[i],sizeof(char),1,f_bin);
		}

		for (i = 0; i < pmax; i++){
			dir_encontrado[i] = bloco[i];
		}

		for (i = 0; i < pmax; i++){
			arq_encontrado[i] = bloco[i+3];
		}

		for (i = 0; i < blk_size - 6; i++){
			nome_encontrado[i] =  bloco[i+6];
		}

		if (strcmp(lbl_dir, dir_encontrado) == 0){

			// printf("\ndir_encontrado: %s\n", dir_encontrado);
			// printf("arq_encontrado: %s\n", arq_encontrado);
			// printf("nome_arquivo: %s\n", nome_arquivo);
			// printf("nome_encontrado: %s\n", nome_encontrado);
			// printf("p: %d\n\n", p );

			// for (i = 0; i < blk_size; i++){
			// 	printf("%x ", *(nome_arquivo + i));
			// }

			// printf("\n");

			// for (i = 0; i < blk_size; i++){
			// 	printf("%x ", *(nome_encontrado + i));
			// }

			if (strcmp(nome_arquivo, nome_encontrado) == 0){
				// printf("nome_encontrado: %s\n", nome_encontrado);
				break;
			}
		}
	}

	fclose(f_bin);

	if (p >= blk_qtd){
		free(bloco);
		free(dir_encontrado);
		free(arq_encontrado);
		free(nome_encontrado);
		free(escreve_bloco);
		
		printf("\n\tEste arquivo nao existe neste diterorio!\n\n");
		return;
	}

	f_bin = fopen(diretorio, "rb+");

	// retira lixo
	for (i = 0; i < blk_size; i++){
		escreve_bloco[i] = '\0';
	}

	strcat(escreve_bloco, lbl_dir);
	strcat(escreve_bloco, arq_encontrado);
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
	free(arq_encontrado);
	free(nome_encontrado);
	free(escreve_bloco);

	printf("\n\tArquivo %s renomeado com sucesso!\n\n", nome_arquivo);
}

#endif