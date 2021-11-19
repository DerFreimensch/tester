#pragma warning(disable : 4996)
#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <string.h>
char** dictionary, ** swop;
char* word, * ptr;
char line[1024];
FILE* file;
int i = 0, j = 0, k = 0;
int nw = 1, lw = 0, plw = 0, flag = 0, s = 1, si = 0;
void write() {
	dictionary = (char**)realloc(dictionary, nw * sizeof(char*));
	dictionary[nw - 1] = (char*)calloc(plw + 1, sizeof(char));
	for (i = nw - 1; i < nw; i++) {
		for (j = 0; j < plw; j++) {
			dictionary[i][j] = word[j];
		}
		dictionary[i][j] = '\0';
	}
	nw++;
}
void sort() {
	i = 0;
	while (si != nw - 1) {
		while (i + s < nw - 1) {
			if (dictionary[i] != NULL && dictionary[i+s] != NULL) {
				if (strcmp(dictionary[i], dictionary[i + s]) == 0) {
					dictionary[i + s] = NULL;
					lw++;
				}
			}
			s++;
		}
		i++;
		s = 1;
		si++;
	}
	si = 0;
	i = 0;
	s = 1;
	swop = (char**)calloc(nw - 1 - lw, sizeof(char*));
	while (si != nw - 1 - lw) {
		while (i + s < nw - 1) {
			if (dictionary[i] != NULL && dictionary[i + s] != NULL) {
				if (strcmp(dictionary[i], dictionary[i + s]) < 0) {
					flag = i;
					s++;
				}
				else {
					flag = i + s;
					i = flag;
					s = 1;
				}
				swop[si] = (char*)calloc(_msize(dictionary[flag]) / sizeof(char), sizeof(char));
				strcpy(swop[si], dictionary[flag]);
				dictionary[flag] = NULL;
				si++;
				for (int g = 0; g < nw; g++) {
					if (dictionary[g] != NULL) {
					i = g;
					break;
					}
				}
				s = 1;
				
			}
			else s++;
		}
		si++;
		for (int g = 0; g < nw; g++) {
			if (dictionary[g] != NULL) {
				i = g;
				break;
			}
		}
		s = 1;
	}
	free(dictionary);
}
void read() {
	while (!feof(file)) {
		ptr = fgets(line, 1024, file);
		while (*ptr != '\0') {
			if (*ptr != ' ' && *ptr != ',' && *ptr != '.' && *ptr != '?' && *ptr != '!' && *ptr
				!= '(' && *ptr != ')' && *ptr != ':' && *ptr != ';' && *ptr != '"' && *ptr != '\n') {
				plw++;
				word = (char*)realloc(word, plw * sizeof(char));
				word[k++] = *(ptr++);
			}
			else {
				if (*(ptr - 1) == ' ' || *(ptr - 1) == ',' || *(ptr - 1) == '.' || *(ptr - 1)
					== '?' || *(ptr - 1) == '!' || *(ptr - 1) == '(' || *(ptr - 1) == ')' || *(ptr - 1) == ':' || *(ptr - 1) == ';' || *(ptr
						- 1) == '"' || *(ptr - 1) == '\n') {
					ptr++;
				}
				else {
					ptr++;
					write();
					plw = 0;
					k = 0;
					free(word);
					word = (char*)calloc(0, sizeof(char));
				}
			}
		}
	}
}
int main(void) {
	fopen_s(&file, "help.txt", "r+t");
	word = (char*)calloc(plw, sizeof(char));
	dictionary = (char**)calloc(nw, sizeof(char*));
	read();
	fclose(file);
	write();
		sort();
	for (i = 0; i < nw - 1 - lw; i++) {
		puts(swop[i]);
	}
	for (i = 0; i < nw - 1 - lw; i++) {
		free(swop[i]);
	}
	free(swop);
	return 0;
}
