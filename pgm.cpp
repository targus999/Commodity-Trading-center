// header files are used for implementing in-build functions
#include<iostream>
#include<stdio.h>
#include<gdbm.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

// key_buffer to store key values( which we set as key ) and record buffer to store record of the class in the dbms

char key_buffer[800],record_buffer[4096];	
datum key,record;

class Commodity      //commidity class starts here
{
        protected:
                char cname[50],s_email[50],c_id[20],hbidder[50];
                int weight;
                float price;
                bool active=false;
        public:
                friend class DBMS;	// here dbms class has been declareed as friend of this class 
                friend class Admin;	// here admin class has been declareed as friend of this class 
                Commodity(){}			// constructor
                void get_function(const char* i)	// to get the details of the commodity and the name of the seller
				{
                        cout<<"\n Seller email : "<<i;
                        strcpy(s_email,i);
                        cout<<"\n Enter name of commodity:"<<endl;
                        cin>>cname;
                        cout<<"\n Enter commodity ID:"<<endl;
                        cin>>c_id;
                        cout<<"\n Enter weight of commodity:"<<endl;
                        cin>>weight;
                        cout<<"\n Enter price of commodity:"<<endl;
                        cin>>price;
                        strcpy(hbidder,"nil");
                        cout<<"\n";
                }
                
               //parameterized constructor 
              Commodity(const char *cn, const char *sm,const char *id,int w,float p,bool a,const char *h) 
				{
                        strcpy(cname,cn);
			 strcpy(s_email,sm);
                        strcpy(c_id,id);
                        strcpy(hbidder,h);
                        weight=w;
                        price=p;
			 active=a;
                }
                
			void set_price(float p){price=p;} 		
			// this fuction makes admin to set the minimum price inorder to start the bidding 
		
            static void create_key(const char *c_id)		// to create  key with commodity id
               {
                        strcpy(key_buffer,c_id);
                        key.dptr=key_buffer;
                        key.dsize=strlen(key_buffer);
                        return;

                }
                
             static void create_record(Commodity c)			// to create record for the corresponding key 
              {
               sprintf(record_buffer,"%s %s %s %d %f %d %s",c.cname,c.s_email,c.c_id,c.weight, c.price,c.active, c.hbidder);
                        record.dptr=record_buffer;
                        record.dsize=strlen(record_buffer);
                        return;
                }
                
                // here state function returns current state of the commodity which denotes whether the commodity have been closed or open for bidding
		bool state(){return active;}	
		
                void accept_bid(float p,char* i){ 				// funtion to accept bid
			price=p;
			strcpy(hbidder,i);
		}
		
		void close_bid(){active=false;}					// function to close bid 
		
		// function to start the bidding and this is called by the admin		
		bool activate(){active=true;return active;}		
		
		void display_Commodity()  							// to display commodity
		{
			cout<<"\n\t COMMODITY ID : "<<c_id<<endl;
        		cout<<"\n COMMODITY NAME    : "<<cname<<endl;
        		cout<<"\n COMMODITY PRICE   : "<<price<<endl;
        		cout<<"\n HIGHEST BIDDER    : "<<hbidder<<endl;
        		cout<<"\n Status            : ";
        		if(active)cout<<"OPEN"<<endl;
        		else cout<<"CLOSED"<<endl;
		}
		
		float get_price(){return price;}		// to return price
		char* get_id(){return c_id;}			// this funtion return's commodity id to the main function
		

};			// commidity class ends here





class User				// user class starts here
{
	protected:
		char name[25],email[50];
		int age;
		float balance;
		long int phone;
		bool accept=true;
		bool active=false;
	public:
		void get_function()      // function to get the general details of buyer and seller 
                {
                        cout<<"\n Enter your name    		 :	";
                        cin>>name;
                        cout<<"\n Enter your E-mail   		 :	";
                        cin>>email;
                        cout<<"\n Enter your phone number     	 :      ";
                        cin>>phone;
                        cout<<"\n Enter your age			 :      ";
                        cin>>age;
                        balance=0;
                        //cout<<"\n";
                }	
         	// here key is created using  seller's and buyer's email id       
       	static void create_key(const char *email_id)  	
		{
			strcpy(key_buffer,email_id);
			key.dptr=key_buffer;
			key.dsize=strlen(key_buffer);
			return;
		}
                
