#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstdio>
#include<assert.h>
int main(){

    //read
    int fd = open("./sstable-1.sst", O_RDWR, 0);
    
    int c;
    read(fd, &c,4);
    printf("%d\n", c);

    //write to current file
    lseek(fd, 0, SEEK_SET);
    write(fd, &c, 4);
    lseek(fd, 0, SEEK_SET);
    
    int c1;
    read(fd, &c1, 4);
    printf("%d\n", c1);
    assert(c1==c);
    
}