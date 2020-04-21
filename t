#include <bits/stdc++.h>
#include <unordered_map>
#define N 600005
#define M 300005

using namespace std;

int g[N][50];
int fg[N][50];

struct nd{
    int from;
    int to;
}rd[M];
unordered_map<int,int> mp;
unordered_map<int,bool> is;
struct B{
	int a;
	int b;
};
vector<unordered_map<int,vector<B>>> target;
//unordered_map<int,int> itv;
int itv[N];
int yid[N];

int isD[N];
int stk[10];
int top;
/*struct A{
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
}ans[3000005];*/
int ans3[3000005][3],ans4[3000005][4],ans5[3000005][5],ans6[3000005][6],ans7[3000005][7];
int anstot3,anstot4,anstot5,anstot6,anstot7;
/*void creatAns()
{
	ans[anstot].id[0] = yid[stk[0]];
	ans[anstot].num = top;
	for(int i = 1;i < top;i++)
		ans[anstot].id[i] = yid[stk[i]];
	ans[anstot++].id[top] = -1;
}*/
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
void DFS(int first,int id)
{
    isD[id] = 1;
    stk[top++] = id;
	//if(top)c++;//faster
	if(top == 5){
		int i = itv[id];
		if(i){
			i--;
			unordered_map<int,vector<B>>::iterator it;
			if((it = target[i].find(first)) != target[i].end()){
				for(int j = 0;j < (it->second).size();j++)
				{
					if(isD[(it->second)[j].a] == 1 || isD[(it->second)[j].b] == 1)continue;
					stk[top++] = (it->second)[j].a;
					stk[top++] = (it->second)[j].b;
					creatAns();
					top -= 2;
				}
			}
		}
	}
	int num_of_edge = g[id][0];
	for(int i = 1;i <= num_of_edge;i++)
    {
        if((Next = g[id][i]) < first)continue;
        if(isD[Next] == 1){
            if(top >= 3 && Next == stk[0]){
				creatAns();
				if(top == 6)break;
			}
        }else{
            if(top < 6)DFS(first,Next);
        }
    }
    isD[id] = 0;
    top--;
    return;
}
bool ismk[N];
void mktarget(int first,int second,int id,int step)
{
	if(ismk[id])return;
	ismk[id] = 1;
	if(step == 1){
		int jie = g[id][0];
		for(int i=1;i <= jie;i++)
			mktarget(first,second,g[id][i],step+1);
	}else if(step == 2){
		int jie = g[id][0];
		for(int i=1;i <= jie;i++)
			mktarget(first,id,g[id][i],step+1);
	}else{
		int jie = g[id][0];
		for(int i=1;i <= jie;i++)
		{
			if(first < g[id][i] || second < g[id][i] || id < g[id][i] || ismk[g[id][i]])continue;
			if(!itv[first]){
				itv[first] = target.size()+1;
				unordered_map<int,vector<B>> a;
				a.clear();
				vector<B> b;
				b.clear();
				B c;
				c.a = second;
				c.b = id;
				b.push_back(c);
				a[g[id][i]] = b;
				target.push_back(a);
			}else{
				int j = itv[first]-1;
				if(target[j].find(g[id][i]) == target[j].end()){
					vector<B> a;
					a.clear();
					B c;
					c.a = second;
					c.b = id;
					a.push_back(c);
					target[j][g[id][i]] = a;
				}else{
					B c;
					c.a = second;
					c.b = id;
					target[j][g[id][i]].push_back(c);
				}
			}
		}
	}
	ismk[id] = 0;
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
	for(int i = 1;i < n+1;i++)
		if(in[i] > 0 && out[i] > 0)sort(g[i]+1,g[i]+1+g[i][0]);
	for(int i = 1;i < n+1;i++)
		 if(in[i] > 0 && out[i] > 0)mktarget(i,0,i,1);
	for(int i = 1;i < n+1;i++)
        if(isD[i] == 0 && in[i] > 0)DFS(i,i);
    //sort(ans,ans+anstot);
	int anstot = anstot3 + anstot4 + anstot5 + anstot6 + anstot7;
    printf("%d\n",anstot);
	//cout << b << endl;
	//double ti = clock() - t;
    //printf("%fs\n",ti/CLOCKS_PER_SEC);
    for(int i = 0;i < anstot3;i++)
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
    }
	exit(0);
    return 0;
}
