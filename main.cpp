#include <bits/stdc++.h>
#define N 100005
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
int tag = 2;

struct nd{
    int from;
    int to;
}rd[1000005];
map<int,int> mp;
map<int,bool> is;
map<int,bool> is2;

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
int stk[100005];
int top;
struct A{
    int id;
    int num;
    A* next;
    bool operator == (const struct A b) const{
        if(this->num != b.num || this->id != b.id)return 0;
        const A* p = this;
        const A*q = &b;
        for(int i = 0;i < num;i++)
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
}ans[100005];
int anstot;
void creatAns(int jj)
{
    int minn = jj;
    for(int i = jj;i < top;i++)
        if(stk[i] < stk[minn])minn = i;
    A* p = &ans[anstot++];
    p->id = g[stk[minn]].id;
    p->num = top-jj;
    for(int i = 1;i < top - jj;i++)
    {
        p->next = new A;
        p = p->next;
        if(i + minn < top)p->id = g[stk[i+minn]].id;
        else p->id = g[stk[(i+minn)%top + jj]].id;
    }
    for(int i = 0;i < anstot-1;i++)
    {
        if(ans[i] == ans[anstot-1]){
            anstot--;//memory
            break;
        }
    }
}
int Next;
void DFS(int id)
{
    isD[id] = 1;
    stk[top++] = id;
    int j = g[id].next;
    while(j)
    {
        Next = edge[j].to;
        if(isD[Next] == 1){
            is2.clear();
            //findnn();
            int jj = 0;
            while(jj < top)
            {
                if(stk[jj] == Next)break;
                jj++;
            }
            //cout << top-jj << endl;
            if(top - jj >= 3 && top - jj <= 7)creatAns(jj);
            j = edge[j].next;
            continue;
        }else{
            DFS(Next);
        }
        j = edge[j].next;
    }
    isD[id] = 2;
    top--;
    return;
}

int main()
{
    freopen("/data/test_data.txt","r",stdin);
    freopen("/projects/student/result.txt","w",stdout);
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
            is[rd[m].to] =   1;
        }
        m++;
    }
    sort(g+1,g+n+1,cmp);
    for(int i = 1;i < n + 1;i++)
        mp[g[i].id] = i;
    for(int i = 0;i < m;i++)
        addEdge(mp[rd[i].from],mp[rd[i].to]);
    for(int i = 1;i < n+1;i++)
        if(isD[i] == 0)DFS(i);
    sort(ans,ans+anstot);
    cout << anstot << endl;
    for(int i = 0;i < anstot;i++)
    {
        A* p = &ans[i];
        cout << p->id;
        p = p->next;
        while(p)
        {
            cout << "," << p->id;
            p = p->next;
        }
        cout << endl;
    }
    return 0;
}
