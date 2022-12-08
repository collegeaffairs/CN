//CRC

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int dSize;
int gSize=6;
int g[6]={1,1,0,1,0,1};               //g(x)= x^5 + x^4 + x^2 +1

//Function to return a random number
int randomNum(int min = 1, int max = 100)
{
    srand((unsigned int)time(NULL));
    int num = (rand() % max + min);
    
    return num;
 
}

//Function to add noice in message at random index
int *noiceAdder(int ogMsg[], int mSize)
{
    static int *noiceMsg = NULL;
    noiceMsg = new int[mSize];
    int zeros = gSize-1;
    for(int i=0;i<mSize;i++)
    {
        noiceMsg[i]=ogMsg[i];
    }
    int randLoc = randomNum(1, dSize+6);
    if(randLoc<dSize)
    {
        noiceMsg[randLoc]=0;
        return noiceMsg;
    }
    else
    {
        return noiceMsg;
    }
}

//function for dividing message with generator polynomial
void division(int temp[],int gen[],int mSize,int zeros)
{
    for(int i=0;i<mSize;i++)
    {
        if (gen[0]==temp[i])
        {
            for(int j=0,k=i;j<zeros+1;j++,k++)
            {
                if(!(temp[k]^gen[j]))
                {
                    temp[k]=0;
                }
                else
                {
                    temp[k]=1;
                }
            }
        } 
    }
}

// function for Sender side work
int *sender(int data[])
{
    int i,j;

    int zeros = gSize-1;
    int mSize= dSize + zeros;
    
    static int *msg;
    msg = new int[mSize]; 

    int temp[mSize];

    //Copying data bits to sending message
    for(i=0;i<dSize;i++)
    {
        msg[i]=data[i];
    }
    //Adding zeros to sending Message
    for(i=dSize; i<mSize; i++)
    {
        msg[i]=0;
    }
    cout<<endl<<endl<<">> Sender's Side:--------------------------------";
    cout<<endl<<">> Message after adding Zero is :  "<<endl<<">> ";
    for(i=0;i<mSize; i++)
    {
        temp[i]=msg[i];
        cout<<msg[i]<<" ";
    }

    //Dividing temp by g
    division(temp,g,dSize,zeros);

    //Copying parity Bits from temp
    int parityBit[zeros];
    for(int i=0;i<zeros;i++)
    {
        parityBit[i]=temp[dSize+i];
    }
    cout<<endl;
    cout<<endl<<">> CRC's Bits to be added are:";
    for(i=0;i<zeros;i++)
    {
        cout<<parityBit[i]<<" ";
        msg[dSize+i] = parityBit[i];
    }
    
    cout<<"\b"<<endl<<endl<<">> Final Message to be sent is :"<<endl<<">> ";
    for(i=0;i<mSize;i++)
    {
        cout<<msg[i]<<" ";
    }
    cout<<endl;

    return msg;

}

// function for receiver side work
void receiver(int rMsg[], int mSize){

    int i,j;
    
    int zeros = gSize -1;
    int temp[mSize];
    cout<<endl<<endl<<">> Reciever's Side:-----------------------------------------";
    cout<<endl<<">> Recieved Message: ";
    for(int i=0;i<mSize;i++)
    {
        cout<<rMsg[i]<<" ";
        temp[i]=rMsg[i];
    }

    division(temp, g, dSize, zeros);

    cout<<endl<<endl<<">> Remainder: ";
    int rrem[zeros];
    for (i = dSize, j = 0; i < mSize; i++, j++)
    {
        rrem[j] = temp[i];
    }
    for (i = 0; i < zeros; i++)
    {
        cout << rrem[i];
    }
    int flag = 0;
    for (i = 0; i < zeros; i++)
    {
        if (rrem[i] != 0)
        {
            flag = 1;
        }
    }
    if (flag == 1)
    {
        cout<<endl<<endl<<">> Remainder is not 0,hence the Message Transmitted from Sender to Receiver is Corrupted";
        
    }
    else
    {
        cout<<endl<<endl<<">> Remainder is 0, hence the Message Transmitted from Sender to Receiver is Correct";
    }
}

//Main function for execution of program
int main()
{
    int *data;
    cout<<endl<<">> Enter Length of Message:";
    cin>> dSize;
    data = new int[dSize];
    
    cout<<endl<<">> Enter Sending Message bit by bit (0 or 1): ";
    for(int i=0; i<dSize; i++)
    {
        cin>>data[i];
    }
    cout<<endl<<">> Entered Message is: ";
    for(int i=0; i<dSize; i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
    int *sMsg;
    int *noice;
    sMsg = sender(data);
    
    int mSize = dSize+gSize-1;
    int senderMsg[mSize];
    
    for(int i=0; i<mSize; i++)
    {
        senderMsg[i]= *(sMsg+i);
    }
    
    //Adding noice to sending message if generated random number is even.
    int rNum= randomNum();
    if(rNum%2==0)
    {
        noice = noiceAdder(senderMsg, mSize);
        for(int i=0; i<mSize; i++)
        {
            senderMsg[i]= *(noice+i);
        }
    }

    receiver(senderMsg, mSize);

    return 0;
}
