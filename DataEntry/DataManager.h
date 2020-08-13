#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#define DATA_MAX_COUNT (10)
#define DATA_MAX_LENGTH (40)
struct data {
	int number;
	char name[DATA_MAX_LENGTH];
	char yomi[DATA_MAX_LENGTH];
};
bool DMInitialization(char* path);
bool DMAddNew(int input_number, char* input_name, char* input_yomi);
void DMDelete(int input_number);
int DMListFetch(struct data result[]);
int DMSearch(char* input_yomi, struct data search_result[]);
bool DMTerminate(char* path);
int DMGetUserCount();