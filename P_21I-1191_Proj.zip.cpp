                                                                         //Fatima-Bilal(21I-1191) //FinalProject //traffic light simulator
#include<iostream>
#include<conio.h>
#include<Windows.h>

#define BLACK			 0
#define BLUE 			 1
#define GREEN   		 2
#define CYAN			 3
#define	RED			     4
#define PURPLE  		 5
#define	YELLOW			 6
#define LIGHT_GRAY		 7
#define	GRAY			 8
#define	LIGHT_BLUE 		 9
#define	LIGHT_GREEN 	10
#define LIGHT_CYAN		11
#define LIGHT_RED		12
#define PINK			13
#define MAGNETA			13
#define LIGHT_YELLOW	14
#define WHITE			15

using namespace std;

void Color(int textColor, int bgColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}           //sets the background of the text



COORD coord = {0, 0};
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void signal_light_color(int signal_number, bool red, bool yellow, bool green)
{
    int x_top_pos = 10;
    int pos_x = (x_top_pos * signal_number) + (10 * signal_number) +2;
    int pos_y = 10;
                                        // Signal Red Light
    if(red == true)
    {
        Color(LIGHT_RED, BLACK);
    } else
    {
        Color(RED, BLACK);
    }
    gotoxy(pos_x, pos_y+1);
    cout<<"\xdb";
    gotoxy(pos_x+1, pos_y+1);
    cout<<"\xdb";

                                        // Signal Yellow Light
    if(yellow == true)
    {
        Color(LIGHT_YELLOW, BLACK);
    } else
    {
        Color(YELLOW, BLACK);
    }
    gotoxy(pos_x, pos_y+3);
    cout<<"\xdb";
    gotoxy(pos_x+1, pos_y+3);
    cout<<"\xdb";

                                         // Signal Green Light
    if(green == true)
    {
        Color(LIGHT_GREEN, BLACK);
    } else
    {
        Color(GREEN, BLACK);
    }
    gotoxy(pos_x, pos_y+5);
    cout<<"\xdb";
    gotoxy(pos_x+1, pos_y+5);
    cout<<"\xdb";
}


void reset_signals(int signals)
{
    for(int signal_count = 1; signal_count <= signals; signal_count++)
    {
        signal_light_color(signal_count, true, false, false);
    }
}



void signal_timer(int signals, int green_start, int green_time)
{
    int yellow_count = 3;               // Timer for yellow color in seconds
    int current_green = green_start;    // First signal to be green
    int current_yellow_green = 0;
    int current_yellow_red = 0;

                                        // Set initial signal state (that is 1st will be green and others will be red)
                                        // Turn all signals to red
    reset_signals(signals);
                                        // Change the color of signal (signal number, red, yellow, green) for this we are setting 1st signal to green.
    signal_light_color(current_green, false, false, true);

                                        // Run the loop to number of seconds entered by user
    for (int sec=green_time;sec>=0;sec--)
    {
                                        // If none of the signal is yellow (before green or red) and remaining seconds are greater than 0, timer will keep the signal green
        if(sec > 0 && (current_yellow_green == 0 && current_yellow_red == 0))
        {
            Sleep(1000);                 // Sleep for 1 second (for timer)
        }
        else
        {
            if(current_yellow_green == 0 && current_yellow_red == 0)
            {
                sec = 1;                                                    // to run loop again to change yellow to red
                current_yellow_red = current_green;                         // turn on yellow light for current green signal
                current_green = 0;                                          // turn off all green lights - no signal will be green

                signal_light_color(current_yellow_red, false, true, false); // show graphically

                                                                            // Keep signal to yellow for defined number of seconds (that is set to 3 seconds)
                for(int counter = yellow_count; counter >= 0; counter--)
                Sleep(1000);
            }
            else if(current_yellow_red != 0)
            {
                                                                            // Turn all signals to red
                reset_signals(signals);

                sec = 1;                                                    // to run loop again to change yellow to green

                                                                            // Check if next signal is greater than number of signals, defined by user
                if((current_yellow_red + 1) > signals)
                {
                                                                            // If next signal is greater than number of signals, next will be 1st signal
                    current_yellow_green = 1;
                }
                else
                {
                                                                            // If next signal is less than or equal to number of signals.
                    current_yellow_green = current_yellow_red + 1;
                }

                current_yellow_red = 0;                                         // turn off yellow light for previous signal

                signal_light_color(current_yellow_green, false, true, false);   // Graphically show next yellow signal

                                                                                // Keep signal to yellow for defined number of seconds (that is set to 3 seconds)
                for(int counter = yellow_count; counter >= 0; counter--)
                Sleep(1000);
            }
            else if(current_yellow_green != 0)
            {
                                                                                // Reset the timer for green signal
                sec=green_time+1;
                current_green = current_yellow_green;                            // change current yellow signal to green
                current_yellow_green = 0;                                        // turn off yellow light

                signal_light_color(current_green, false, false, true);           // Graphically show the green signal
            }
        }

    }
}

void design_signal(int signals)
{
    for(int signal_count = 1; signal_count <= signals; signal_count++)
        {
        int screen_top = 10;
        int pos_x = 10;
        int pos_y = 10;

        pos_x=(screen_top * signal_count) + (10 * signal_count);

        for(int top=0;top<=5;top++)
        {
            gotoxy(pos_x, pos_y - 1);
            cout<<"\xdc";
            gotoxy(pos_x, (pos_y + 7));
            cout<<"\xdc";

            pos_x++;
        }
        pos_x = (screen_top * signal_count) + (10 * signal_count);

        for(int top=0;top<=7;top++)
        {
            gotoxy(pos_x, pos_y);
            cout<<"\xdb";
            gotoxy((pos_x + 5), pos_y);
            cout<<"\xdb";

            pos_y++;
        }
    }
}

int main()
{
    int signals;
    int signal_count;
    int time;

    cout << "\nTraffic light simulation\n";
    cout<<"\n Enter the number of signals (3 or 4)\n";
    cin>>signals;
    cout<<"\n Enter the time duration for a signal between 10 and 30 seconds \n";
    cin>>time;
    do
    {
    if(time<10 || time>30)
    {
        cout<<"\n Invalid valid time limit. Enter the time duration for a signal between 10 and 30 seconds \n";
        cin>>time;
    }
    else
        {
            signal_count = signals;

            design_signal(signal_count);

            signal_timer(signal_count, 1, time);
        }
    }
    while(time>10 && time<30);
return 0;
}
