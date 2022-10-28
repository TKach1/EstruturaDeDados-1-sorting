#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/time.h>
#include <fstream>
//tkachi
#define MAX 100

typedef struct node //agora duplamente encadeado
{
    char nome[30];
    int rg;
    node *proximo;
    node *anterior;
}node;

typedef struct fila{
    char nome[MAX][30];
    int rg[MAX];
    int tam;
}fila;

typedef struct line{
    char nome[30];
    int rg;
}line;

int lineTam = 0;
const char* arq = "NomeRG10.txt";

struct manager{
    long int m, c;
};

void InsertionSort(node **head);
void SelectionSort(node **head);
void sortingMenu(node **head);

void S_search(fila lista, int rg);
void S_removeFromStart(fila *lista);
void S_removeFromEnd(fila *lista);
void S_removeFrom(fila *lista, int n);
void S_inserirAt(fila *lista, int n, char *nome, int rg);
void S_inserirAtEnd(fila *lista, char *nome, int rg);
void S_inserirAtStart(fila *lista, char *nome, int rg);
void S_listar(fila lista);
void S_docToList(fila *lista);

void inserir(node **head, int data, char *name, node **no);
void inserirAtStart(node **head, char *nome, int rg);
void inserirAtEnd(node **head, char *nome, int rg);
void inserirAt(node **head, int n, char *nome, int rg);
void removeFromStart(node **head);
void removeFromEnd(node **head);
void removeFrom(node **head, int n);
void docToList(node **head);
void listToDoc(node *head);
void search(node *head, fila lista);
void searchRG(node *head, int rg);
void listar(node *head);

void menu(node **head, fila *lista);
void desalocarAll(node *head);

double getTime(struct timeval begin);

int main()
{
    fila lista;
    lista.tam = 0;
    node *cabeca = NULL;
    menu(&cabeca, &lista);
    return 0;
}

void menu(node **head, fila *lista){
    int op;
    int n;
    char nome[30];
    int rg;
    printf("1-Insercao de um no no início\n2-Insercao de um no no fim\n3-Insercao de um no na posicao N\n4-Retirar um no do início\n5-Retirar um no no fim\n6-Retirar um no na posicao N\n7-Procurar um no\n8-Mostrar a lista\n9-Salvar a lista em um arquivo\n10-Ler a lista de um arquivo\n11-Sair do sistema\n:");
    scanf("%d", &op);
    switch (op) {
        case 1:
            printf("Insira o nome: ");
            std::cin >> nome;
            printf("Insira o RG: ");
            std::cin >> rg;
            inserirAtStart(head, nome, rg);
            S_inserirAtStart(lista, nome, rg);
            break;
        case 2:
            printf("Insira o nome: ");
            std::cin >> nome;
            printf("Insira o RG: ");
            std::cin >> rg;
            inserirAtEnd(head, nome, rg);
            S_inserirAtEnd(lista, nome, rg);
            break;
        case 3:
            printf("Insira o nome: ");
            std::cin >> nome;
            printf("Insira o RG: ");
            std::cin >> rg;
            std::cout << "insira a posicao: ";
            std::cin >> n;
            inserirAt(head, n, nome, rg);
            S_inserirAt(lista, n, nome, rg);
            break;
        case 4:
            removeFromStart(head);
            S_removeFromStart(lista);
            break;
        case 5:
            removeFromEnd(head);
            S_removeFromEnd(lista);
            break;
        case 6:
            std::cout << "insira a posicao: ";
            std::cin >> n;
            removeFrom(head, n);
            S_removeFrom(lista, n);
            break;
        case 7:
            search(*head, *lista);
            break;
        case 8:
            std::cout << "\n\n\n ENCADEADA\n";
            listar(*head);
            //std::cout << "\n\n\n SEQUENCIAL\n";
            //S_listar(*lista);
            break;
        case 9:
            listToDoc(*head);
            break;
        case 10:
            docToList(head);
            S_docToList(lista);
            break;
        case 20: //Teste para listas de dados maiores
            docToList(head);
            system("pause");
            //listar(*head);
            break;
        case 21:
            std::cout << "insira um RG para pesquisa: ";
            std::cin >> rg;
            searchRG(*head, rg);
            break;
        case 22:
            sortingMenu(head);
            break;
        default:
            std::cout << "Saindo..." <<  std::endl;
            desalocarAll(*head);
            return;
    }
    system("pause");
    menu(head, lista);
}

