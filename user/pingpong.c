#include <kernel/types.h>
#include <user/user.h>

/*
    xv6
    pingpong test
*/

int 
main(){
    //pipe1(p1):写端父进程，读端子进程
    //pipe2(p2):写端子进程，读端父进程
    int p1[2],p2[2];
    //pingpong transport data
    char buffer[] = {'X'};
    //transport length if data
    long length = sizeof(buffer);
    //pipe for parent process write, children process read
    pipe(p1);
    //pipe for children process write, parent process read
    pipe(p2);
    if(fork() == 0){
        //close unused pipe channel (in children process)
        close(p1[1]);//close write
        close(p2[0]);//close read
        if(read(p1[0], buffer, length) != length){
            printf("a--->b read error!");
            exit(1);
        }
        printf("%d: received ping\n", getpid());
        if(write(p2[1], buffer, length) != length){
            printf("a<---b write error");
            exit(1);
        }
        exit(0);
    }
    close(p1[0]);
    close(p2[1]);
    if(write(p1[1], buffer, length) != length){
            printf("a--->b write error");
            exit(1);
    }
    if(read(p2[0], buffer, length) != length){
            printf("a<---b read error!");
            exit(1);
    }
    printf("%d: received pong\n", getpid());

    wait(0);
    exit(0);

}

