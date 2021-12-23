#include<iostream>
#include<stdio.h>
#include<gdbm.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

char key_buffer[400],record_buffer[2048];
datum key,record;

class Commodity{
        protected:
                char cname[50],s_email[50],c_id[20],hbidder[50];
                int weight;
                float price;
                bool active=false;
        public:
                friend class DBMS;
                friend class Admin;
                Commodity(){}
                void get_function()
                {
                        cout<<"Enter seller email:"<<endl;
                        cin>>s_email;
                        cout<<"Enter name of commodity:"<<endl;
                        cin>>cname;
                        cout<<"Enter commodity ID:"<<endl;
                        cin>>c_id;
                        cout<<"Enter weight of commodity:"<<endl;
                        cin>>weight;
                        cout<<"Enter price of commodity:"<<endl;
                        cin>>price;
                        strcpy(hbidder,"nil");
                        cout<<"\n";
                }
                
                Commodity(const char *cn, const char *sm,const char *id,int w,float p,bool a,const char *h){
                        strcpy(cname,cn);
			 strcpy(s_email,sm);
                        strcpy(c_id,id);
                        strcpy(hbidder,h);
                        weight=w;
                        price=p;
			 active=a;
                }
                
		void set_price(float p){price=p;}
		
               static void create_key(const char *c_id)
               {
                        strcpy(key_buffer,c_id);
                        key.dptr=key_buffer;
                        key.dsize=strlen(key_buffer);
                        return;

                }
                
                static void create_record(Commodity c)
                {
                        sprintf(record_buffer,"%s %s %s %d %f %d %s",c.cname,c.s_email,c.c_id,c.weight,c.price,c.active,c.hbidder);
                        record.dptr=record_buffer;
                        record.dsize=strlen(record_buffer);
                        return;
                }
                
		bool state(){return active;}
		
                void accept_bid(float p,char* i){
			price=p;
			strcpy(hbidder,i);
		}
		
		void close_bid(){active=false;}
		
		bool activate(){active=true;return active;}
		
		void display_Commodity(){
			cout<<"COMMODITY ID : "<<c_id<<endl;
        		cout<<"COMMODITY NAME : "<<cname<<endl;
        		cout<<"COMMODITY PRICE : "<<price<<endl;
        		cout<<"HIGHEST BIDDER : "<<hbidder<<endl;
        		cout<<"status : "<<active<<endl;
		}
		
		float get_price(){return price;}

};







class Seller				                                                      //seller class
{
	protected:
		char email_id[50];
		char sname[25];
		long int mob;
		int age;
		float rating=5,balance=0;
		bool accept=false;
		bool active=false;
	public:	
		Seller(){}					                                //constructor
		friend class DBMS;
		friend class Admin;
		void get_function()			                                        // function to get input from the user
		{
			cout<<"\n Enter your name  :  ";
	  		cin>>sname;
	  		cout<<"\n Enter your email id  : ";
	  		cin>>email_id; 
	  		cout<<"\n Enter your age : ";
			cin>>age;
	  		cout<<"\n Enter your mobile number : ";
			cin>>mob;
	  		
		}
		
		Seller(const char* n,const char* c,long int f,int a,float b,bool g,float h,bool ac)			//parameterized constructor 
		{
			strcpy(sname,n);
			strcpy(email_id,c);
			mob=f;
			age=a;
			rating=b;
			accept=g;
			balance=h;
			active=ac;
		}
		~Seller(){}			//destructor
		
		// functions that return's values of seller class variables to the main section
		
		
		bool get_accept(void){return accept;}
		
		
		static void create_key(const char *email_id)  		// to create key
		{
			strcpy(key_buffer,email_id);
			key.dptr=key_buffer;
			key.dsize=strlen(key_buffer);
			return;
		}
		
		static void create_record(Seller e)					// to create record
		{
			sprintf(record_buffer," %s %s %ld %d %f %d %f %d",e.sname,e.email_id,e.mob,e.age,e.rating,e.accept,e.balance,e.active);
			record.dptr=record_buffer;
			record.dsize=strlen(record_buffer);
			return;
		}
		
		//function to update rating of the seller based on successfull completion of bidding process i.e bool accept
		
	    void update_rating()									
		{
		  if(accept==false)
		    {
		       rating=rating-0.1;
		       if(rating==5)
		       rating=5;
		    }
		  else
		    {
		       rating=rating+0.1;
		       if(rating>=5)
		       rating=5;
		       return ; 
		    }
		}
		
