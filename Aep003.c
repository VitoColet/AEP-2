#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>

void start_color(int id_cor) { // muda a cor do terminal
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), id_cor);
}

void gotoxy(int x, int y) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x-1, y-1});
}

int opcao_selecionada=0;

void format(int primeira_coluna, int ultima_coluna, int primeira_linha, int ultima_linha, char vetor_texto[][30], int tot_opcoes) {
	int conta_linhas2, conta_colunas2, conta_texto;
	
	start_color(113);
	
	for (conta_linhas2=primeira_linha; conta_linhas2<=ultima_linha; conta_linhas2++) {
		
		for (conta_colunas2=primeira_coluna; conta_colunas2<=ultima_coluna; conta_colunas2++) {
			gotoxy(conta_colunas2, conta_linhas2);
			
			if (conta_linhas2 == primeira_linha) {
				
				if (conta_colunas2 == primeira_coluna) {
					printf("%c", 201);
				}
				else if (conta_colunas2 != primeira_coluna && conta_colunas2 != ultima_coluna) {
					printf("%c", 205);
				}
				else if (conta_colunas2 == ultima_coluna) {
					printf("%c", 187);
				}
			}
			else if (conta_linhas2 == ultima_linha) {
				
				if (conta_colunas2 == primeira_coluna) {
					printf("%c", 200);
				}
				else if (conta_colunas2 != primeira_coluna && conta_colunas2 != ultima_coluna) {
					printf("%c", 205);
				}
				else if (conta_colunas2 == ultima_coluna) {
					printf("%c", 188);
				}
			}
			
			else if (conta_colunas2 == primeira_coluna || conta_colunas2 == ultima_coluna) {
				printf("%c", 186);
			}
			else if (conta_colunas2 != primeira_coluna && conta_colunas2 != ultima_coluna) {
				printf(" ");
			}	
			
		}
		
	}
	
	for (conta_texto=0; conta_texto<tot_opcoes;conta_texto++) {
		gotoxy(primeira_coluna+1, primeira_linha+conta_texto+1);
		printf("%s", vetor_texto[conta_texto]);
	}
	
	start_color(7);
}

int cria_menu(int coluna_inicial, int coluna_final, int linha_inicial, int linha_final,char vetor_opcoes[][30], int qntd_opcoes) {
	int conta_colunas, conta_linhas, indice_opcoes=0;
	int comprimento=coluna_final-coluna_inicial;
				
	start_color(113);
	
	for (conta_linhas=linha_inicial; conta_linhas<=linha_final; conta_linhas++) {
		
		for (conta_colunas=coluna_inicial; conta_colunas<=coluna_final; conta_colunas++) {
			
			gotoxy(conta_colunas, conta_linhas);
			
			if (conta_linhas == linha_inicial) { 
				
				if (conta_colunas == coluna_inicial) {
					printf("%c", 201);
				}
				else if (conta_colunas == coluna_final) {
					printf("%c", 187);
				}
				else if (conta_colunas != coluna_inicial && conta_colunas != coluna_final) {
					printf("%c", 205);
				}
		
			}
			else if (conta_linhas == linha_final) {
				if (conta_colunas == coluna_inicial) {
					printf("%c", 200);
				}
				else if (conta_colunas == coluna_final) {
					printf("%c", 188);
				}
				else if (conta_colunas != coluna_inicial && conta_colunas != coluna_final) {
					printf("%c", 205);
				}
			}
			else if (conta_linhas != linha_inicial && conta_linhas != linha_final) {
				if (conta_colunas == coluna_inicial || conta_colunas == coluna_final) {
					printf("%c", 186);	
				}		
				else if (conta_colunas != coluna_inicial && conta_colunas != coluna_final){
	
					printf(" ");
					
				}
			}
			
		}
				
	}
	
	while (TRUE){
	
		for (conta_linhas=0; conta_linhas<qntd_opcoes;conta_linhas++) {
			
			gotoxy(coluna_inicial+1, conta_linhas+linha_inicial+1);
			
			if (conta_linhas == opcao_selecionada) {
				start_color(23);
				printf("%s", vetor_opcoes[conta_linhas]);
				start_color(113);
			}
			else if (conta_linhas != opcao_selecionada) {
				printf("%s", vetor_opcoes[conta_linhas]);
			}
			
		}
			
		int tecla_pressionada[2] = {0, 0};
		
		tecla_pressionada[0] = getch();
		
		if (tecla_pressionada[0] == 224) {
			
			tecla_pressionada[1] = getch();
			
			if (tecla_pressionada[1] == 80) {
				opcao_selecionada++;
				
				if (opcao_selecionada == 5) {
					opcao_selecionada = 0;
				}
				
			}
			else if (tecla_pressionada[1] == 72) {
				opcao_selecionada--;
				
				if (opcao_selecionada == -1) {
					opcao_selecionada = 4;
				}
				
			}
		}
		else if (tecla_pressionada[0] == 13) {
			start_color(7);
			return opcao_selecionada;
			
		}
	}
	start_color(7);
	
}

