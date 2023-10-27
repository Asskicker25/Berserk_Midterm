
#include "Berserk.h"

//Main function that creates a instance of a class that handles the game
int main()
{
	//It is a derived class of my graphics library to draw a window and other functions with virtual functions
	Berserk berserkWindow;

	//You can toggle the message printing in the console 
	Debugger::print = true;

	//Creates a glfw window with the specified resoluition
	berserkWindow.InitializeWindow(1366, 728);

	//Acts as the render loop 
	berserkWindow.Render();

	return -1;
}