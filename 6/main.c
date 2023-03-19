#include "../occurance.h"

int main(int argc, char **argv){
    int fd1[2], fd2[2];
    pid_t chpid1;

    pipe(fd1);
    pipe(fd2);
    chpid1 = fork();
    if (chpid1 == -1) {
        printf("An error occurred while creating first child\n");
        exit(-1);
    } else if (chpid1 == 0) {
        close(fd2[1]);
        char str[INP_SIZE+1];
        ssize_t len;
        read(fd2[0], &len, sizeof(ssize_t));
        read(fd2[0], str, len);
        int ans[CMP_WORD];
        memset(ans, 0, CMP_WORD * sizeof(int));
        processString(str, ans);
        close(fd1[0]);
        write(fd1[1], ans, sizeof(ans));
        exit(0);
    } else {
        int file = open(argv[1], O_RDONLY);
        char str[INP_SIZE+1];
        ssize_t n_bytes = read(file, str, INP_SIZE);
        close(file);
        str[n_bytes++] = '\0';
        close(fd2[0]);
        write(fd2[1], &n_bytes, sizeof(ssize_t));
        write(fd2[1], str, n_bytes);

        wait(NULL);

        close(fd1[1]);
        int ans[CMP_WORD];
        read(fd1[0], ans, sizeof(ans));
        file = open(argv[2], O_WRONLY);
        char outp_str[100];
        int outp_len = output_ans(ans, outp_str);
        write(file, outp_str, outp_len);
        close(file);
    }
}
