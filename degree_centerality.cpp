#include <iostream>
using namespace std;

int main()
{
	int n,m,temp;
	cin >> n >> m;
	int * _array = new int[n];
	for (int i = 0; i < n; i++)
		_array[i] = 0;
	for (int i = 0; i < m; i++)
	{
		cin >> temp;
		_array[temp]++;
		cin >> temp;
		_array[temp]++;
		cin >> temp;
	}

	for (int i = 0; i < n-1; i++)
		cout << _array[i] << "\n";
		cout<<_array[n-1];
}