		// fuction on link bank account with trading account of the seller
		
		
		void activate(){active=true;}
		
		
		void link_bankAccnt()
		{
			int c;
			printf("\n Enter amount to be credited to your account  : ");
			cin>>balance;
			cout<<"\n Bank Balance is  :  "<<balance<<endl;
			return ;
		}
		void set_accept(){
			cout<<"Will you accept the outcome"<<endl;
			cout<<"1.YES"<<endl;
			cout<<"2.NO"<<endl;
			int x;
			cin>>x;
			if(x==1)accept=true;
			else accept=false;
		}
		
};	// seller class ends here







class Buyer
{
	protected:
		char name[25],email[50];
		int age, phone_no;
        	float balance=0;
		bool active=false;
		bool accept=false;
    	public:
		friend class DBMS;
		friend class Admin;
		Buyer(){}
		Buyer(const char *n,long unsigned ph,const char *e,float b,bool a,bool i,int g){   
		       strcpy(name,n);
               	strcpy(email,e);
               	phone_no=ph;
               	age=g;
               	balance=b;
               	accept=a;
               	active=i;
         	}
		
        	~Buyer(){}
        	float get_balance(){return balance;}
		void link_bankAccnt()
		{   
			
			printf("\n Enter amount to be credited to your account  : ");
			cin>>balance;
			cout<<"\n Bank Balance is : "<<balance<<endl;
			return ;
		}
		
		void get_function()
		{
				cout<<"\n Enter your name  :  ";
				cin>>name;
				cout<<"\n Enter email id  :  ";
				cin>>email;
				cout<<"\n Enter your phone number  :  ";
				cin>>phone_no;
				cout<<"\n Enter age  :  ";
				cin>>age;
		}

       	static void create_key(const char *email)
       	{
              		strcpy(key_buffer,email);
              		key.dptr=key_buffer;
              		key.dsize=strlen(key_buffer);
              		return;
       	 }
       	 
    	   	static void create_record(Buyer b)
       	{
          		sprintf(record_buffer,"%s %d %s %f %d %d %d",b.name,b.phone_no,b.email,b.balance,b.accept,b.active,b.age);
          		record.dptr=record_buffer;
          		record.dsize=strlen(record_buffer);
          		return;
		}
		void set_accept(){
			cout<<"Will you accept the outcome"<<endl;
			cout<<"1.YES"<<endl;
			cout<<"2.NO"<<endl;
			int x;
			cin>>x;
			if(x==1)accept=true;
			else accept=false;
		}
		
		void update_rating()									
		{
		  active=accept;
		}
		
		void activate(){active=true;}
};





	
       // dbms class for storing adding,deleting.updating and fetching details from database

class DBMS 				
{
protected:	
	GDBM_FILE dbf=NULL;	                                                       // gdbm file pointer dbfs		
public:	
	DBMS(const char *db_name){ 				                                 //db_name is db.sellbook
		dbf=gdbm_open(db_name,0,GDBM_WRCREAT,0666,NULL);					//creating database
		if(dbf==NULL){
			  cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			  exit(1);
		}
	}
	~DBMS(){gdbm_close(dbf);}				// closing dbfs
			
			
			
			
	void add_Seller(Seller s){	// function to add seller details by creating record and key
			Seller::create_key(s.email_id);
			Seller::create_record(s);
			int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
			if(ret_val) cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			else cout<<"\n Seller added Successfully \n";
	}
		
		// function to fetch seller details by creating a new key in the database aswell as creating the records with the corresponding key
		
	Seller fetch_Seller(const char *email_id){
			Seller::create_key(email_id);
			datum record=gdbm_fetch(dbf,key);
			if(record.dptr==NULL)cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			char n[25],c[20];
			long int f;
			int a,g,ac;
			float b,h;
			strncpy(record_buffer,record.dptr,record.dsize);
			record_buffer[record.dsize]='\0';
			free(record.dptr);
			sscanf(record_buffer," %s %s %ld %d %f %d %f %d",n,c,&f,&a,&b,&g,&h,&ac);
			return Seller(n,c,f,a,b,g,f,ac);
	}
		
		// function to update seller details by overwriting the existing key with updated details and storing it in the database with the corresponding key
		
	void update_Seller(Seller s){
			Seller::create_key(s.email_id);
			Seller::create_record(s);
			int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
			if(ret_val) cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			else cout<<"\n Seller Details Updated \n";
	}
	
	
	
	
	     
