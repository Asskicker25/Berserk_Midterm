
#include "Berserk.h"

int main()
{
	Berserk berserkWindow;

	Debugger::print = true;

	berserkWindow.InitializeWindow(800, 600);

	berserkWindow.Render();

	return -1;
}