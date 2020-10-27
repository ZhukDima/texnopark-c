#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysinfo.h>

int main()
{
    char pid[255];
    printf("%d\n", get_nprocs_conf());
    int s = 0;
    int a = fork();
    s += a == 0;
    int b = fork();
    s += b == 0;
    int c = fork();
    s += c == 0;
    sprintf(pid, "PID : %6d %6d %6d %6d %6d\n", getpid(), a, b, c, s);
    int id;
    if (a != 0) usleep(100);
    if (b != 0) usleep(100);
    if (c != 0) usleep(100);
    waitpid(a, &id, 0);
    // waitpid(b, &id, 0);
    // waitpid(c, &id, 0);
    write(STDOUT_FILENO, pid, strlen(pid));
    return 0;
}