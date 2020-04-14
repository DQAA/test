#include <bits/stdc++.h>
#define N 600005
#define M 300005

using namespace std;

vector<int> g[N];
vector<int> fg[N];

struct nd{
    int from;
    int to;
}rd[M];
map<int,int> mp;
map<int,bool> is;
int yid[N];

void addEdge(int s,int t)
{
	g[s].push_back(t);
}

int isD[N];
int stk[10];
int top;
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
}ans[3000005];
int anstot;
void creatAns()
{
	ans[anstot].id[0] = yid[stk[0]];
	ans[anstot].num = top;
	for(int i = 1;i < top;i++)
		ans[anstot].id[i] = yid[stk[i]];
	ans[anstot++].id[top] = -1;
}
int Next;
int in[N];
int out[N];
void DFS(int first,int id)
{
	if(top >= 7)return;
    if(id < first)return;
	if(out[id] == -1)return;
    isD[id] = 1;
    stk[top++] = id;
	vector<int>:: iterator j = g[id].begin();
    while(j != g[id].end())
    {
        Next = *j;
        if(isD[Next] == 1){
            if(top >= 3 && Next == stk[0]){
				creatAns();
				if(top == 7)break;
			}
        }else{
            DFS(first,Next);
        }
        j++;
    }
    isD[id] = 0;
    top--;
    return;
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
    freopen("/data/test_data.txt","r",stdin);
    freopen("/projects/student/result.txt","w",stdout);
    //int t = clock();
    int tmp;
    int n = 0;
    int m = 0;
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
    for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,i);
    sort(ans,ans+anstot);
    printf("%d\n",anstot);
	//double ti = clock() - t;
    //printf("%fs\n",ti/CLOCKS_PER_SEC);
    for(int i = 0;i < anstot;i++)
    {
        printf("%d",ans[i].id[0]);
        int p = 1;
        while(ans[i].id[p] != -1)
        {
            printf(",%d",ans[i].id[p]);
            p++;
        }
        printf("\n");
    }
    return 0;
}
//注释掉的版本100万数据400
//4.11最快
//4.12提交
