#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector> 
#include <fstream>
using namespace std;
int id=0;
struct student{
	string name;
	string lname;
	string email;
	string phone_number;
	int id;
};
typedef struct student student;

void read_csv(vector <student>& stu);
void write_csv(vector <student>& stu);


void add_student(vector <student>& stu);
void search_student(vector <student>& stu,string s_search);
void delete_student(vector <student>& stu,int id_stu);
void update_student(vector <student>& stu,int update_id);

bool check_valid_email(string email);
bool check_valid_phone_number(string phone_number);
bool check_valid_id(vector <student>& stu,int Id);

int check_id(vector <student>& stu,int Id);

int main(){
	vector <student> stu;
	string operate,sub_operate;
	int del,update;
	read_csv(stu);
	while (cin >> operate){
		if (operate=="add") add_student(stu);
		else if (operate=="search"){
			cin >> sub_operate;
			search_student(stu,sub_operate);
		}
		else if (operate=="delete"){
			cin >> del;
			delete_student(stu,del);
		}
		else if (operate=="update"){
			cin >> update;
			update_student(stu,update);
		}
	}
}
void add_student(vector <student> & stu){
	string checker;
	string name,lname,email,phone_number;
	char c=' ';
	int count=0,counts=0,i=0,fail=0,fali_name=0,fail_lname=0,name_check;
	student s; 	
	while((s.name.length()==0 || s.lname.length()==0 || s.email.length()==0 || s.phone_number.length()==0) && counts<4 ){/*check the fields given */
		cin >> checker;
		counts++;
		if (fail==1) break;
		else{
			if (checker=="-f") {
				count++;
				cin >> name;
				for (i=0;i<stu.size();i++){
					if (name==stu[i].name){
						fali_name=1;
						name_check=i;
						break;
					}
				}
			}
			if (checker=="-l") {
				count++;
				cin >> lname;
				for (i=0;i<stu.size();i++){
					if (lname==stu[i].lname && name_check==i){
						fail_lname=1;
						break;
					}
				}
			}
			if (checker=="-e"){
				cin >> email;
				if (check_valid_email(email)==true){
					count++;
					for (i=0;i<stu.size();i++){
						if (email==stu[i].email){
							fail=1;
							break;
						}
					}
				}
			}
			if (checker=="-p"){
				cin >> phone_number;
				if (check_valid_phone_number(phone_number)==true){
					count++;
					for (i=0;i<stu.size();i++){
						if (phone_number==stu[i].phone_number){
							fail=1;
							break;
						}
					}
				}
			}
			if (fali_name==1 && fail_lname==1) fail=1;
		}
		c=getchar(); 
		if (c=='\n') break;
	}
	if (fail==0 && count==4){/*add was succesfully*/
		s.name=name;
		s.lname=lname;
		s.email=email;
		s.phone_number=phone_number;
		s.id=id;
		id++;
		stu.push_back(s);
		cout << "Command Ok"<<endl;
	}
	else cout << "Commans Failed" << endl;
	write_csv(stu);
}
bool check_valid_email(string email){
	int i=0,j=0;
	bool validation=0;
	for (i=0;i<email.size()-1;i++){
		if (email[i]=='@'){
			for(j=i+1;j<email.size();j++){
				if (email[j]=='@' || email[j]=='-'){ 
					break;
					validation=0;
				}
				else if (email[j]=='.' && (j-i!=1)) validation=1;
			}
		}
	}
	return validation;
}
bool check_valid_phone_number(string phone_number){
	int i=0,j=0;
	bool flag=1;
	if (phone_number[0]=='0' && phone_number[1]=='9' && phone_number.size()==11){
		for (i=2;i<phone_number.size();i++){
			if (((int)phone_number[i]<48) || ((int)phone_number[i]>57)) flag=0;
		}
	}
	else flag=0;
	return flag;
}
void search_student(vector <student>& stu,string s_search){
	int i=0,j=0,k=0,count=0,flag=0;
	for (i=0;i<stu.size();i++){
		flag=0;
		if (flag!=1 && s_search.size()<=stu[i].name.size()){
			for (j=0;j<stu[i].name.size()-s_search.size()+1;j++){
				count=0;
				for(k=0;k<s_search.size();k++){
					if (s_search[k]!=stu[i].name[j+k]) break;
					else count++;
				}
				if (count==s_search.size()) flag=1;
			}
		}
		if (flag!=1 && s_search.size()<=stu[i].lname.size()){
			for (j=0;j<stu[i].lname.size()-s_search.size()+1;j++){
				count=0;
				for(k=0;k<s_search.size();k++){
					if (s_search[k]!=stu[i].lname[j+k]) break;
					else count++;
				}
				if (count==s_search.size()) flag=1;
			}
		}
		if (flag!=1 && s_search.size()<=stu[i].email.size()){
			for (j=0;j<stu[i].email.size()-s_search.size()+1;j++){
				count=0;
				for(k=0;k<s_search.size();k++){
					if (s_search[k]!=stu[i].email[j+k]) break;
					else count++;
				}
				if (count==s_search.size()) flag=1;
			}
		}
		if (flag!=1 && s_search.size()<=stu[i].phone_number.size()){
			for (j=0;j<stu[i].phone_number.size()-s_search.size()+1;j++){
				count=0;
				for(k=0;k<s_search.size();k++){
					if (s_search[k]!=stu[i].phone_number[j+k]) break;
					else count++;
				}
				if (count==s_search.size()) flag=1;
			}
		}
		if (flag==1)
			cout << stu[i].id << " " << stu[i].name << " " << stu[i].lname << " " << stu[i].email << " " << stu[i].phone_number << endl ;
	}
}
void delete_student(vector <student>& stu,int id_stu){
	int i=0,erased=0;
	for(i=0;i<stu.size();i++){
		if (stu[i].id==id_stu){
			stu.erase(stu.begin()+i);
			cout << "Command Ok" << endl;
			erased=1;
			break;
		}
	}
	if (erased==0) cout << "Command Failed" << endl;
}
bool check_valid_id(vector <student>& stu,int Id){
	int i=0;
	bool flag=0;
	for(i=0;i<stu.size();i++){
		if (stu[i].id==Id){
			flag=1;
			break;
		}
	}
	return flag;
}
int check_id(vector <student>& stu,int Id){
	int i=0,ret;
	for(i=0;i<stu.size();i++){
		if (stu[i].id==Id){
			ret=i;
			return ret;
		}
	}
	return -1;
}
void update_student(vector <student> & stu,int update_id ){
	string checker;
	string name,lname,email,phone_number;
	char c=' ';
	int count=0,n=0,fail=0,fali_name=0,fail_lname=0,name_check,i=0,lname_check=0;
	if (check_valid_id(stu,update_id)==1){
		n=check_id(stu,update_id);
		if(check_id(stu,update_id)!=-1){
			while(c!='\n'){/*check the end of the operation */
				cin >> checker;
				if (fail==1) break;
				else{
					if (checker=="-f") {
						count++;
						cin >> name;
						for (i=0;i<stu.size();i++){				
							if (name==stu[i].name && i!=n){
								break;
							}
						}
						
					}
					if (checker=="-l") {
						count++;
						cin >> lname;
						if (lname==stu[i].lname && name_check==n){
							break;
						}
					}
					if (checker=="-e"){
						cin >> email;
						if (check_valid_email(email)==true){
							count++;
							for (i=0;i<stu.size();i++){	
								if (email==stu[i].email && i!=n){
									fail=1;
									break;
								}
							}
						}
						else fail=1;
					}
					if (checker=="-p"){
						cin >> phone_number;
						if (check_valid_phone_number(phone_number)==true){
							count++;
							for (i=0;i<stu.size();i++){	
								if (phone_number==stu[i].phone_number && i!=n){
								fail=1;
								break;
							}
							}
						}
						else fail=1;
					}
					if (fali_name==1 && fail_lname==1) fail=1;

				}
				c=getchar(); 
				if (c=='\n') break;
			}
		}
	}
	if (name.size()==0) name=stu[n].name;
	if (lname.size()==0) lname=stu[n].name;
	for (i=0;i<stu.size();i++){
		if (name==stu[n].name && lname==stu[i].lname && i!=n) fail=1;
	}
	if (fail==0 && count!=0){/*no fail + there is at least one change */
		if (name.size()!=0)	stu[n].name=name;
		if (lname.size()!=0)	stu[n].lname=lname;
		if (email.size()!=0)	stu[n].email=email;
		if (phone_number.size()!=0)	stu[n].phone_number=phone_number;
		cout << "Command Ok"<<endl;
	}
	else cout << "Command Failed" << endl;
}
void read_csv(vector <student>& stu){
	int field=0,i=0;
	fstream input;
	string line;
	input.open("contacts.csv",ios::in);
	while (getline(input, line))
    {
    	field=0;
    	student s;
    	for (i=0;i<line.size();i++){
    		if (line[i]==',')
    			field++;
    		else{
    			if (field==0) s.name += line[i];
    			else if (field==1) s.lname += line[i];
    			else if (field==2) s.email += line[i];
    			else if (field==3) s.phone_number += line[i];	
    		}
    	}
    	s.id=id;
    	id++;
    	stu.push_back(s);
	}
	input.close();
}
void write_csv(vector <student>& stu){
	int i=0;
	fstream output;
	output.open("contacts.csv",ios::out);
	for (i=0;i<stu.size();i++)
		output << stu[i].name << ',' << stu[i].lname << ',' << stu[i].email << ',' << stu[i].phone_number << endl;
	output.close();
}
