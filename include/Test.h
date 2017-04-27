#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "Grafo.h"

bool comparaResultado(const char *caminho1, const char *caminho2);
void geraResultado(const char *nome, Grafo* grafo);

#endif // TEST_H
