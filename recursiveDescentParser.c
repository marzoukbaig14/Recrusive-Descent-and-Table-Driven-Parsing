#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiveDescentParser.h"

State newState(String S) {

    // printf("in newstate");

    State this = (State) malloc(sizeof(struct State));
    this->expression = S;
    this -> idx = 0;
    

    return this;
}

char* getProductionType(Type T) {

    switch (T)
    {
    case E: return "E";
    case ET: return "ET";
    case C: return "C";
    case CT: return "CT";
    case S: return "S";
    case ST: return "ST";
    case A: return "A";
    case X: return "X"; 
    case TERMINAL: return "";
    default : return "";
    }
}

Node newNode(Type type) {

    Node this = (Node) malloc(sizeof(struct Node));
    this->centreNode = NULL;
    this->rightNode = NULL;
    this->leftNode = NULL;
    this->type = type;
    return this;
}

Node epsilon_function() {

    Node node = newNode(TERMINAL);
    node->c = '$';
    return node;
}

Node X_function(State s) {

    // printf("\n in X ");
    // printf("idx: ");
    // printf(s->idx);
    // printf("\n");
    // printf(s->expression);
    // printf(s->expression[s->idx]);
    printf("\n index in X-func: %d \n", s->idx);
    printf("\n expression in X: %c \n", s->expression[s->idx]);
    if (s->expression[s->idx] == 'a' || s->expression[s->idx] == 'b' ||
    s->expression[s->idx] == 'c' || s->expression[s->idx] == 'd' ||
    s->expression[s->idx] == 'e' || s->expression[s->idx] == 'f' ||
    s->expression[s->idx] == 'g' || s->expression[s->idx] == 'h' ||
    s->expression[s->idx] == 'i' || s->expression[s->idx] == 'j' ||
    s->expression[s->idx] == 'k' || s->expression[s->idx] == 'l' ||
    s->expression[s->idx] == 'm' || s->expression[s->idx] == 'n' ||
    s->expression[s->idx] == 'o' || s->expression[s->idx] == 'p' ||
    s->expression[s->idx] == 'q' || s->expression[s->idx] == 'r' ||
    s->expression[s->idx] == 's' || s->expression[s->idx] == 't' ||
    s->expression[s->idx] == 'u' || s->expression[s->idx] == 'v' ||
    s->expression[s->idx] == 'w' || s->expression[s->idx] == 'x' ||
    s->expression[s->idx] == 'y' || s->expression[s->idx] == 'z') 
    {

    Node node = newNode(X);
    Node child = newNode(TERMINAL);
    child->c = s->expression[s->idx];
    s->idx = s->idx+1;
    node->centreNode = child;
    return node;
    }
    return NULL;


}

Node operators(State s) {

    printf("\n index in O-func: %d \n", s->idx);
    printf("\n expression in O: %c \n", s->expression[s->idx]);

    if (s->expression[s->idx] == '.' || s->expression[s->idx] == '*' ||
    s->expression[s->idx] == '|') {
        
        Node node = newNode(TERMINAL);
        node->c = s->expression[s->idx];
        s->idx = s->idx+1;
        return node;
    }
    return NULL;

}

Node ET_function(State s) {

    
    // printf("\n in ET function");
    // printf(s->expression);
    printf("\n index in ET-func: %d \n", s->idx);
    printf("\n expression in ET: %c \n", s->expression[s->idx]);

    int ind = s->idx;

    if (s-> expression[s->idx] == '|') {
        Node node = newNode(ET);
        node->leftNode = operators(s);
        node->rightNode = E_function(s);

        if (node->rightNode != NULL) {
            return node;
        }
     
    }
    s-> idx = ind;
    Node node = newNode(ET);
    node->centreNode = epsilon_function();
    return node;
}

