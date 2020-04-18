#include <bits/stdc++.h>
#include <unordered_map>
#define N 600005
#define M 300005

using namespace std;

vector<int> g[N];
vector<int> fg[N];
struct B{
	int id;
	int num;
	int k[50];
};
vector<B> target[N];
unordered_map<uint64_t,int> is2[N];
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct nd{
    int from;
    int to;
}rd[M];
unordered_map<int,int> mp;
unordered_map<int,bool> is;
int yid[N];

void addEdge(int s,int t)
{
	g[s].push_back(t);
}
int b;
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
	if(top >= 6)return;
    if(id < first)return;
	if(out[id] == -1)return;
    isD[id] = 1;
    stk[top++] = id;
	if(top == 6){
		b++;
		int i = is2[id][stk[0]];
		/*if(i){
			int jie = target[id][i-1].num;
			for(int kk = 0;kk < jie;kk++)
			{
                if(isD[target[id][i-1].k[kk]] == 1)continue;
				stk[top++] = target[id][i-1].k[kk];
				creatAns();
                top--;
			}
        }*/
	}
	vector<int>:: iterator j = g[id].begin();
    while(j != g[id].end())
    {
        Next = *j;
        if(isD[Next] == 1){
            if(top >= 3 && Next == stk[0]){
				creatAns();
				if(top == 6)break;
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
bool ismk[N];
void mkTargrt(int first,int id,int step)
{
	if(step >= 3 || ismk[id] == 1)return;
	if(in[id] <= 0 || out[id] <= 0)return;
    ismk[id] = 1;
	if(step == 1){
		for(int i = 0;i < g[id].size();i++)
		{
			mkTargrt(first,g[id][i],step+1);
		}
	}else if(step == 2){
		for(int i = 0;i < g[id].size();i++)
		{
            int next = g[id][i];
            if(first < next || id < next || ismk[next] == 1)continue;
			if(is2[first][next] == 0){
				//is3[first][next] = 1;
				is2[first][next] = target[first].size()+1;
				B* ne = new B;
				ne->id = next;
				ne->num = 0;
				target[first].push_back(*ne);
			}
			target[first][is2[first][next]-1].k[target[first][is2[first][next]-1].num++] = id;
		}
	}
    ismk[id] = 0;
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
		if(--out[fg[i][0]] == 0){
			processOut(fg[i][0]);
		}
		fg[i].erase(fg[i].begin());
	}
}
int main()
{

    //freopen("E:\\data\\3738\\test_data.txt","r",stdin);
    //freopen("/projects/student/result.txt","w",stdout);
    double begin = clock();
    double end;
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
    //end = clock();
    //printf("%f\n",(end-begin)/CLOCKS_PER_SEC);
    //begin = clock();
	for(int i = 1;i < n+1;i++)
	{
		mkTargrt(i,i,1);
	}
    //end = clock();
    //printf("%f\n",(end-begin)/CLOCKS_PER_SEC);
    //begin = clock();
    for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] != 0)DFS(i,i);
    sort(ans,ans+anstot);
    printf("%d\n",anstot);
	end = clock();
	cout << b << endl;
    printf("%fs\n",(end-begin)/CLOCKS_PER_SEC);
	//double ti = clock() - t;
    //printf("%fs\n",ti/CLOCKS_PER_SEC);
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
}//记忆化搜索，未成功，结果不对
