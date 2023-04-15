// Popa Bogdan Florin - Tema 2 SDA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    int level;
    unsigned char node_type;
    unsigned char red_value;
    unsigned char green_value;
    unsigned char blue_value;
    struct node *left_up, *right_up, *right_down, *left_down;
}TreeNode, *Tree;

typedef struct{
    unsigned char red, green, blue;
}pixel;

typedef struct QueueNode{
    Tree elem;
    struct QueueNode *next;
}QueueNode, *PQueueNode;

typedef struct Queue{
    PQueueNode front;
    PQueueNode rear;
}QueueSize, *Queue;

Queue createQueue() {
    Queue queue = (Queue)malloc(sizeof(QueueSize));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

int isQueueEmpty(Queue queue) {
    return (queue->front == NULL);
}

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

Tree dequeue(Queue queue) {
    if (isQueueEmpty(queue)) {
        // printf("Queue is empty.\n");
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

Tree front(Queue queue) {
    if (isQueueEmpty(queue)) {
        // printf("Queue is empty.\n");
        return NULL;
    }
    return queue->front->elem;
}

Tree rear(Queue queue) {
    if (isQueueEmpty(queue)) {
        // printf("Queue is empty.\n");
        return NULL;
    }
    return queue->rear->elem;
}

Tree initTree()
{
    Tree t = (Tree) malloc(sizeof(TreeNode));
    t->left_up = NULL;
    t->right_up = NULL;
    t->right_down = NULL;
    t->left_down = NULL;
    return t;
}

int get_mean(int x, int y, int size, int submatrixSize,  pixel (*pixelMap)[size]);

void solve(int x, int y, int size, int submatrixSize, Tree currentNode, 
pixel (*pixelMap)[size], int param){
    int mean = get_mean(x, y, size, submatrixSize, pixelMap);

    // printf("Current node address is %p@\n", currentNode);
    // printf("Current x and y are : %d %d\n", x, y);
    // printf("Current submatrix size is : %d\n", submatrixSize);
    // printf("Current mean is : %d\n", mean);

    //aflam la ce nivel se afla nodul curent;
    currentNode->level = size/submatrixSize;

    //daca media este mai mica sau egala decat pragul nu este
    //nevoie de inca o divizare, deci ne aflam la o frunza finala
    if (mean <= param) {
        // printf("Mean %d <= param %d so initialize a terminal leaf\n\n\n", mean, param);
        currentNode->node_type = 1;
        currentNode->red_value = pixelMap[x][y].red;
        currentNode->green_value = pixelMap[x][y].green;
        currentNode->blue_value = pixelMap[x][y].blue;

        currentNode->left_up = NULL;
        currentNode->right_up = NULL;
        currentNode-> right_down = NULL;
        currentNode->left_down = NULL;
    }
    //daca media este mai mare decat pragul atunci tipul nodului
    //curent va fi 0 si va fi nevoie de divizare
    else {
        // printf("Mean %d > param %d so initialize a non terminal node\n\n\n", mean, param);
        currentNode->node_type = 0;

        Tree leftUp = initTree();
        Tree rightUp = initTree();
        Tree rightDown = initTree();
        Tree leftDown = initTree();

        currentNode->left_up = leftUp;
        currentNode->right_up = rightUp;
        currentNode->right_down = rightDown;
        currentNode->left_down = leftDown;

        solve(x, y, size, submatrixSize / 2, currentNode->left_up, pixelMap, param);
        solve(x, y + submatrixSize / 2, size, submatrixSize / 2, currentNode->right_up, pixelMap, param);
        solve(x + submatrixSize / 2, y + submatrixSize / 2, size, submatrixSize / 2, currentNode->right_down, pixelMap, param);
        solve(x + submatrixSize / 2, y, size, submatrixSize / 2, currentNode->left_down, pixelMap, param);
    }
}

void fillPixelMap(int x, int y, int size, int submatrixSize, Tree currentNode,
pixel (*pixelMap)[size])
{
    if (currentNode->node_type == 0) {
        fillPixelMap(x, y, size, submatrixSize / 2, 
        currentNode->left_up, pixelMap);
        fillPixelMap(x, y + submatrixSize / 2, size, submatrixSize / 2,
         currentNode->right_up, pixelMap);
        fillPixelMap(x + submatrixSize / 2, y + submatrixSize / 2, size,
         submatrixSize / 2, currentNode->right_down, pixelMap);
        fillPixelMap(x + submatrixSize / 2, y, size, submatrixSize / 2,
        currentNode->left_down, pixelMap);
    } else if (currentNode->node_type == 1) {
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

int get_mean(int x, int y, int size, int submatrixSize,  pixel (*pixelMap)[size]) {
    int i, j, red = 0, green = 0, blue = 0, mean = 0;

    // printf("Mean function args x y subsize: %d %d %d\n", x, y, submatrixSize);

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
    // printf("means of R: %d   G: %d   B: %d   \n", red, green, blue);

    for (i = x; i < x + submatrixSize; i++) {
        for (j = y; j < y + submatrixSize; j++) {
            mean = mean + (red - pixelMap[i][j].red) * (red - pixelMap[i][j].red) +
            (green - pixelMap[i][j].green) * (green - pixelMap[i][j].green) +
            (blue - pixelMap[i][j].blue) * (blue - pixelMap[i][j].blue);
        }
    }

    mean = mean / (3 * submatrixSize * submatrixSize);
    return mean;
}

Tree* BFS(Tree root, int *index){
    // Tree t;
    if (root == NULL) {
        // printf("Arbore vid\n");
        return NULL;
    }

    Tree* quadTreeArray = (Tree*) malloc(sizeof(Tree));
    *index = 1;

    Queue queue = createQueue();
    enqueue(queue, root);
    quadTreeArray[(*index)-1] = root;

    while (!isQueueEmpty(queue)) {
        Tree node = dequeue(queue);
        // printf("Node type is : %d", node->node_type);
        if (node->node_type == 1){
            // printf("  {%d %d %d}", node->red_value, node->green_value, node->blue_value);
        }
        // printf("\n");

        if (node->left_up != NULL) {
            enqueue(queue, node->left_up);
            (*index)++;
            quadTreeArray = realloc(quadTreeArray, (*index) * sizeof(Tree));
            quadTreeArray[(*index)-1] = node->left_up;
            
        }
        if (node->right_up != NULL) {
            enqueue(queue, node->right_up);
            (*index)++;
            quadTreeArray = realloc(quadTreeArray, (*index) * sizeof(Tree));
            quadTreeArray[(*index)-1] = node->right_up;
        }
        if (node->right_down != NULL) {
            enqueue(queue, node->right_down);
            (*index)++;
            quadTreeArray = realloc(quadTreeArray, (*index) * sizeof(Tree));
            quadTreeArray[(*index)-1] = node->right_down;
        }
        if (node->left_down != NULL) {
            enqueue(queue, node->left_down);
            (*index)++;
            quadTreeArray = realloc(quadTreeArray, (*index) * sizeof(Tree));
            quadTreeArray[(*index)-1] = node->left_down;
        }
    }

    free(queue);

    // (*index)--;

    return quadTreeArray; 
}

int main(int argc, char **argv){

    if (strcmp(argv[1], "-c1") == 0 || strcmp(argv[1], "-c2") == 0) {

        int size, channelSize, i, j;
        char buffer[4];

        FILE *inputFile;
        inputFile = fopen("Exemple/exemplu0.ppm", "rb");

        //read the text data from the file
        fscanf(inputFile, "%s", buffer);
        fscanf(inputFile, "%d %d", &size, &size);
        fscanf(inputFile, "%d", &channelSize);

        // printf("%s@, %d %d\n", buffer, size, channelSize);

        //read the binary data from the file in the pixel matrix
        pixel pixelMap[size][size];
        fseek(inputFile, 1, SEEK_CUR);
        for (i = 0; i < size; i++) {
            for (j = 0; j < size; j++) {
                fread(&pixelMap[i][j].red, sizeof(unsigned char), 1, inputFile);
                fread(&pixelMap[i][j].green, sizeof(unsigned char), 1, inputFile);
                fread(&pixelMap[i][j].blue, sizeof(unsigned char), 1, inputFile);
            }
        }

        fclose(inputFile);


        Tree root = initTree();
        // printf("%p\n", root);

        int param = atoi(argv[2]);

        solve(0, 0, size, size, root, pixelMap, param);

        int arraySize;
        Tree* quadTreeArray = BFS(root, &arraySize);

        for (int i = 0; i < arraySize; i++) {
            // printf("At index %d node is of type %d", i, quadTreeArray[i]->node_type);
            if (quadTreeArray[i]->node_type == 1) {
                // printf(" {%d %d %d}", quadTreeArray[i]->red_value, quadTreeArray[i]->green_value, quadTreeArray[i]->blue_value);
            }
            // printf("  Level %d ", quadTreeArray[i]->level);
            // printf("\n");
        }

        //rezolvam cerinta 1
        if (strcmp(argv[1], "-c1") == 0) {
            int quadTreeLevels = quadTreeArray[arraySize-1]->level;

            i = 0;
            while (quadTreeArray[i]->node_type == 0) {
                i++;
            }
            int maxSide = size / (quadTreeArray[i]->level);

            int counter = 0;
            for (i = 0; i < arraySize; i++) {
                if (quadTreeArray[i]->node_type == 1) {
                    counter++;
                }
            }

            // printf("%d\n%d\n%d\n", quadTreeLevels, counter, maxSide); 
            FILE *outputFile;
            outputFile = fopen(argv[4], "wt");
            fprintf(outputFile, "%d\n%d\n%d\n", quadTreeLevels, counter, maxSide);
            fclose(outputFile);           

        } else if (strcmp(argv[1], "-c2") == 0) {
            FILE *outputFile;
            outputFile = fopen(argv[argc-1], "wb");

            fwrite(&size, sizeof(int), 1, outputFile);
            for (i = 0; i < arraySize; i++) {
                fwrite(&(quadTreeArray[i]->node_type), sizeof(unsigned char), 1, outputFile);
                if (quadTreeArray[i]->node_type == 1) {
                    fwrite(&(quadTreeArray[i]->red_value), sizeof(unsigned char), 1, outputFile);
                    fwrite(&(quadTreeArray[i]->green_value), sizeof(unsigned char), 1, outputFile);
                    fwrite(&(quadTreeArray[i]->blue_value), sizeof(unsigned char), 1, outputFile);
                }
            }

            fclose(outputFile);
        }
        
    } else if (strcmp(argv[1], "-d") == 0) {
        // printf("Solving the decompress\n");
        FILE *inputFile;
        inputFile = fopen(argv[2], "rb");

        unsigned int image_size;
        fread(&image_size, sizeof(unsigned int), 1, inputFile);

        int i = 0;
        Tree* quadArrayTree = (Tree*) malloc(sizeof(Tree));
        while (!feof(inputFile)) {
            quadArrayTree = realloc(quadArrayTree, (i + 1) * sizeof(Tree));
            quadArrayTree[i] = initTree();
            fread(&(quadArrayTree[i])->node_type, sizeof(unsigned char), 1, inputFile);
            if (quadArrayTree[i]->node_type == 1) {
                fread(&(quadArrayTree[i])->red_value, sizeof(unsigned char), 1, inputFile);
                fread(&(quadArrayTree[i])->green_value, sizeof(unsigned char), 1, inputFile);
                fread(&(quadArrayTree[i])->blue_value, sizeof(unsigned char), 1, inputFile);

            }
            i++;
        }

        fclose(inputFile);

        int arraySize = i-1;
        for (i = 0; i < arraySize; i++) {
            // printf("At index %d node is of type %d", i, quadArrayTree[i]->node_type);
            if (quadArrayTree[i]->node_type == 1) {
                // printf(" {%d %d %d}", quadArrayTree[i]->red_value, quadArrayTree[i]->green_value, quadArrayTree[i]->blue_value);
            }
            // printf("\n");
        }

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
        }

        // printf("%d \n",root->node_type);
        // printf("%d ",root->left_up->node_type);
        // printf(" {%d %d %d} ", root->left_up->red_value,root->left_up->green_value, root->left_up->blue_value);
        // printf("%d ",root->right_up->node_type);
        // printf(" {%d %d %d} ", root->right_up->red_value,root->right_up->green_value, root->right_up->blue_value);
        // printf("%d ",root->right_down->node_type);
        // printf(" {%d %d %d} ", root->right_down->red_value,root->right_down->green_value, root->right_down->blue_value);
        // printf("%d ",root->left_down->node_type);
        // printf(" {%d %d %d} \n\n\n", root->left_down->red_value,root->left_down->green_value, root->left_down->blue_value);

        pixel pixelMap[image_size][image_size];
        fillPixelMap(0, 0, image_size, image_size, root, pixelMap);
        int j;

        for (i = 0; i < image_size; i++) {
            for (j = 0; j < image_size; j++) {
                // printf("{%d %d %d} ", pixelMap[i][j].red, pixelMap[i][j].green, pixelMap[i][j].blue);
            }
            // printf("\n");
        }

        FILE *outputFile;
        outputFile = fopen(argv[3], "wb");
        char str[] = "P6\n";
        fwrite(str, sizeof(char), 3, outputFile);
        char str2[20];
        sprintf(str2, "%d", image_size);
        // printf("IMAGE SIZE AS STRING %s@\n", str2);
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
                fwrite(&(pixelMap[i][j].red), sizeof(unsigned char), 1, outputFile);
                fwrite(&(pixelMap[i][j].green), sizeof(unsigned char), 1, outputFile);
                fwrite(&(pixelMap[i][j].blue), sizeof(unsigned char), 1, outputFile);
            }
            // fwrite(newline, sizeof(char), 1, outputFile);
            
        }
        

    }



    return 0;
}