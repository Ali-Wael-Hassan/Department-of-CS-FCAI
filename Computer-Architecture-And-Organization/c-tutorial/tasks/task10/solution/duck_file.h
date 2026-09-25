#ifndef DUCK_FILE_H
#define DUCK_FILE_H

#include <stdio.h>


void duckcat(FILE *left, FILE *right, FILE *out);
void duckcopy(FILE *dst, FILE *src);
void duckhead(FILE *src, FILE *out);
void ducktail(FILE *src, FILE *out);

#endif