#include <bits/stdc++.h>
#define N 600005
#define M 300005

using namespace std;

struct timeval start;
struct timeval end;
double timer;

struct node{
    int next;
    int id;
}g[N];
struct nde{
    int to;
    int next;
}edge[M];
int tot;

struct nd{
    int from;
    int to;
}rd[M];
map<int,int> mp;
map<int,bool> is;

int cmp(node a,node b)
{
    if(a.id < b.id)return 1;
    else return 0;
}

void addEdge(int s,int t)
{
    edge[++tot].to = t;
    edge[tot].next = g[s].next;
    g[s].next = tot;
}

int isD0[N],isD1[N];
int stk0[10],stk1[10];
int top0,top1;
int n,m;
/*struct A{
    int id;
    int num;
    A* next;
    bool operator == (const struct A b) const{
        if(this->num != b.num || this->id != b.id)return 0;
        const A* p = this;
        const A* q = &b;
        while(p != NULL && q != NULL)
        {
            if(p->id != q->id)return 0;
            p = p->next;q = q->next;
        }
        return 1;
    }
    bool operator < (const struct A b) const{
        if(this->num < b.num)return 1;
        else if(this->num == b.num){
            const A* p = this;
            const A* q = &b;
            for(int i = 0;i < num;i++)
            {
                if(p->id < q->id)return  1;
                else if(p->id > q->id)return 0;
                p = p->next;q = q->next;
            }
        }
        return 0;
    }
}ans[3000005];*/
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
}ans0[3000005];
A ans1[3000005];
int anstot0,anstot1,anstot2,anstot3;
/*void creatAns()
{
    A* p = &ans[anstot++];
    p->id = g[stk[0]].id;
    p->num = top;
    for(int i = 1;i < top;i++)
    {
        p->next = new A;
        p = p->next;
        p->id = g[stk[i]].id;
        p->next = NULL;
    }
}*/
void creatAns0()
{
	ans0[anstot0].id[0] = g[stk0[0]].id;
	ans0[anstot0].num = top0;
	for(int i = 1;i < top0;i++)
		ans0[anstot0].id[i] = g[stk0[i]].id;
	ans0[anstot0++].id[top0] = -1;
}
int Next0,Next1;
void DFS0(int first,int id)
{
	if(top0 >= 7)return;
    if(id < first)return;
    isD0[id] = 1;
    stk0[top0++] = id;
    int j = g[id].next;
    while(j)
    {
        Next0 = edge[j].to;
        if(isD0[Next0] == 1){
            if(top0 >= 3 && Next0 == stk0[0])creatAns0();
        }else{
            DFS0(first,Next0);
        }
        j = edge[j].next;
    }
    isD0[id] = 0;
    top0--;
    return;
}
void creatAns1()
{
	ans1[anstot1].id[0] = g[stk1[0]].id;
	ans1[anstot1].num = top1;
	for(int i = 1;i < top1;i++)
		ans1[anstot1].id[i] = g[stk1[i]].id;
	ans1[anstot1++].id[top1] = -1;
}
void DFS1(int first,int id)
{
	if(top1 >= 7)return;
    if(id < first)return;
    isD1[id] = 1;
    stk1[top1++] = id;
    int j = g[id].next;
    while(j)
    {
        Next1 = edge[j].to;
        if(isD1[Next1] == 1){
            if(top1 >= 3 && Next1 == stk1[0])creatAns1();
        }else{
            DFS1(first,Next1);
        }
        j = edge[j].next;
    }
    isD1[id] = 0;
    top1--;
    return;
}
void *th0(void *a)
{
	for(int i = 0;i < n/2;i++)
		DFS0(i,i);
}
void *th1(void *a)
{
	for(int i = n/2+1;i < n;i++)
		DFS1(i,i);
}
int in[N];
void process(int i)
{
    //if(in[i] == -1)return;//不用
    while(g[i].next > 0)
    {
        if(--in[edge[g[i].next].to] == 0){
            in[edge[g[i].next].to] = -1;
            process(edge[g[i].next].to);
        }
        g[i].next = edge[g[i].next].next;
    }
}
int main()
{
    //freopen("/data/test_data.txt","r",stdin);
    //freopen("/projects/student/result.txt","w",stdout);
	gettimeofday(&start,NULL);
    //int t = clock();
    int tmp;
    while(scanf("%d,%d,%d",&rd[m].from,&rd[m].to,&tmp) != EOF)
    {
        if(!is[rd[m].from]){
            g[1+n++].id = rd[m].from;
            is[rd[m].from] = 1;
        }
        if(!is[rd[m].to]){
            g[1+n++].id = rd[m].to;
            is[rd[m].to] =     1;
        }
        m++;
    }
    sort(g+1,g+n+1,cmp);
    for(int i = 1;i < n + 1;i++)
        mp[g[i].id] = i;
    for(int i = 0;i < m;i++)
    {
        addEdge(mp[rd[i].from],mp[rd[i].to]);
        in[mp[rd[i].to]]++;
    }
    for(int i = 1;i < n+1;i++)
    {
        if(in[i] == -1)continue;
        else if(in[i] == 0)process(i);
    }
	pthread_t threads[2];
	pthread_create(&threads[0],NULL,th0,NULL);
	pthread_create(&threads[1],NULL,th1,NULL);
	pthread_join(threads[0],NULL);
	pthread_join(threads[1],NULL);
	int anstot = anstot0 + anstot1;
	for(int i = 0;i < anstot1;i++)
		ans0[i + anstot0] = ans1[i];
	sort(ans0,ans0+anstot);
    /*for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,i);
    sort(ans,ans+anstot);*/
    printf("%d\n",anstot);
	gettimeofday(&end,NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
	printf("%fs\n",timer/1000000);
	//double ti = clock() - t;
    //printf("%fs\n",ti/CLOCKS_PER_SEC);
    /*for(int i = 0;i < anstot;i++)
    {
        printf("%d",ans0[i].id[0]);
        int p = 1;
        while(ans0[i].id[p] != -1)
        {
            printf(",%d",ans0[i].id[p]);
            p++;
        }
        printf("\n");
    }*/
    return 0;
}
