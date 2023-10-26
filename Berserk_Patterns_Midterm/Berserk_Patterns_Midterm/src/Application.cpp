
#include "Berserk.h"

int main()
{
	Berserk berserkWindow;

	Debugger::print = true;

	berserkWindow.InitializeWindow(1366, 728);

	berserkWindow.Render();

	return -1;
}