#include <iostream>
#include <stack>

using namespace std;



void printStack(stack<bool> stk){
while(stk.size() !=0){
    cout<<stk.top()<<" ";
    stk.pop();
}
}

stack<bool> push_instk(int d){
    int temp=d;
stack<bool> stkm;
while(temp){
    stkm.push(temp&1);
    temp = temp>>1;
}
return stkm;
}


void findRemainder(int data,int ppp){

int div = 0b11001;
int degree = 4;

stack<bool> stkm;
int temp= data;
stkm = push_instk(temp);

int work = degree+1;
int ss= stkm.size();

while(ss >= work){
    stack<bool> stkd;
stkd = push_instk(div);
int arr[work];
for(int i=0;i<work;i++){ 
        int res = stkm.top() ^ stkd.top();
    arr[i] =res;
    stkm.pop();
    stkd.pop();
}
for(int i=0;i<work;i++){
       stkm.push(arr[i]);
}
while(stkm.top() != 1){
    stkm.pop();
}
ss = stkm.size();
}
cout<<"CRC IS : ";
printStack(stkm);

}

int main()
{
   //1010101010 / 11001 --> remainder is crc
   //using 2 stack and 1 array of size degree+1
   int d = 0b1010101010;
   int size=10;
   findRemainder(d,size);
    return 4;
}
