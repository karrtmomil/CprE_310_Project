#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

typedef struct Page {
	vector<int> linkTo;
	vector<int> linkFrom;
	double rankOld;
	double rankNew;

	Page()
	{
		linkTo = vector<int>();
		linkFrom = vector<int>();
		rankOld = 1.0;
		rankNew = 1.0;
	}
} Page;

void addEdge(int a, int b, deque<Page>& pages);
bool iteration(deque<Page> &pages);
bool contains(const std::vector<int> &vec, const int &value);
void printRankNew(deque<Page> &pages);
void printRankOld(deque<Page> &pages);

void main()
{
	int maxPages = 100;
	string filename;
	cout << "Enter a file to open:" << endl;
	cin >> filename;
	cout << "Enter the number of pages:" << endl;
	cin >> maxPages;
	//cout << filename << endl;

	deque<Page> pages1(maxPages, Page());
	deque<Page> pages2(maxPages, Page());
	
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
			//cout << i << endl;
			a = atoi(line.substr(0,i).c_str());
			i = line.find_last_of("\t");
			if ( i == -1) i = line.find_last_of(" ");
			//cout << i << endl;
			b = atoi(line.substr(i + 1).c_str());
			//cout << a << " " << b << endl;

			addEdge(a,b,pages1);
			addEdge(b,a,pages2);
			
			//cout << pages1[a - 1].linkTo.size() << endl;
			//cout << pages1[b - 1].linkFrom.size() << endl;
			//cout << a << ": " << pages1[a-1].linkTo.back() <<"	"<< b << ": " <<pages1[b-1].linkFrom.back() << endl;
			//cout << pages2[a - 1].linkTo.size() << endl;
			//cout << pages2[b - 1].linkFrom.size() << endl;
			//cout << b << ": " << pages2[b-1].linkTo.back() <<"	"<< a << ": " <<pages2[a-1].linkFrom.back() << endl;
		}
	}
	input.close();

	bool iterate = true;
	int iterations = 0;
	while(iterate)
	{
		iterate = !iteration(pages1);
		iterations++;
	}
	//cout << "completed iterating" << endl;
	cout << "Interpretation 1, Iterations: " << iterations - 1 << endl;
	printRankOld(pages1);

	iterate = true;
	iterations = 0;
	while(iterate)
	{
		iterate = !iteration(pages2);
		iterations++;
	}
	//cout << "completed iterating" << endl;
	cout << "Interpretation 2, Iterations: " << iterations - 1 << endl;
	printRankOld(pages2);
}

void addEdge(int a, int b, deque<Page> &pages)
{
	if(!contains(pages[a-1].linkTo, b) && a != b)
	{
		pages[a - 1].linkTo.push_back(b);
		pages[b - 1].linkFrom.push_back(a);
	}
}

/**
* This function runs a single iteration and returns true if no more iterations are needed
*/
bool iteration(deque<Page> &pages)
{
	bool last = true;
	
	// calculate pagerank
	for (int i = 0; i < pages.size(); i++)
	{
		double sum = 0;
		for (int j = 0; j < pages[i].linkFrom.size(); j ++)
		{
			Page temp = pages[pages[i].linkFrom[j] - 1];
			sum += (temp.rankOld / temp.linkTo.size());
		}
		pages[i].rankNew = 0.85 + 0.15 * sum;

		if(abs(pages[i].rankNew - pages[i].rankOld) > 0.001)
		{
			last = false;
		}
	}

	//printRankNew(pages);

	if(!last)
	{
		// Update the pagerank values from new to old
		for (int i = 0; i < pages.size(); i++)
		{
			pages[i].rankOld = pages[i].rankNew;
		}
	}

	return last;
}

bool contains(const std::vector<int> &vec, const int &value)
{
    return find(vec.begin(), vec.end(), value) != vec.end();
}

void printRankNew(deque<Page> &pages)
{
	for (int i = 0; i < pages.size(); i++)
	{
		cout << /*"Pagerank " <<*/ i + 1 << ": " << pages[i].rankNew << "\t";// << endl;
	} 
	cout << endl;
}

void printRankOld(deque<Page> &pages)
{
	for (int i = 0; i < pages.size(); i++)
	{
		cout << /*"Pagerank " <<*/ i + 1 << ": " << pages[i].rankOld << "\t";// << endl;
	} 
	cout << endl;
}