#include<bits/stdc++.h>
using namespace std;
class node{
	public:
	int id;       //storing id
	string name;
	node *next;
	vector<int> requests;      		//it stores the connection requests of the user
	vector<int> connections;		//it stores the accepted connections of the user
	node(int id1,string name1)
	{
		id=id1;
		name = name1;
		next = NULL;
	}
	//node(int rid){
	//	requests.push_back(rid);
//	}
};
	map<int,string> m;
node *insertion(int id, string name,node* head)		//inserting the profiles
{
	if(head==NULL) return new node(id,name);
	if(head!=NULL) 
		head->next=insertion(id,name,head->next);
	return head;
}
void display(node* head)			//displays the profiles in linkedin
{
	if(head == NULL) return;
	node* temp=head;
	while(temp!=NULL)
	{
		cout<<"UserProfile(User ID: "<<temp->id<<", Name:"<<temp->name<<")"<<endl;
		temp=temp->next;
	}
}
bool find(vector<int> arr,int gid){			//tells about existing connections in request
	for(int i=0;i<arr.size();i++){
		if(arr[i]==gid) return false;
	}
	return true;
}
//void vecdis(node* head){
//cout<<head->requests[0];
//}
void requesting(int uid,int oid,node* head){	//inserting request id's
	node* temp=head;
	while(temp->id!=oid){
		temp=temp->next;
	}
	temp->requests.push_back(uid);
	//vecdis(temp);
}
void connecting(int reqid,int accid,node* head){	//inserting connection id's
		node* temp=head;
	while(temp->id!=reqid){
		temp=temp->next;
	}
	if(find(temp->connections,accid))
	    temp->connections.push_back(accid);
//	cout<<"Viewing "<<temp->connections[0]<<endl;
}
void viewconnections(int lid,node* head){			//Displays all connections of userid
	node* temp=head;
	while(temp->id!=lid){
		temp=temp->next;
	}
	if(temp->connections.size()==0)
	 	cout<<" No connections "<<endl;
	for(int i=0;i<temp->connections.size();i++){
		cout<<" UserProfile(UserId: "<<temp->connections[i]<<", Name: "<<m[temp->connections[i]]<<")"<<endl;
	}
}
void checkrequests(int cid,node* head){			//checks the requests of userid
	node* temp=head;
	while(temp->id!=cid){
		temp=temp->next;
	}
	if(temp->requests.size()==0)
	cout<<" No requsets "<<endl;
	else{
		int n=temp->requests.size();
		for(int i=0;i<n;i++){
			cout<<" Connection request from "<<m[temp->requests[i]]<<" to "<<m[cid]<<endl;
			cout<<" Do you want to accept the request from "<<m[temp->requests[i]]<<" ?(y/n): ";
			char key;
			cin>>key;
			if(key=='n'){
				temp->requests.erase(temp->requests.begin()+i);
				i--;
			n=temp->requests.size();
			}
			else{
				if(find(temp->connections,temp->requests[i]))
				    temp->connections.push_back(temp->requests[i]);
				connecting(temp->requests[i],cid,head);
				temp->requests.erase(temp->requests.begin()+i);
				cout<<m[cid]<<" is now connected with "<<m[temp->requests[i]]<<endl;
			//	cout<<"Viewing "<<temp->connections[0]<<endl;
			i--;
			n=temp->requests.size();
			}
		}
	}
}
int main()
{
	node* head = NULL;
	while(1)
	{
		cout<<endl<<"Linkedin profile connection"<<endl;
		cout<<"1. Add Profile"<<endl;
		cout<<"2. View Profile"<<endl;
		cout<<"3. Send Connection Request"<<endl;
		cout<<"4. Manage connections requsets"<<endl;
		cout<<"5. Views connections"<<endl;
		cout<<"6. Close System"<<endl;
		cout<<endl<<"Enter your choice : ";
		int n;
		cin>>n;
		if(n==6)
		{
			cout<<"Exiting the System";
			break;
		}
		switch(n)
		{
			case 1: {
				cout<<endl<<"Enter Id : ";
				int id;
				cin>>id;
//				s.insert(id);
				while(m.find(id)!=m.end()){
					cout<<"Id Already exists"<<"\nEnter id: ";
					cin>>id;                                      //asks for new id if entered id already exists
				}
				cout<<"Enter your name : ";
				string name;
				cin>>name;
				m[id]=name;
				cout<<endl;
				head=insertion(id,name,head);				//adding the users details
				cout<<"Profile for "<<name<<" added successfully."<<endl;
				break;
			}
			case 2:
				display(head);								//displays the profiles
				break;
			case 3:{
				cout<<"Enter Your id: ";
				int uid;
				cin>>uid;
				int oid;
				cout<<"Enter User ID to send connection request : ";
				cin>>oid;
				if(m.find(uid)!=m.end()&& m.find(oid)!=m.end()){			//checks if entered id's valid or not
					requesting(uid,oid,head);			//adding the id's of requesting user to the acceptor profile 
					cout<<"Connection request sent from "<<m[uid]<<" to "<<m[oid]<<endl;
				}
				break;
			}
			case 4:{
				cout<<"Enter your User Id to manage connection requests : ";
				int id;
				cin>>id;
				checkrequests(id,head);						//checks for managing the connection requets
				break;
			}
			case 5:{
				cout<<"Enter your User id to view connections:";
				int l;
				cin>>l;
				cout<<m[l]<<"'s connections:"<<endl;
				viewconnections(l,head);						//displays all the connnection of the user
				break;
			}
			default: cout<<"Enter valid option"<<endl;
		}
	}
	return 0;
}