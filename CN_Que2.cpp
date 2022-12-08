//CN QUe2

#include<iostream>
#include <time.h>
#include <cstdlib>
#include<ctime>
#include <unistd.h>
using namespace std;

//Function to print dashes
void printDashes(int max)
{
    cout<<endl;
    for (int i = 0; i <max; i++)
    {
        cout<<"-";
    }
}

//Function to return a random number
int randomNum(int min = 1, int max = 100)
{
    srand((unsigned int)time(NULL));
    int num = (1 + rand() % max + min);
    
    return num;
}

//Function to create delay
void doDelay()
{
    int waitTime = randomNum(24600,64000-24600);
    for(int i=0;i<64000;i++)
    {
        for(int j=0;j<waitTime;j++)
        {
            //Loop to create time delays randomly
        }
    }
}

class timer {
    private:
        unsigned long begTime;
    public:
        void start()
        {
            begTime = clock();
        }
        unsigned long elapsedTime()
        {
            return ((unsigned long) clock() - begTime) / CLOCKS_PER_SEC;
        }
        bool isTimeout(unsigned long seconds)
        {
            return seconds >= elapsedTime();
        }
}t;

int main()
{
    //int *frames;
    int fSize;
    cout<<">> Enter No. of Frames: ";
    cin>>fSize;
    //frames = new int[fSize];
    /*
    cout<<endl<<">> Enter Frames one by one: ";
    for(int i=0;i<fSize;i++)
    {
        cin>>frames[i];
    }
    */
    int frames[] = {1,2,3,4,5,6,7,8,9,10};
    printDashes(32+(fSize*2));
    cout<<endl<<">> Sender has to send frames : ";
    for(int i=0;i<fSize;i++)
    {
        cout<<frames[i]<<" ";
    }
    printDashes(32+(fSize*2));
    cout<<endl<<"\tSender\t\t\tReceiver"<<endl;
    int frames_sent = 0;
    unsigned long int timeLimit = 5;
    bool ack_Delay = false;
    srand(time(NULL));
    do
    {
        bool timeOut = false;
        cout<<endl<<"Frame Sent: "<<frames[frames_sent];
        cout.flush();
        cout<<"\t\t";
        t.start();
        if(rand()%2)
        {
            doDelay();
        }
        if(t.elapsedTime() <= timeLimit)
        {
            cout<<"Frame Received: "<<frames[frames_sent];
            if(ack_Delay)
            {
                cout<<"\t--Duplicate--";
                ack_Delay = false;
            }
            cout<<endl;
            frames_sent++;
        }
        else
        {
            cout<<"--Nothing Received--"<<endl;
            cout<<"---Timeout---"<<endl;
            timeOut  = true;
        }
        t.start();
        if(rand()%2 || !timeOut)
        {
            doDelay();
            if(t.elapsedTime() > timeLimit)
            {
                cout<<"--Delayed Acknowledgement--"<<endl;
                frames_sent--;
                ack_Delay = true;
            }
            else if(!timeOut)
            {
                cout<<"-> Acknowledgement : "<<frames[frames_sent]-1<<endl;
            }
        }
    }while(frames_sent!=fSize);

    return 0;
}