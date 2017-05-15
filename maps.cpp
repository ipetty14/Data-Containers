#include <iostream>
#include <map>

using namespace std;

int main() 
{
	map < string, int > m;
	m["Apple"] = 1;
	m["Banana"] = 5;
	
	if (m["Apple"] > m["Banana"])
		cout << m["Apple"] << endl;
	else 
	{
		cout << m["Banana"] << endl;
	}
}