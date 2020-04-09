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
int stk[1000005];
int top;
struct A{
    int id;
    int num;
    A* next;
    bool operator == (const struct A b) const{
        if(this->num != b.num || this->id != b.id)return 0;
        const A* p = this;
        const A* q = &b;
        while(p != NUll && q != NULL)
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
    int minn = 0;
    for(int i = 0;i < top;i++)
        if(stk[i] < stk[minn])minn = i;
    A* p = &ans[anstot++];
    p->id = g[stk[minn]].id;
    p->num = top;
    for(int i = 1;i < top;i++)
    {
        p->next = new A;
        p = p->next;
        if(i + minn < top)p->id = g[stk[i+minn]].id;
        else p->id = g[stk[(i+minn)%top]].id;
    }
    for(int i = 0;i < anstot-1;i++)
    {
        if(ans[i] == ans[anstot-1]){
            A* p = &ans[--anstot];
            A* q = p;
            while(p != NUll)
            {
                q = p;
                p = p->next;
                delete q;
            }
            break;
        }
    }
}
int Next;
int last;
void DFS(int id,int step)
{
    if(anstot != last){
        last = anstot;
        cout << anstot << " " << g[id].id << endl;
    }
    if(step > 7)return;
    isD[id] = 1;
    stk[top++] = id;
    int j = g[id].next;
    while(j)
    {
        Next = edge[j].to;
        if(isD[Next] == 1){
            is2.clear();
            //findnn();
            //cout << top-jj << endl;
            if(top >= 3 && top <= 7 && Next == stk[0])creatAns();
            j = edge[j].next;
            continue;
        }else{
            DFS(Next,step+1);
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
    //if(in[i] == -1)return;//??
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
    //freopen("E:\\test_data3.txt","r",stdin);
    //freopen("E:\\result","w",stdout);
    int t = time(0);
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
    {
        addEdge(mp[rd[i].from],mp[rd[i].to]);
        in[mp[rd[i].to]]++;
    }
    //cout << "before tuopu" << endl;
    for(int i = 1;i < n+1;i++)
    {
        if(in[i] == -1)continue;
        else if(in[i] == 0)process(i);
    }
    //cout << "done tuopu" << endl;
    //cout << "before DFS" <<endl;
    for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,1);
    //cout << "done DFS" << endl;
    sort(ans,ans+anstot);
    cout << anstot << endl;
    cout << time(0) - t << endl;
    /*for(int i = 0;i < anstot;i++)
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
    }*/
    return 0;
}
