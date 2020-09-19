#include<pthread.h>
#include<iostream>
#include<vector>
#include<semaphore.h>
#include<iostream>
#include<stdlib.h>
int ali_key = 0;
sem_t mutex;

void *thread(void *vargp)
{
    int connfd=*((int *)vargp);
    while(true){
        // 加锁保证order
        sem_wait(&mutex);
        if(ali_key==connfd){
            char c;
            switch (ali_key)
            {
            case 0:
                c='a';
                break;
            case 1:
                c='l';
                break;
            case 2:
                c='i';
                break;
            default:
                break;
            }
            std::cout<<c; 
            ali_key=(ali_key+1)%3; 
        }
        sem_post(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t tid1,tid2,tid3;
    sem_init(&mutex,0,1);
    int *connfd,*connfd2,*connfd3;
    connfd=(int *)malloc(sizeof(int));
    connfd2=(int *)malloc(sizeof(int));
    connfd3=(int *)malloc(sizeof(int));
    *connfd=0;
    pthread_create(&tid1,NULL,thread,connfd);
    *connfd2=1;
    pthread_create(&tid2,NULL,thread,connfd2);
    *connfd3=2;
    pthread_create(&tid3,NULL,thread,connfd3);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);
    return 0;
}