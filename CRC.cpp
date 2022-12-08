#include <iostream>
#include <string>
#include <stack>
#include <math.h>
#include <bitset>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>


using namespace std;

static int CRC =  0b11011;            // X^3 + x^1 + 1 ,  degree=3
int degreCal( unsigned int n){
    
    int count=0;
    while(n){
        count++;
        n = n>>1;
    }
    return count;
    
}

void print( unsigned int input){
    stack<bool> data;
    while(input){
        data.push(input&1);
        input = input>>1;
    }
    while(!data.empty()){
        cout<<data.top();
        data.pop();
    }
}

void printStack(stack<bool> ptr){
    while(!ptr.empty()){
        cout<<ptr.top()<<" ";
        ptr.pop();
        
    }
    cout<<endl;
    
}

void printData(int data){
  stack<bool> stk;
   while(data){
       stk.push(data&1);
       data = data>>1;
   }
   printStack(stk);
}


void errorInjection(int &data,int limit){ //limit is the number of bits
	
	
	
	
	int k=0;
	srand ( time(NULL) );

	k=	(rand()%(2*limit)); // 7,  14 




if(k<limit){

	int a =1;
	
	for(int i=0;i<k;++i){
	 a=	a<<1;
	}
  data=data|a ;
	
	cout<<endl;
}else{
	//no error injected
	
}
	
}


void copyStack(stack<bool> &ptr, stack<bool> temp){
    
    stack<bool> temp2;
    
    while(!temp.empty()){
        temp2.push(temp.top());
        temp.pop();
    }
    
    while(!temp2.empty()){
        ptr.push(temp2.top());
        temp2.pop();
    }
}



//=============================================================
int calCulateRem(int inputInt,int crcDegree){
    
 
    stack<bool> stk1;  //big stack
    stack<bool> stk2;   //crc stack
    stack<bool> stk3;
    int saveOriginal = inputInt;
    
    while(inputInt){
        stk1.push(inputInt&1);
        inputInt = inputInt>>1;
    }
    int crc = CRC;
    
    while(crc){
        stk2.push(crc&1);
        crc = crc>>1;
    }
    
    while(stk1.size() >crcDegree){
        stack<bool> temp;
        copyStack(temp,stk2);
        
        
        while(!temp.empty()){
        stk3.push(stk1.top()^temp.top());
        stk1.pop();
        temp.pop();
        
        }
        while(!stk3.empty()){
            stk1.push(stk3.top());
            stk3.pop();
        }
        
       
        while(stk1.top() != 1){         //removing zeroes
            stk1.pop();
             if(stk1.size()<=crcDegree){
            break;
        }
        }
      //  printStack(stk1);
        
    }
   //  printStack(stk1);
int ans=0;



    while(!stk1.empty()){
      //  cout<<"top : "<<stk1.top()<<endl;
        if(stk1.top()){
            ans = ans<<1;
            ans = ans|1;
        }else{
             ans = ans<<1;
        }
        stk1.pop();
    }


      
   return ans;
    
}


void printBitS( bitset<16> y){
	
	bool start=false;
	int i=15;
	for(;i>=0;i--){
		if(y[i]== 1){
			break;
		}
	}
	
	while(i >=0){
		cout<<y[i--];
	}
}



int main()
{
	
	cout<<"#CRC USED IS ";
	print(CRC);
	cout<<endl;
	cout<<"Enter the data to be send :";
   string input;
   cin>>input;             // 10110110
   
  unsigned int inputInt=0;
   for(int i= input.length()-1,j=0; i>=0;--i,j++){
          
       if(input[i]=='1'){
                      
            inputInt += 1*pow(2,j);
       }else{
             inputInt += 0*pow(2,j);
       }      
   }
  

  
   
  //appending 0's at the end of data
  int degreeOfCrc = degreCal(CRC)-1;
  
  for(int i = 0 ;i<degreeOfCrc;++i){
      inputInt=inputInt<<1;            //will be working on bits
  }
  
  cout<<"#DATA AFTER APPENDING ZEROES ";
  print(inputInt);
  cout<<endl;
//========================sender side===============================================
 cout<<"#CHECKSUM IS ";
  int ans=calCulateRem( inputInt,degreeOfCrc); //ans is check sum
  print(ans);
  cout<<endl;
 

  int encryptedData = inputInt; 
    encryptedData = encryptedData|ans;          //inserting checksum
    
  
  bitset<16> y(encryptedData);
 
  cout<<"#DATA WHICH WILL BE FINALLY SEND AFTER (APPENDING CHECKSUM) : ";
  printBitS(y);
  cout<<endl;
   
   
   //=============here inject some error to simulate noisy channel========================================
     int dataR =  encryptedData;
     
     int numberOfBits = degreCal(dataR);
  
    
     
     errorInjection(dataR,numberOfBits);
     
     
   
   
   //=======================after data is sent Receiver side=======================================================================
   

   int degreeCRC = degreCal(CRC)-1;
   
   cout<<"#DATA RECEVIED IS ";
   print(dataR);
   cout<<endl;
   
   if(calCulateRem(dataR,degreeCRC)){
       cout<<"#DATA HAS ERROR"<<endl;
       
   }else{
      cout<<"#DATA HAS NO ERROR"<<endl;
      cout<<"#DATA AFTER EXCLUDING CHECKSUM : ";
      int removedLastBits = (dataR>>degreeCRC);
      printData(removedLastBits);
   }
   cout<<endl<<endl;
   
   

	return 0;
}