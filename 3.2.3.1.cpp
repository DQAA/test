#include <bits/stdc++.h>
#include <unordered_map>
#include <sys/time.h>
#define N 600005
#define M 300005

using namespace std;

int g[N][50];
int fg[N][50];
struct timeval Begin;
struct timeval End;
double timer;

struct nd{
    int from;
    int to;
}rd[M];
unordered_map<int,int> mp;
unordered_map<int,bool> is;
int yid[N];
int n,m;
int isD[4][N];
int stk[4][10];
int top[4];
struct A{
	int id[8];//7时排序出错，过程未知
	int num;
	bool operator < (const struct A b) const{
		if(this->num < b.num)return 1;
		else if(this->num == b.num){
			int p = 0;
			int q = 0;
			while(this->id[p] != -1 && b.id[q] != -1)
			{
				if(this->id[p] < b.id[q])return 1;
				else if (this->id[p] > b.id[q])return 0;
				p++;q++;
			}
		}
		return 0;
	}
}ans[4][3000005];
int anstot[4];
void creatAns(int pid)
{
	int anstotq = anstot[pid];
	ans[pid][anstotq].id[0] = yid[stk[pid][0]];
	ans[pid][anstotq].num = top[pid];
	for(int i = 1;i < top[pid];i++)
		ans[pid][anstotq].id[i] = yid[stk[pid][i]];
	ans[pid][anstot[pid]++].id[top[pid]] = -1;
}
int b;
int in[N];
int out[N];
void DFS(int first,int id,int pid)
{
	if(top[pid] >= 7)return;
    if(id < first)return;
	if(out[id] == -1)return;
    isD[pid][id] = 1;
    stk[pid][top[pid]++] = id;
	if(top[pid])b++;//faster
	int num_of_edge = g[id][0];
	for(int i = 1;i <= num_of_edge;i++)
    {
        int Next = g[id][i];
        if(isD[pid][Next] == 1){
            if(top[pid] >= 3 && Next == stk[pid][0]){
				creatAns(pid);
				if(top[pid] == 7)break;
			}
        }else{
            DFS(first,Next,pid);
        }
    }
    isD[pid][id] = 0;
    top[pid]--;
    return;
}
void *th(void *ID)
{
	long long pid = (long long)ID;
	for(int i =  1;i < n + 1;i++)
		if(i%4 == pid)DFS(i,i,pid);
}
void processIn(int i)
{
	in[i] = -1;
	int num_of_edge = g[i][0];
	for(int j = 1;j <= num_of_edge;j++)
        if(--in[g[i][j]] == 0)processIn(g[i][j]);
}
void processOut(int i)
{
	out[i] =  -1;
	int num_of_edge = g[i][0];
	for(int j = 1;j <= num_of_edge;j++)
		if(--out[fg[i][j]] == 0)processOut(fg[i][j]);
}
int main()
{
    //freopen("/data/test_data.txt","r",stdin);
    //freopen("/projects/student/result.txt","w",stdout);
    gettimeofday(&Begin,NULL);
    int tmp;
    while(scanf("%d,%d,%d",&rd[m].from,&rd[m].to,&tmp) != EOF)
    {
        if(!is[rd[m].from]){
            yid[1+n++] = rd[m].from;
            is[rd[m].from] = 1;
        }
        if(!is[rd[m].to]){
            yid[1+n++] = rd[m].to;
            is[rd[m].to] =     1;
        }
        m++;
    }
    sort(yid+1,yid+n+1);
    for(int i = 1;i < n + 1;i++)
        mp[yid[i]] = i;
    for(int i = 0;i < m;i++)
    {
		int s = mp[rd[i].from];
		int t = mp[rd[i].to];
        g[s][++g[s][0]] = t;
		fg[t][++fg[t][0]] = s;
        in[t]++;
		out[s]++;
    }
    for(int i = 1;i < n+1;i++)
    {
        if(in[i] == -1)continue;
        else if(in[i] == 0)processIn(i);
    }
	for(int i = 1;i < n+1;i++)
	{
		if(out[i] == -1)continue;
		else if(out[i] == 0)processOut(i);
	}
	pthread_t thread[4];
	for(int i = 0;i < 4;i++)
		pthread_create(&thread[i],NULL,th,(void*)i);
	for(int i = 0;i < 4;i++)
		pthread_join(thread[i],NULL);
	for(int i = 1;i < 4;i++)
		for(int j = 0;j < anstot[i];j++)
			ans[0][anstot[0]++] = ans[i][j];
    sort(ans[0],ans[0]+anstot[0]);
    printf("%d\n",anstot[0]);
	//cout << b << endl;
	gettimeofday(&End,NULL);
	timer = 1000000 * (End.tv_sec - Begin.tv_sec) + End.tv_usec - Begin.tv_usec;
	printf("%fs\n",timer/1000000);
    /*for(int i = 0;i < anstot[0];i++)
    {
        printf("%d",ans[0][i].id[0]);
        int p = 1;
        while(ans[0][i].id[p] != -1)
        {
            printf(",%d",ans[0][i].id[p]);
            p++;
        }
        printf("\n");
    }*/
	exit(0);
    return 0;
}
