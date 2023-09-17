 #include<iostream>
using namespace std;
class node{
public:
	int data;
	node *next;
	//constructor-->perametrized kyuki data ko d se denote kar rhe hain toh humne yaha par parameters define kar diye ya pass kar diye 
	node(int d){
		data=d;

		next=NULL;//initial functioning hain ki phele jo bhi next pointer bna ussko null par point karwao and this null cannot be accessed
	}
	//constructor ko define krne ka 2nd way
	// node(int d):data(d),next*(NULL);--->initialization list
};

void insert_at_front(node *&head,node*&tail,int data){
	node *n=new node(data);//new node formation
	if(head==NULL && tail==NULL){//usske bad check krega ki kya head null hain mtlb abhi tk ll create hi nhi hui hain
		head=n;
		tail=n;
	}
	else{
		n->next=head;
		head=n;
	}
	
}

void insert_at_tail(node *&head,node *&tail,int data){
	node *n=new node(data);//node bna liya 
	if(head ==NULL && tail==NULL){
		head=n;
		tail=n;
	}
	else{
		tail->next=n;
		tail=n;
	}
}

// //iterative way
int length(node *head){
	int count=0;
	while(head!=NULL){
		count++;
		head=head->next;
	}
	return count;
}
//recursive case
// int len_rec(node *head){
// 	if(head==NULL){
// 		return 0;
// 	}
// 	return 1+len_rec(head->next);
// }

void insert_at_any_position(node*&head,node*&tail,int data,int position){
	if(position==0){
		insert_at_front(head,tail,data);
	}
	else if(position>=length(head)){
		insert_at_tail(head,tail,data);
	}
	else{//n ke next mein address daal do
		// n ke previous mein n ka address daal do
		// link between n previous and n next dissolve kar do
		node *temp=head;
		node *n=new node(data);
		for(int i=1;i<=position-1;i++){
			temp=temp->next;
		}
		n->next=temp->next;
		temp->next=n;
	}
}

//deletion at front 
void delete_at_front(node *&head,node*&tail){
	if(head==NULL){
		return;
	}
	else if(head->next==NULL){
		delete head;
		head=NULL;
	}
	else{
		node *n=head;
		head=head->next;
		delete n;
	}
}

void delete_at_end(node *&head,node*&tail){
	if(head==NULL){
		return;
	}
	else if(head->next==NULL){
		delete head;
		head=NULL;
	}
	else{
		node *temp=head;
		while(temp->next!=tail){
			temp=temp->next;
		}
		delete tail;
		tail=temp;
		tail->next=NULL;
	}
}

void delete_at_any_position(node *&head,node*&tail,int position){
	if(position==0){
		delete_at_front(head,tail);
	}
	else if(position>=length(head)-1){
		delete_at_end(head,tail);
	}
	else{
		node *temp=head;
		for(int i=1;i<=position-1;i++){
			temp=temp->next;
		}
		node *n=temp->next;
		temp->next=n->next;
		delete n;
	}
}
//Iteration
node *search_ite(node*head,node*tail,int key){
	while(head!=NULL){
		if(head->data==key){
			return head;
		}
		head=head->next;
	}
	return NULL;
}

//recursive
node *search_rec(node*head,node*tail,int key){
	//base case
	if(head==NULL){
		return NULL;
	}
	if(head->data==key){
		return head;
	}
	//recursive case
	return search_rec(head->next,tail,key);

}
void print_ll(node *head){//yaha by reference pass nhi hoga kyuki hum sirf chahte hain ki ll print ho original ll mein koi change na ho
	while(head!=NULL){
		cout<<head->data<<"->";
		head=head->next;
	}
	cout<<"NULL";
	cout<<endl;
}
void reverse_ll(node *&head){
	node *current=head;
	node*previous=NULL;
	node *n=NULL;
	while(current!=NULL){
		n=current->next;
		current->next=previous;
		previous=current;
		current=n;
	}
	head=previous;

}