                void activate(){active=true;}									// to approve the user
                char* get_email(){return email;}								// return's email id 
       	 void link_bankAccnt()  				// function to link bank with the trading account
		{
			int c;
			printf("\n Enter amount to be credited to your account  : ");
			cin>>balance;
			cout<<"\n Bank Balance is  :  "<<balance<<endl;
			return ;
		}
		
		void set_accept()						// to decide whether the user want to accept the winning's or not
		{	
			int x;					
			cout<<"\n Will you accept the outcome "<<endl;
			cout<<"\t 1.YES"<<endl;
			cout<<"\t 2.NO"<<endl;
			cout<<"\n Enter your choice   :  ";
			cin>>x;
			if(x==1)accept=true;
			else accept=false;
		}
		
		bool get_accept(void){return accept;}		// this returns accept value
		bool get_status(void){return active;}         // this returns active value
		
                
};		// user class  ends here



class Seller:public User				                                                      //seller class
{
	protected:
		float rating=5;
	public:	
		Seller(){}					                                //constructor
		friend class DBMS;				// here dbms class has been declareed as friend of this class
		friend class Admin;				// here admin class has been declareed as friend of this class
		
		Seller(const char* n,const char* c,long int f,int a,float b,bool g,float h,bool ac)	//parameterized constructor 
		{
			strcpy(name,n);
			strcpy(email,c);
			phone=f;
			age=a;
			rating=b;
			accept=g;
			balance=h;
			active=ac;
		}
		
		~Seller(){}			//destructor		
		
		static void create_record(Seller e)					// to create record of seller
		{
		 sprintf(record_buffer," %s %s %ld %d %f %d %f %d",e.name,e.email,e.phone,e.age, e.rating,e.accept, e.balance,  			e.active);
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
		       if(rating<=0)
		       rating=0;
		    }
		  else
		    {
		       rating=rating+0.1;
		       if(rating>=5)
		       rating=5;
		       return ; 
		    }
		}
		

};	// seller class ends here





class Buyer:public User			// buyer class starts here
{
    public:
		friend class DBMS;					// here dbms class has been declareed as friend of this class
		friend class Admin;					// here admin class has been declareed as friend of this class
		Buyer(){}			//constructor
		Buyer(const char *n,long unsigned ph,const char *e,float b,bool a,bool i,int g)	// parameterized constructor
		{   
		        strcpy(name,n);
               		strcpy(email,e);
               		phone=ph;
               		age=g;
               		balance=b;
               		accept=a;
               		active=i;
         	}
		
        	~Buyer(){}    				// destructor
        	float get_balance(){return balance;}			// return's balance amount in the account
		

    	   	static void create_record(Buyer b)       			// to create record of buyer
       	{
          		sprintf(record_buffer,"%s %ld %s %f %d %d %d",b.name,b.phone,b.email,b.balance,b.accept,b.active,b.age);
          		record.dptr=record_buffer;
          		record.dsize=strlen(record_buffer);
          		return;
		}
		
		
		void update_rating()	// function to blacklist the buyer and this is done by admin 								
		{
		  active=accept;
		}
		
		
};									// buyer class ends here



	
       // dbms class for storing adding,deleting.updating and fetching details from database

class DBMS 				
{
protected:	

	GDBM_FILE dbf=NULL;	 
	                                                      // gdbm file pointer dbfs		
public:	

	DBMS(){ 
		char db_name[11]="db.trading";				                                 //db_name is db.sellbook
		dbf=gdbm_open(db_name,0,GDBM_WRCREAT,0666,NULL);		//creating database
		if(dbf==NULL){
			  cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			  exit(1);
		}
	}
	~DBMS(){gdbm_close(dbf);}				// closing dbfs
			
			
			
	void add_Seller(Seller s){	// function to add seller details by creating record and key
			Seller::create_key(s.email);
			Seller::create_record(s);
			int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
			if(ret_val) cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			else cout<<"\n Seller added Successfully \n";
	}
		