void printr(char carac,int tot_caracs) { // printa um determinado caracter x vezes
	int execs;
	
	for (execs=0;execs<tot_caracs;execs++) {
		printf("%c", carac);
	}
}

int retorna_linhas(FILE *arq, char nome_arquivo[]) {
	int contador_de_linhas=0;
	char temp[30];
	
	arq = fopen(nome_arquivo, "r");
	
	while (!feof(arq)) {
		fgets(temp, 30, arq);
		
		contador_de_linhas++;
	}
	
	fclose(arq);
	
	return contador_de_linhas-1; // -1 para não contar a última linha vazia
}

void limpa_console(int ColunaC, int ColunaF, int linhaC, int linhaF) {
	int conta_coluna3, conta_linha3;
	
	for (conta_linha3=linhaC;conta_linha3<=linhaF; conta_linha3++) {
		
		for (conta_coluna3=ColunaC; conta_coluna3<=ColunaF; conta_coluna3++) {
			
			start_color(7);
			gotoxy(conta_coluna3, conta_linha3);
			printf(" ");
			start_color(113);
		}
		
	}
}

int procura_string(char nome_do_txt[], char string_procurada[30], int categoria, int linha_de_partida, int linha_de_parada) { // 0 nome | 1 senha
	
	FILE *arq;
	
	arq = fopen(nome_do_txt, "r");
	
	char tempo[30];
	
	int contador_=0;
	char string_maiuscula[30];
	strcpy(string_maiuscula, string_procurada);
	strupr(string_maiuscula);
	
	while (!feof(arq)) {
		contador_++;
		
		fgets(tempo, 30, arq);
		
		if (categoria == 0) {
			strupr(string_procurada);
		}
		
		if (strcmp(string_procurada, tempo) == 0 && contador_ >= linha_de_partida && contador_ <= linha_de_parada) {
			fclose(arq);
			return contador_;
		}
		
	}
	fclose(arq);
	return 0;
	
}

