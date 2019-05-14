#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector> 
#include <fstream>
using namespace std;
int power(int base,int pow);
void code_gray(vector<vector <int> >& v,int n);
int main(){
	int n;
	cin >> n;
	vector< vector<int> > v (2,vector <int> (n));
	v[0][0]=0;
	v[1][0]=1;
	code_gray(v,n);
}
int power(int base,int pow){
	int i=0,ans=1;
	for(i=0;i<pow;i++) ans=ans*base;
		return ans;
}
void code_gray(vector<vector <int> >& v,int n){
	int i=0,j=0,size=v.size(),jazr=0;
	if (size==power(2,n)){/*checking the end */
		for (i=0;i<power(2,n);i++){
			for(j=n-1;j>=0;j--)	cout << v[i][j];
		cout << endl;
		}
		return; 
	}
	for (i=0;i<size;i++){ /* double the size of vector with the previeus values */
		vector <int> a(n);
		v.push_back(a);
	}
	for (i=size;i<v.size();i++){
		for (j=0;j<n;j++){
			v[i][j]=v[v.size()-i-1][j];/* above comment */
		}
	}
	for(i=0;i<v.size();i++){ /* add the next value to each vector (in the double vector)*/
		for (jazr=0;power(2,jazr)!= v.size();jazr++);
		if (i<size) v[i][jazr-1]=0;
		else v[i][jazr-1]=1; 
	}
	code_gray(v,n);
}