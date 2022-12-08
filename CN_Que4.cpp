// CN Practical List Que:4 (Selective Repeat Sliding Window Protocal)
#include <iostream>
#include<conio.h>
#include<stdlib.h>
#include<ctime>
#include<cmath>
using namespace std;


#define TOTAL_FRAME 100
#define FRAMES_SEND 10

//Selective repeat class
class SelectiveRepeat
{
    private:
        int frame_in_window;
        int allFrames[TOTAL_FRAME];
        int sentFrame[FRAMES_SEND];
        int receivedFrame[FRAMES_SEND];
        char rec_frame_ack[FRAMES_SEND];
        int senderWindow;
        int receiverWindow;
    public:
        SelectiveRepeat()
        {
            senderWindow=0;
            receiverWindow=0;
        }
        void inputData();
        void sender(int);
        void receiver(int);
};

//Input function
void SelectiveRepeat::inputData()
{
    cout<<endl<<"----------------------------Selective Repeat--------------------------------"<<endl;
    int n;     //no. of bits for the frame
    int m;    //no. of frames from n bits
    int i;
    cout<<endl<<">> Enter the no. of bits for the sequence no. : ";
    cin>>n;
    m=pow(2,n);
    int t=0;
    frame_in_window=(m/2);
    for(i=0;i<TOTAL_FRAME;i++)
    {
        allFrames[i]=t;
        t=(t+1)%m;
    }

    for(i=0;i<frame_in_window;i++)
    {
        sentFrame[i]=allFrames[i];
        receivedFrame[i]=allFrames[i];
        rec_frame_ack[i]='n';
    }
    receiverWindow=senderWindow=frame_in_window;
    sender(m);
}

//Sender's function
void SelectiveRepeat::sender(int m)
{
    cout<<endl<<"----------------------------------------------------------"<<endl;
    cout<<endl<<"---------------------------SENDER-------------------------"<<endl;
    for(int i=0;i<frame_in_window;i++)
    {
        if(rec_frame_ack[i]=='n')
            cout<<"-----> Frame "<<sentFrame[i]<<" is sent"<<endl;
    }
    cout<<endl<<"----------------------------------------------------------"<<endl;
    receiver(m);
}

//Receiver's function
void SelectiveRepeat::receiver(int m)
{
    time_t t;
    int f;
    int j;
    int f1;
    int a1;
    char ch;
    srand((unsigned)time(&t));
    
    cout<<endl<<"------------------------RECEIVER--------------------------"<<endl;

    for(int i=0;i<frame_in_window;i++)
    {
        if(rec_frame_ack[i]=='n')
        {
            f=rand()%10;
            if(f!=5)
            {
                for(int j=0;j<frame_in_window;j++)
                    if(receivedFrame[j]==sentFrame[i])
                    {
                        cout<<"------> Receiver : Frame "<<receivedFrame[j]<<" received correctly --------------"<<endl;
                        receivedFrame[j]=allFrames[receiverWindow];
                        receiverWindow=(receiverWindow+1)%m;
                        break;
                    }
                int j;
                if(j==frame_in_window)
                {
                    cout<<"------> Receiver : Duplicate frame "<<sentFrame[i]<<" discarded !!!!!"<<endl;
                }
                a1=rand()%5;
                if(a1==3)
                {
                    cout<<"\t!!! (Acknowledgement "<<sentFrame[i]<<" lost)"<<endl;
                    cout<<"\t!!! (Sender timeouts--->Resend the frame)"<<endl;
                    rec_frame_ack[i]='n';
                }
                else
                {
                    cout<<"\t----> (Acknowledgement "<<sentFrame[i]<<" received)"<<endl;
                    rec_frame_ack[i]='p';
                }
            }
            else
            {
                int ld=rand()%2;
                if(ld==0)
                {
                    cout<<"\t!!! RECEIVER : Frame "<<sentFrame[i]<<" is damaged !!!!!"<<endl;
                    cout<<"\tRECEIVER : Negative Acknowledgement "<<sentFrame[i]<<" sent --->>"<<endl;
                }
                else
                {
                    cout<<"\t!!! RECEIVER : Frame "<<sentFrame[i]<<" is lost !!!"<<endl;
                    cout<<"\t!!! (Sender Timeouts --> Resend Frame) !!!"<<endl;
                }
                rec_frame_ack[i]='n';
            }

        }

    }

    for(int j=0;j<frame_in_window;j++)
    {
        if(rec_frame_ack[j]=='n')
        break;
    }

    int i=0;
    for(int k=j;k<frame_in_window;k++)
    {
        sentFrame[i]=sentFrame[k];
        if(rec_frame_ack[k]=='n')
            rec_frame_ack[i]='n';
        else
            rec_frame_ack[i]='p';

        i++;
    }
    if(i!=frame_in_window)
    {
        for(int k=i;k<frame_in_window;k++)
        {
            sentFrame[k]=allFrames[senderWindow];
            senderWindow=(senderWindow+1)%m;
            rec_frame_ack[k]='n';

        }
    }
    cout<<endl<<"----------------------------------------------------------"<<endl;
    cout<<"-------------> Want to continue (Y/N) : ";
    cin>>ch;
    cout<<"----------------------------------------------------------"<<endl<<endl;
    if(ch=='y'||ch=='Y')
        sender(m);
    else
        exit(0);
}

//main function for execution of program
int main()
{
    SelectiveRepeat sr;
    sr.inputData();
    return 0;
}