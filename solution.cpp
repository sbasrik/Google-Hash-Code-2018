#include <bits/stdc++.h>
#define pb push_back
#define fi first
#define sc second
#define inf 1000000000
#define MP make_pair
#define orta ((a+b)/2)
#define min3(a,b,c) min(a,min(b,c))
#define max3(a,b,c) max(a,max(b,c))
#define dbg(x) cerr<<#x<<":"<<x<<endl
#define N 100005
#define MOD 1000000007
#define H '#'
using namespace std;
typedef  long long int lint;
typedef  pair <int ,int> ii;

class Ride{
public:
    ii startp;
    ii finishp;
    ii tm;
    int number;
    lint uzak;
    // Baslangic yerleri, bitis yerleri , baslangic zamani + bitis zamani;
};


vector < Ride > rides;
pair <lint,int> uz[N];
priority_queue < pair <ii , ii> > q;
// Time, ID , PLACE

int R,C,f,n,bonus,maxTime;
vector <int> print[N]; // print answer
int dist(ii a,ii b)
{
    return abs(b.fi-a.fi)+abs(b.sc-a.sc);
}
void read()
{
    scanf("%d %d",&R,&C);
    scanf("%d %d",&f,&n);
    scanf("%d %d",&bonus,&maxTime);
    
    for (int i = 0; i < n; i++)
    {
        Ride tmp;
        scanf("%d %d %d %d %d %d",&tmp.startp.fi,&tmp.startp.sc,&tmp.finishp.fi,&tmp.finishp.sc,&tmp.tm.fi,&tmp.tm.sc);
        tmp.number=i;
        if(dist(tmp.startp,tmp.finishp)<=(tmp.tm.sc-tmp.tm.fi))
            rides.pb(tmp);
        
    }
   	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			uz[i].fi+=dist(rides[i].finishp,rides[j].startp);
		rides[i].uzak=uz[i].fi/n;
		uz[i].sc=i;
	}
    for (int i = 0; i < f; i++)
    {
        q.push(MP(MP(0,i),MP(0,0)));
    }
}
//MAX POINT ==  BEST CAR
double point(pair <ii , ii>  car,Ride rd)
{
    //~ int ret=0;
    //~ printf("%d %d\n",rd.tm.sc,car.fi.fi + dist(car.sc,rd.startp) + dist(rd.startp,rd.finishp));
    if(rd.tm.sc < car.fi.fi + dist(car.sc,rd.startp) + dist(rd.startp,rd.finishp))
        return -1;
    
    //~ int ft=
    int bz= max(car.fi.fi + dist(car.sc,rd.startp),  rd.tm.fi);
    //~ if(car.fi.fi + dist(car.sc,rd.startp) <= rd.tm.fi)
    //~ bz-=bonus;
    //~ ret= dist(rd.startp,rd.finishp);
    //~ printf("%d %d %lf\n",ret,bz,(double)ret/(ret+bz));
    return inf - bz ;
}

double tolerance=10;

bool fs(Ride a,Ride b){
    if(a.tm.sc-dist(a.startp,a.finishp)!=b.tm.sc-dist(b.startp,b.finishp))
        return a.tm.sc-dist(a.startp,a.finishp)<b.tm.sc-dist(b.startp,b.finishp);
    if(a.tm.fi!=b.tm.fi)
        return a.tm.fi<b.tm.fi;
    return dist(a.startp,a.finishp)<dist(b.startp,b.finishp);
}

void DOIT()
{
    while(n && !q.empty())
    {
        pair <ii , ii> tmp=q.top();
        q.pop();
        tmp.fi.fi=-tmp.fi.fi;
        //~ printf("%d %d\n",tmp.fi.fi,tmp.fi.sc);
        int plc=-1;
        double best=-1;
        sort(rides.begin(),rides.begin()+n,fs);
        for (int i = 0; i < n; i++)
        {
            double po=point(tmp,rides[i]);
            //~ printf("%lf\n",po);
            if(po>best && fabs(po-best)>tolerance)
            {
                best=po;
                plc=i;
            }
        }
        if(best==-1)
        {
            continue;
        }
        print[tmp.fi.sc].pb(rides[plc].number);
        tmp.fi.fi=max(rides[plc].tm.fi, tmp.fi.fi+dist(rides[plc].startp,tmp.sc)) + dist(rides[plc].startp,rides[plc].finishp) ;
        tmp.sc=rides[plc].finishp;
        swap(rides[plc],rides[n-1]);
        n--;
        tmp.fi.fi=-tmp.fi.fi;
        q.push(tmp);
    }
}
void yaz()
{
    for (int i = 0; i < f; i++)
    {
        printf("%d ",(int)print[i].size());
        for (int j = 0; j < (int)print[i].size() ; j++)
            printf("%d ",print[i][j]);
        printf("\n");
    }
}
int main()
{
    //~ srand(time(NULL));
    //~ freopen("b_should_be_easy.in","r",stdin);
    //~ freopen("b_should_be_easy.out","w",stdout);
     //~ freopen("c_no_hurry.in","r",stdin);
    //~ freopen("c_no_hurry.out","w",stdout);
    //~ freopen("d_metropolis.in","r",stdin);
    //~ freopen("d_metropolis.out","w",stdout);
    freopen("e_high_bonus.in","r",stdin);
    freopen("e_high_bonus.out","w",stdout);
    read();
    DOIT(); // Just
    yaz();
}