int main(void) {

	FILE *arquivo;
	FILE *arquivo_temp;
	
	arquivo = fopen("dados_usuarios.txt", "a");
	fclose(arquivo);
	arquivo = fopen("dados_temp.txt", "a");
	fclose(arquivo);
	
	char teste[][30] = {"Cadastrar usuario", "Consultar usuarios","Apagar usuario","Alterar usuario", "Sair"};
	char strings_de_cadastro[][30] = {"Nome:","", "Senha:", ""};
	char nome_temp[30];
	
	
	int qntd_itens;
	int cont=0;
	int opc=0;
	int tam= sizeof(teste)/sizeof(teste[0]);
	int coord_coluna;
	int coord_linha;
	int linha_atual=1;
	int contador=0;
	
	char nome_atual[100];
	char senha_atual[30]="";
	
	
	while (TRUE){
		opc = cria_menu(1, 20, 1, 7, teste, 5);
		
		if (opc == 0) {
			bool user_valido=false;
			while (!user_valido) {
				char descricao_nome[][30] = {"Min 5 Caracteres", "Max 10 Caracteres", "Nao usar acentos","Não usar espacos", "Nao usar caracteres especiais"};
				
				int tot_caractere_normal;
				int tamanho_nome;
				int indice_nome;
				
				arquivo = fopen("dados_usuarios.txt", "r");
				format(22, 41, 1, 7, strings_de_cadastro, 4);
				
				start_color(113);
				
				format(43, 73, 1, 7, descricao_nome, 5);
				
				start_color(113);
				
				do 
				{
					tot_caractere_normal=0;
					tamanho_nome = 0;
					gotoxy(28, 2);
					printr(' ', 13);
					gotoxy(28, 2);
					
					fgets(nome_temp, 30, stdin);
					strupr(nome_temp);
					
					tamanho_nome = strlen(nome_temp)-1;
					
					for (indice_nome=0; indice_nome < tamanho_nome; indice_nome++) {
						char car_atual = nome_temp[indice_nome];
						int car_atual_ascii= car_atual;
					
						
						gotoxy(20, 20);
						if (car_atual_ascii >= 65 && car_atual_ascii <= 90 || car_atual_ascii >= 97 && car_atual_ascii <= 122 ) {
							tot_caractere_normal++;
						}
				
					}
					
				}while (tamanho_nome < 5 || tamanho_nome > 10 || tot_caractere_normal != tamanho_nome );
				
				for (cont=0; cont<strlen(nome_temp)-1;cont++) {
					nome_temp[cont] += 5;
				}
				
				while (!feof(arquivo)) {
					fgets(nome_atual, 100, arquivo);
					
					if (strcmp(strupr(nome_atual), strupr(nome_temp)) == 0) {
						gotoxy(22, 7);
						printf("Nome esta em uso... ");
						user_valido=false;
						fclose(arquivo);
						getch();  // pede o clique de qualquer tecla após a aparição da mensagem 
						gotoxy(22, 7);
						
						start_color(7);
						printr(' ', 20); // apaga a mensagem de nome já cadastrado
						start_color(113);
						break;
					}
					else if (strcmp(strupr(nome_atual), strupr(nome_temp)) != 0) {
						user_valido=true;
					}
						
				}
				limpa_console(43, 73, 1, 7);
							
				if (user_valido){
					bool senha_valida=false;
					
					char descricao_senha[][30] = {"A senha deve conter", "1 Caracter maiusculo","1 Caractere minusculo", "1 Caractere especial", "5 a 8 Caracteres", "1 Numero"};
					
					format(43, 65, 1, 8, descricao_senha, 6);
					
					start_color(113);
					
					while (!senha_valida){
						gotoxy(29, 4);
						printr(' ', 12);
						gotoxy(29, 4);
						int qntd_caracs_senha;
						int indice_ascii=0;
						bool tem_maiusculo = false;
						bool tem_minusculo = false;
						bool tem_numero = false;
						bool tem_especial = false;
						bool tem_espaco = false;
						int tot_numeros =0;
						
						fgets(senha_atual, 30, stdin);
						
						qntd_caracs_senha = strlen(senha_atual)-1;
						
						int vetor_caracs_ascii[qntd_caracs_senha];
						
						for (indice_ascii; indice_ascii<qntd_caracs_senha; indice_ascii++) {
							
							vetor_caracs_ascii[indice_ascii] = senha_atual[indice_ascii];
							
						}
						
						for (indice_ascii=0; indice_ascii<qntd_caracs_senha ;indice_ascii++) {
							int ascii_atual = vetor_caracs_ascii[indice_ascii];
							
							if (ascii_atual >= 65 && ascii_atual <= 90) {
								tem_maiusculo=true;
							}
							else if (ascii_atual >= 97 && ascii_atual <= 122) {
								tem_minusculo=true;
							}
							else if (ascii_atual >= 48 && ascii_atual <= 57) {
								tem_numero=true;
							}
							else if (ascii_atual >= 33 && ascii_atual <= 47 || ascii_atual >= 58 && ascii_atual <= 64 || ascii_atual >= 91 && ascii_atual <= 96 || ascii_atual >= 123 && ascii_atual <= 126) {
								tem_especial=true;
							}	
							else if (senha_atual[indice_ascii] = ' ') {
								tem_espaco=true;
							}
							
						}
						
						if (tem_maiusculo && tem_minusculo && tem_numero && tem_especial && strlen(senha_atual)-1 >= 5 && strlen(senha_atual)-1 <= 8 && !tem_espaco) {
					
							senha_valida=true;
							
						}
						
					start_color(113);
					
					}
					
					for (cont=0; cont<strlen(senha_atual)-1; cont++) {
						senha_atual[cont]+= 5;
					}
				}
				
			}
			limpa_console(43, 65, 1, 8);
			gotoxy(23, 6);
			printf("CADASTRO COMPLETO.");
			getch();
			
			start_color(7);
			
			arquivo = fopen("dados_usuarios.txt", "a");
			
			fprintf(arquivo, nome_temp);
			fprintf(arquivo, senha_atual);
			fclose(arquivo);
		}
		else if (opc == 1) {
			char texto_cripto[][30] = {"[ 1 ] DADOS CRIPTOGRAFADOS", "[ 2 ] DADOS NORMAIS","", "APERTE 1 OU 2 NO TECLADO"};
			int key;
			
			format(23, 50, 1, 6, texto_cripto, 4);
			
			do{
			
				key = getch();
			
			}while (key != 49 && key != 50);
			
			limpa_console(23, 50, 1, 6);
			
			char vet_vazio[][30]={""};
			
			char temp_info[30];
			int cont_linha=0, qntd_linhas;
			int linha_atual, coluna_atual;
			int contador_colunas=0;
			int tot_execs=0;
			
			arquivo = fopen("dados_usuarios.txt", "r");
			
			qntd_linhas = retorna_linhas(arquivo, "dados_usuarios.txt");
			
			int qntd_colunas = qntd_linhas/6+1;
			
			start_color(113);
			
			int coluna_c=23, coluna_f=40, linha_c=1, linha_f=19;
			coluna_atual = coluna_c+1;
			linha_atual = linha_c+1;
	
				
			while (!feof(arquivo)) {
				
				cont_linha++;
				
				
				fgets(temp_info, 30, arquivo);
				
				
				if (cont_linha <= qntd_linhas) {
					tot_execs++;
					
					
					if (tot_execs == 1) {
						format(coluna_c, coluna_f, linha_c, linha_f, vet_vazio, 1);
						coluna_c=coluna_f+2;
						coluna_f= coluna_c+17;
					}
					
					
					gotoxy(coluna_atual, linha_atual);
					
					start_color(113);
					
					if (key == 50) {
						
						for (cont=0; cont<strlen(temp_info)-1; cont++) {
							temp_info[cont] -= 5;
						}
						
					}
					
					if (tot_execs % 2 != 0) {
						
						printf("Nome:%s", temp_info);
						
					}
					else if (tot_execs % 2 == 0) {

						
						printf("Senha:%s", temp_info);
						
					}
				
					start_color(7);
					
					linha_atual++;
					
					if (tot_execs % 2 == 0) {
						linha_atual++;
					}
					 if (tot_execs % 12 == 0 && tot_execs < qntd_linhas) {
						format(coluna_c, coluna_f, linha_c, linha_f, vet_vazio, 1);
						coluna_atual = coluna_c+1;
						linha_atual = 2;
						coluna_c=coluna_f+2;
						coluna_f=coluna_c+17;
					}		
				}
			}
			start_color(7);
		getch();
		}
		else if (opc == 2) {
			char info_procurada[30];
			char nome_procurado[30];
			char senha_procurada[30];
			char descricao_senha1[][30] = {"Confirme sua senha para", "apagar a sua conta"};
			
			int linha_nome=0;
			int linha_senha=0;
			int linha_nome_temp = -1;
			int linha_senha_temp = -1;
			
			format(22, 43, 1, 6, strings_de_cadastro, 4);
			start_color(113);
			
			do {
				gotoxy(28, 2);
				printr(' ', 15);
				gotoxy(28, 2);
				fgets(nome_procurado, 30, stdin);
				strupr(nome_procurado);
				
				for (cont=0; cont<strlen(nome_procurado)-1;cont++) {
					nome_procurado[cont] += 5;
				}
				
				if (strcmp(nome_procurado, " ") == 0) {
					start_color(7);
					break;
				}
			
				linha_nome = procura_string("dados_usuarios.txt", nome_procurado, 0, 1, 500);
				
				if (linha_nome == 0) {
					gotoxy(22, 7);
					printf(" Nome nao encontrado. ");
					getch();
				}
			
			
				limpa_console(22, 44, 7, 7);
				
			}while (linha_nome == 0);
			
			if (linha_nome != 0){
				
				format(45, 69, 1, 4, descricao_senha1, 2);
				start_color(113);
			
				do {
					gotoxy(29, 4);
					printr(' ', 14);
					
					gotoxy(29, 4);
					fgets(senha_procurada, 30, stdin);
					
					for (cont=0; cont<strlen(senha_procurada)-1;cont++) {
						senha_procurada[cont] += 5;
					}
					
					linha_senha = procura_string("dados_usuarios.txt", senha_procurada, 1, linha_nome, linha_nome+1);
					
				}while (linha_senha == 0);
				
				int ultima_linha1 = retorna_linhas(arquivo_temp, "dados_usuarios.txt");
				arquivo = fopen("dados_usuarios.txt", "r");
				arquivo_temp = fopen("dados_temp.txt", "w");
				
				
				int cont_temp=0;
				
				char info_maiusc[30];
				
				while (!feof(arquivo)) {
					cont_temp++;
					
					fgets(info_procurada, 30, arquivo);
					strcpy(info_maiusc, info_procurada);
					strupr(info_maiusc);
					
					if (strcmp(info_maiusc, strupr(nome_procurado)) == 0) {
						linha_nome_temp = cont_temp;
						linha_senha_temp = cont_temp+1;
					}
					
					if (cont_temp != linha_nome_temp && cont_temp != linha_senha_temp && cont_temp <= ultima_linha1) {
						
						fprintf(arquivo_temp, info_procurada);
						
					}
					
					
				}
				fclose(arquivo);
				fclose(arquivo_temp);
				
				ultima_linha1 = retorna_linhas(arquivo_temp, "dados_temp.txt");
				
				arquivo = fopen("dados_usuarios.txt", "w");
				arquivo_temp = fopen("dados_temp.txt", "r");
				
				int conta_linhas1 = 0;
				
				
				while (!feof(arquivo_temp)) {
					conta_linhas1++;
					
					fgets(info_procurada, 30, arquivo_temp);
					
					if (conta_linhas1 <= ultima_linha1) {
						
						fprintf(arquivo, info_procurada);
						
					}
					
				}
					
				gotoxy(45, 6);
				printf("Conta apagada com sucesso");
				fclose(arquivo);
				fclose(arquivo_temp);
				getch();
				limpa_console(45, 80, 6, 6);
				
				
				start_color(7);
			}
		}
		else if (opc == 3){
			while (TRUE){
				char nome_antigo[30];
				char car_atual_antigo;
				int car_antigo_ascii=0;
				int tamanho_nome_antigo=0;
				int indice_antigo=0;
				int tot_carac_antigo=0;
							
				format(22, 40, 1, 6, strings_de_cadastro, 4);
				
				do {
					start_color(113);
					gotoxy(28, 2);
					printr(' ', 11);
					gotoxy(28, 2);
					fgets(nome_antigo, 30, stdin);
					strupr(nome_antigo);
					tamanho_nome_antigo=strlen(nome_antigo)-1;
					
					for (indice_antigo=0;indice_antigo<tamanho_nome_antigo; indice_antigo++) {
						car_atual_antigo = nome_antigo[indice_antigo];
						car_antigo_ascii = car_atual_antigo;
						
						if (car_antigo_ascii >= 65 && car_antigo_ascii <= 90) {
							tot_carac_antigo++;
						}
						
					}
					
					
					
					start_color(7);
					
				}while (tamanho_nome_antigo < 5 || tamanho_nome_antigo > 10 || tot_carac_antigo != tamanho_nome_antigo);
				
			for (cont=0; cont<tamanho_nome_antigo; cont++) {
				nome_antigo[cont] += 5;
			}
			
			int linha_nome_antigo = procura_string("dados_usuarios.txt", nome_antigo, 0, 1, 500);
			int linha_senha1=0;
			char confirmacao_senha[30];
			
			
			if (linha_nome_antigo == 0) {
				gotoxy(22, 7);
				start_color(113);
				printf("Nome nao cadastrado.");
				getch();
				gotoxy(22, 7);
				start_color(7);
				printr(' ', 20);
			}
			else if (linha_nome_antigo != 0) {
				do {
					start_color(113);
					gotoxy(29, 4);
					printr(' ', 10);
					gotoxy(29, 4);
					fgets(confirmacao_senha, 30, stdin);
					start_color(7);
					
					for (cont=0; cont<strlen(confirmacao_senha)-1; cont++) {
						confirmacao_senha[cont] += 5;
					}
					
					linha_senha1 = procura_string("dados_usuarios.txt",  confirmacao_senha, 1, linha_nome_antigo, linha_nome_antigo+1);
					
					
				}while(linha_senha1 == 0);
			}
			
			char novo_nome[30];
			char texto_novo_nome[][30] = {"Novo nome:",""};
			int char_ascii1;
			int tot_ascii=0;
			int linha_novo_nome=0;
			bool validacao_novo_nome=false;
			
			if (linha_senha1 != 0) {
				limpa_console(22, 40, 1, 6);
				format(22, 43, 1, 3, texto_novo_nome, 2);
				
				
				do {
					tot_ascii=0;
					
					start_color(113);
					gotoxy(33, 2);
					printr(' ', 10);
					gotoxy(33, 2);
					fgets(novo_nome, 30, stdin);
					strupr(novo_nome);
					
					for (cont=0; cont<=strlen(novo_nome)-1; cont++) {
						char_ascii1 = novo_nome[cont];
						
						if (char_ascii1 >= 65 && char_ascii1 <= 90) {
							tot_ascii++;	
						}
						
					}
					if (tot_ascii != strlen(novo_nome)-1 || strlen(novo_nome)-1 < 5 || strlen(novo_nome)-1 > 10) {
						validacao_novo_nome = false;
					}
					else {
						validacao_novo_nome = true;
					}
					
					for (cont=0; cont<strlen(novo_nome)-1;cont++) {
						novo_nome[cont] += 5;
					}
					
					linha_novo_nome = procura_string("dados_usuarios.txt", novo_nome, 0, 1, 500);
					
					printf("%d", linha_novo_nome);
					
					
				}while (!validacao_novo_nome || linha_novo_nome != 0);
				
				
				arquivo = fopen("dados_usuarios.txt", "r");
				arquivo_temp = fopen("dados_temp.txt", "w");
				
				char place_holder[30];
				int conta_linhas3=0;
				
				int ultima_linha = retorna_linhas(arquivo, "dados_usuarios.txt");
				
				while (!feof(arquivo)) {
					conta_linhas3++;
					
					fgets(place_holder, 30, arquivo);
					
					
					if (conta_linhas3 <= ultima_linha) {
					
						if (conta_linhas3 == linha_nome_antigo) {
							
							fprintf(arquivo_temp, novo_nome);
							
						}
						else if (conta_linhas3 != linha_nome_antigo) {
							
							fprintf(arquivo_temp, place_holder);
						}
						
					}
				}
				
				fclose(arquivo);
				fclose(arquivo_temp);
				
				arquivo = fopen("dados_usuarios.txt", "w");
				arquivo_temp = fopen("dados_temp.txt", "r");
				conta_linhas3=0;
				
				while (!feof(arquivo_temp)){
					conta_linhas3++;
					
					fgets(place_holder, 30, arquivo_temp);
					
					if (conta_linhas3 <= ultima_linha) {
						fprintf(arquivo, place_holder);
					}
					
				}
				fclose(arquivo);
				fclose(arquivo_temp);
				
				limpa_console(22, 43, 1, 3);
				start_color(7);	
				break;
			}
			getch();		
			}
		}
  		else if (opc == 4) {
			gotoxy(1, 10);
			break;
		}
	system("cls");
	}
	return 0;
}
