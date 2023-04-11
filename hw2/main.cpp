#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#define all(x) begin(x),end(x)
using namespace std;
int main(int argc, char** argv){
	// sort : salary , age , female , id
	map<int,vector<vector<int> > > employeeList;
	const string FEMALE = "f";
	const string MALE = "m";
	string csvFile(argv[1]);
	fstream readStream (csvFile, ios::in);
	if(readStream.is_open())
	{
		string line;
		while(getline(readStream, line))
		{
			vector<int> row;
			stringstream str(line);

			string word;
			while(getline(str, word, ',')){
				if( word == FEMALE ){
					row.push_back(0);
				}
				else if( word == MALE ){
					row.push_back(1);
				}
				else{
					row.push_back(stoi(word));
				}
			}

			int id = row[0];
			int age = row[1];
			int gender = row[2];
			int salary = row[3];

			vector<int> current = {  age , gender , id };
			employeeList[salary].push_back( current );
		}
	}


	for(auto & i : employeeList ){
		cout<<i.first;
		sort(all(i.second));
		for(const auto & j : i.second ){
			cout<<","<<j[2];
		}
		cout<<"\n";
	}

	return 0;
}