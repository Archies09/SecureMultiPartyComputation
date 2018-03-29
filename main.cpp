#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <bits/stdc++.h>

using namespace std;

int sharedVariable = 0;

void  setSeedFromCpuUtil()
{
    FILE *statptr;
    unsigned long long statArray[4];
    statptr=fopen("/proc/stat","r");
    char noUse[10];
    fscanf(statptr,"%s %llu %llu %llu %llu",noUse,&statArray[0],&statArray[1],&statArray[2],&statArray[3]);
    unsigned long long finalrandomnumber = (statArray[0]+statArray[1]+statArray[2]+statArray[3])/3;
    srand(finalrandomnumber%13121);
    fclose(statptr);
    //printf("%d\n",(int)(finalrandomnumber%13121));
    //Now rand can be used
}


void *ThreadOne(void *vargp)
{
    usleep(rand()%1000000000);
    ::sharedVariable = 1;
    usleep(rand()%1000000000);
    return NULL;
}

void *ThreadTwo(void *vargp)
{
    usleep(rand()%1000000000);
    ::sharedVariable = 2;
 //   usleep(rand()%1000000000);
    return NULL;
}

void *ThreadThree(void *vargp)
{
    usleep(rand()%1000000000);
    ::sharedVariable = 3;
  //  usleep(rand()%1000000000);
    return NULL;
}

void *ThreadFour(void *vargp)
{
    usleep(rand()%1000000000);
    ::sharedVariable = 4;
//    usleep(rand()%1000000000);
    return NULL;
}


int main()
{
    setSeedFromCpuUtil();
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;
    pthread_t tid4;
    cout << "Hello world!" << endl;
    int p1=0;
    int p2=0;
    int p3=0;
    int p4=0;
    int n = 100000;
    for(int i=0;i<n;i++)
    {
        pthread_create(&tid1, NULL, ThreadOne, NULL);
        //pthread_join(tid1, NULL);
        pthread_create(&tid2, NULL, ThreadTwo, NULL);
        //pthread_join(tid2, NULL);
        pthread_create(&tid3, NULL, ThreadThree, NULL);
        //pthread_join(tid3, NULL);
        pthread_create(&tid4, NULL, ThreadFour, NULL);
        //pthread_join(tid4, NULL);
        //usleep(1000000000);
        if(::sharedVariable==1)
               p1++;
        else if(::sharedVariable==2)
               p2++;
        else if(::sharedVariable==3)
               p3++;
        else if(::sharedVariable==4)
               p4++;
    }

    cout<<"Probablity p1"<<p1/(n*1.0)<<endl;
    cout<<"Probablity p2"<<p2/(n*1.0)<<endl;
    cout<<"Probablity p3"<<p3/(n*1.0)<<endl;
    cout<<"Probablity p4"<<p4/(n*1.0)<<endl;
    //pthread_join(tid, NULL);
    cout<<"Shared Variable"<<::sharedVariable<<endl;
    return 0;
}
