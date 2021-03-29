#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "recursiveDescentParser.h"
#include "Stack.h"

struct StackNode {

	Node tn;
	String data;
	StackNode next;

};

StackNode new_StackNode(String s, StackNode next) {

	StackNode this = (StackNode) malloc(sizeof(struct StackNode));
	this -> tn = (Node) malloc(sizeof(struct Node));
	this -> data = s;
	this -> next = next;
	return this;

}

struct Stack {
	StackNode head;
};

Stack new_Stack() {
	Stack this = (Stack) malloc(sizeof(struct Stack));
	this -> head = NULL;
	return this;
}

Type getTypeFromString(String str) {

	if (!strcmp(str, "<E>")) {
		return E;
	} else if (!strcmp(str, "<ET>")) {
		return ET;
	} else if (!strcmp(str, "<C>")) {
		return C;
	} else if (!strcmp(str, "<CT>")) {
		return CT;
	} else if (!strcmp(str, "<S>")) {
		return S;
	} else if (!strcmp(str, "<ST>")) {
		return ST;
	} else if (!strcmp(str, "<A>")) {
		return A;
	} else if (!strcmp(str, "<X>")) {
		return X;
	} else {
		return TERMINAL;
	}

}

bool isEmpty(Stack s) {
	return s -> head == NULL;
}

void push(Stack s, String k, char c) {

	StackNode temp = new_StackNode(k, s -> head);
	temp -> tn = new_Node(getTypeFromString(k));
	temp -> tn -> c = c;

	s -> head = temp;
}

StackNode pop(Stack s) {

	if (s -> head == NULL) {
		printf("Stack is Empty");
		return NULL;
	}

	StackNode data = s -> head;
	s -> head = s -> head -> next;
	return data;
}

StackNode peek(Stack s) {
	return s -> head;
}