Node E_function(State S) {

    printf("\n index in E-func: %d \n", S->idx);
    printf("\n expression in E: %c \n", S->expression[S->idx]);

    Node leftChild = C_function(S);
    if (leftChild == NULL) {
        return NULL;
    }

    Node rightChild = ET_function(S);
    if (rightChild == NULL) {
        return NULL;
    } 

    Node node = newNode(E);
    node->leftNode = leftChild;
    node->rightNode = rightChild;
    // printf("in E_function\n");
    // printf(S->idx);
    return node;
}

Node CT_function(State s) {

    printf("\n index in CT-func: %d \n", s->idx);
    printf("\n expression in CT: %c \n", s->expression[s->idx]);

    int ind = s->idx;

    if (s-> expression[s->idx] == '.') {
        Node node = newNode(CT);
        node->leftNode = operators(s);
        node->rightNode = C_function(s);

        if (node->rightNode != NULL) {
            return node;
        }
     
    }
    s-> idx = ind;
    Node node = newNode(CT);
    node->centreNode = epsilon_function();
    return node;
}

Node C_function(State s) {

    printf("\n index in C-func: %d \n", s->idx);
    printf("\n expression in C: %c \n", s->expression[s->idx]);

    Node leftChild = S_function(s);
    if (leftChild == NULL) {
        return NULL;
    }

    Node rightChild = CT_function(s);
    if (rightChild == NULL) {
        return NULL;
    }
    
    Node node = newNode(C);
    node->leftNode = leftChild;
    node->rightNode = rightChild;
    return node;
}

Node ST_function(State s) {

    printf("\n index in ST-func: %d \n", s->idx);
    printf("\n expression in ST: %c \n", s->expression[s->idx]);

    int ind = s->idx;

    if (s-> expression[s->idx] == '*') {
        Node node = newNode(ST);
        node->leftNode = operators(s);
        node->rightNode = ST_function(s);

        if (node->rightNode != NULL) {
            return node;
        }
     
    }
    s-> idx = ind;
    Node node = newNode(ST);
    node->centreNode = epsilon_function();
    return node;
}



Node S_function(State s) {

    printf("\n index in S-func: %d \n", s->idx);
    printf("\n expression in S: %c \n", s->expression[s->idx]);
    
    Node leftChild = A_function(s);
    if (leftChild == NULL) {
        return NULL;
    }

    Node rightChild = ST_function(s);
    if (rightChild == NULL) {
        return NULL;
    }
    
    Node node = newNode(S);
    node->leftNode = leftChild;
    node->rightNode = rightChild;
    return node;

}

Node A_function(State s) {

    printf("\n index in X-func: %d \n", s->idx);
    printf("\n expression in newState: %c \n", s->expression[s->idx]);

    if (s->expression[s->idx] == '(') {

        s->idx = s->idx+1;
        Node node2 = E_function(s);
        if (node2 == NULL) {
            return NULL;
         }

    // if (s->expression[s->idx] != ')') {
    //     return NULL;
    // }

    s->idx = s->idx+1;

        Node n = newNode(A);
        n->leftNode = newNode(TERMINAL);
        n->leftNode->c = '(';
        n-> centreNode = node2;
        n->rightNode = newNode(TERMINAL);
        n->rightNode->c = ')';

        return n;
    }

    int saveidx = s->idx;

    Node node1 = X_function(s);
    if (node1 != NULL) {
        Node node = newNode(A);
        node->centreNode = node1;
        return node;
    }

    // s->idx = saveidx;
    return NULL;
   

}



void indent(int num_Tabs) {
	for (int i=0; i<num_Tabs; i++) {
		printf("  ");
	}
}

void makeTree(Node node, int num_Tabs) {

	if (node != NULL) {
		indent(num_Tabs);

		if (node -> type != TERMINAL) {
			printf("%s", getProductionType(node->type));
			printf("\n");
			makeTree(node->leftNode, num_Tabs+1);
			makeTree(node->centreNode, num_Tabs+1);
			makeTree(node->rightNode, num_Tabs+1);
		} else {
			printf("%c", node -> c);
			printf("\n");
		}
	}

}

void printTree (Node node) {
    printf("here");
    makeTree(node, 0);
}