#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// Assigning values to each color
enum {
    RED = 0,
    BLUE = 1,
    WHITE = 2,
    YELLOW = 3,
    GREEN = 4,
    ORANGE = 5,
};

char color(int cc) {
    switch (cc) {
        case RED: return 'R';
        case BLUE: return 'B';
        case WHITE: return 'W';
        case GREEN: return 'G';
        case ORANGE: return 'O';
        default: return 'Y';
    }
}
// Initializing the 6 faces of a cube
typedef char face[2][2];
typedef struct {
    face f0;
    face f1;
    face f2;
    face f3;
    face f4;
    face f5;
} cube_t;

// Initializing the cube
void init_cube(cube_t* cube) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cube->f0[i][j] = color(RED);
            cube->f1[i][j] = color(BLUE);
            cube->f2[i][j] = color(WHITE);
            cube->f3[i][j] = color(YELLOW);
            cube->f4[i][j] = color(GREEN);
            cube->f5[i][j] = color(ORANGE);
        }
    }
}
// Rotate a face clockwise
void clockwise(face of,face cf){

    for (int i = 0; i < 2; i++)

    {
        for (int j = 0; j < 2; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[1][0];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[0][0];
                break;
                }
                else{
                    of[i][j] = cf[1][1];
                    break;
                }
                
            case 2:
                
                of[i][j]= cf[0][1];
                break;
            
            }
        }
        
    }
    
}
// Rotate a face anti-clockwise
void anti_clockwise(face of,face cf){

    for (int i = 0; i < 2; i++)

    {
        for (int j = 0; j < 2; j++)
        {
            switch (i+j)
            {
            case 0:
                of[i][j]= cf[0][1];
                break;
            case 1:
                if (i<j){
                of[i][j]= cf[1][1];
                break;
                }
                else{
                    of[i][j] = cf[0][0];
                    break;
                }
                
            case 2:
                
                of[i][j]= cf[1][0];
                break;
            
            }
        }
        
    }
    
}
// Function to print the cube faces one by one 
void printcube(cube_t* cube) {
    printf("Front face: %c %c\n", cube->f0[0][0], cube->f0[0][1]);
    printf("                   %c %c\n", cube->f0[1][0], cube->f0[1][1]);
    printf("Top face:   %c %c\n", cube->f1[0][0], cube->f1[0][1]);
    printf("                   %c %c\n", cube->f1[1][0], cube->f1[1][1]);
    printf("Left face:  %c %c\n", cube->f2[0][0], cube->f2[0][1]);
    printf("                   %c %c\n", cube->f2[1][0], cube->f2[1][1]);
    printf("Right face: %c %c\n", cube->f3[0][0], cube->f3[0][1]);
    printf("                   %c %c\n", cube->f3[1][0], cube->f3[1][1]);
    printf("Bottom face:%c %c\n", cube->f4[0][0], cube->f4[0][1]);
    printf("                   %c %c\n", cube->f4[1][0], cube->f4[1][1]);
    printf("Back Face:  %c %c\n", cube->f5[0][0], cube->f5[0][1]);
    printf("                   %c %c\n", cube->f5[1][0], cube->f5[1][1]);
}

void R(cube_t* cube) {
    face tf0, tf1, tf2, tf3, tf4, tf5;

    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));


    for (int i = 0; i < 2; i++) {
        cube->f0[i][1] = tf4[i][1];
        cube->f1[i][1] = tf0[i][1];
        cube->f4[i][1] = tf5[i][0];
        cube->f5[i][0] = tf1[1-i][1];
    }
    clockwise(cube->f3,tf3);
}

void Rp(cube_t* cube) {
    face tf0, tf1, tf2, tf3, tf4, tf5;

    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));

    for (int i = 0; i < 2; i++) {
        cube->f0[i][1] = tf1[i][1];
        cube->f1[i][1] = tf5[1-i][0];
        cube->f4[i][1] = tf0[i][1];
        cube->f5[i][0] = tf4[1-i][1];
    }
    anti_clockwise(cube->f3,tf3);
}


void U(cube_t* cube) {
    
    face tf0, tf1, tf2, tf3, tf4, tf5;

    
    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));

    
    for (int i = 0; i < 2; i++) {
        cube->f0[0][i] = tf3[0][i];
        cube->f2[0][i] = tf0[0][i];
        cube->f3[0][i] = tf5[0][i];
        cube->f5[0][i] = tf2[0][i];
    }
    clockwise(cube->f1,tf1);
}

