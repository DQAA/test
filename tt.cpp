#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/time.h>
#include <stdlib.h>

int N,t;
double ans,Pi;
pthread_mutex_t lock;
struct timeval start;
struct timeval end;
double timer;

double cal(int l,int r)
{
	int i;
	double ans;
	ans = 0;
	for(i = l;i <= r;i++)
		ans += 4/(1 + ((i+0.5)/N) * ((i+0.5)/N));
	return ans;
}

void *thread(void *ID)
{
	int id = (int)ID;
	int length = N/t;
	double a;
	if(id == t-1){
		a = cal(id*length,(id+1)*length);
	}else{
		a = cal(id*length,(id+1)*length);
	}
	ans += a;
	pthread_mutex_unlock(&lock);
}

int calPi()
{
	int i;
	pthread_t *threads;
	gettimeofday(&start, NULL);
	pthread_mutex_init(&lock,NULL);
	threads = (pthread_t*)malloc(sizeof(pthread_t)*t);
	pthread_mutex_unlock(&lock);
	for(i = 0;i < t;i++)
	{
		pthread_create(&threads[i],NULL,thread,(void*)i);
	}
	for(i = 0;i < t;i++)
	{
		pthread_join(threads[i],NULL);
	}
	Pi = ans;
	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	return 1;
}

int main()
{
    while(scanf("%d%d",&N,&t) != EOF)
    {
        if(N == 0)break;
        ans = 0;
        calPi();
        Pi = Pi/N;
        printf("Pi: %f\nTime: %fms\n",Pi,timer/1000);
    }
	return 0;
}
