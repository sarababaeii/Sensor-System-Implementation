#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max_n 1000

//left to right: +1	   right to left: -1
//down to up: +2       up to down: -2

int a[max_n][max_n];
int m, n;

void init(int m, int n){
	int i, j;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			a[i][j] = 0;
}
void input(){
	int m0, m1; //m0->/=1 & m1->\=-1 
	scanf("%d%d%d%d", &m, &n, &m0, &m1);
	init(m,n);
	int i, j;
	for (i=0; i<m0+m1; i++){
		int x, y;
		scanf("%d%d", &x, &y);
		if (i<m0)
			a[x-1][y-1] = 1;
		else
			a[x-1][y-1] = -1;
	}
}
int next_path(int pp, int mir){ //gets: perevious path and mirror of current cell. returns: next path.
	if (mir==0)
		return pp;
	int ans=3^abs(pp); //11^1=10  11^10=1 (binary)
	if (mir*pp<0) //m<0&pp>0 or m>0&pp<0
		ans *= -1;
	return ans;
}
int next_mirror(int p, int x, int y){ //gets: perevious path and coordinate of curren mirror. returns: next mirror.
	p = next_path(p,a[x][y]);
	int i;
	if(p==1){
		for (i=y+1; i<n; i++)
			if (a[x][i]!=0)
				return x*n+i;
		if (x==m-1)
			return m*n-1;
	}
	if (p==-1)
		for (i=y-1; i>=0; i--)
			if (a[x][i]!=0)
				return x*n+i;
	if (p==2)
		for (i=x-1; i>=0; i--)
			if (a[i][y]!=0)
				return i*n+y;
	if (p==-2)
		for (i=x+1; i<m; i++)
			if (a[i][y]!=0)
				return i*n+y;
	return -1;
}
int solve(int p, int x, int y){
	int t;
	t = next_mirror(p,x,y);
	if (t==-1)
		return 0;
	if (t==m*n-1)
		return 1;
	return solve(next_path(p,a[x][y]),(t-t%n)/n,t%n);
}
int main(){
	int I;
	for (I=0; 1; I++){
		input();
		printf("case %d: ", I+1);
		int i, j;
		int t=solve(1,0,0);
		if (t==1)
			printf("0\n");
		else{
			int num=0, xans=m-1, yans=n-1;
			for (i=0; i<m; i++)
				for (j=0; j<n; j++){
					if (a[i][j]==0){
						a[i][j] = 1;
						if (solve(1,0,0)==1){
							num++;
							if (i*i+j*j<xans*xans+yans*yans){
								xans = i;
								yans = j;
							}
						}
						a[i][j] = -1;
						if (solve(1,0,0)==1){
							num++;
							if (i*i+j*j<xans*xans+yans*yans){
								xans = i;
								yans = j;
							}
						}
						a[i][j] = 0;
					}
				}
			if (num==0)
				printf("impossible\n");
			else
				printf("%d %d %d\n", num, xans+1, yans+1);
		}
	}
	return 0;
}
