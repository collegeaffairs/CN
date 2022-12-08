//CN Practical List Que3: Go-Back-NSliding Window Protocol

#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

#define TOTAL_FRAMES 100
#define FRAMES_SEND 10

class GoBackN
{
private:
    int frame_in_window;
    int allFrames[TOTAL_FRAMES];
    int sendFrames[FRAMES_SEND];
    int senderWindow;
    int receiverWindow;
public:
    GoBackN();
    void inputData();
    void sender(int);
    void receiver(int);
};

GoBackN ::GoBackN()
{
    senderWindow = 0;
    receiverWindow = 0;
}

//Input function
void GoBackN ::inputData()
{
    cout << endl
         << "---------------------------- GO-BACK-N --------------------------------" << endl;
    int n; //no. of bits for the frame
    int m; //no. of frames from n bits
    cout << endl
         << ">> Enter the no. of bits for the sequence no. : ";
    cin >> n;

    m = pow(2, n);
    int t = 0;
    frame_in_window = (m / 2);
    for (int i = 0; i < TOTAL_FRAMES; i++)
    {
        allFrames[i] = t;
        t = (t + 1) % m;
    }

    sender(m);
}

//Sender's function
void GoBackN ::sender(int m)
{
    cout << endl
         << "----------------------------------------------------------" << endl;
    cout << endl
         << "---------------------------SENDER-------------------------" << endl;
    int j = 0;
    for (int i = senderWindow; i < senderWindow + frame_in_window; i++)
    {
        sendFrames[j] = allFrames[i];
        j++;
    }
    for (int i = 0; i < j; i++)
    {
        cout << "-----> Frame " << sendFrames[i] << " is sent !" << endl;
    }
    cout << endl
         << "----------------------------------------------------------" << endl;
    receiver(m);
}

void GoBackN ::receiver(int m)
{
    cout << endl
         << "------------------------RECEIVER--------------------------" << endl;
    time_t t;
    int f;
    int f1;
    int a1;
    char ch;
    int i;
    srand((unsigned)time(&t));
    f = rand() % 10;

    if (f != 5)
    {
        for (int i = 0; i < frame_in_window; i++)
        {
            if (receiverWindow == sendFrames[i])
            {
                cout << "------> Receiver : Frame " << sendFrames[i] << " received correctly --------------" << endl;
                receiverWindow = (receiverWindow + 1) % m;
            }
            else
                cout << "------> Receiver : Duplicate frame " << sendFrames[i] << " discarded !!!!!" << endl;
        }
        a1 = rand() % 15;
        if (a1 >= 0 && a1 <= 3)
        {
            cout << "\t!!! (Acknowledgement " << sendFrames[a1] << " & all after this lost) !!!" << endl;
            senderWindow = sendFrames[a1];
        }
        else
            senderWindow = (senderWindow + frame_in_window) % m;
    }
    else
    {
        f1 = rand() % frame_in_window;

        for (int i = 0; i < f1; i++)
        {
            if (receiverWindow == sendFrames[i])
            {
                cout << "------> Receiver : Frame " << sendFrames[i] << " received correctly --------------" << endl;
                receiverWindow = (receiverWindow + 1) % m;
            }
            else
            {
                cout << "------> Receiver : Duplicate frame " << sendFrames[i] << " discarded !!!!!" << endl;
            }
        }

        int ld = rand() % 2;
        if (ld == 0)
        {
            cout << "\t!!! RECEIVER : Frame " << sendFrames[f1] << " is damaged !!!!!" << endl;
        }
        else
        {
            cout << "\t!!! RECEIVER : Frame " << sendFrames[f1] << " is lost !!!" << endl;
        }

        for (i = f1 + 1; i < frame_in_window; i++)
        {
            cout << "\t!!! RECEIVER : Frame " << sendFrames[f1] << " discarded !!!!!" << endl;
        }

        cout << "\t!!! (Sender Timeouts --> Resend Frame) !!!" << endl;
        senderWindow = sendFrames[f1];
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
    GoBackN gb;
    gb.inputData();
    return 0;
}