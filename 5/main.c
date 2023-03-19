#include "../occurance.h"

int main(int argc, char **argv) {
    pid_t chpid1;
    chpid1 = fork();

    if (chpid1 == -1) {
        printf("An error occurred while creating first child\n");
        exit(-1);
    } else if (chpid1 == 0) {
        //int fd2[2];
        pid_t chpid2;
        //pipe(fd2);
        chpid2 = fork();
        if (chpid2 == -1) {
            printf("An error occurred while creating second child\n");
            exit(-1);
        } else if (chpid2 == 0) {
            int file = open(argv[1], O_RDONLY);
            char str[INP_SIZE+1];
            ssize_t n_bytes = read(file, str, INP_SIZE);
            close(file);
            str[n_bytes++] = '\0';
            umask(0);
            mknod("FIFO1", S_IFIFO | 0222, 0);
            int fn = open("FIFO1", O_CREAT | O_WRONLY);
            write(fn, &n_bytes, sizeof(ssize_t));
            write(fn, str, n_bytes);
            exit(0);
        } else {
            char str[INP_SIZE+1];
            ssize_t len;
            umask(0);
            mknod("FIFO1", S_IFIFO | 0444, 0);
            int fn;
            do {
                fn = open("FIFO1", O_RDONLY);
            } while (fn == -1);
            read(fn, &len, sizeof(ssize_t));
            read(fn, str, len);
            close(fn);
            int ans[CMP_WORD];
            memset(ans, 0, CMP_WORD * sizeof(int));
            processString(str, ans);
            umask(0);
            mknod("FIFO2", S_IFIFO | 0222, 0);
            fn = open("FIFO2", O_CREAT | O_WRONLY);
            write(fn, ans, sizeof(ans));
            close(fn);
            exit(0);
        }
    } else {
        umask(0);
        mknod("FIFO2", S_IFIFO | 0444, 0);
        int fn;
        do {
            fn = open("FIFO2", O_RDONLY);
        } while (fn == -1);
        int ans[CMP_WORD];
        read(fn, ans, sizeof(ans));
        close(fn);
        int file = open(argv[2], O_WRONLY);
        char outp_str[100];
        int outp_len = output_ans(ans, outp_str);
        write(file, outp_str, outp_len);
        close(file);
    }
    return 0;
}