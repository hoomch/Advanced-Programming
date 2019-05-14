#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector> 
#include <fstream>
using namespace std;
int power(int base,int pow);
int f(int *a,int n);
int main(){
	int n=0,*a,i=0;
	cin >> n;
	a = new int [n];
	for (i=0;i<n;i++)	cin >> a[i];
	cout << f(a,n-1);
}
int power(int base,int pow){
	int i=0,ans=1;
	if (pow==0) return 1;
	else for (i=0;i<pow;i++)	ans=ans*base;
		return ans;
}
int f(int *a,int n){
	if (n<0) return 0;
	return power(-1,n)*a[n] + f(a,n-1);
}