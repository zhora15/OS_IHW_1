#ifndef OS1__OCCURANCE_C_
#define OS1__OCCURANCE_C_

#include "occurance.h"

char *words[] = {"for", "while", "void", "return", "int"};

int is_digit(char c) {
    return ((c >= '0') && (c <= '9'));
}
int is_letter(char c) {
    return (((c >= 'A') && (c <= 'z')) || ((c >= 'a') && (c <= 'z')));
}

int is_delim(char c) {
    char delim[] = {'-', '_', '.'};
    return (c == delim[0]) || (c == delim[1]) || (c == delim[2]);
}

void processString(char *str, int *ans) {
    char words_len[CMP_WORD];
    for (int i = 0; i < CMP_WORD; ++i) {
        words_len[i] = strlen(words[i]);
    }
    char *word_begin = str, *word_end;
    while (*word_begin && (!is_letter(*word_begin))) {
        word_begin++;
    }
    word_end = word_begin;

    while (*word_end) {
        if (!(is_letter(*word_end) || is_digit(*word_end) || is_delim(*word_end))) {
            for (int i = 0; i < CMP_WORD; ++i) {
                long word_len = word_end - word_begin > words_len[i] ? word_end - word_begin : words_len[i];
                if (!strncmp(word_begin, words[i], word_len)) {
                    ++ans[i];
                    break;
                }
            }
            word_begin = word_end;
            while (*word_begin && !(is_letter(*word_begin))) {
                word_begin++;
            }
            word_end = word_begin;
        }
        if (*word_end) {
            ++word_end;
        }
    }
}

int output_ans(int *ans, char *outp_str) {
    int outp_len = 0;

    outp_len += sprintf(outp_str, "Occurrence:\n");
    for (int i = 0; i < CMP_WORD; ++i) {
        outp_len += sprintf(&outp_str[outp_len], "%s: %d\n", words[i], ans[i]);
    }
    outp_str[outp_len++] = '\0';
    return outp_len;
}
#endif