// Grupo Omega: 
// Pedro Moura				- 22.215.054-2
// Vinicius Calil Ferraz	- 22.215.064-1
// Yumi Sato Macedo			- 22.115.062-6

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "globais.c"
#include "hd_metodos.c"
#include "dir_metodos.c"
#include "arq_metodos.c"

void help(){
	printf("\n\tMenu de comandos:\n"
		"\n\tEste menu pode ser acessado com o comando 'help' ou '?'\n"
		"\n\tPrimeiro crie o HD, formate-o e selecione-o antes de qualquer coisa!\n"

		"\n\tFUNCIONALIDADE - SINTAXE DO COMANDO\n"

		"\n\tajuda (este menu) - help ou ?"
		"\n\tsair do sistema - ext ou exit"
		"\n"
		
		"\n\tcria HD - createhd [nome do hd]"
		"\n\tformatar HD - formathd [nome do hd]"
		"\n\texibir conteudo do HD - typehd [nome do hd]"
		"\n\tseleciona HD - selecthd [nome do hd]"
		"\n\tlista HDs - dirhd"
		"\n\tstatus do HD - statushd [nome do hd]"
		"\n\tremove HD - removehd [nome do hd]"
		"\n"
		
		"\n\tcria arquivo - create [nome do arquivo]"
		"\n\texibe arquivo - type [nome do arquivo]"
		"\n\tremove arquivo - remove [nome do arquivo]"
		// "\n\tedita arquivo - edit [nome do arquivo]"
		// "\n\tcopia arquivo - copy [arquivo existente] [novo arquivo]"
		// "\n\tmove arquivo - move [origem] [destino]"
		"\n\trenomeia arquivo - rename [arquivo existente] [novo nome]"
		"\n"

		// "\n\tlista diretorio - dir"
		"\n\tcria diretorio - createdir [nome do diretorio]"
		"\n\tremove diretorio - removedir [nome do diretorio]"
		// "\n\tcopiar diretorio - copydir [origem] [destino]"
		// "\n\tmove diretorio - movedir [origem] [destino]"
		"\n\trenomeia diretorio - renamedir [diretorio existente] [novo nome]"
		"\n"
		
		"\n\tNAVEGAR PELOS DIRETORIOS:"
		"\n\tvolta para diretorio raiz - cdr"
		"\n\tvolta um diretorio - cd .."
		"\n\tmuda diretorio - cd [nome do diretorio]"
		"\n\n");
}

int get_id_comando (char *comando){
	char aux[max]; // receberá apenas o comando sem parametro

	for (i = 0; comando[i] != '\0'; i++){
		aux[i] = comando[i];
		if (comando[i + 1] == '\0'){
			aux[i] = '\0';
		}
		if (comando[i] == ' '){
			aux[i] = '\0';
			break;
		}
	}

	if (strcmp(aux,"help") == 0) return 1;
	if (strcmp(aux,"?") == 0) return 1;
	if (strcmp(aux,"ext") == 0) return 2;
	if (strcmp(aux,"exit") == 0) return 2;
	if (strcmp(aux,"dirhd") == 0) return 3;
	// if (strcmp(aux,"dir") == 0) return 4;
	if (strcmp(aux,"cdr") == 0) return 5;

	if (strcmp(aux,"createhd") == 0) return 10;
	if (strcmp(aux,"formathd") == 0) return 11;
	if (strcmp(aux,"typehd") == 0) return 12;
	if (strcmp(aux,"selecthd") == 0) return 13;
	if (strcmp(aux,"statushd") == 0) return 14;
	if (strcmp(aux,"removehd") == 0) return 15;

	if (strcmp(aux,"create") == 0) return 20;
	if (strcmp(aux,"type") == 0) return 21;
	if (strcmp(aux,"remove") == 0) return 22;
	// if (strcmp(aux,"edit") == 0) return 23;
	// if (strcmp(aux,"copy") == 0) return 100;
	// if (strcmp(aux,"move") == 0) return 101;
	if (strcmp(aux,"rename") == 0) return 102;

	if (strcmp(aux,"createdir") == 0) return 30;
	if (strcmp(aux,"removedir") == 0) return 31;
	if (strcmp(aux,"cd") == 0) return 32;
	// if (strcmp(aux,"copydir") == 0) return 110;
	// if (strcmp(aux,"movedir") == 0) return 111;
	if (strcmp(aux,"renamedir") == 0) return 112;

	return -1;
}

