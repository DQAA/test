#include <bits/stdc++.h>
#define N 600005
#define M 300005

using namespace std;

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

int isD[N];
int stk[10];
int top;
struct A{
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
}ans[3000005];
int anstot;
void creatAns()
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
}
int Next;
void DFS(int first,int id)
{
    if(id < first)return;
    isD[id] = 1;
    stk[top++] = id;
    int j = g[id].next;
    while(j)
    {
        Next = edge[j].to;
        if(isD[Next] == 1){
            if(top >= 3 && Next == stk[0])creatAns();
        }else if(top < 7){
            DFS(first,Next);
        }
        j = edge[j].next;
    }
    isD[id] = 0;
    top--;
    return;
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
    freopen("/data/test_data.txt","r",stdin);
    freopen("/projects/student/result.txt","w",stdout);
    int t = clock();
    int tmp;
    int n = 0;
    int m = 0;
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
    for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,i);
    sort(ans,ans+anstot);
    printf("%d\n",anstot);
	double ti = clock() - t;
    printf("%fs\n",ti/CLOCKS_PER_SEC);
    for(int i = 0;i < anstot;i++)
    {
        A* p = &ans[i];
        printf("%d",p->id);
        p = p->next;
        while(p)
        {
            printf(",%d",p->id);
            p = p->next;
        }
        printf("\n");
    }
    return 0;
}
