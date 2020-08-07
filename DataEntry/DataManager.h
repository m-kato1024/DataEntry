#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
int DMInitialization(char* path);
void DMAddNew(int input_number, char* input_name, char* input_yomi);
void DMDelete(int input_number);
void DMListFetch(char display_Num, char* display_Name);
void DMSearch(char* input_yomi, char search_result);
int DMEnd(char* path);