	// function to fetch seller details by creating a new key in the database as well as creating the records with the corresponding key	
	Seller fetch_Seller(const char *email){
			Seller::create_key(email);
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
		
	void update_Seller(Seller s)
	{
			Seller::create_key(s.email);
			Seller::create_record(s);
			int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
			if(ret_val) cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
			else cout<<"\n Seller Details Updated \n";
	}
		
	     
	void add_Buyer(Buyer b)					// function to add buyer details by creating record and key
	{
			Buyer::create_key(b.email);
			Buyer::create_record(b);
            		int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Buyer added successfully \n";
        }
        
	// function to fetch buyer details by creating a new key in the database as well as creating the records with the corresponding key
     	Buyer fetch_Buyer(const char *email){
	 		Buyer::create_key(email);
            		datum record=gdbm_fetch(dbf,key);
            		if(record.dptr==NULL)cout<<"\n GDBM error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
            		char n[100],e[50];
            		int g;
            		long int ph;
			float b;
			int a,i;
			char record_buffer[1024];
            		strncpy(record_buffer,record.dptr,record.dsize);
            		record_buffer[record.dsize]='\0';
            		free(record.dptr);
            		sscanf(record_buffer,"%s %ld %s %f %d %d %d",n,&ph,e,&b,&a,&i,&g);
            		return Buyer(n,ph,e,b,a,i,g);
	}
	
	// function to update buyer details by overwriting the existing key with updated details and storing it in the database with the corresponding key	
	void update_Buyer(Buyer b)		
	{
			Buyer::create_key(b.email);
			Buyer::create_record(b);
            		int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Buyer updated successfully \n";
      	}
		
		
		
		
		
	void add_Commodity(Commodity c)				// function to add commodity details by creating record and key
	{
                	 Commodity::create_key(c.c_id);
                	 Commodity::create_record(c);
                        int ret_val=gdbm_store(dbf,key,record,GDBM_INSERT);
                        if(ret_val)cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
                        else cout<<"\n Commodity details added successfully \n"<<endl;
       }
	// function to fetch commodity details by creating a new key in the database as well as creating the records with the corresponding key
       Commodity fetch_Commodity(const char *c_id){
                        Commodity::create_key(c_id);
                        datum record=gdbm_fetch(dbf,key);
                        if(record.dptr==NULL)cout<<"\n GDBM Error   :   "<<gdbm_strerror(gdbm_errno)<<endl;
                        char cn[100],sm[100],id[100],h[50];
                        int w,a;
                        float p;
                        strncpy(record_buffer,record.dptr,record.dsize);
			 record_buffer[record.dsize]='\0';
                        free(record.dptr);
                        sscanf(record_buffer,"%s %s %s %d %f %d %s",cn,sm,id,&w,&p,&a,h);
                        return Commodity(cn,sm,id,w,p,a,h);
       }
	// function to selete detail's of the commodity
       void delete_Commodity(const char *c_id){
                        Commodity::create_key(c_id);
                        int ret_val=gdbm_delete(dbf,key);
                        if(ret_val)cout<<"\n GDBM Error  :  "<<gdbm_strerror(gdbm_errno)<<endl;
                        else cout<<"\n Commodity details successfully deleted \n"<<endl;
       }
	// function to update commodity details by overwriting the existing key with updated details and storing it in the database with the corresponding key
       void update_Commodity(Commodity c)
       {
			Commodity::create_key(c.c_id);
			Commodity::create_record(c);                
            		int ret_val=gdbm_store(dbf,key,record,GDBM_REPLACE);
            		if(ret_val)cout<<"\n GDBM error : "<<gdbm_strerror(gdbm_errno)<<endl;
            		else cout<<"\n Commodity updated successfully \n";
      	}	
}; 
                     // dbms class ends here


class Admin 						// admin class starts here
{
	public:
	       void approve_user()		// function to approve the user
	       {
	        	int x;
	        	DBMS d;
	       	cout<<"\n Select the type of user"<<endl;
			cout<<"\t 1.Buyer"<<endl;
			cout<<"\t 2.Seller"<<endl;
			cout<<"\n Enter your choice   :  ";
			cin>>x;
      	  		if(x==1)
      	  		{
      	  			char i3[20];
      	  			cout<<"\n Enter the User id   :  ";
      	  			cin>>i3;
      	  			Buyer b=d.fetch_Buyer(i3);
      	  			if(strcmp(i3,b.email)==0){
      	  				b.activate();
      	  				d.update_Buyer(b);
      	  			}	
      	  		}
      	  		else
      	  		{
      	  			char i1[20];
      	  			cout<<"\n Enter the User id   :  ";
      	  			cin>>i1;
      	  			Seller s=d.fetch_Seller(i1);
      	  			if(strcmp(i1,s.email)==0){
      	  				s.activate();
      	  				d.update_Seller(s);
      	  			}
      	  		}      	  	    	      	  	     	
	       }
	       void start_bid()			// function to start the bidding
	       {	       
	       	DBMS d;
	       	char i[20];
      	  		cout<<"\n Enter the Commodity id  :  ";
      	  		cin>>i;
      	  		float p;
      	  		Commodity c1=d.fetch_Commodity(i);
      	  		if(strcmp(i,c1.c_id)==0){
      	  			cout<<"\n Enter the Commodity price  :  ";
      	  	    		cin>>p;
      	  			cout<<"\n";
      	  			c1.set_price(p);
      	  	    		bool j=c1.activate();
      	  	     		d.update_Commodity(c1);
      	  	     		if(j==true){cout<<"\n Bidding started "<<endl;}
      	  	     		else cout<<"\n Bidding has not start "<<endl;
      	  	     	}
	       }
	       void close_bid()			// function to close the bidding
	       {
	       	char i[20];
	       	DBMS d;
      	  		cout<<"\n Enter the Commodity id  :  ";
      	  		cin>>i;
      	  		cout<<"\n";
      	  		Commodity c1=d.fetch_Commodity(i);
      	  		if(strcmp(i,c1.c_id)==0){
      	  			c1.close_bid();
      	  			if(strcmp(c1.hbidder,"nil")!=0){
      	  				Buyer b=d.fetch_Buyer(c1.hbidder);
      	  				Seller s=d.fetch_Seller(c1.s_email);
      	  				s.update_rating();
      	  				b.update_rating();
      	  	     			if(b.accept==true && s.accept==true){
      	  	     				int com=c1.price/200;
      	  	     				cout<<"\n A commission of Rs"<<com<<" taken by both parties "<<endl;
      	  	     				b.balance=b.balance-c1.price-com;
      	  	     				s.balance=s.balance+c1.price-com;
      	  	     			
      	  	     			}
      	  	     			else cout<<"\n Item was not sold Bidding closed "<<endl;
      	  	     			d.update_Commodity(c1);
      	  	     			d.update_Buyer(b);
      	  	     			d.update_Seller(s);
      	  	     		}
      	  	     		else cout<<"\n No one bidded on the item, item NOT SOLD "<<endl;
      	  	     	}	
      	  	     	
	       }
};                     // admin class ends here



int main()				// main section starts here
{
	int ch,m,r,e,j,k;
    	Admin a;
    	const char *sna,*email;
    	char *mail;	
    	m:
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
      		system("clear");
      		
      switch(ch)
      {
        case 1:    // case 1 starts
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
      	  	system("clear");
      	  	switch(m)
      	  	{
      	  	
      	  	 case 1:
      	  	      {
      	  	      		
      	  	      		a.approve_user();
      	  	      		
      	  	       	break;     	  	      
      	  	      }
      	  	 case 2:
      	  	      {
      	  	      		
      	  	      		a.start_bid();
      	  	      		
      	  	       	break;      	  	      
      	  	      }
      	  	 case 3:
      	  	      {	
      	  	      		
      	  	       	a.close_bid();
      	  	       	
      	  	       	break;
      	  	       }
      	  	 case 4:  
      	  	 	  {        	  	 	   
      	  	       	break; 	  	      
      	  	      }
             } 
          }while(m!=4);
          break;
         }				// case 1 ends here
         
