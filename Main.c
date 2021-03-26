#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Structs.h"
#include "recursiveDescentParser.h"

void expr() {


	while(1) {

		printf("\n----------------------------------\n");

		printf("Enter a mathematical expression to be evaluated or quit to exit\n");
		char input[128];
		fgets(input,100,stdin);
		input[strlen(input) - 1] = '\0';
		if (!strcmp(input, "quit")) {
			return;
		}

		State s = newState(input);
		// printf("\n in Main");
		// printf(s->idx);
		Node tree = E_function(s);

		int valid = 0;

		if (tree != NULL && s -> expression[s -> idx] == '\0') {

			printf("Parse Tree generated from Recursive Descent:\n");
			printTree(tree);
			// printf("\n\n\nEvaluation = %s\n\n", compute(tree));
			valid = 1;

		}

	}
}


int main(int argc, char* argv[]) {

	expr();

}