char *get_parametro_extra(char *comando, int id_comando){
	char *aux;
	aux = malloc(sizeof(char) * max);	

	// retira lixo de memoria
	for (i = 0; i < max; i++){
		aux[i] = '\0';
	}

	for (i = 0; comando[i] != ' '; i++);
	for (j = i + 1; comando[j] != ' '; j++);

	k = 0;

	for (p = j + 1; comando[p] != '\0'; p++){
		aux[k] = comando[p];
		if (comando[p + 1] == '\0'){
			aux[k] = '\0';
		}
		k++;
	}

	return aux;
}

char *get_parametro(char *comando, int id_comando){
	char *aux;
	aux = malloc(sizeof(char) * max);

	// retira lixo de memoria
	for (i = 0; i < max; i++){
		aux[i] = '\0';
	}

	if (id_comando < 100){

		for (i = 0; comando[i] != ' '; i++);

		if (id_comando < 100){
			k = 0;

			for (j = i + 1; comando[j] != '\0'; j++){
				aux[k] = comando[j];
				if (comando[j + 1] == '\0'){
					aux[k] = '\0';
				}
				k++;
			}

			return aux;
		}
	}

	else {

		for (i = 0; comando[i] != ' '; i++);

		k = 0;

		for (p = i + 1; comando[p] != ' '; p++){
			aux[k] = comando[p];
			k++;
		}
	}

	return aux;
	
}

