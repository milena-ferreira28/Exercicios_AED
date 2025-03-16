#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dif;
    int pro;
} Job;

int compareJob(const void* a, const void* b){
    Job* jobA = (Job*)a;
    Job* jobB = (Job*)b;
    return jobA -> dif - jobB -> dif;
}

int compare(const void* a, const void* b){
  return (*(int*)a - *(int*)b);
}

int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize)  {
    Job jobs[difficultySize];
    for(int i=0; i< difficultySize; i++){
        jobs[i].dif =  difficulty[i];
        jobs[i].pro = profit[i];
    }

    qsort(jobs,  difficultySize, sizeof(Job), compare);

    int maxProfit = 0;
    for (int i = 0; i < difficultySize; i++) {
        if (jobs[i].pro > maxProfit) {
            maxProfit = jobs[i].pro;
        } else {
            jobs[i].pro = maxProfit;
        }
    }
    
    qsort(worker, workerSize, sizeof(int), compare);
    
    int totalProfit = 0;
    int currentJob = 0;
    
    for (int i = 0; i < workerSize; i++) {
        while (currentJob < difficultySize && jobs[currentJob].dif <= worker[i]) {
            currentJob++;
        }
        
        if (currentJob > 0) {
            totalProfit += jobs[currentJob - 1].pro;
        }
    }
    
    return totalProfit;
}

int main (){
    int jobs, workers;

    printf("Digite a quantidade de trabalhos a serem executados:\n");
    scanf("%d", &jobs);
    printf("Digite a quantidade de trabalhadores:\n");
    scanf("%d", &workers);

    int* difficulty = (int*)malloc(jobs * sizeof(int));
    int* profit = (int*)malloc(jobs * sizeof(int));
    int* ability = (int*)malloc(workers * sizeof(int));

    if (difficulty == NULL || profit == NULL || ability == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    for (int i=0; i<jobs; i++){
        printf("Digite a dificuldade do trabalho %d:\n", i+1);
        scanf("%d", &difficulty[i]);
        printf("Digite o lucro do trabalho %d:\n", i+1);
        scanf("%d", &profit[i]);
    }
    for (int i=0; i<workers; i++){
        printf("Digite a habilidade do trabalhador %d:\n", i+1);
        scanf("%d", &ability[i]);
    }
    
    int totalProfit = maxProfitAssignment(difficulty, jobs, profit, jobs, ability, workers);

    printf("O lucro total é: %d\n", totalProfit);

    free(difficulty);
    free(profit);
    free(ability);

    return 0;
}   

