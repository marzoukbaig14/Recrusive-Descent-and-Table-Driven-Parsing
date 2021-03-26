#include "Structs.h"

#ifndef RECURSIVEDESCENTPARSER_H_
#define RECURSIVEDESCENTPARSER_H_

extern Node newNode(Type t);

extern State newState(String s);

extern Node E_function(State S);

extern Node ET_function(State S);

extern Node C_function(State S);

extern Node CT_function(State S);

extern Node S_function(State S);

extern Node ST_function(State S);

extern Node A_function(State S);

extern Node X_function(State S);

extern Node operators(State S);

extern Node epsilon_function();

extern void printTree(Node N);

extern String getProductionType(Type T);

#endif /* RECURSIVEDESCENTPARSER_H_*/