#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void main()
{
	string filename;
	cout << "Enter a file to open:" << endl;
	cin >> filename;
	//cout << filename << endl;
	
	ifstream input;
	input.open(filename);

	string line;

	while (!input.eof())
	{
		getline(input, line);
		//cout << line << endl;
		if (line != "")
		{
			int a, b;
			a = atoi(line.substr(0,1).c_str());
			b = atoi(line.substr(2,1).c_str());
			cout << a << " " << b << endl;
		}
	}

	input.close();
}