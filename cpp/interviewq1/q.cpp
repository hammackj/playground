#include <iostream>

class BaseClass
{
	public: 
	
	int X;

	virtual void SetX() { X = 1; }

	BaseClass() { SetX(); }
};

class DerivedClass : public BaseClass
{
	public:
		void SetX() { X = 2; }
};

int main()
{
	DerivedClass obj;

	std::cout << obj.X << std::endl;
}
