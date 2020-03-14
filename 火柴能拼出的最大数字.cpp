#include <cstdio>
#include <cmath>
#include <vector>
#include <climits>
using namespace std;
int number[10] = { 0,1,2,3,4,5,6,7,8,9 };
int expend[10] = { 0,2,5,5,4,5,6,3,7,6 };
int main() {
	int n, m;
	scanf("%d", &n);
	scanf("%d", &m);
	vector<bool> canuse(10, false);
	vector<int> dp(n+1,0);
	for (int i = 0; i<m; i++) {
		int temp;
		scanf("%d", &temp);
		canuse[temp] = true;
	}
	dp[0]=0;
	for(int i=1;i<=n;i++){
		int choice=0;
		int maxvalue=0;
		for(int j=1;j<=9;j++){
			if(canuse[j]) {
				if(i-expend[j]<0) continue;
				if(dp[i-expend[j]]==-1) continue;
				if(dp[i-expend[j]]>=maxvalue){
					choice=j;
					maxvalue=dp[i-expend[j]];
				}
			}
		}
		if(choice==0) dp[i]=-1;
		else{
			dp[i]=maxvalue*10+choice;
		}
		printf("%d\n",dp[i]);
	}
	printf("%d",dp[n]);
	return 0;
}
