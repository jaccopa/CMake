#include <iostream>
#include "test2.cxx"
#include "test3.cxx"
using namespace std;

typedef int (*init)(int);

int myInit(int para)
{
	cout << "myInit:" << para << endl;
};


typedef struct WorkFlow
{
	init initFunc;
}*pWorkFlow,IWorkFlow;

int main()
{

    WorkFlow wf;
    wf.initFunc = myInit;

	wf.initFunc(2);

    IWorkFlow *iwFlow = new IWorkFlow();
	iwFlow->initFunc = myInit;

    iwFlow->initFunc(3);


	delete iwFlow;
    iwFlow = NULL;

	MessageSender *ptSender = new MessageSender();

	ptSender->Init("192.168.0.108",8080);
	ptSender->Send("Hello",5);
	if(ptSender)
	{
		delete ptSender;
		ptSender = NULL;
	}

	MessageRecver *ptRecv = new MessageRecver();
	ptRecv->Init("192.168.0.108",8081);
    ptRecv->RecvLoop();	

	return 0;
}