void QuickSort(){

}

void ShellSort(line *lista){
    for (int interval = lineTam / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < lineTam; i += 1) {
            line temp = lista[i];
            int j;
            for (j = i; j >= interval && lista[j - interval].rg > temp.rg; j -= interval) {
                lista[j] = lista[j - interval];
            }
            lista[j] = temp;
        }
    }
}

void BubbleSort(node **head){
    node* sorted = (*head)->proximo;
    node* current = *head;
    char nome[30];
    int rg;
    bool Swap = true;

    while(Swap){
        Swap = false;
        while(sorted != NULL){
            if(sorted->rg < current->rg){
                strcpy(nome, current->nome);
                rg = current->rg;
                current->rg = sorted->rg;
                strcpy(current->nome, sorted->nome);
                sorted->rg = rg;
                strcpy(sorted->nome, nome);
                Swap = true;
            }
            current = current->proximo;
            sorted = sorted->proximo;
        }
        sorted = (*head)->proximo;
        current = *head;
    }
}

void sortedInsert(node** head_ref, node* newNode)
{
    node* current;

    if (*head_ref == NULL)
        *head_ref = newNode;

    else if ((*head_ref)->rg >= newNode->rg) {
        newNode->proximo = *head_ref;
        newNode->proximo->anterior = newNode;
        *head_ref = newNode;
    }

    else {
        current = *head_ref;

        while (current->proximo != NULL && current->proximo->rg < newNode->rg)
            current = current->proximo;

        newNode->proximo = current->proximo;

        if (current->proximo != NULL)
            newNode->proximo->anterior = newNode;

        current->proximo = newNode;
        newNode->anterior = current;
    }
}

void InsertionSort(node **head){
    node* sorted = NULL;

    node* current = *head;
    while (current != NULL) {
        node* next = current->proximo;
        current->anterior = current->proximo = NULL;
        sortedInsert(&sorted, current);
        current = next;
    }

    *head = sorted;
}

void SelectionSort(node **head){
    node *nodeAtual= *head;
    node *nodeModular;
    char nome[30];
    int rg;
    node *menor;
    while(nodeAtual->proximo!=NULL){
        menor = nodeAtual;
        nodeModular = nodeAtual;
        while(nodeModular!=NULL){
            //std::cout << nodeModular->nome << " - ";
            if(nodeModular->rg < menor->rg){
                menor = nodeModular;
            }
            nodeModular = nodeModular->proximo;
        }
        //std::cout << std::endl;
        strcpy(nome, nodeAtual->nome);
        rg = nodeAtual->rg;
        nodeAtual->rg = menor->rg;
        strcpy(nodeAtual->nome, menor->nome);
        strcpy(menor->nome, nome);
        menor->rg = rg;

        nodeAtual = nodeAtual->proximo;
    }
}

line* LS_docToList(line *lista){
    char c;
    int tam=0;
    int i = 0, j = 0;
    char nome[30];
    char rg[8];
    FILE *fp;
    fp=fopen (arq,"r");
    if (!fp) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        while ((c = getc(fp)) != EOF) {
            if(c == '\n') {
                tam++;
            }
        }
    }

    lineTam = tam;
    lista = (line *) malloc(lineTam * sizeof(line));
    rewind(fp);
    memset(nome, 0, sizeof(nome));
    strcpy(rg, "");
    while ((c = getc(fp)) != EOF) {
        while(c != ','){
            nome[i] = c;
            i++;
            c = getc(fp);
        }
        i=0;
        c = getc(fp);
        while(c != '\n' && c != EOF) {
            rg[i] = c;
            i++;
            c = getc(fp);
        }
        i=0;
        if(j < lineTam){
            strcpy(lista[j].nome, nome);
            lista[j].rg = atoi(rg);
            j++;
        }
        memset(nome, 0, sizeof(nome));
        strcpy(rg, "0000000");
    }
    return lista;
}

void LS_listar(line *lista){
    for(int j = 0; j < lineTam; j++){
        printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista[j].nome, lista[j].rg, j+1);
    }
}