	void add_Buyer(Buyer b){
			Buyer::create_key(b.email);
			Buyer::create_record(b);
            		int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Buyer added successfully \n";
        }
     	Buyer fetch_Buyer(const char *email){
	 		Buyer::create_key(email);
            		datum record=gdbm_fetch(dbf,key);
            		if(record.dptr==NULL)cout<<"GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		char n[100],e[50];
            		int ph,g;
			float b;
			int a,i;
			char record_buffer[1024];
            		strncpy(record_buffer,record.dptr,record.dsize);
            		record_buffer[record.dsize]='\0';
            		free(record.dptr);
            		sscanf(record_buffer,"%s %d %s %f %d %d %d",n,&ph,e,&b,&a,&i,&g);
            		return Buyer(n,ph,e,b,a,i,g);
	}
		
	void update_Buyer(Buyer b){
			Buyer::create_key(b.email);
			Buyer::create_record(b);
            		int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Buyer updated successfully \n";
      	}
		
		
		
		
		
	void add_Commodity(Commodity c){
                	 Commodity::create_key(c.c_id);
                	 Commodity::create_record(c);
                        int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
                        if(ret_val)cout<<"GDBM Error: "<<gdbm_strerror(gdbm_errno)<<endl;
                        else cout<<"Commodity details added successfully"<<endl;
       }
       Commodity fetch_Commodity(const char *c_id){
                        Commodity::create_key(c_id);
                        datum record=gdbm_fetch(dbf,key);
                        if(record.dptr==NULL)cout<<"GDBM Error : "<<gdbm_strerror(gdbm_errno)<<endl;
                        char cn[100],sm[100],id[100],h[50];
                        int w,a;
                        float p;
                        strncpy(record_buffer,record.dptr,record.dsize);
			 record_buffer[record.dsize]='\0';
                        free(record.dptr);
                        sscanf(record_buffer,"%s %s %s %d %f %d %s",cn,sm,id,&w,&p,&a,h);
                        return Commodity(cn,sm,id,w,p,a,h);
       }
       void delete_Commodity(const char *c_id){
                        Commodity::create_key(c_id);
                        int ret_val=gdbm_delete(dbf,key);
                        if(ret_val)cout<<"GDBM Error: "<<gdbm_strerror(gdbm_errno)<<endl;
                        else cout<<"Commodity details successfully deleted"<<endl;
       }
       void update_Commodity(Commodity c){
			Commodity::create_key(c.c_id);
			Commodity::create_record(c);
            		int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Commodity updated successfully \n";
      	}	
}; 
                     // dbms class ends here


class Admin : public Commodity, public Seller, public Buyer{
	public:
	       void approve_user(Buyer b,Seller s,DBMS d){
	       	cout<<"Select the type of user"<<endl;
			cout<<"1.Buyer"<<endl;
			cout<<"2.Seller"<<endl;
			int x;
			cin>>x;
	       	char i[20];
      	  		cout<<"\nEnter the User id : ";
      	  		cin>>i;
      	  		if(x==1){
      	  			b=d.fetch_Buyer(i);
      	  			b.activate();
      	  		}
      	  		else{
      	  			s=d.fetch_Seller(i);
      	  			s.activate();
      	  		}
      	  	    	
      	  	     	
	       }
	       void start_bid(Commodity c,DBMS d){
	       	char i[20];
      	  		cout<<"\nEnter the Commodity id : ";
      	  		cin>>i;
      	  		float p;
	       	cout<<"\nEnter the Commodity price : ";
      	  	    	cin>>p;
      	  		cout<<"\n";
      	  		c=d.fetch_Commodity(i);
      	  		c.set_price(p);
      	  	    	bool j=c.activate();
      	  	     	d.update_Commodity(c);
      	  	     	if(j==true){cout<<"Bidding started"<<endl;}
      	  	     	else cout<<"Bidding has not start"<<endl;
	       }
	       void close_bid(Commodity c,DBMS d){
	       	char i[20];
      	  		cout<<"\nEnter the Commodity id : ";
      	  		cin>>i;
      	  		cout<<"\n";
      	  		c=d.fetch_Commodity(i);
      	  		c.close_bid();
      	  		if(c.hbidder!="nil"){
      	  			Buyer b=d.fetch_Buyer(c.hbidder);
      	  			Seller s=d.fetch_Seller(c.s_email);
      	  			s.update_rating();
      	  			b.update_rating();
      	  	     		if(b.accept==true && s.accept==true){
      	  	     			int com=c.price/200;
      	  	     			cout<<"A commission of Rs"<<com<<" taken by both parties. "<<endl;
      	  	     			b.balance=b.balance-c.price-com;
      	  	     			s.balance=s.balance+c.price-com;
      	  	     			
      	  	     		}
      	  	     		else cout<<"item was not sold Bidding closed"<<endl;
      	  	     		d.update_Commodity(c);
      	  	     		d.update_Buyer(b);
      	  	     		d.update_Seller(s);
      	  	     	}
      	  	     	else cout<<"No one bidded on the item, item NOT SOLD"<<endl;	
      	  	     	
	       }
};


