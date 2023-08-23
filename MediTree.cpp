#include<iostream>
#include<string>
#include<cstring>
using namespace std;
// patient record class
class patientrec
{
public:
	int id;
	string name;
	string date;
	string disease;
	string status;
// default constructor
patientrec()
{
	id=0;
	name=".";
	date=".";
	disease=".";
	status=".";
}
// parameterized constructor
patientrec(int ID,string n, string d, string dis,string s)
{
	id=ID;
	name=n;
	date=d;
	disease=dis;
	status=s;
}
};
// node class
class tnode
{
public:
	patientrec rec;
	tnode* right;
	tnode* left;
	int height;
};
// hospital data class
class hospitaldata
{
	tnode* root;
	int size;
public:
// default constructor
hospitaldata()
{
	root=nullptr;
	size=0;
}
//helper function for getheight
int max(int x, int y)
{
	if(x>y)
	{
		return x;
	}
	else
	{
		return y;
	}
}
// to get height of a node
int getheight(tnode* r)
{
	if(r==nullptr)
	{
		return -1;
	}

	return 1+max(getheight(r->left),getheight(r->right));
}
// wrapper function
int getheight()
{
	return getheight(root);
}
// rotate right function
void ror(tnode* & x)
{
	tnode* y=x->left;
	x->left=y->right;
	y->right=x;
	x->height=1+max(getheight(x->right),getheight(x->left));
	y->height=1+max(getheight(y->left),x->height);
	x=y;
}
// rotate left function
void rol(tnode* & x)
{
	tnode* y=x->right;
	x->right=y->left;
	y->left=x;
	x->height=1+max(getheight(x->right),getheight(x->left));
	y->height=1+max(getheight(y->right),x->height);
	x=y;
}
// insert function
void insert(tnode* & r,patientrec p1)
{
	
	if(r==nullptr)
	{
		r= new tnode;
		r->rec=p1;
		r->right=nullptr;
		r->left=nullptr;
		r->height=0;
		size++;
		return;
	}
	else if(r->rec.id>p1.id)
	{
		insert(r->left,p1);
			ror(r);
	}
	else
	{
		insert(r->right,p1);
			rol(r);
		
	}
	r->height=1+ max(getheight(r->right),getheight(r->left));
}
// wrapper function for insert
void insert(patientrec p1)
{
	insert(root,p1);
}
// function to get level of a node
int level(tnode* r, int ID)
{
	if(r->rec.id==ID)
	{
		return 0;
	}
	else
	{
		if(r->rec.id>ID)
		{
		return 1+level(r->left, ID);
		}
		else
		{
			return 1+level(r->right, ID);
		}
	}
}
// searches if a node is present in the hospital data or not
tnode* searchnode(tnode* r, int ID)
{
	while(r!=nullptr)
	{
		if(r->rec.id==ID)
		{
			return r;
			break;
		}
		else if(r->rec.id>ID)
		{
			r=r->left;
		}
		else
		{
			r=r->right;
		}
	}
	if(r==nullptr)
	{
		cout<<"Record does not exist"<<endl;
	return nullptr;
	}
}
// checks if a node is present or not and then moves it to the desired level if it is present
tnode*searchif(int ID, int k)
{
	tnode* temp=searchnode(root,ID);
	if(temp!=nullptr)
	{
		search(root,ID,k);
	}
	return temp;
}
// searches the node and moves it to the desired level
void search(tnode*& r,int ID, int k)
{
	if(r->rec.id==ID)
	{
		return;
	}
	else if(r->rec.id>ID)
	{
		search(r->left,ID,k);
		
			
		if(k<=level(root,r->rec.id))
		{
			ror(r);
		}
	}
	else
	{
		search(r->right,ID,k);
		
		if(k<=level(root,r->rec.id))
		{
			rol(r);
		}
		
	}
	
}
// prints the data of the admitted patients
void outputall(tnode* r)
{
	if(r!=nullptr)
	{
		outputall(r->left);
		if(r->rec.status!="Discharged")
		{
		  cout<<"patient id:"<<r->rec.id<<endl;
           cout<<"patient name:"<<r->rec.name<<endl;
           cout<<"patient's date of admission:"<<r->rec.date<<endl;
           cout<<"patient's disease:"<<r->rec.disease<<endl;
           cout<<"patient's status:"<<r->rec.status<<endl;
		   
		}
		outputall(r->right);
	}
}
// wrapper function
void outputall()
{
	outputall(root);
}
// outputs the data of a specific patient
void output(tnode* r,int ID)
{
  while(r!=nullptr)
  {
	  if(r->rec.id==ID)
	  {
		   cout<<"patient id:"<<r->rec.id<<endl;
           cout<<"patient name:"<<r->rec.name<<endl;
           cout<<"patient's date of admission:"<<r->rec.date<<endl;
           cout<<"patient's disease:"<<r->rec.disease<<endl;
           cout<<"patient's status:"<<r->rec.status<<endl;
		   break;
		 
	  }
	  else if(r->rec.id>ID)
	  {
		  r=r->left;
	  }
	  else
	  {
		  r=r->right;
	  }
  }
}
// wrapper function
void output(int ID)
{
	output(root,ID);
}
// finds the maximum id in a subtree, helper function for remove
tnode* findmax(tnode* r)
{
	while(r->right!=nullptr)
	{
		r=r->right;
	}

	return r;
}
// function to remove a patient's data
tnode* remove(tnode*& r, int ID)
{
	if(r==nullptr)
	{
		return r;
	}
	else if(r==root && root->rec.id==ID)
	{
		if(r->right==nullptr)
		{
			tnode* temp=r->left;
			delete r;
			size--;
			root=temp;
			return temp;
		}
		else if(r->left==nullptr)
		{
			tnode* temp=r->right;
			delete r;
			size--;
			root=temp;
			return temp;
		}
		else
		{
			tnode* temp=findmax(r->left);
			r->rec.id=temp->rec.id;
			r->left=remove(r->left,temp->rec.id);
		}
	}

	else if(r->rec.id>ID)
	{
		r->left=remove(r->left,ID);
	}
	else if(r->rec.id<ID)
	{ r->right=remove(r->right,ID);

	}
	else
	{
		if(r->right==nullptr)
		{
			tnode* temp=r->left;
			delete r;
			size--;
			return temp;
		}
		else if(r->left==nullptr)
		{
			tnode* temp=r->right;
			delete r;
			size--;
			return temp;
		}
		else
		{
			tnode* temp=findmax(r->left);
			r->rec.id=temp->rec.id;
			r->left=remove(r->left,temp->rec.id);
		}
	}
		return r;
	
	}
// wrapper function
void remove(int ID)
{
	remove(root,ID);
}
// function to edit a patient's record
void edit(tnode* & r, int i, string n, string d, string dis, string s)
{
	if(r->rec.id==i)
	{
		r->rec.name=n;
		r->rec.date=d;
		r->rec.disease=dis;
		r->rec.status=s;
		return;
	}
	else if(r->rec.id>i)
	{
		edit(r->left,i,n,d,dis,s);
	}
	else
	{
		edit(r->right,i,n,d,dis,s);
	}
}
// wrapper function
void edit(int i, string n, string d, string dis, string s)
{
	edit(root, i,  n,  d,  dis, s);
}
// calculates the sum of all the ids, helper function for splitree()
int getsum(tnode* r)
{
	if(r==nullptr)
	return 0;

	else
	{
		int sum=r->rec.id;
		sum=sum+getsum(r->left);
		sum=sum+getsum(r->right);
		return sum;
	}
}
// finds the median of the tree and then moves it to level 0 and returns it's right subtree
hospitaldata* splitree()
{
	int median;
	median=(getsum(root))/size;
	search(root,median,0);

	hospitaldata* r= new hospitaldata;
	r->root=root->right;
	tnode* temp=root->left;
	delete root;
	root=temp;
	return r;

}

//print function which prints the ids in order
void print(tnode* r)
	{
		if(r!=nullptr)
		{
		print(r->left);
		cout<<r->rec.id<<" ";
		print(r->right);
		}
	}
// wrapper function
void print()
	{
		print(root);
	}
};
int main()
{
	patientrec r1(6,"Manal","16-10-21","Memory loss","Admitted");
	patientrec r2(4,"Malaika","19-08-21","Malaria","Discharged");
	patientrec r3(10,"Wardah","02-09-21","Covid","Admitted");
	patientrec r4(2,"Zahida","01-07-21","Flu","Discharged");
	patientrec r5(5,"Eimaan","21-03-21","Dry cough","Admitted");
	patientrec r6(8,"Elise","18-02-21","Rabies","Discharged");
	patientrec r7(12,"Albab","14-05-21","Migraine","Admitted");
	patientrec r8(7,"Sauria","04-04-21","Arthritis","Discharged");
	patientrec r9(9,"Azulfa","02-01-21","Diabetes","Discharged");
	patientrec r10(11,"Nimra","07-08-21","Head injury","Admitted");
	patientrec r11(14,"Sameera","09-10-21","Covid","Admitted");



	// inserting data
	hospitaldata H;
	H.insert(r11);
	H.insert(r10);
	H.insert(r9);
	H.insert(r8);
	H.insert(r7);
	H.insert(r6);
	H.insert(r5);
	H.insert(r4);
	H.insert(r3);
	H.insert(r2);
	H.insert(r1);
	cout<<"Hospital Management System:"<<endl;

	// printing the data of patients who are admitted
	cout<<"----------------------------------------------------------------"<<endl;
	cout<<"Printing the data of admitted patients:"<<endl;
    H.outputall();
	//cout<<"---------------------------------------------------------------"<<endl;

	// printing the record of a specific patient
	cout<<"Printing the record of patient with id 5:"<<endl;
	H.output(5);
	cout<<"----------------------------------------------------------------"<<endl;

	//searching an existing node and moving it a level up
	cout<<"Searching patient id 4 and moving it to level 2:"<<endl;
	H.searchif(4,2);
	H.print();
	cout<<endl;
	cout<<"----------------------------------------------------------------"<<endl;

	//searching a node which is not present in the hospital data
	cout<<"Searching an id which does not exist in the hospital data:"<<endl;
	H.searchif(13,1);
	cout<<"----------------------------------------------------------------"<<endl;

	// deleting a node
	cout<<"Deleting the patient's record with id :"<<endl;
	H.remove(6);
	H.print();
	cout<<endl;
	cout<<"----------------------------------------------------------------"<<endl;
	
	//editing a patient's record
	cout<<"Editing a patient's record with id 2:"<<endl;
	H.edit(2,"Hunaina","11-11-21","Dengue","Admitted");
	H.output(2);
	cout<<"----------------------------------------------------------------"<<endl;

	//splitting the tree
	cout<<"Splitting the tree:"<<endl;
	hospitaldata *newtree=H.splitree();
	cout<<"Tree after splitting:"<<endl;
	H.print();
	cout<<endl;
	// printing the new tree
	cout<<"New tree:"<<endl;
	newtree->print();
	cout<<endl;
	cout<<"----------------------------------------------------------------"<<endl;









	system("pause");
	return 0;
}







