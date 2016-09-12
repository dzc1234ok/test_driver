#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int test_fd;

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s dir_dev \n", argv[0]);
    }

    test_fd = open(argv[1], O_RDWR);
    if (test_fd == -1) {
        perror("open");
    }

    return 0;
}
