#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void create_child_processes(void) {
    int number_of_children;

    printf("\nEnter number of child processes: ");
    if (scanf("%d", &number_of_children) != 1 ||
        number_of_children < 0) {
        fprintf(stderr, "Please enter a non-negative integer.\n");
        return;
    }

    fflush(stdout);
    for (int i = 0; i < number_of_children; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return;
        }

        if (pid == 0) {
            printf("Child %d: PID = %ld, Parent PID = %ld\n",
                   i + 1, (long)getpid(), (long)getppid());
            fflush(stdout);
            _exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < number_of_children; ++i) {
        if (wait(NULL) == -1) {
            perror("wait");
            return;
        }
    }
    printf("Parent PID = %ld: all child processes have finished.\n",
           (long)getpid());
}

static void demonstrate_wait(void) {
    fflush(stdout);
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return;
    }

    if (pid == 0) {
        printf("Child PID = %ld is running.\n", (long)getpid());
        printf("Child will finish after 3 seconds.\n");
        fflush(stdout);
        sleep(3);
        printf("Child PID = %ld is terminating.\n", (long)getpid());
        fflush(stdout);
        _exit(EXIT_SUCCESS);
    }

    printf("Parent PID = %ld is waiting for child PID = %ld.\n",
           (long)getpid(), (long)pid);

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return;
    }

    if (WIFEXITED(status)) {
        printf("Parent: child ended with exit status %d.\n",
               WEXITSTATUS(status));
    } else {
        printf("Parent: child ended abnormally.\n");
    }
}

int main(void) {
    int choice;

    printf("Linux Process System Calls Demonstration\n");
    printf("1. Create N child processes using fork()\n");
    printf("2. Demonstrate parent waiting using waitpid()\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        fprintf(stderr, "Invalid choice.\n");
        return EXIT_FAILURE;
    }

    switch (choice) {
        case 1:
            create_child_processes();
            break;
        case 2:
            demonstrate_wait();
            break;
        default:
            fprintf(stderr, "Please choose 1 or 2.\n");
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