        case 2:									// case 2 starts here
        {
       	do
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
      		system("clear");
      		switch(r)
      		{
      			case 1:
      				{      	  			
      						DBMS d;
      	 					cout<<"\n Enter the details as a buyer ...........\n";  
      	 					Buyer b;
	 			   		b.get_function();              			
						d.add_Buyer(b);
						cout<<"\n";             	      
      	  	      		break;      	  	      
      	  	      	}
      	  	 	case 2:
      	  	      	{		
      	  	      			DBMS d;
      	  	      			char i[20];
        				cout<<"\n Enter the Buyer e-mail : ";
        				cin>>i; 
        				Buyer b=d.fetch_Buyer(i);
        				if(strcmp(i,b.get_email())==0){
        				  if(b.get_status()==0)
        				 	{       				
        				  	cout<<"\n User not approved by Admin"<<endl;
        				  	goto m;
        				  	break;    				  
        				  	}
        				  else{
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
      							system("clear");
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
      	  	      						cout<<"\n Enter the Commodity id : ";
        								cin>>i; 
        								Commodity c=d.fetch_Commodity(i);
        								if(strcmp(i,c.get_id())==0)
        								{
        								c.display_Commodity();
        								}
      	  	       						break;      	  	      
      	  	      					}
      	  	 					case 3:{
      	  	       					char j[20];
      	  	      						cout<<"\n Enter the Commodity id : ";
        							cin>>j; 
        							Commodity c=d.fetch_Commodity(j); 
        							if(strcmp(j,c.get_id())==0)
        							{
        								bool x=c.state();
        								if(x==1){
        									float p=c.get_price();
        									float bid;
        									cout<<p<<" is the current value of item"<<endl;
        									cout<<"\n Enter your bid : ";
        									cin>>bid;
        									if(p<bid){
        										if(b.get_balance()>=bid){
        										c.accept_bid(bid,i);
        										d.update_Commodity(c);
        										}
        										else cout<<"\n Buyer does not have sufficient balance"<<endl;
        									}   	
        									else cout<<"\n Please enter a value greater than current price"<<endl;  
        								}	       
        								else cout<<"\n Bidding is closed for this commodity"<<endl; 
        							}
        							break;      	  	      
      	  	        				}
      	  	 					case 4:
      	  	 						{      	  	        		
      	  	       						b.set_accept();
      	  	       						break;      	  	      
      	  	        				}
      	  	 					case 5:      	 
      	  	 				     {
      	  	 				     	break;
      	  	        					}      	  	        				
             				}      	  	      
      	  	      	        }while(j!=5);
      	  	      	   }
        				 
      	  	      	}
      	  	      	break;
      	  	      	}
      	  	 	case 3:
      	  	 		 {
      	  	        	break;
      	  	         }
      	  	   	default:
                 	{
                  		cout<<"\n\t\t\t Enter a valid choice  :  ";
                   		break;
                 	}     	
          } 				// switch case of case 2 ends here          
         }while(r!=3);
          break;
         }				//case 2 ends here
         
        case 3:						// case 3 starts here
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
      		system("clear");
      		switch(e)
      		{
      			case 1:
      				{  		
      						DBMS d;
      						Seller s;
      						cout<<"\n Enter the details as a seller ...........\n";  
	 			   		s.get_function();
	 			   		d.add_Seller(s);
						cout<<"\n";             	      
      	  	      		break;      	  	      
      	  	      	}
      	  	 	case 2:
      	  	      	{	
      	  	      		Seller s;
      	  	      		DBMS d;
      	  	      		char i[20];
        			cout<<"\n Enter the Seller e-mail : ";
        			cin>>i; 
        			s=d.fetch_Seller(i);
        			if(strcmp(i,s.get_email())==0){
        			     if(s.get_status()==0)
        				 	{       				
        				  	cout<<"\n User not approved by Admin"<<endl;
        				  	goto m;
        				  	break;    				  
        				  	}
        				 else{	
      	  	      		     	do{      	  	      		     			
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
      							system("clear");
      							switch(k)      						
      							{
      							case 1:{
      								 cout<<"\n Link your bank account to become a part of bidding process....\n";      
  			   					 s.link_bankAccnt();
			   					 d.update_Seller(s);   	  	
      	 							 break;      	  	      
      	  	      					}
      	  	 					case 2:{	
      	  	 							Commodity c;
      	  	 							c.get_function(i);
      	  	 							d.add_Commodity(c);
      	  	       						break;      	  	   
      	  	      					}
      	  	 					case 3:{
      	  	       					s.set_accept();   	  	       
      	  	       					break;      	  	      
      	  	        				}
      	  	        			case 4:
      	  	        				{
      	  	       						break;      	  	           	  	        				
             						}
             					}
             			   	   }while(k!=4);
             			      }            			        
             			     }
             			 break;
             			}
      	  	 	case 3:
      	  	 		{
      	  	        	break; 
      	  	        }
      	  	       		     	  	      
       			default:
                 	{
                  		cout<<"\n\t\t\t Enter a valid choice  :  ";
                   		break;
                 	}
           	}          	
          }while(e!=3);
          break; 
        }    			// case 3 ends here
                
        case 4:				// case 4 starts here
        {
          exit(0);
          break;
        }      				// case 4 ends here     
        default:{
              cout<<"\n\t\t\t Enter a valid choice  :  ";
               break;
        } 
      }							// main switch ends here
    }  
  cout<<"\n";
  return 0;
} 
