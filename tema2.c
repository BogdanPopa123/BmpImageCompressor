// Popa Bogdan Florin - Tema 2 SDA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Structura specifica pentru nodul din arborele de compresie
typedef struct node{
    int level;
    unsigned char node_type;
    unsigned char red_value;
    unsigned char green_value;
    unsigned char blue_value;
    struct node *left_up, *right_up, *right_down, *left_down;
}TreeNode, *Tree;

//structura specifica pentru pixel, care va stoca valorile RGB
//ale fiecarui pixel din imaginea PPM
typedef struct{
    unsigned char red, green, blue;
}pixel;

//implementarea unui element de coada, care este o lista simpla
typedef struct QueueNode{
    Tree elem;
    struct QueueNode *next;
}QueueNode, *PQueueNode;

//implementarea cozii
typedef struct Queue{
    PQueueNode front;
    PQueueNode rear;
}QueueSize, *Queue;

//functie de initializare a cozii
Queue createQueue() {
    Queue queue = (Queue)malloc(sizeof(QueueSize));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

//verific daca este coada goala
int isQueueEmpty(Queue queue) {
    return (queue->front == NULL);
}

//adaug un nou element in coada
void enqueue(Queue queue, Tree elem) {
    PQueueNode new_node = (PQueueNode)malloc(sizeof(QueueNode));
    new_node->elem = elem;
    new_node->next = NULL;
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
    } else {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
}

//scot ultimul element din coada
Tree dequeue(Queue queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    PQueueNode front_node = queue->front;
    Tree elem = front_node->elem;
    queue->front = front_node->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(front_node);
    return elem;
}

//returnez ce se afla in fata cozii
Tree front(Queue queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    return queue->front->elem;
}

//returnez ce se afla in spatele cozii
Tree rear(Queue queue) {
    if (isQueueEmpty(queue)) {
        return NULL;
    }
    return queue->rear->elem;
}

//initializez un nod al arborelui de compresie
Tree initTree()
{
    Tree t = (Tree) malloc(sizeof(TreeNode));
    t->left_up = NULL;
    t->right_up = NULL;
    t->right_down = NULL;
    t->left_down = NULL;
    t->red_value = 0;
    t->green_value = 0;
    t->blue_value = 0;
    t->node_type = 0;
    return t;
}

unsigned long long get_mean(int x, int y, int size, int submatrixSize,
pixel **pixelMap);

//functie recursiva pentru a construi arborele de compresie
void solve(int x, int y, int size, int submatrixSize, Tree currentNode,
pixel **pixelMap, int param){
    int mean = get_mean(x, y, size, submatrixSize, pixelMap);

    currentNode->level = (int)(log2(size/submatrixSize) + 1);

    //daca media este mai mica sau egala decat pragul nu este
    //nevoie de inca o divizare, deci ne aflam la o frunza finala
    if (mean <= param) {
        currentNode->node_type = 1;

        //calculam culoarea medie a blocului in care ne aflam
        //si o atribuim frunzei din arbore
        unsigned long long red_mean = 0, green_mean = 0, blue_mean = 0;
        int i, j;

        for (i = x; i < x + submatrixSize; i++) {
            for (j = y; j < y + submatrixSize; j++) {
                red_mean = red_mean + pixelMap[i][j].red;
                green_mean = green_mean + pixelMap[i][j].green;
                blue_mean = blue_mean + pixelMap[i][j].blue;
            }
        }

        red_mean = red_mean / (submatrixSize * submatrixSize);
        green_mean = green_mean / (submatrixSize * submatrixSize);
        blue_mean = blue_mean / (submatrixSize * submatrixSize);

        currentNode->red_value = red_mean;
        currentNode->green_value = green_mean;
        currentNode->blue_value = blue_mean;

        currentNode->left_up = NULL;
        currentNode->right_up = NULL;
        currentNode-> right_down = NULL;
        currentNode->left_down = NULL;
    }
    //daca media este mai mare decat pragul atunci tipul nodului
    //curent va fi 0 si va fi nevoie de divizare
    else {
        currentNode->node_type = 0;

        Tree leftUp = initTree();
        Tree rightUp = initTree();
        Tree rightDown = initTree();
        Tree leftDown = initTree();

        currentNode->left_up = leftUp;
        currentNode->right_up = rightUp;
        currentNode->right_down = rightDown;
        currentNode->left_down = leftDown;

        solve(x, y, size, submatrixSize / 2, currentNode->left_up,
        pixelMap, param);

        solve(x, y + submatrixSize / 2, size, submatrixSize / 2,
        currentNode->right_up, pixelMap, param);

        solve(x + submatrixSize / 2, y + submatrixSize / 2, size,
        submatrixSize / 2, currentNode->right_down, pixelMap, param);

        solve(x + submatrixSize / 2, y, size, submatrixSize / 2,
        currentNode->left_down, pixelMap, param);
    }
}

//functie cu care construim imaginea sub forma unei matrici, plecand
//de la arborele de compresie
void fillPixelMap(int x, int y, int size, int submatrixSize, Tree currentNode,
pixel **pixelMap)
{
    //daca nu ne aflam pe un nod final, vom imparti blocul
    //curent in 4 blocuri si vom apela recurisv functia
    if (currentNode->node_type == 0) {
        fillPixelMap(x, y, size, submatrixSize / 2, 
        currentNode->left_up, pixelMap);
        fillPixelMap(x, y + submatrixSize / 2, size, submatrixSize / 2,
         currentNode->right_up, pixelMap);
        fillPixelMap(x + submatrixSize / 2, y + submatrixSize / 2, size,
         submatrixSize / 2, currentNode->right_down, pixelMap);
        fillPixelMap(x + submatrixSize / 2, y, size, submatrixSize / 2,
        currentNode->left_down, pixelMap);
    } 
    //daca ne aflam pe o frunza finala a arborelui
    //atunci punem in blocul curent culorile specificate
    else if (currentNode->node_type == 1) {
        int i, j;
        for (i = x; i < x + submatrixSize; i++) {
            for (j = y; j < y + submatrixSize; j++) {
                pixelMap[i][j].red = currentNode->red_value;
                pixelMap[i][j].green = currentNode->green_value;
                pixelMap[i][j].blue = currentNode->blue_value;
            }
        }
    }
}

//functia de calculare a scorului de similaritate
unsigned long long get_mean(int x, int y, int size, int submatrixSize,
pixel **pixelMap) {
    int i, j;
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;

    for (i = x; i < x + submatrixSize; i++) {
        for (j = y; j < y + submatrixSize; j++) {
            red = red + pixelMap[i][j].red;
            green = green + pixelMap[i][j].green;
            blue = blue + pixelMap[i][j].blue;
        }
    }
    red = red / (submatrixSize * submatrixSize);
    green = green / (submatrixSize * submatrixSize);
    blue = blue / (submatrixSize * submatrixSize);

    for (i = x; i < x + submatrixSize; i++) {
        for (j = y; j < y + submatrixSize; j++) {
            mean = mean + (red - pixelMap[i][j].red) *
            (red - pixelMap[i][j].red) +
            (green - pixelMap[i][j].green) *
            (green - pixelMap[i][j].green) +
            (blue - pixelMap[i][j].blue) *
            (blue - pixelMap[i][j].blue);
        }
    }

    mean = mean / (3 * submatrixSize * submatrixSize);
    return mean;
}

//functie care calculeaza numarul de noduri dintr un quadtree
int countNodes(Tree root) {
    if (root == NULL) {
        return 0;
    } else {
        int count = 1;
        count += countNodes(root->left_up);
        count += countNodes(root->right_up);
        count += countNodes(root->right_down);
        count += countNodes(root->left_down);
        return count;
    }
}

//aceasta functie este folosita pentru a parcurge toate elementele
//din quadtree si a le returna intr un array
//parcuregerea se realizeaza pe latime
Tree* BFS(Tree root, int *index){
    if (root == NULL) {
        return NULL;
    }

    int counter = countNodes(root);

    Tree* quadTreeArray = (Tree*) malloc(counter * sizeof(Tree));
    *index = 1;

    Queue queue = createQueue();
    enqueue(queue, root);
    quadTreeArray[(*index)-1] = root;

    while (!isQueueEmpty(queue)) {
        Tree node = dequeue(queue);
        if (node->node_type == 1){
        }

        if (node->left_up != NULL) {
            enqueue(queue, node->left_up);
            (*index)++;
            quadTreeArray[(*index)-1] = node->left_up;
            
        }
        if (node->right_up != NULL) {
            enqueue(queue, node->right_up);
            (*index)++;
            quadTreeArray[(*index)-1] = node->right_up;
        }
        if (node->right_down != NULL) {
            enqueue(queue, node->right_down);
            (*index)++;
            quadTreeArray[(*index)-1] = node->right_down;
        }
        if (node->left_down != NULL) {
            enqueue(queue, node->left_down);
            (*index)++;
            quadTreeArray[(*index)-1] = node->left_down;
        }
    }
    free(queue);

    return quadTreeArray; 
}

int main(int argc, char **argv){

    //pentru cerintele 1 si 2 vom avea nevoie de contruirea
    //unui quadtree, iar aceste cerinte au acelasi numar
    //de argumente in linie de comanda, de aceea 
    //aceste doua cerinte vor fi tratate similar
    if (strcmp(argv[1], "-c1") == 0 || strcmp(argv[1], "-c2") == 0) {

        int channelSize, i, j;
        char buffer[4];
        unsigned int size;

        FILE *inputFile;
        inputFile = fopen(argv[3], "rb");

        //read the text data from the file
        fscanf(inputFile, "%s", buffer);
        fscanf(inputFile, "%d %d", &size, &size);
        fscanf(inputFile, "%d", &channelSize);

        //read the binary data from the file in the pixel matrix
        pixel **pixelMap = malloc(size * sizeof(pixel *));
        for (i = 0; i < size; i++) {
            pixelMap[i] = malloc(size * sizeof(pixel));
        }

        fseek(inputFile, 1, SEEK_CUR);
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fread(&pixelMap[i][j].red, sizeof(unsigned char),
                1, inputFile);
                fread(&pixelMap[i][j].green, sizeof(unsigned char),
                1, inputFile);
                fread(&pixelMap[i][j].blue, sizeof(unsigned char),
                1, inputFile);
            }
        }
        fclose(inputFile);

        Tree root = initTree();

        int param = atoi(argv[2]);

        //aceasta functie creeaza arborele de compresie
        solve(0, 0, size, size, root, pixelMap, param);

        int arraySize;
        Tree* quadTreeArray = BFS(root, &arraySize);

        //rezolvam cerinta 1
        if (strcmp(argv[1], "-c1") == 0) {
            //inaltimea arborelui este echivalenta cu inaltimea
            //la care se afla ultimul nod din arbore
            int quadTreeLevels = quadTreeArray[arraySize-1]->level;

            //primul nod de tip 1 va avea latura maxima, de aceea
            //il vom cauta
            i = 0;
            while (quadTreeArray[i]->node_type == 0) {
                i++;
            }
            int maxSide = size>>(quadTreeArray[i]->level - 1);

            //numaram nodurile de tip 1
            int counter = 0;
            for (i = 0; i < arraySize; i++) {
                if (quadTreeArray[i]->node_type == 1) {
                    counter++;
                }
            }

            //afisam rezultatele calculate pentru taskul c1
            FILE *outputFile;
            outputFile = fopen(argv[4], "wt");
            fprintf(outputFile, "%d\n%d\n%d\n", quadTreeLevels,
            counter, maxSide);
            fclose(outputFile);

        } else if (strcmp(argv[1], "-c2") == 0) {
            FILE *outputFile;
            outputFile = fopen(argv[argc-1], "wb");

            //pentru taskul c2, scriem fisierul in forma comprimata
            fwrite(&size, sizeof(unsigned int), 1, outputFile);
            for (i = 0; i < arraySize; i++) {
                fwrite(&(quadTreeArray[i]->node_type), sizeof(unsigned char),
                1, outputFile);
                if (quadTreeArray[i]->node_type == 1) {
                    fwrite(&(quadTreeArray[i]->red_value),
                    sizeof(unsigned char), 1, outputFile);

                    fwrite(&(quadTreeArray[i]->green_value),
                    sizeof(unsigned char), 1, outputFile);

                    fwrite(&(quadTreeArray[i]->blue_value),
                    sizeof(unsigned char), 1, outputFile);
                }
            }
            fclose(outputFile);
        }

        //free pixelmap and tree
        for (i = 0; i < size; i++) {
            free(pixelMap[i]);
        }
        free(pixelMap);

        for (i = 0; i < arraySize ; i++) {
            free(quadTreeArray[i]);
        }
        free(quadTreeArray);

        
    } else if (strcmp(argv[1], "-d") == 0) {

        //citim datele din fisierul comprimat si le punem
        //intr un array

        FILE *inputFile;
        inputFile = fopen(argv[2], "rb");

        unsigned int image_size;
        fread(&image_size, sizeof(unsigned int), 1, inputFile);

        int i = 0;
        Tree* quadArrayTree = (Tree*) malloc(sizeof(Tree));
        while (!feof(inputFile)) {
            quadArrayTree = realloc(quadArrayTree, (i + 1) * sizeof(Tree));
            quadArrayTree[i] = initTree();
            fread(&(quadArrayTree[i])->node_type, sizeof(unsigned char),
            1, inputFile);
            if (quadArrayTree[i]->node_type == 1) {
                fread(&(quadArrayTree[i])->red_value,
                sizeof(unsigned char), 1, inputFile);

                fread(&(quadArrayTree[i])->green_value,
                sizeof(unsigned char), 1, inputFile);

                fread(&(quadArrayTree[i])->blue_value,
                sizeof(unsigned char), 1, inputFile);

            }
            i++;
        }

        fclose(inputFile);

        int arraySize = i-1;

        //construim quadtree ul pe baza array ului furnizat de
        //fisierul de input
        Tree root = quadArrayTree[0];
        i = 1;
        int level = 1;
        root->level = level;
        if (root->node_type == 0) {
            Queue queue = createQueue();
            enqueue(queue, root);
            while (!isQueueEmpty(queue)) {
                Tree node = dequeue(queue);
                if(node->node_type == 0){
                    node->left_up = quadArrayTree[i++];
                    node->right_up = quadArrayTree[i++];
                    node->right_down = quadArrayTree[i++];
                    node->left_down = quadArrayTree[i++];

                    node->left_up->level = node->level + 1;
                    node->right_up->level = node->level + 1;
                    node->right_down->level = node->level + 1;
                    node->left_down->level = node->level + 1;

                    enqueue(queue, node->left_up);
                    enqueue(queue, node->right_up);
                    enqueue(queue, node->right_down);
                    enqueue(queue, node->left_down);
                }
            }
            free(queue);
        }

        //alocam memorie pentru fisierul continutul priopriu zis
        //al fisierului ppm si populam aceasta matrice
        //pe baza arborelui cuaternar
        pixel **pixelMap = malloc(image_size * sizeof(pixel *));
        for (i = 0; i < image_size; i++) {
            pixelMap[i] = malloc(image_size * sizeof(pixel));
        }
        fillPixelMap(0, 0, image_size, image_size, root, pixelMap);
        int j;

        //scriem datele in fisier

        FILE *outputFile;
        outputFile = fopen(argv[3], "wb");
        char str[] = "P6\n";
        fwrite(str, sizeof(char), 3, outputFile);
        char str2[20];
        sprintf(str2, "%d", image_size);
        fwrite(str2, sizeof(char), strlen(str2), outputFile);
        char space[] = " ";
        fwrite(space, sizeof(char), 1, outputFile);
        fwrite(str2, sizeof(char), strlen(str2), outputFile);
        char newline[] = "\n";
        fwrite(newline, sizeof(char), 1, outputFile);
        char channelSize[] = "255";
        fwrite(channelSize, sizeof(char), 3, outputFile);
        fwrite(newline, sizeof(char), 1, outputFile);

        for (i = 0; i < image_size; i++) {
            for (j = 0; j < image_size; j++) {
                fwrite(&(pixelMap[i][j].red), sizeof(unsigned char),
                1, outputFile);

                fwrite(&(pixelMap[i][j].green), sizeof(unsigned char),
                1, outputFile);

                fwrite(&(pixelMap[i][j].blue), sizeof(unsigned char),
                1, outputFile);
            }       
        }

        //free pixelmap and tree
        for (i = 0; i < image_size; i++) {
            free(pixelMap[i]);
        }
        free(pixelMap);

        for (i = 0; i <= arraySize; i++) {
            free(quadArrayTree[i]);
        }
        free(quadArrayTree);
        
        fclose(outputFile);
    }

    return 0;
}