void Up(cube_t* cube) {
    
    face tf0, tf1, tf2, tf3, tf4, tf5;

    
    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));

    anti_clockwise(cube->f1,tf1);
    for (int i = 0; i < 2; i++) {
        cube->f0[0][i] = tf2[0][i];
        cube->f2[0][i] = tf5[0][i];
        cube->f3[0][i] = tf0[0][i];
        cube->f5[0][i] = tf3[0][i];
    }
    
}
void F(cube_t* cube) {
    
    face tf0, tf1, tf2, tf3, tf4, tf5;

    
    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));

    clockwise(cube->f0,tf0);
    for (int i = 0; i < 2; i++) {
        cube->f1[1][i] = tf2[1-i][1];
        cube->f2[i][1] = tf4[0][i];
        cube->f3[i][0] = tf1[1][i];
        cube->f4[0][i] = tf3[1-i][0];
    }
    
}
void Fp(cube_t* cube) {
    
    face tf0, tf1, tf2, tf3, tf4, tf5;

    
    memcpy(tf0, cube->f0, sizeof(face));
    memcpy(tf1, cube->f1, sizeof(face));
    memcpy(tf2, cube->f2, sizeof(face));
    memcpy(tf3, cube->f3, sizeof(face));
    memcpy(tf4, cube->f4, sizeof(face));
    memcpy(tf5, cube->f5, sizeof(face));

    anti_clockwise(cube->f0,tf0);
    for (int i = 0; i < 2; i++) {
        cube->f1[1][i] = tf3[i][0];
        cube->f2[i][1] = tf1[1][1-i];
        cube->f3[i][0] = tf4[0][1-i];
        cube->f4[0][i] = tf2[i][1];
    }
    
}

void R2(cube_t* cube){
    R(cube);
    R(cube);
}
void U2(cube_t* cube){
    U(cube);
    U(cube);
}
void F2(cube_t* cube){
    F(cube);
    F(cube);
}

int check_solved(cube_t* cube){
    char x= cube->f0[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f0[i][j] != x){
                return 0;
            }
        }
        
    }
    char y= cube->f1[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f1[i][j] != y){
                return 0;
            }
        }
        
    }
    char z= cube->f2[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f2[i][j] != z){
                return 0;
            }
        }
        
    }
    char a= cube->f3[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f3[i][j] != a){
                return 0;
            }
        }
        
    }
    char b= cube->f4[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f4[i][j] != b){
                return 0;
            }
        }
        
    }
    char c= cube->f5[0][0];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (cube->f5[i][j] != c){
                return 0;
            }
        }
        
    }

    return 1;
     
}

typedef struct CubeState {
    cube_t cube;
    char moves[50];
} CubeState;

typedef struct QueueNode {
    CubeState state;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

void initQueue(Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
}

void enqueue(Queue* queue, CubeState state) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->state = state;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

CubeState dequeue(Queue* queue) {
    if (queue->front == NULL) {
        CubeState emptyState;
        return emptyState;
    }
    CubeState state = queue->front->state;
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return state;
}

bool isSolved(cube_t* cube) {
    return check_solved(cube);
}

void solvePocketCube(cube_t* initialCube, int * count) {
    Queue queue;
    initQueue(&queue);
    int a =1;
    CubeState initialState;
    initialState.cube = *initialCube;
    memset(initialState.moves, 0, sizeof(initialState.moves));

    enqueue(&queue, initialState);
    
    while (queue.front) {
        CubeState currentState = dequeue(&queue);
        
        if (isSolved(&currentState.cube)) {
            
            printf("Solved! Following are the moves in sequence: %s\n", currentState.moves);
            return;
        }
        CubeState childState = currentState;
        
        strcat(childState.moves, "R ");
        R(&childState.cube);
        enqueue(&queue, childState);
        
        
        CubeState childState1 = currentState;
        strcat(childState1.moves, "U ");
        U(&childState1.cube);
        enqueue(&queue, childState1);
        

        CubeState childState3 = currentState;
        strcat(childState3.moves, "F ");
        F(&childState3.cube);
        enqueue(&queue, childState3);

        CubeState childState4 = currentState;
        strcat(childState4.moves, "Rp ");
        Rp(&childState4.cube);
        enqueue(&queue, childState4);

        CubeState childState5 = currentState;
        strcat(childState5.moves, "Up ");
        Up(&childState5.cube);
        enqueue(&queue, childState5);

        CubeState childState6 = currentState;
        strcat(childState6.moves, "Fp ");
        Fp(&childState6.cube);
        enqueue(&queue, childState6);

        CubeState childState7 = currentState;
        strcat(childState7.moves, "R2 ");
        R2(&childState7.cube);
        enqueue(&queue, childState7);

        CubeState childState8 = currentState;
        strcat(childState8.moves, "U2 ");
        U2(&childState8.cube);
        enqueue(&queue, childState8);

        CubeState childState2 = currentState;
        strcat(childState2.moves, "F2 ");
        F2(&childState2.cube);
        enqueue(&queue, childState2);
        
        a+=9;

       
    }

    printf("Unable to solve the Pocket Cube.\n");
}

int main(int argc, char const *argv[]) {
    cube_t cube;
    int count = 0;
    init_cube(&cube);
    Fp(&cube);
    Fp(&cube);
    F(&cube);
    Fp(&cube);
    F(&cube);
    Up(&cube);
    Fp(&cube);
    F(&cube);
    Up(&cube);
    F(&cube);
    Up(&cube);
    Up(&cube);
    R2(&cube);
    printcube(&cube);

    printf("Calculating moves, please wait....\n");
    solvePocketCube(&cube, &count);

    return 0;
}