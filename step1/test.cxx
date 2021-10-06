#include <iostream>
using namespace std;

class A
{
public:
	A()
	{
		a =0;
	}

    int a;
    
    void  Show()
	{
		cout << a << endl;
	}

};

void Test(A* a)
{
	cout << a->a << endl;
    a->a =1;
}

int main()
{
	int i=0;
	std::cout << "test" << std::endl;

	A a;
    Test(&a);
    a.Show();
	return 0;
}
