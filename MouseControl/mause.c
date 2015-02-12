#include <windows.h>
#include <winable.h>
#include <stdio.h>


/*Main takes 2, 1, or 0 inputs

    -In the case of the 2 inputs, main converts those into
    x and y displacments and moves the mouse by that amount

    -In the case of 1 inputs, main causes a left click at the
    current location

    -In the case of 0 inputs, main calculates exact center of
    screen and sets the mouse to that location

    -else main returns the error message "Incorrect number of arguments"

*/

int main(int argc, char *argv[])
{

    if (argc == 3)
    {
        //Displace Mouse code

        //Convert input to long
        long x,y;
        x = strtol(argv[1], NULL, 0);
        y = strtol(argv[2], NULL, 0);

        //Create mouse input
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.mouseData = 0;
        input.mi.time = 0;

        //Set x && y displacement
        input.mi.dx = x;
        input.mi.dy = y;

        //Set flag to movment, send input to system
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        SendInput(1, &input, sizeof(INPUT));
        printf("%d\n",argc );
    }


    else if(argc == 2)
    {
        //Left click code

        //Create mouse input
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.mouseData = 0;
        input.mi.time = 0;

        //Press down left mouse button and send input
        input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
        SendInput(1,&input,sizeof(INPUT));

        //Release left mouse button and send input
        input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
        SendInput(1,&input,sizeof(INPUT));
    }


    else if(argc == 1)
    {
        //Center mouse code

        //Create input
        INPUT input;
        input.type = INPUT_MOUSE;
        input.mi.mouseData=0;
        input.mi.time = 0;

        //Set x and y coordinates to exact center
        int x = GetSystemMetrics(SM_CXSCREEN)/2;
        int y = GetSystemMetrics(SM_CYSCREEN)/2;
        input.mi.dx =  x*(65536/GetSystemMetrics(SM_CXSCREEN));//x being coord in pixels
        input.mi.dy =  y*(65536/GetSystemMetrics(SM_CYSCREEN));//y being coord in pixels

        //Set flag to absolute postion movment, send input to system
        input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
        SendInput(1,&input,sizeof(input));
    }

    else
    {
        //Returning error message
        printf("Incorrect number of arguments");

    }
    
    return 0;
}