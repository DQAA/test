#include <bits/stdc++.h>
#define N 600005
#define M 300005
#define num_of_pth 4

using namespace std;

struct timeval Begin;
struct timeval End;
double timer;

vector<int> g[N];
vector<int> fg[N];

struct nd{
    int from;
    int to;
}rd[M];
map<int,int> mp;
map<int,bool> is;
int yid[N];
int n,m;

void addEdge(int s,int t)
{
	g[s].push_back(t);
}

int isD[num_of_pth][N];
int stk[num_of_pth][10];
int top[num_of_pth];
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
}ans[num_of_pth][3000005];
int anstot[num_of_pth];
void creatAns(int pid)
{
	int anstotq = anstot[pid]++;
	int topq = top[pid];
	ans[pid][anstotq].id[0] = yid[stk[pid][0]];
	ans[pid][anstotq].num = topq;
	for(int i = 1;i < topq;i++)
		ans[pid][anstotq].id[i] = yid[stk[pid][i]];
	ans[pid][anstotq].id[topq] = -1;
}
int in[N];
int out[N];
void DFS(int first,int id,int pid)
{
	if(top[pid] >= 7)return;
    if(id < first)return;
	if(out[id] == -1)return;
    isD[pid][id] = 1;
    stk[pid][top[pid]++] = id;
	int j = 0;
	int Next;
    while(j < g[id].size())
    {
        Next = g[id][j];
        if(isD[pid][Next] == 1){
            if(top[pid] >= 3 && Next == stk[pid][0])creatAns(pid);
        }else{
            DFS(first,Next,pid);
        }
        j++;
    }
    isD[pid][id] = 0;
    top[pid]--;
    return;
}
int Min(int a,int b)
{
	if(a < b)return a;
	else return b;
}
void *th(void *ID)
{
	long long id = (long long)ID;
	for(int i = id*(n/num_of_pth) + 1;i < Min((id+1)*(n/num_of_pth),n) + 1;i++)
	{
		DFS(i,i,id);
	}
}	
void processIn(int i)
{
    while(g[i].begin() != g[i].end())
    {
        if(--in[g[i][0]] == 0){
            in[g[i][0]] = -1;
            processIn(g[i][0]);
        }
		g[i].erase(g[i].begin());
    }
}
void processOut(int i)
{
	out[i] =  -1;
	while(fg[i].begin() != fg[i].end())
	{
		//g[i].erase(it - fg[i].begin() + g[i].begin());
		if(--out[fg[i][0]] == 0){
			processOut(fg[i][0]);
		}
		fg[i].erase(fg[i].begin());
	}
}
int main()
{
    //freopen("/data/test_data.txt","r",stdin);
    //freopen("/projects/student/result.txt","w",stdout);
    //int t = clock();
	gettimeofday(&Begin,NULL);
	memset(anstot,0,sizeof(anstot));
	memset(top,0,sizeof(top));
	memset(Next,0,sizeof(Next));
	for(int i = 0;i < num_of_pth;i++)
		for(int j = 0;j < N;j++)
			isD[i][j] = 0;
	for(int i = 0;i < num_of_pth;i++)
		for(int j = 0;j < 10;j++)
			stk[i][j] = 0;
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
        addEdge(s,t);
		fg[t].push_back(s);
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
	pthread_t threads[num_of_pth];
	for(int i = 0;i < num_of_pth;i++)
		pthread_create(&threads[i],NULL,th,(void*)i);
	for(int i = 0;i < num_of_pth;i++)
		pthread_join(threads[i],NULL);
    /*for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,i);*/
	for(int i = 1;i < num_of_pth;i++)
	{
		for(int j = 0;j < anstot[i];i++)
		{
			ans[0][anstot[0]+j] = ans[i][j];
		}
		anstot[0] += anstot[i];
	}
    sort(&ans[0],(&ans[0])+anstot[0]);
    printf("%d\n",anstot[0]);
	//double ti = clock() - t;
    //printf("%fs\n",ti/CLOCKS_PER_SEC);
	gettimeofday(&End,NULL);
	timer = 1000000 * (End.tv_sec - Begin.tv_sec) + (End.tv_usec - Begin.tv_usec);
	printf("%fs\n",timer/1000000);
    /*for(int i = 0;i < anstot;i++)
    {
        printf("%d",ans[i].id[0]);
        int p = 1;
        while(ans[i].id[p] != -1)
        {
            printf(",%d",ans[i].id[p]);
            p++;
        }
        printf("\n");
    }*/
    return 0;
}
