#include <stdio.h>
#include <stdlib.h>

// struct para armazenar informações de uma classe
typedef struct {
    int pass;
    int total;
} ClasseInfo;

// struct para armazenar um nó da maxHeap
typedef struct {
    double ganho;
    ClasseInfo classeInfo;
} HeapNode;

// calcular o ganho ao adicionar um aluno extra
double calcularGanho(int pass, int total) {
    return (double)(pass + 1) / (total + 1) - (double)pass / total;
}

//  reorganizar a heap
void maxHeap(HeapNode* heap, int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < size && heap[left].ganho > heap[largest].ganho)
        largest = left;

    if (right < size && heap[right].ganho > heap[largest].ganho)
        largest = right;

    if (largest != i) {
        HeapNode temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        maxHeap(heap, size, largest);
    }
}

// extrair o nó com o maior ganho da heap
HeapNode extrairMax(HeapNode* heap, int* size) {
    HeapNode maxNode = heap[0];
    heap[0] = heap[--(*size)];
    maxHeap(heap, *size, 0);
    return maxNode;
}

// inserir um nó na heap
void insert(HeapNode* heap, int* size, HeapNode novoNode) {
    heap[(*size)++] = novoNode;
    int i = *size - 1;

    while (i > 0 && heap[(i - 1) / 2].ganho < heap[i].ganho) {
        HeapNode temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

//  calcular o max avarage ratio (taxa maxima de aprovação)
double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
    // Criar a maxHeap
    HeapNode* heap = (HeapNode*)malloc(classesSize * sizeof(HeapNode));
    int heapSize = 0;

    // inicializa a heap com os ganhos iniciais
    for (int i = 0; i < classesSize; i++) {
        double ganho = calcularGanho(classes[i][0], classes[i][1]);
        ClasseInfo classeInfo = {classes[i][0], classes[i][1]};
        HeapNode novoNode = {ganho, classeInfo};
        insert(heap, &heapSize, novoNode);
    }

    // distribui os alunos extras
    while (extraStudents--) {
        HeapNode maxNode = extrairMax(heap, &heapSize);
        int pass = maxNode.classeInfo.pass + 1;
        int total = maxNode.classeInfo.total + 1;
        double novoGanho = calcularGanho(pass, total);
        ClasseInfo novaClasseInfo = {pass, total};
        HeapNode novoNode = {novoGanho, novaClasseInfo};
        insert(heap, &heapSize, novoNode);
    }

    // calcular a taxa média de aprovação total
    double totalPassRatio = 0;
    while (heapSize > 0) {
        HeapNode maxNode = extrairMax(heap, &heapSize);
        totalPassRatio += (double)maxNode.classeInfo.pass / maxNode.classeInfo.total;
    }

    // libera a memória da heap
    free(heap);

    return totalPassRatio / classesSize;
}

int main (){

int classesSize, extraStudents;
    printf("Digite quantas classes vao ser lidas:\n");
    scanf("%d", &classesSize);

    printf("Digite quantos estudantes extras vao ser lidos:\n");
    scanf("%d", &extraStudents);


    int** classes = (int**)malloc(classesSize * sizeof(int*));
    for (int i = 0; i < classesSize; i++) {
        classes[i] = (int*)malloc(2 * sizeof(int)); 
    }

   for (int i=0; i<classesSize; i++){
    printf("\nDigite a quantidade de alunos aprovados da classe %d:\n", i+1);
    scanf("%d",&classes[i][0]);
    printf("Digite a quantidade de alunos total da classe %d:\n", i+1);
    scanf("%d",&classes[i][1]);
 
   }
    printf("\nMaximum Average Ratio: %.5f\n", maxAverageRatio(classes, classesSize, NULL, extraStudents));
    
    for (int i = 0; i < classesSize; i++) {
        free(classes[i]);
    }
    free(classes);

    return 0;
}