//caluculating mid point of ll without using length 
// complete it by mid point runner technique stated that we have two horses running in a race 
// if one hourse is running at x speed then the other will run at 2x speed
// this concluded that jis horse ki speed 2x hogi woh finish line par pauch jayega and dusra wala horse mid par pauchega 
node *mid_pint_runner_technique(node *head){
	if(head==NULL){
		return head;
	}
	node *slow = head;
	node *fast = head->next;//fast ko ek advantage hain ki woh head->next se strt krega which means pos 1 se strt krega this is done so as to get the first mid in even length linked list
	while(fast!=NULL && fast->next!=NULL){//phele humko check krna hain ki fast null toh nhi hain agar hain toh stop and agar fast null hain toh fast ka next access nhi kar sakte hain aayse conditon likhna zaruri hain
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}
  
node *merge(node *a,node *b){
	//base case
	if(a==NULL){
		return b;
	}
	if(b==NULL){
		return a;
	}

	//recursive case
	node *newhead;
	if(a->data<b->data){//1-->4-->6-->a
						//2-->3-->7-->b
		newhead=a;
		node *c=merge(a->next,b);
		newhead->next=c;
	}
	else{//2-->4-->6-->a
		 //1-->3-->7-->b
		newhead=b;
		node*d=merge(a,b->next);
		newhead->next=d;
	}
	return newhead;
}
node *merge_sort(node*head){
	//base case
	if(head==NULL || head->next==NULL){
		return head;
	}
	//recursive case
	//1)divide
	node *m=mid_pint_runner_technique(head);
	node *b=head;
	node*c=m->next;
	m->next=NULL;
	//2)sort
	b=merge_sort(b);
	c=merge_sort(c);
	//3)merge
	node *final_head=merge(b,c);
	return final_head;
}
bool is_cyclic(node*head){
	node *fast=head;
	node *slow=head;
	while(fast!=NULL && fast->next!=NULL){//liner
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow){
			return true;
		}

	}
	return false;
}
void create_cycle(node *head){
	node *temp=head;
	while(temp->next!=NULL){
		temp=temp->next;
	}
	temp->next=head->next->next;
}
void break_cycle(node *head){
	 node *fast=head;
	node *slow=head;
	while(fast!=NULL && fast->next!=NULL){//liner
		fast=fast->next->next;
		slow=slow->next;
		if(fast==slow){
			break_cycle;
		}  
	}
	node*prev=head;
	while(prev->next!=fast){
		prev=prev->next;
	}
	slow=head;
	while(slow!=fast){
		prev=fast;
		fast=fast->next;
		slow=slow->next;
	}
	prev->next=NULL;
}

int main(){
	// node n1(3);//data -->3 address -->null
	// node n2(4);//data->4 address->null
	// n1.next=&n2;//n1 ke next mein n2 ka address dal do
	// cout<<n1.data<<" "<<(*n1.next).data<<endl;//"<<(*n1.next).data--->n1 ki help se n2 ka data print kiya hain isska mtln n1 ke address ko derefer krna pdega and then usska data print krna pdega
	// cout<<n1.data<<" "<<n1->next.data<<endl;
	node *head=NULL , *tail = NULL;//head and tail 2 pointer create ho gye and they both are pointing to null
	// insert_at_front(head,tail,data);data-->jo bhi data dalna hain
	// insert_at_front(head,tail,5);
	// insert_at_front(head,tail,4);
	// insert_at_front(head,tail,1);
	// // insert_at_front(head,tail,2);
	// // insert_at_front(head,tail,1);
	// print_ll(head);

	// insert_at_tail(head,tail,6);
	// insert_at_tail(head,tail,7);
	// print_ll(head);
	// cout<<"length of linked list :"<<length(head)<<endl;

	// insert_at_any_position(head,tail,70,2);
	// print_ll(head);

	// cout<<"length of linked list :"<<length(head)<<endl;

	// delete_at_front(head,tail);
	// print_ll(head);
	// cout<<"length of linked list :"<<length(head)<<endl;

	// delete_at_end(head,tail);
	// print_ll(head);
	// cout<<"length of linked list :"<<length(head)<<endl;

	// delete_at_any_position(head,tail,2);
	// print_ll(head);
	// cout<<"length of linked list :"<<length(head)<<endl;

	// node *y=search_ite(head,tail,2);
	// if(y==NULL){
	// 	cout<<"Key not found"<<endl;
	// }
	// else{
	// 	cout<<"key found"<<endl;
	// }
	// print_ll(head);

	// node *x=search_ite(head,tail,1);
	// if(x==NULL){
	// 	cout<<"Key not found"<<endl;
	// }
	// else{
	// 	cout<<"key found"<<endl;
	// }
	// print_ll(head);

	// node *mid=mid_pint_runner_technique(head);
	// 	if(mid==NULL){
	// 		cout<<"mid does not exist"<<endl;
	// 	}
	// 	else{
	// 		cout<<"Mid exist at mid is"<<mid->data<<endl;
	// 	}

	// reverse_ll(head);
	// print_ll(head);
	// node *head2=NULL,*tail2=NULL;
	// insert_at_front(head2,tail2,6);
	// insert_at_front(head2,tail2,3);
	// insert_at_front(head2,tail2,2);
	// print_ll(head2);

	// node*final_head=merge(head,head2);
	// print_ll(final_head);

	insert_at_front(head,tail,5);
	insert_at_front(head,tail,32);
	insert_at_front(head,tail,11);
	insert_at_front(head,tail,90);
	insert_at_front(head,tail,34);
	insert_at_front(head,tail,10);
	// insert_at_front(head,tail,2);
	// insert_at_front(head,tail,1);
	print_ll(head);
	// merge_sort(head);
	// print_ll(head);
	
	create_cycle(head);
	if(is_cyclic(head)){
		cout<<"Yes Cyclic"<<endl;
	}
	else{
		cout<<"No cyclic"<<endl;
	}
	return 0; 
}