int main(){
	// mantem sistema rodando
	bool syscmd = true; 

	// guarda retorno das funcoes dos comandos
	bool existe;
	int aux;
	int id_comando;
	char resposta;

	// recebe comando + parametros
	char *comando = malloc(sizeof(char) * max2); 

	// guardam parametro separados do comando
	char *parametro = malloc(sizeof(char) * max);
	char *parametro_extra = malloc(sizeof(char) * max);

	// utilizada apos selecionar o hd
	char *hd_selecionado = malloc(sizeof(char) * max3);
	char *nome_hd = malloc(sizeof(char) * max);

	// variaveis para arquivos e diretorios
	int *bloco_livre = malloc(sizeof(int) * blk_qtd);
	char *atual_arq = malloc(sizeof(char) * pmax);
	char *atual_dir = malloc(sizeof(char) * pmax);
	char *aux_dir = malloc(sizeof(char) * pmax);

	// retira lixo de memoria
	for (i = 0; i < max; i++){
		nome_hd[i] = '\0';
	}

	for (i = 0; i < max3; i++){
		hd_selecionado[i] = '\0';
	}

	// retira lixo de memoria
	for (i = 0; i < pmax; i++){
		atual_arq[i] = '-';
		atual_dir[i] = '-';
		aux_dir[i] = '-';
	}

	help();

	while (syscmd){

		// retira lixo de memoria
		for (i = 0; i < max2; i++){
			comando[i] = '\0';
		}

		// retira lixo de memoria
		for (i = 0; i < max; i++){
			parametro[i] = '\0';
			parametro_extra[i] = '\0';
		}
		
		printf("meu_hd: %s# ", nome_hd);
		fgets(comando, max, stdin);

		id_comando = get_id_comando(comando);

		if (id_comando > 9){
			strcpy(parametro, get_parametro(comando, id_comando));
		}

		if (id_comando > 99){
			strcpy(parametro_extra, get_parametro_extra(comando, id_comando));
		}

		switch (id_comando){
			// exibe help
			case 1:
			help();
			break;

			// sai do sistema
			case 2:
			syscmd = false;
			printf("\n\tSaindo do sistema!\n\n");
			break;

			// lista hds
			case 3:
			lista_hds();
			break;

			// volta ao diretorio raiz
			case 5:
			if (hd_selecionado[0] == '\0'){
				printf("\n\tNenhum hd foi selecionado!\n\n");
			}
			else {
				strcpy(atual_dir, primeiro_dir);
				printf("\n\tDiretorio atual: raiz\n\n");
			}
			break;

			// cria HD virtual
			case 10:
			strcat(parametro, extensao);
			cria_hd(parametro);
			break;

			// formata HD virtual
			case 11:
			strcat(parametro, extensao);
			formata_hd(parametro);

			strcat(diretorio, parametro);
			cria_raiz(diretorio, dir_raiz, primeiro_dir);
			bloco_livre = conta_blocos_livres(diretorio, bloco_livre);
			strcpy(diretorio, reseta_dir);
			break;

			// type do conteudo do HD
			case 12:
			strcat(parametro, extensao);
			type_hd(parametro);
			break;

			// seleciona HD
			case 13:
			strcat(parametro, extensao);
			strcpy(nome_hd, parametro);
			strcat(diretorio, parametro);

			existe = verifica_hd(diretorio);
			if (existe){
				// passa diretorio para hd_selecionado e reseta diretorio
				strcpy(hd_selecionado, diretorio);
				strcpy(diretorio, reseta_dir);

				// reseta labels
				strcpy(atual_dir, primeiro_dir);
				strcpy(atual_arq, "---\0");

				bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);

				puts("\n\tHD selecionado com sucesso!\n");
			}
			break;

			// status do HD
			case 14:
			strcat(parametro, extensao);
			strcat(diretorio, parametro);

			bloco_livre = conta_blocos_livres(diretorio, bloco_livre);

			status_hd(diretorio, bloco_livre);
			strcpy(diretorio, reseta_dir);
			break;

			// remove HD
			case 15:
			strcat(parametro, extensao);
			strcat(diretorio, parametro);

			remove_hd(diretorio);

			strcpy(diretorio, reseta_dir);
			break;

			// cria arquivo no hd
			case 20:
			if (strcmp(atual_arq, "---") == 0){
				strcpy(atual_arq, encontra_lbl_arq(hd_selecionado));
				strcpy(atual_arq, define_lbl_arq(atual_arq));
			}
			// strcpy(atual_arq, cria_arquivo(hd_selecionado, parametro, atual_dir, atual_arq, bloco_livre));
			// strcpy(atual_arq, define_lbl_arq(atual_arq));

			if (cria_arquivo(hd_selecionado, parametro, atual_dir, atual_arq, bloco_livre) != -1){
				bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);
				strcpy(atual_arq, conteudo_arquivo(hd_selecionado, atual_arq, bloco_livre));
				strcpy(atual_arq, define_lbl_arq(atual_arq));
			}

			bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);
			break;

			// type do arquivo
			case 21:
			type_arquivo(hd_selecionado, parametro, atual_dir);
			break;

			// remove arquivo do hd
			case 22:
			remove_arquivo(hd_selecionado, parametro, atual_dir);
			bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);
			break;

			// cria diretorio
			case 30:
			strcpy(aux_dir, encontra_lbl_dir(hd_selecionado));
			strcpy(aux_dir, soma_lbl_dir(aux_dir));

			cria_diretorio(hd_selecionado, parametro, atual_dir, aux_dir, bloco_livre);
			bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);
			break;

			// remove diretorio
			case 31:
			if (strcmp(parametro, "raiz") == 0){
				printf("\n\tRemover diretorio raiz causa na formatacao do hd!"
					"\n\tConfirma?(s/n): ");
				scanf("%c", &resposta);
				getchar();

				if (resposta == 's'){
					formata_hd(nome_hd);
				}
			}

			else {
				remove_diretorio(hd_selecionado, parametro, atual_dir);
			}

			bloco_livre = conta_blocos_livres(hd_selecionado, bloco_livre);
			break;

			// navega pelos diretorios
			case 32:
			strcpy(atual_dir, navega_diretorio(hd_selecionado, parametro, atual_dir));
			// printf("\n\tDiretorio atual: %s\n\n", atual_dir);
			printf("\n\tDiretorio alterado\n\n");
			break;

			// renomeia arquivo
			case 102:
			renomeia_arquivo(hd_selecionado, parametro, parametro_extra, atual_dir);
			break;

			// renomeia diretorio
			case 112:
			renomeia_diretorio(hd_selecionado, parametro, parametro_extra, atual_dir);
			break;

			default:
			printf("\n\tComando invalido!\n\n");
			break;

		}
	}

	free(comando);
	free(parametro);
	free(parametro_extra);
	free(hd_selecionado);
	free(nome_hd);
	free(bloco_livre);
	free(atual_arq);
	free(atual_dir);
	free(aux_dir);

	return 0;
}