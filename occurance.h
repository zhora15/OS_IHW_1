#ifndef OS1__OCCURANCE_H_
#define OS1__OCCURANCE_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define CMP_WORD 5
#define INP_SIZE 5000

int is_digit(char c);
int is_letter(char c);
int is_delim(char c);
void processString(char *str, int *ans);
int output_ans(int *ans, char *outp_str);

#endif //OS1__OCCURANCE_H_