void sortingMenu(node **head){
    line *lista = nullptr;
    docToList(head);
    int op;
    //system("cls");
    std::cout << "1 - Selection Sort\n"
              << "2 - Insertion Sort\n"
              << "3 - Bubble Sort\n"
              << "4 - Shell Sort\n"
              << "5 - Quick sort\n"
              << "6 - Merge sort" << std::endl;
    std::cin >> op;
    switch(op){
        case 1:
            SelectionSort(head);
            listar(*head);
            break;
        case 2:
            InsertionSort(head);
            listar(*head);
            break;
        case 3:
            BubbleSort(head);
            listar(*head);
            break;
        case 4:
            lista = LS_docToList(lista);
            ShellSort(lista);
            LS_listar(lista);
            break;
        case 5:
            lista = LS_docToList(lista);
            ShellSort(lista);
            LS_listar(lista);
            break;
        default:
            std::cout << "opcao invalida";
            sortingMenu(head);
            break;
    }
}

void S_search(fila lista, int rg){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    bool r = false;
    g.c++;for(int i = 0; i < lista.tam; i++){g.c++;
        g.c++;if(lista.rg[i] == rg) {
            printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista.nome[i], lista.rg[i], i+1);
            printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
            r = true;
        }
    }
    g.c++;if(!r){
        std::cout << "\nNao fo possivel localizar o RG" << std::endl;
        printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    }
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_removeFromStart(fila *lista){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    lista->tam--;
    printf("\nRemovendo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[0], lista->rg[0], 1);
    g.c++;for(int i = 0; i < lista->tam; i++){g.c++;
        strcpy(lista->nome[i], lista->nome[i+1]);g.m++;
        lista->rg[i] = lista->rg[i+1];g.m++;
    }
    lista->rg[lista->tam+1] = NULL;g.m++;
    memset(lista->nome[lista->tam+1], 0, sizeof(lista->nome[lista->tam+1]));g.m++;
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_removeFromEnd(fila *lista){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    lista->tam--;
    printf("\nRemovendo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[lista->tam+1], lista->rg[lista->tam+1], lista->tam+1);
    lista->rg[lista->tam+1] = NULL;g.m++;
    memset(lista->nome[lista->tam+1], 0, sizeof(lista->nome[lista->tam+1]));g.m++;
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_removeFrom(fila *lista, int n){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    g.c++;if(n == 1){
        S_removeFromStart(lista);
        return;
    }
    g.c++;if(n == lista->tam+1){
        S_removeFromEnd(lista);
        return;
    }
    lista->tam--;
    n-= 2;
    printf("\nRemovendo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[n+1], lista->rg[n+1], n+2);
    g.c++;for(int i = n+1; i < lista->tam; i++){g.c++;
        strcpy(lista->nome[i], lista->nome[i+1]);g.m++;
        lista->rg[i] = lista->rg[i+1];g.m++;
    }
    lista->rg[lista->tam+1] = NULL;g.m++;
    memset(lista->nome[lista->tam+1], 0, sizeof(lista->nome[lista->tam+1]));g.m++;
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_inserirAt(fila *lista, int n, char *nome, int rg){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    lista->tam++;
    n--;
    g.c++;for(int i = lista->tam; i > n; i--){g.c++;
        strcpy(lista->nome[i], lista->nome[i-1]);g.m++;
        lista->rg[i] = lista->rg[i-1];g.m++;
    }
    lista->rg[n] = rg;g.m++;
    strcpy(lista->nome[n], nome);g.m++;
    printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[n], lista->rg[n], n+1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_inserirAtEnd(fila *lista, char *nome, int rg){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    lista->tam++;
    lista->rg[lista->tam-1] = rg;g.m++;
    strcpy(lista->nome[lista->tam-1], nome);g.m++;
    printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[lista->tam-1], lista->rg[lista->tam-1], lista->tam);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_inserirAtStart(fila *lista, char *nome, int rg){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    lista->tam++;
    g.c++;for(int i = lista->tam; i > 0; i--){g.c++;
        strcpy(lista->nome[i], lista->nome[i-1]);g.m++;
        lista->rg[i] = lista->rg[i-1];g.m++;
    }
    lista->rg[0] = rg;g.m++;
    strcpy(lista->nome[0], nome);g.m++;
    printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista->nome[0], lista->rg[0], 1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao SEQUENCIAL: %.9f\n\n", getTime(begin));
}

void S_listar(fila lista){
    for(int j = 0; j < lista.tam; j++){
        printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", lista.nome[j], lista.rg[j], j+1);
    }
}

void S_docToList(fila *lista){
    char c;
    char nome[30];
    char rg[8];
    int i = 0, j = lista->tam;
    FILE *fp;
    fp=fopen ("NomeRG10.txt","r");
    if (!fp) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        memset(nome, 0, sizeof(nome));
        strcpy(rg, "");
        while ((c = getc(fp)) != EOF) {
            while(c != ','){
                nome[i] = c;
                i++;
                c = getc(fp);
            }
            i=0;
            c = getc(fp);
            while(c != '\n' && c != EOF) {
                rg[i] = c;
                i++;
                c = getc(fp);
            }
            i=0;
            if(j < MAX){
                strcpy(lista->nome[j], nome);
                lista->rg[j] = atoi(rg);
                j++;
            }
            memset(nome, 0, sizeof(nome));
            strcpy(rg, "0000000");
        }
        lista->tam = j;
    }
}

// -=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-
// -=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-<Encadeada>-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-
// -=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-

void listToDoc(node *head){
    std::ofstream o("debug.txt");

    node *noatual;
    noatual = head;
    o << noatual->nome << "," << noatual->rg << std::endl;
    while(noatual->proximo != NULL){
        noatual = noatual->proximo;
        o << noatual->nome << "," << noatual->rg << std::endl;
    }
}

void docToList(node **head){
    node *no = NULL;
    char c;
    char nome[30];
    char rg[8];
    int i = 0;
    FILE *fp;
    if(*head != NULL){
        no = *head;
        while(no->proximo != NULL){
            no = no->proximo;
        }
    }
    fp=fopen ("NomeRG10.txt","r");
    if (!fp) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        memset(nome, 0, sizeof(nome));
        strcpy(rg, "");
        while ((c = getc(fp)) != EOF) {
            while(c != ','){
                nome[i] = c;
                i++;
                c = getc(fp);
            }
            i=0;
            c = getc(fp);
            while(c != '\n' && c != EOF) {
                rg[i] = c;
                i++;
                c = getc(fp);
            }
            i=0;
            inserir(head, atoi(rg), nome, &no);
            memset(nome, 0, sizeof(nome));
            strcpy(rg, "0000000");
        }
    }
}

void search(node *head, fila lista){
    int rg;
    std::cout << "insira um RG para pesquisa: ";
    std::cin >> rg;
    searchRG(head, rg);
    S_search(lista, rg);
}

void searchRG(node *head, int rg){
    struct timeval begin{};
    node *noatual;
    noatual = head;
    manager g;
    g.m = 0;
    g.c = 0;
    int i= 1;
    gettimeofday(&begin, 0);
    g.c++;while(noatual->proximo != NULL && noatual->rg != rg){g.c++;
        noatual = noatual->proximo;g.m++;
        i++;
    }
    g.c++;if(noatual->rg == rg){
        printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", noatual->nome, noatual->rg, i);
        printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    }else{
        std::cout << "\nNao fo possivel localizar o RG" << std::endl;
    }
    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void removeFrom(node **head, int n){
    struct timeval begin{};
    node *noatual = *head;
    node *aux;
    manager g;
    g.m = 0;
    g.c = 0;
    int i = n;
    gettimeofday(&begin, 0);
    g.c++;if(n == 1){
        removeFromStart(head);
        return;
    }else {
        n--;
        g.c++;while (noatual->proximo != NULL && n > 1) {g.c++;
            noatual = noatual->proximo;g.m++;
            n--;
        }
    }
    aux = noatual->proximo;g.m++;
    noatual->proximo = (noatual->proximo)->proximo;g.m++;
    printf("\nRemovendo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", aux->nome, aux->rg, i);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    free(aux);
    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void removeFromEnd(node **head){
    struct timeval begin{};
    node *noatual = *head;
    node *aux;
    int i = 1;
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    g.c++;while((noatual->proximo)->proximo != NULL){g.c++;
        noatual = noatual->proximo;g.m++;
        i++;
    }
    aux = noatual->proximo;g.m++;
    noatual->proximo = NULL;g.m++;
    printf("\nRemovendo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", aux->nome, aux->rg, i+1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    free(aux);
    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void removeFromStart(node **head){
    struct timeval begin{};
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    node *nonovo = *head;g.m++;
    printf("\nNome: %s\nRG: %d \nPosição na lista: %d\n", nonovo->nome, nonovo->rg, 1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    *head = (*head)->proximo;g.m++;
    free(nonovo);
    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void inserirAt(node **head, int n, char *nome, int rg){
    struct timeval begin{};
    node *noatual = *head;
    node *nonovo = (node *) malloc (sizeof(node));
    int i = n;
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    g.c++;if(n == 1){
        inserirAtStart(head, nome, rg);
        return;
    }else{
        g.c++;while(noatual->proximo != NULL && n-1>1){g.c++;
            noatual = noatual->proximo;g.m++;
            n--;
        }
    }
    nonovo->proximo = noatual->proximo;g.m++;
    noatual->proximo = nonovo;g.m++;
    strcpy(nonovo->nome, nome);g.m++;
    nonovo->rg = rg;g.m++;
    printf("\nInserindo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", nonovo->nome, nonovo->rg, i);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);

    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void inserirAtEnd(node **head, char *nome, int rg){
    struct timeval begin{};
    node *noatual = *head;
    node *nonovo = (node *) malloc (sizeof(node));
    int i= 1;
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    strcpy(nonovo->nome, nome);g.m++;
    nonovo->rg = rg;g.m++;
    g.c++;while(noatual->proximo != NULL){g.c++;
        noatual = noatual->proximo;g.m++;
        i++;
    }
    noatual->proximo = nonovo;g.m++;
    nonovo->proximo = NULL;g.m++;
    printf("\nInserindo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", nonovo->nome, nonovo->rg, i+1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);
    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void inserirAtStart(node **head, char *nome, int rg){
    struct timeval begin{};
    node *nonovo = (node *) malloc (sizeof(node));
    manager g;
    g.m = 0;
    g.c = 0;
    gettimeofday(&begin, 0);
    strcpy(nonovo->nome, nome);g.m++;
    nonovo->rg = rg;g.m++;
    nonovo->proximo = *head;g.m++;
    *head = nonovo;g.m++;
    printf("\nInserindo:\nNome: %s\nRG: %d \nPosição na lista: %d\n", nonovo->nome, nonovo->rg, 1);
    printf("\nMov: %ld\nComp: %ld\n", g.m, g.c);

    printf("Tempo de execucao ENCADEADA: %.9f\n\n", getTime(begin));
}

void inserir(node **head, int data, char *name, node **no)
{
    node *noatual = *no;
    node *nonovo;
    if(*head == NULL)
    {
        *head = (node *) malloc (sizeof(node));
        (*head)->rg = data;
        strcpy((*head)->nome, name);
        (*head)->proximo= NULL;
        (*head)->anterior= NULL;
        *no = *head;
    }
    else
    {
        while(noatual->proximo != NULL){
            noatual = noatual->proximo;
        }
        nonovo = (node *) malloc (sizeof (node));
        nonovo->rg = data;
        strcpy((nonovo)->nome, name);
        nonovo->proximo = NULL;
        nonovo->anterior = noatual;
        noatual->proximo = nonovo;
        *no = nonovo;
    }
}

void listar(node *head)
{
    node *noatual;
    noatual = head;
    printf("Nome: %s\n RG: %d \n\n", noatual->nome, noatual->rg);
    while(noatual->proximo != NULL){
        noatual = noatual->proximo;
        printf("Nome: %s\n RG: %d \n\n", noatual->nome, noatual->rg);
    }
    /*while(noatual->anterior != NULL){
        printf("Nome: %s\n RG: %d \n\n", noatual->nome, noatual->rg);
        noatual = noatual->anterior;
    }*/
}

void desalocarAll(node *head){
    node *noatual;
    noatual = head;
    while(noatual != NULL){
        node *paux = noatual;
        noatual = noatual->proximo;
        //printf("%p Destruido\n", paux);
        free(paux);
    }
}

double getTime(struct timeval begin){
    struct timeval end{};
    gettimeofday(&end, 0);
    long s = end.tv_sec - begin.tv_sec;
    long ms = end.tv_usec - begin.tv_usec;
    double elapsed = s + ms*1e-6;
    return elapsed;
}