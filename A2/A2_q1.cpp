#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector> 
#include <fstream>
using namespace std;
void days_to_go(vector <int> &fields,vector < vector<int> > &relations , int root ,int first_root);
int main(){
	int field=0,relation=0,root=0;
	cin >> field >> relation >> root ;
	vector <int> fields(field);
	vector < vector<int> > relations(relation,vector<int>(2));
	for (int i=0;i<field;i++) cin >> fields[i];
	for (int i=0;i<relation;i++) {
		cin >> relations[i][0] >> relations[i][1];
	}
	days_to_go(fields,relations,root,root);
}
void days_to_go(vector <int> &fields ,vector < vector<int> > &relations,int root,int first_root){
	int count=0;
	bool not_max=0,last=1;
	for (int i=0;i<relations.size();i++){
		if (relations[i][1]==root){
 			days_to_go(fields,relations,relations[i][0],first_root);
 		}
 	}
	 for (int i=0;i<relations.size();i++){
		if (relations[i][1]==root){
			last=0;	
 		}	
 	}
	if (last==1) return;
	else{
 	int max=0;
		for (int i=0;i<relations.size();i++){	
			if (relations[i][1]==root){
	 			if(fields[relations[i][0]]>max)	max=fields[relations[i][0]];
	 		}
 		}
			fields[root] += max;
	}
	if (root==first_root)	cout << fields[root];
}