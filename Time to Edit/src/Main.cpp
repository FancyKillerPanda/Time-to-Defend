#include "pch.h"

#include "Editor.h"


int main(int argc, char* argv[])
{
	Editor* timeToEdit = new Editor();
	timeToEdit->run();
	delete timeToEdit;

#ifdef _DEBUG
	system("PAUSE");
#endif // _DEBUG

	return 0;
}
