#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<iostream>

int main(){
    int fd = open("./file.txt", O_RDWR|O_TRUNC,0 );

    for(int i=0;i<10000;++i){
        std::srand(std::time(0));
        int random_variable = std::rand()%26;
        std::cout<<random_variable;
        char ch='a'+random_variable;
        for(int t=0;t<1000000   ;++t){}
        write(fd, &ch, 1);
    }

    close(fd);
}