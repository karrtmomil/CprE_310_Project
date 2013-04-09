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
			int a, b, i;
			i = line.find("\t");
			if( i == -1) i = line.find(" ");
			cout << i << endl;
			a = atoi(line.substr(0,i).c_str());
			i = line.find_last_of("\t");
			if ( i == -1) i = line.find_last_of(" ");
			cout << i << endl;
			b = atoi(line.substr(i + 1).c_str());
			cout << a << " " << b << endl;
		}
	}

	input.close();
}