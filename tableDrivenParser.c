#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "TableImplement.h"
#include "tableDrivenParser.h"
#include "Structs.h"
#include "Stack.h"

struct StackNode {

	Node tn;
	String data;
	StackNode next;

};

struct State2 {
	Stack stack;
	String expression;
	int idx;
};


State2 new_State2(String expression) {
	State2 this = (State2) malloc(sizeof(struct State2));
	this -> stack = new_Stack();
	push(this -> stack, "<E>", ' ');
	this -> expression = expression;
	this -> idx = 0;
	return this;
}

int get_Category_Index(String category, Table table) {
	for (int i=0; i<8; i++) {
		if (!strcmp(table -> category_symbols[i], category)) {
			return i;
		}
	}
	return -1;
}

int get_Symbol_Index(Table table, char c) {
	for (int i=0; i<32; i++) {
		if (table -> input_symbols[i] == c) {
			return i;
		}
	}
	return -1;
}

String get_Production(Table table, String category, char c) {


	//this is necessary because 0 is the same as null in c
	if (c == '\0') {
		return NULL;
	}

	int row = get_Category_Index(category, table);
	int col = get_Symbol_Index(table, c);

	int production = table -> table_driver[row][col];

	if (production == -1) {
		return NULL;
	}

	return table -> productions[production];
}

bool isTerminal(String category) {
	if (!strcmp(category, "(") || !strcmp(category, ")")
			|| !strcmp(category, "a") || !strcmp(category, "b")
			|| !strcmp(category, "c") || !strcmp(category, "d")
			|| !strcmp(category, "e") || !strcmp(category, "f")
			|| !strcmp(category, "g") || !strcmp(category, "h")
			|| !strcmp(category, "i") || !strcmp(category, "j")
			|| !strcmp(category, "k") || !strcmp(category, "l")
			|| !strcmp(category, "m") || !strcmp(category, "n")
            || !strcmp(category, "o") || !strcmp(category, "p")
            || !strcmp(category, "q") || !strcmp(category, "r")
            || !strcmp(category, "s") || !strcmp(category, "t")
            || !strcmp(category, "u") || !strcmp(category, "v")
            || !strcmp(category, "w") || !strcmp(category, "x")
            || !strcmp(category, "y") || !strcmp(category, "z")
            || !strcmp(category, "*") || !strcmp(category, "|")
            || !strcmp(category, ".")
            ){
		return true;
	}

	return false;
}


bool evaluate(String expression, Node* n) {

	State2 s = new_State2(expression);
	Table t = new_Table();
	*n = (peek(s -> stack) -> tn);
	//printf("%s", getTypeName(n -> type));
	//return true;


	while (true) {

		StackNode top = pop(s -> stack);
		String category = top -> data;
		Node node = top ->tn;
		node -> c = s -> expression [s -> idx];

		//printf("%s", getTypeName(node ->type));

		if (!strcmp(category, "e")) {
			//do nothing
			node -> c = 'e';
		}

		else if (isTerminal(category)) {

			if (category[0] == s -> expression [s -> idx]) {
				s -> idx ++;
			}
			else {
				*n = NULL; //return null tree
				return false;
			}

		}

		else {


			String production = get_Production(t, category, s -> expression[s -> idx]);

			if (production == NULL) {
				//try matching epsilon
				production = get_Production(t, category, 'eps');
			}

			if (production == NULL) {
				*n = NULL; //return null tree
				return false;
			}

			String str = "";

			int i=0;
			int child = 0;
			while(production[i]!='\0') {
				if (production[i]!=',') {

					//for appending a character to the end of a string
					size_t len = strlen(str);
					char *str2 = malloc(len + 1 + 1 ); //one for extra char, one for '/0'
					strcpy(str2, str);
					str2[len] = production[i];
					str2[len + 1] = '\0';
					str = str2;

				}
				else {
					push(s -> stack, str, ' ');
					str = "";
					if (child == 0) {
						node ->rightNode = peek(s -> stack) -> tn;
					}else if (child == 1) {
						node ->centreNode = peek(s -> stack) -> tn;
					}

					child++;

				}
				i++;
			}
			push(s -> stack, str, ' ');
			node ->leftNode = peek(s -> stack) -> tn;


		}

		//if we have finished reading string
		if (s -> expression[s -> idx] == '\0' && isEmpty(s -> stack)) {

			return true;

		}

	}

}
