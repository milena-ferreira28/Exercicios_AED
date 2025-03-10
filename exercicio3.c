
#include <stdio.h>
#include <stdlib.h>

//struct do nó da árvore
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

//cria novo nó da árvore
struct TreeNode* createNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

//calcula as somas das subárvores e armazena em um array dinâmico
int dfs(struct TreeNode* node, int** sums, int* index) {
    if (node == NULL) {
        return 0;
    }

    //calcula a soma da subárvore
    int leftSum = dfs(node->left, sums, index);
    int rightSum = dfs(node->right, sums, index);
    int subtreeSum = node->val + leftSum + rightSum;

    //armazena a soma no array dinâmico
    (*sums)[(*index)++] = subtreeSum;

    return subtreeSum;
}

//compara dois inteiros (usado pra ordenar)
int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

//encontra as somas das subárvores mais frequentes
int* findFrequentTreeSum(struct TreeNode* root, int* returnSize) {
    if (root == NULL) {
        *returnSize = 0;
        return NULL;
    }

    //array dinâmico para armazenar as somas das subárvores
    int* sums = (int*)malloc(10000 * sizeof(int)); // Tamanho inicial arbitrário
    if (!sums) {
        *returnSize = 0;
        return NULL;
    }

    int index = 0; //índice inicializado em 0 para armazenar as somas no array

    //calcula todas as somas das subárvores
    dfs(root, &sums, &index);

    //ordena o array de somas
    qsort(sums, index, sizeof(int), compare);

    //encontra a frequência máxima
    int maxFreq = 0;
    int currentFreq = 1;
    for (int i = 1; i < index; i++) {
        if (sums[i] == sums[i - 1]) {
            currentFreq++;
        } else {
            if (currentFreq > maxFreq) {
                maxFreq = currentFreq;
            }
            currentFreq = 1;
        }
    }
    if (currentFreq > maxFreq) {
        maxFreq = currentFreq;
    }

    //conta quantas somas tem a maior frequência
    int resultSize = 0;
    currentFreq = 1;
    for (int i = 1; i < index; i++) {
        if (sums[i] == sums[i - 1]) {
            currentFreq++;
        } else {
            if (currentFreq == maxFreq) {
                resultSize++;
            }
            currentFreq = 1;
        }
    }
    if (currentFreq == maxFreq) {
        resultSize++;
    }

    //aloca o array de resultados
    int* result = (int*)malloc(resultSize * sizeof(int));
    if (!result) {
        free(sums);
        *returnSize = 0;
        return NULL;
    }

    //preenche o array com as somas mais frequentes
    int resultIndex = 0;
    currentFreq = 1;
    for (int i = 1; i < index; i++) {
        if (sums[i] == sums[i - 1]) {
            currentFreq++;
        } else {
            if (currentFreq == maxFreq) {
                result[resultIndex++] = sums[i - 1];
            }
            currentFreq = 1;
        }
    }
    if (currentFreq == maxFreq) {
        result[resultIndex++] = sums[index - 1];
    }

    //libera a memória do array de somas
    free(sums);

    *returnSize = resultSize;
    return result;
}

//constroi a árvore a partir da entrada do usuário
struct TreeNode* buildTree() {
    int val;
    printf("Digite o valor da raiz (ou -1 para NULL): ");
    scanf("%d", &val);

    if (val == -1) {
        return NULL;
    }

    struct TreeNode* root = createNode(val);

    //fila para auxiliar na construção da árvore
    struct TreeNode** queue = (struct TreeNode**)malloc(10000 * sizeof(struct TreeNode*));
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        struct TreeNode* current = queue[front++];

        //lê o filho esquerdo
        printf("Digite o valor do filho esquerdo de %d (ou -1 para NULL): ", current->val);
        scanf("%d", &val);
        if (val != -1) {
            current->left = createNode(val);
            queue[rear++] = current->left;
        }

        //lê o filho direito
        printf("Digite o valor do filho direito de %d (ou -1 para NULL): ", current->val);
        scanf("%d", &val);
        if (val != -1) {
            current->right = createNode(val);
            queue[rear++] = current->right;
        }
    }

    free(queue);
    return root;
}

int main() {
    printf("Construa a árvore binária:\n");
    struct TreeNode* root = buildTree();

    int returnSize;
    int* result = findFrequentTreeSum(root, &returnSize);

    printf("Somas mais frequentes: ");
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    //libera a memória alocada
    free(result);

    return 0;
}