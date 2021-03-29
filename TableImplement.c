#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TableImplement.h"
#include "Structs.h"
#include "Stack.h"
#include <stdbool.h>




void fill_Input_Symbols(Table table) {
	
    table -> input_symbols[0] = "a";
	table -> input_symbols[1] = "b";
	table -> input_symbols[2] = "c";
	table -> input_symbols[3] = "d";
	table -> input_symbols[4] = "e";
	table -> input_symbols[5] = "f";
	table -> input_symbols[6] = "g";
	table -> input_symbols[7] = "h";
	table -> input_symbols[8] = "i";
	table -> input_symbols[9] = "j";
	table -> input_symbols[10] = "k";
	table -> input_symbols[11] = "l";
	table -> input_symbols[12] = "m";
	table -> input_symbols[13] = "n";
	table -> input_symbols[14] = "o";
	table -> input_symbols[15] = "p";
	table -> input_symbols[16] = "q";
	table -> input_symbols[17] = "r";
	table -> input_symbols[18] = "s";
	table -> input_symbols[19] = "t";
	table -> input_symbols[20] = "u";
	table -> input_symbols[21] = "v";
	table -> input_symbols[22] = "w";
	table -> input_symbols[23] = "x";
	table -> input_symbols[24] = "y";
	table -> input_symbols[25] = "z";
	table -> input_symbols[26] = '(';
	table -> input_symbols[27] = ')';
	table -> input_symbols[28] = '*';
	table -> input_symbols[29] = '|';
    table -> input_symbols[30] = '.';
	table -> input_symbols[31] = 'eps';
}


void fill_Category_Symbols(Table table) {
	table -> category_symbols[0] = "<E>";
	table -> category_symbols[1] = "<ET>";
	table -> category_symbols[2] = "<C>";
	table -> category_symbols[3] = "<CT>";
	table -> category_symbols[4] = "<S>";
	table -> category_symbols[5] = "<A>";
	table -> category_symbols[6] = "<ST>";
	table -> category_symbols[7] = "<X>";
}

//productions are stored in reverse order because
//they will be pushed to stack in reverse order
void fill_Productions_In_Reverse_Order(Table table) {

    for (int i =0; i< 26; i++) {

        table->productions[i] = table->input_symbols[i];
    }

    table -> productions[26] = 'eps';
    table -> productions[27] = '<X>';
	table -> productions[28] = "),<E>,(";
	table -> productions[29] = "<ST>,*";
	table -> productions[30] = "<ST>,<A>";
	table -> productions[31] = "<C>.";
	table -> productions[32] = "<CT>,<S>";
	table -> productions[33] = "<E>,|";
	table -> productions[34] = "<ET>,<C>";
}

void fill_Row_Table_Driver(Table table, int row, int from, int to, int val) {
	for (int i=from; i<=to; i++) {
		table -> table_driver[row][i] = val;
	}
}

void fill_Table_Driver(Table table) {
	//fill row 0
	fill_Row_Table_Driver(table, 0, 0, 25, 34);

    fill_Row_Table_Driver(table, 0, 26, 27, 34);
    fill_Row_Table_Driver(table, 0, 28, 34, -1);

    // fill row 1
    table->table_driver[1][29] = 33;
    table->table_driver[1][30] = 26;
    fill_Row_Table_Driver(table, 1, 0, 28, -1);
    fill_Row_Table_Driver(table, 1, 31, 34, -1);

    //fill row 2
    fill_Row_Table_Driver(table, 2, 0, 25, 34);

    fill_Row_Table_Driver(table, 2, 26, 27, 34);
    fill_Row_Table_Driver(table, 2, 28, 34, -1);

    // fill row 3
    table->table_driver[3][30] = 31;
    table->table_driver[3][31] = 26;
    fill_Row_Table_Driver(table, 3, 0, 29, -1);


    //fill row 4
	fill_Row_Table_Driver(table, 4, 0, 25, 34);

    fill_Row_Table_Driver(table, 4, 26, 27, 34);
    fill_Row_Table_Driver(table, 4, 28, 34, -1);

    //row 5
	fill_Row_Table_Driver(table, 5, 0, 25, 34);

    fill_Row_Table_Driver(table, 5, 26, 27, 34);
    fill_Row_Table_Driver(table, 5, 28, 34, -1);

    //row 6
    table->table_driver[6][28] = 29;
    table->table_driver[6][31] = 26;
    fill_Row_Table_Driver(table, 6, 0, 27, -1);
    fill_Row_Table_Driver(table, 6, 29, 30, -1);

    // row 7
    int index = 0;
    char c;
    for(c='a'; c<='z';c++){
        table->table_driver[7][index]=c;
        index++;
    }



   
}

void fill_Table(Table table) {
	fill_Input_Symbols(table);
	fill_Category_Symbols(table);
	fill_Productions_In_Reverse_Order(table);
	fill_Table_Driver(table);
}

void print_Table(Table table) {
	for (int i=0; i<8; i++) {
		for (int j=0; j<17; j++) {
			printf("%i\t", table -> table_driver[i][j]);
		}
		printf("\n");
	}
}

Table new_Table() {
	Table this = (Table) malloc(sizeof(struct Table));

	this -> table_driver = (int**) calloc(8, sizeof(int*));
	for (int i=0; i<8; i++) {
		this -> table_driver[i] = (int*) calloc(32, sizeof(int));
	}

	this -> input_symbols = (char*) calloc(32, sizeof(char));

	this -> category_symbols = (char**) calloc(8, sizeof(char*));
	for (int i=0; i<8; i++) {
		this -> category_symbols[i] = (char*) calloc(4, sizeof(char));
	}

	this -> productions = (char**) calloc(35, sizeof(char*));
	for (int i=0; i<35; i++) {
		this -> productions[i] = (char*) calloc(10, sizeof(char));
	}

	fill_Table(this);

	return this;
}
