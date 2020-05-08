#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
#define N 4000005
#define M 2000005

using namespace std;

struct node{
	int to;
	int cost;
	bool operator < (const struct node b) const{
		if(to < b.to)return 1;
		else return 0;
	}
};
vector<node> g[N];
vector<node> fg[N];

struct nd{
    int from;
    int to;
	int cost;
}rd[M];
unordered_map<int,int> mp;
unordered_map<int,bool> is;
struct B{
	int a;
	int b;
	int fcost;
	int lcost;
};
vector<unordered_map<int,vector<B>>> target;
//unordered_map<int,int> itv;
int itv[N];
int yid[N];

int isD[N];
int stk[10];
int top;
unordered_set<int> st[N];
int ans3[15000005][3],ans4[15000005][4],ans5[15000005][5],ans6[15000005][6],ans7[15000005][7];
int anstot3,anstot4,anstot5,anstot6,anstot7;
void creatAns()
{
	if(top == 3){
		for(int i = 0;i < 3;i++)
			ans3[anstot3][i] = yid[stk[i]];
		anstot3++;
	}else if(top == 4){
		for(int i = 0;i < 4;i++)
			ans4[anstot4][i] = yid[stk[i]];
		anstot4++;
	}else if(top == 5){
		for(int i = 0;i < 5;i++)
			ans5[anstot5][i] = yid[stk[i]];
		anstot5++;
	}else if(top == 6){
		for(int i = 0;i < 6;i++)
			ans6[anstot6][i] = yid[stk[i]];
		anstot6++;
	}else if(top == 7){
		for(int i = 0;i < 7;i++)
			ans7[anstot7][i] = yid[stk[i]];
		anstot7++;
	}
}
/*void creatAns()
{
	switch(top){
		case 3:
			for(int i = 0;i < 3;i++)
				ans3[anstot3][i] = stk[i];
			anstot3++;
			break;
		case 4:
			for(int i = 0;i < 4;i++)
				ans4[anstot4][i] = stk[i];
			anstot4++;
			break;
		case 5:
			for(int i = 0;i < 5;i++)
				ans5[anstot5][i] = stk[i];
			anstot5++;
			break;
		case 6:
			for(int i = 0;i < 6;i++)
				ans6[anstot6][i] = stk[i];
			anstot6++;
			break;
		case 7:
			for(int i = 0;i < 7;i++)
				ans7[anstot7][i] = stk[i];
			anstot7++;
	}
}*/
int c;
int Next;
int in[N];
int out[N];
void DFS(int first,int id,int cost,int fcost)
{
    isD[id] = 1;
    stk[top++] = id;
	//if(top)c++;//faster
	if(top == 4){
		int i = itv[id];
		if(i){
			i--;
			unordered_map<int,vector<B>>::iterator it;
			if((it = target[i].find(first)) != target[i].end()){
				for(int j = 0;j < (it->second).size();j++)
				{
					if(isD[(it->second)[j].a] == 1 || isD[(it->second)[j].b] == 1 || (it->second)[j].fcost/((double)cost) < 0.2 || (it->second)[j].fcost/((double)cost) > 3 || ((double)fcost)/(it->second)[j].lcost < 0.2 || ((double)fcost)/(it->second)[j].lcost > 3)continue;
					stk[top++] = (it->second)[j].a;
					stk[top++] = (it->second)[j].b;
					creatAns();
					top -= 2;
				}
			}
		}
	}
	if(top == 5){
		int i = itv[id];
		if(i){
			i--;
			unordered_map<int,vector<B>>::iterator it;
			if((it = target[i].find(first)) != target[i].end()){
				for(int j = 0;j < (it->second).size();j++)
				{
					if(isD[(it->second)[j].a] == 1 || isD[(it->second)[j].b] == 1 || (it->second)[j].fcost/((double)cost) < 0.2 || (it->second)[j].fcost/((double)cost) > 3 || ((double)fcost)/(it->second)[j].lcost < 0.2 || ((double)fcost)/(it->second)[j].lcost > 3)continue;
					stk[top++] = (it->second)[j].a;
					stk[top++] = (it->second)[j].b;
					creatAns();
					top -= 2;
				}
			}
		}
	}
	int num_of_edge = g[id].size();
	node z;
	z.to = stk[0];
	int ii = lower_bound(g[id].begin(),g[id].end(),z)-g[id].begin();
	for(int i = ii;i < num_of_edge;i++)
    {
        //if((Next = g[id][i].to) < first)continue;
		Next = g[id][i].to;
		if(top >= 3 && Next == stk[0] && ((double)g[id][i].cost)/cost >= 0.2 && ((double)g[id][i].cost)/cost <= 3 && fcost/((double)g[id][i].cost) >= 0.2 && fcost/((double)g[id][i].cost) <= 3){
			creatAns();
			if(top == 5)break;
		}
        if(isD[Next] == 0 && top < 5){
			if(top == 1)DFS(first,Next,g[id][i].cost,g[id][i].cost);
			else if(((double)g[id][i].cost)/cost >= 0.2 && ((double)g[id][i].cost)/cost <= 3){
			if(top >= 3 && st[Next].find(stk[0]) == st[Next].end())continue;
			DFS(first,Next,g[id][i].cost,fcost);}
        }
    }
    isD[id] = 0;
    top--;
    return;
}
bool ismk[N];
void mktarget(int first,int second,int id,int step,int cost,int cost2)
{
	if(ismk[id])return;
	ismk[id] = 1;
	if(step == 1){
		int jie = g[id].size();
		for(int i=0;i < jie;i++)
			mktarget(first,second,g[id][i].to,step+1,g[id][i].cost,g[id][i].cost);
	}else if(step == 2){
		st[first].insert(id);
		int jie = g[id].size();
		for(int i=0;i < jie;i++)
			if(cost2 <= 5*g[id][i].cost && g[id][i].cost <= 3*cost2)
				mktarget(first,id,g[id][i].to,step+1,cost,g[id][i].cost);
	}else if(step == 3){
		st[first].insert(id);
		int jie = g[id].size();
		for(int i=0;i < jie;i++)
		{
			if(cost2 <= 5*g[id][i].cost && g[id][i].cost <= 3*cost2)
				mktarget(first,id,g[id][i].to,step+1,cost,g[id][i].cost);
			if(first < g[id][i].to || second < g[id][i].to || id < g[id][i].to || ismk[g[id][i].to] || cost2 > 5*g[id][i].cost || g[id][i].cost > 3*cost2)continue;
			//st[first].insert(g[id][i].to);mktarget(first,id,g[id][i].to,step+1,cost,g[id][i].cost);
			if(!itv[first]){
				itv[first] = target.size()+1;
				unordered_map<int,vector<B>> a;
				a.clear();
				vector<B> b;
				b.clear();
				B c;
				c.a = second;
				c.b = id;
				c.fcost = cost;
				c.lcost = g[id][i].cost;
				b.push_back(c);
				a[g[id][i].to] = b;
				target.push_back(a);
			}else{
				int j = itv[first]-1;
				if(target[j].find(g[id][i].to) == target[j].end()){
					vector<B> a;
					a.clear();
					B c;
					c.a = second;
					c.b = id;
					c.fcost = cost;
					c.lcost = g[id][i].cost;
					a.push_back(c);
					target[j][g[id][i].to] = a;
				}else{
					B c;
					c.a = second;
					c.b = id;
					c.fcost = cost;
					c.lcost = g[id][i].cost;
					target[j][g[id][i].to].push_back(c);
				}
			}
		}
	}else{
		st[first].insert(id);
		int jie = g[id].size();
		for(int i=0;i < jie;i++)
		{
			if(first < g[id][i].to || second < g[id][i].to || id < g[id][i].to || ismk[g[id][i].to] || cost2 > 5*g[id][i].cost || g[id][i].cost > 3*cost2)continue;
			st[first].insert(g[id][i].to);
		}
	}
	ismk[id] = 0;
}
void processIn(int i)
{
	in[i] = -1;
	int num_of_edge = g[i].size();
	for(int j = 0;j < num_of_edge;j++)
        if(--in[g[i][j].to] == 0)processIn(g[i][j].to);
}
void processOut(int i)
{
	out[i] =  -1;
	int num_of_edge = fg[i].size();//
	for(int j = 0;j < num_of_edge;j++)
		if(--out[fg[i][j].to] == 0)processOut(fg[i][j].to);
}
int main()
{
    //freopen("/data/test_data.txt","r",stdin);
    //freopen("/projects/student/result.txt","w",stdout);
    int t = clock();
    int n = 0;
    int m = 0;
    while(scanf("%d,%d,%d",&rd[m].from,&rd[m].to,&rd[m].cost) != EOF)
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
	node tmp;
    for(int i = 0;i < m;i++)
    {
		int s = mp[rd[i].from];
		int t = mp[rd[i].to];
		tmp;
		tmp.to = t;
		tmp.cost = rd[i].cost;
		g[s].push_back(tmp);
		tmp.to = s;
		fg[t].push_back(tmp);
        in[t]++;
		out[s]++;
    }
	//double tt = clock();
	//cout << (tt - t)/CLOCKS_PER_SEC << endl;
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
		if(in[i] > 0 && out[i] > 0)sort(g[i].begin(),g[i].end());
	//cout << (clock()-tt)/CLOCKS_PER_SEC << endl;
	//tt = clock();
	for(int i = 1;i < n+1;i++)
		 if(in[i] > 0 && out[i] > 0)mktarget(i,0,i,1,0,0);
	//cout << (clock() - tt)/CLOCKS_PER_SEC << " mktarget" << endl;
	//tt = clock();
	for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] > 0)DFS(i,i,0,0);
	//cout << (clock() - tt)/CLOCKS_PER_SEC << " DFS" << endl;
    //sort(ans,ans+anstot);
	int anstot = anstot3 + anstot4 + anstot5 + anstot6 + anstot7;
    printf("%d\n",anstot);
	//cout << b << endl;
	double ti = clock() - t;
    printf("%fs\n",ti/CLOCKS_PER_SEC);
    /*for(int i = 0;i < anstot3;i++)
    {
		printf("%d",ans3[i][0]);
		for(int j =  1;j < 3;j++)
			printf(",%d",ans3[i][j]);
		printf("\n");
    }
	for(int i = 0;i < anstot4;i++)
    {
		printf("%d",ans4[i][0]);
		for(int j =  1;j < 4;j++)
			printf(",%d",ans4[i][j]);
		printf("\n");
    }
	for(int i = 0;i < anstot5;i++)
    {
		printf("%d",ans5[i][0]);
		for(int j =  1;j < 5;j++)
			printf(",%d",ans5[i][j]);
		printf("\n");
    }
	for(int i = 0;i < anstot6;i++)
    {
		printf("%d",ans6[i][0]);
		for(int j =  1;j < 6;j++)
			printf(",%d",ans6[i][j]);
		printf("\n");
    }
	for(int i = 0;i < anstot7;i++)
    {
		printf("%d",ans7[i][0]);
		for(int j =  1;j < 7;j++)
			printf(",%d",ans7[i][j]);
		printf("\n");
    }*/
	exit(0);
    return 0;
}
