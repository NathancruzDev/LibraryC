#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void startscreen(int *navigation);
void clear();
void showInvalidInput();

int main() {
    int navigation;

    while (1) {
        // Exibe o menu principal com ponteiro para acesso de endereco na memoria 
        startscreen(&navigation); 

            if (navigation == 1) {
             clear();

            FILE *file = fopen("dados.csv", "r");

            if (file == NULL) {
                printf("Error opening file\n");
                return 1;
            }
            // chamadando as "tabelas" do csv e adicionadno tamanho que ela pode ocupar em uma array ,101 pois conto com o /n que aloca espaco na memoria
            int ID;
            char BOOK[101];  
            char SECTION[51];

            // Buffer que meu c ira ler.(array de caracteres)
            char header[200];
            //e acessa o cabeçalho do csv contando com o tamanho dele ao pegar uma entrada padraom 
            fgets(header, sizeof(header), file);

            
            printf("====== Library ======\n");
            printf("%-5s %-40s %-30s\n", "ID", "BOOK", "SECTION");
            printf("-------------------------------------------------------------\n");

            // Lê os dados do arquivo CSV e imprime em tabela
            while (fscanf(file, "%d,%100[^,],%50[^\n]", &ID, BOOK, SECTION) == 3) {
                // Remover quebras de linha
                BOOK[strcspn(BOOK, "\n")] = 0;
                SECTION[strcspn(SECTION, "\n")] = 0;

    
                printf("%-5d %-40s %-30s\n", ID, BOOK, SECTION);
            }
            //ponteiro para fechar arquivo apos
            fclose(file);

            // Exibe a opção para retornar ao menu
            printf("\n[0] Return to menu\n");
            printf("What do you want to access? ");
            scanf("%d", &navigation);

            if (navigation == 0) {
                clear();
                continue;  // Retorna para o menu principal
            }
        }
        
        //Para sair do programa.
        else if (navigation == 99) {
           
            clear();
            printf("Exiting program...\n");
            sleep(3);
            break;  // Encerra o programa
        }
        else {
            // Entrada invalida
            showInvalidInput();  
        }
    }

    return 0;
}

// Função para exibir a tela inicial.
void startscreen(int *navigation) {
    printf("======= Local Library System ========\n");
    printf("[1] Library\n");
    printf("[99] Exit\n");
    printf("What do you want to access? ");
    scanf("%d", navigation);
}

// Função para limpar a tela.
void clear() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Função que exibe uma mensagem de erro e espera 3 segundos
void showInvalidInput() {
    printf("Invalid option. Try again");

    for (int i = 0; i < 3; i++) {
        printf("...");
        fflush(stdout);  // Força a saída para ser exibida imediatamente
        sleep(1);  // Aguarda 1 segundo
    }
    printf("\nProgram will exit after 3 seconds.\n");
    sleep(2);
}