int main()
{
	DBMS d("db.trading");			// d is an object of class dbms 
	int ch,m,r,e,j,k;
    	Seller s;
    	Buyer b;
    	Commodity c;
    	Admin a;
    	const char *sna,*email;
    	char *mail;	
    	while(ch!=4)					//display control
    	{
      		cout<<"\n \t\t\t========================================\n";
      		cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
     		cout<<"\n \t\t\t========================================\n\n";
      		cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      		cout<<"\n\t\t\t  1. ADMIN";
      		cout<<"\n\t\t\t  2. BUYER";
      		cout<<"\n\t\t\t  3. SELLER";
      		cout<<"\n\t\t\t  4. EXIT";
      		cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      		cout<<"\n \t\t\t========================================";
      		cout<<"\n\t\t\t Enter Your choice  :  ";
      		cin>>ch;
      		cout<<"\n";
      switch(ch)
      {
        case 1: 
         {
          do
          {	
          	cout<<"\n \t\t\t========================================\n";
      	  	cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
      	  	cout<<"\n \t\t\t========================================\n\n";
      	  	cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      	  	cout<<"\n\t\t\t  1. APPROVE USER";
      	  	cout<<"\n\t\t\t  2. START BID";
      	  	cout<<"\n\t\t\t  3. CLOSE BID";
      	  	cout<<"\n\t\t\t  4. Back";
      	  	cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      	  	cout<<"\n \t\t\t========================================";
      	  	cout<<"\n\t\t\t Enter Your choice  :  ";
      	  	cin>>m;
      	  	cout<<"\n";
      	  	switch(m)
      	  	{
      	  	
      	  	 case 1:
      	  	      {
      	  	      a.approve_user(b,s,d);
      	  	       break;
      	  	      
      	  	      }
      	  	 case 2:
      	  	      {
      	  	      a.start_bid(c,d);
      	  	       break;
      	  	      
      	  	      }
      	  	 case 3:
      	  	      {
      	  	       a.close_bid(c,d);
      	  	       break;
      	  	       }
      	  	 case 4:  
      	  	 	  {  
      	  	 	   
      	  	       break; 	  	      
      	  	      }
             }
          }while(m!=4);
          break;
         }
         
        case 2:
        {
         while(r!=3)
         {
            cout<<"\n \t\t\t========================================\n";
      		cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
     		cout<<"\n \t\t\t========================================\n\n";
      		cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      		cout<<"\n\t\t\t  1. CREATE BUYER";
      		cout<<"\n\t\t\t  2. LOGIN";
      		cout<<"\n\t\t\t  3. back";
      		cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      		cout<<"\n \t\t\t========================================";
      		cout<<"\n\t\t\t Enter Your choice  :  ";
      		cin>>r;
      		cout<<"\n";
      		switch(r)
      		{
      			case 1:
      				{      	  	
      	 				cout<<"\n Enter the details as a buyer ...........\n";  
	 			   		b.get_function();              			
						d.add_Buyer(b);
						cout<<"\n";             	      
      	  	      		break;      	  	      
      	  	      	}
      	  	 	case 2:
      	  	      	{	char i[20];
        			cout<<"Enter the Buyer e-mail : ";
        			cin>>i; 
        			b=d.fetch_Buyer(i); 
      	  	      		do{	
            					cout<<"\n";
            					cout<<"\n";
            					cout<<"\n \t\t\t========================================\n";
      						cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
     						cout<<"\n \t\t\t========================================\n\n";
      						cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      						cout<<"\n\t\t\t  1. LINK ACCOUNT";
      						cout<<"\n\t\t\t  2. SEARCH COMMIDITY";
      						cout<<"\n\t\t\t  3. BID ON COMMIDITY";
      						cout<<"\n\t\t\t  4. ACCEPT BID";      						
      						cout<<"\n\t\t\t  5. Back";
      						cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      						cout<<"\n \t\t\t========================================";
      						cout<<"\n\t\t\t Enter Your choice  :  ";
      						cin>>j;
      						cout<<"\n";
      						switch(j)      						
      						{
      							case 1:{
      						  
      								cout<<"\n Link your bank account to become a part of bidding process...\n";
  			   					b.link_bankAccnt();
								d.update_Buyer(b);   	  	
      	 							break;      	  	      
      	  	      					}
      	  	 					case 2:{
      	  	      						char i[20];
      	  	      						cout<<"Enter the Commodity id : ";
        							cin>>i; 
        							
        							c=d.fetch_Commodity(i);
        							c.display_Commodity();
      	  	       					break;
      	  	      
      	  	      					}
      	  	 					case 3:{
      	  	       					char j[20];
      	  	      						cout<<"Enter the Commodity id : ";
        							cin>>j; 
        							c=d.fetch_Commodity(j);  
        							bool x=c.state();
        							if(x==1){
        								float p=c.get_price();
        								float bid;
        								cout<<p<<" is the current value of item"<<endl;
        								cout<<"\nEnter your bid : ";
        								cin>>bid;
        								if(p<bid){
        									if(b.get_balance()>=bid){
        										c.accept_bid(bid,i);
        										d.update_Commodity(c);
        									}
        									else cout<<"Buyer does not have sufficient balance"<<endl;
        								}   	
        								else cout<<"Please enter a value greater than current price"<<endl;  
        							}	       
        							else cout<<"Bidding is closed for this commodity"<<endl; 
      	  	       					break;
      	  	      
      	  	        				}
      	  	        			case 4:{
      	  	       					b.set_accept();
      	  	       					break;      	  	      
      	  	        				}
      	  	        			case 5:
      	  	        			{
      	  	        					break;
      	  	        					}      	  	        				
             				}      	  	      
      	  	      	}while(j!=5);
      	  	      	break;
      	  	      	}
      	  	 	case 3:{
      	  	        	break;
      	  	        	}
          }
          
         }
         break;
         }
         
        case 3:
        {
         do
         {  
         	cout<<"\n";
         	cout<<"\n";
            cout<<"\n \t\t\t========================================\n";
      		cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
     		cout<<"\n \t\t\t========================================\n\n";
      		cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      		cout<<"\n\t\t\t  1. CREATE SELLER";
      		cout<<"\n\t\t\t  2. LOGIN";
      		cout<<"\n\t\t\t  3. Back";
      		cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      		cout<<"\n \t\t\t========================================";
      		cout<<"\n\t\t\t Enter Your choice  :  ";
      		cin>>e;
      		cout<<"\n";
      		switch(e)
      		{
      			case 1:
      				{  
      				    cout<<"\n Enter the details as a seller ...........\n";  
	 			   		s.get_function();
	 			   		d.add_Seller(s);
						cout<<"\n";             	      
      	  	      		break;      	  	      
      	  	      	}
      	  	 	case 2:
      	  	      	{	char i[20];
        			cout<<"Enter the Seller e-mail : ";
        			cin>>i; 
        			s=d.fetch_Seller(i); 
      	  	      		while(k!=4)
        				 {
            				cout<<"\n";
            				cout<<"\n";
            				cout<<"\n \t\t\t========================================\n";
      						cout<<"\n\t\t\t  WELCOME TO COMMIDITY TRADING CENTER  \n";
     						cout<<"\n \t\t\t========================================\n\n";
      						cout<<"\n \t\t\t  * * * * * * * * * * * * * * * ";
      						cout<<"\n\t\t\t  1. LINK ACCOUNT";
      						cout<<"\n\t\t\t  2. ADD COMMIDITY";
      						cout<<"\n\t\t\t  3. ACCEPT BID";
      						cout<<"\n\t\t\t  4. Back";
      						cout<<"\n\t\t\t   * * * * * * * * * * * * * * *\n";
      						cout<<"\n \t\t\t========================================";
      						cout<<"\n\t\t\t Enter Your choice  :  ";
      						cin>>k;
      						cout<<"\n";
      						switch(k)      						
      						{
      							case 1:{
      								 cout<<"\n Link your bank account to become a part of bidding process....\n";      
  			   					 s.link_bankAccnt();
			   					 d.update_Seller(s);   	  	
      	 							 break;      	  	      
      	  	      					}
      	  	 					case 2:{
      	  	 						c.get_function();
      	  	 						d.add_Commodity(c);
      	  	       					break;
      	  	   
      	  	      					}
      	  	 					case 3:{
      	  	       					s.set_accept();   	  	       
      	  	       					break;
      	  	      
      	  	        				}
      	  	        			case 4:
      	  	       				break;      	  	      
      	  	        				
             					}
             				}
             			}
      	  	 	case 3:
      	  	        	break; 
      	  	       		     	  	      
       		default:
                 	{
                  		cout<<"\n\t\t\t Enter a valid choice  :  ";
                   		break;
                 	}
           	}          	
          }while(e!=3);
          break; 
        }
                
        case 4:
        {
          exit(0);
          break;
        }           
        default:{
              cout<<"\n\t\t\t Enter a valid choice  :  ";
               break;
        } 
      }
    }     
  cout<<"\n";
  return 0;
} 
