#include <windows.h>
#include <stdio.h>
#include "ContainerCreate.h"
#include "ContainerTest.h"

void main(int argc, char *argv[])
{
	//ProcessListTest();
	if (!IsInAppContainer())
	{
		RunContainerTests();
		RunExecutableInContainer(argv[0]);
		//RunExecutableInContainer("C:\\Windows\\notepad.exe");
	}
	else {
		RunContainerTests();
	}
	getchar();
}