#include <cstdlib>
#include <iostream>
#include <string>
#include <vector> 
#include <fstream>
using namespace std;
void find_way(vector< string > &table,vector <char> true_way ,vector<vector <bool> > chart,int s1,int s2,int & end);
int main(){
	vector<string > table(1);
	vector<char> true_way;
	int i=0,end=0;
	int s1,s2;
	while(getline(cin, table[i])){
		i++;
		string s;
		table.push_back(s);
	}
	int size=table[0].size();
	vector<vector <bool> > chart(i,vector <bool> (size));
	for (int a=0;a<i;a++){
		for(int b=0;b<size;b++){
			chart[a][b]=0;
			if (table[a][b]=='S'){
				s1=a;
				s2=b;
			}
			if (table[a][b]=='#')	chart[a][b]=1;
		}
	}
	find_way(table,true_way,chart,s1,s2,end);
}
void find_way(vector<string> &table,vector <char> true_way,vector<vector <bool> > chart,int s1,int s2,int & end){
	int rows=chart.size(),column=chart[0].size();
	int i=0,j=0;
	chart[s1][s2]=1;
	if (end) return; 
	if (table[s1][s2]=='E'){
		for (int i=0;i<true_way.size();i++) cout << true_way[i];
		cout << endl;
		end=1;
		return;
	}
	else{
		if (chart[s1][s2+1]==chart[s1][s2-1] && chart[s1+1][s2]==chart[s1-1][s2] && chart[s1+1][s2]==chart[s1][s2+1] && chart[s1][s2+1]==1){
			cout << "NO SOLUTION" << endl;
			end=1;
			return;
		}
		if (table[s1][s2+1]!='#' && chart[s1][s2+1]==0){
			true_way.push_back('R');
			find_way(table,true_way,chart,s1,s2+1,end);
			true_way.pop_back();
		}
		if (table[s1][s2-1]!='#' && chart[s1][s2-1]==0){
			true_way.push_back('L');
			find_way(table,true_way,chart,s1,s2-1,end);
			true_way.pop_back();
		}
		if (table[s1+1][s2]!='#' && chart[s1+1][s2]==0){
			true_way.push_back('D');
			find_way(table,true_way,chart,s1+1,s2,end);
			true_way.pop_back();
		}
		if (table[s1-1][s2]!='#' && chart[s1-1][s2]==0){
			true_way.push_back('U');
			find_way(table,true_way,chart,s1-1,s2,end);
			true_way.pop_back();
		}
		else	return;
	}
}	