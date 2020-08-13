#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
struct data {
	int number;
	char name[40];
	char yomi[40];
};
int DMInitialization(char* path);
void DMAddNew(int input_number, char* input_name, char* input_yomi);
void DMDelete(int input_number);
int DMListFetch(struct data result[]);
int DMSearch(char* input_yomi, struct data search_result[]);
int DMTerminate(char* path);