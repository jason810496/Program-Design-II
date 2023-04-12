#pragma GCC optimize ("O3,unroll-loops")
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>
#define all(x) begin(x),end(x)
using namespace std;
int main(int argc, char** argv){
	// employee_id, #overloading_days, #sign_forget_days
	ios_base::sync_with_stdio(0);cin.tie(0);
	unordered_map<int,pair<int,int> > count;
	unordered_map<int,long long> lastSignIn;
	const string SIGNIN = "sign-in";
	const string SIGNOUT = "sign-out";
	string csvFile(argv[1]);
	fstream readStream (csvFile, ios::in);
	if(readStream.is_open())
	{
		string line;
		vector< vector<long long> > sorted;
		while(getline(readStream, line))
		{
			vector<long long> row;
			stringstream str(line);

			string word;
			while(getline(str, word, ',')){
				if( word == SIGNOUT ){
					row.push_back(0);
				}
				else if( word == SIGNIN ){
					row.push_back(1);
				}
				else{
					row.push_back(stoll(word));
				}
			}
			sorted.push_back(row);

		}

		sort(all(sorted),[&](const vector<long long> &a,const vector<long long> &b){
				return (a[2] == b[2] ? a[1] > b[1] : a[2] < b[2] );
		});

		for(const auto & row : sorted){

			if( count.count(row[0]) == 0 ){
				count[row[0]] = {0,0};
				lastSignIn[row[0]] = 0;
			}
			int id = row[0];
			int status = row[1];
			long long cur  = row[2];
			int date = row[2] / 10000;
			int time = row[2] % 10000;

			long long last = lastSignIn[ id ];
			int lastDate = last / 10000;
			int lastTime = last % 10000;

			if( status ){
				if( date != lastDate && lastDate != 0 ){
					count[ id ].second++;
				}
				lastSignIn[ id ] = cur;
			}
			else{
				if( date == lastDate ){
					if( cur - last > 800){
						count[ id ].first++;
					}
				}
				else{
					if( lastDate == 0 ){
						count[ id ].second++;
					}
					else{
						count[ id ].second+=2;
					}

				}
				lastSignIn[ id ] = 0;
			}

		}


		for(const auto & i : lastSignIn ){
			if( i.second !=0 ){
				count[ i.first ].second++;
			}
		}

		for(const auto & i : count ){
			cout<<i.first<<","<<i.second.first<<","<<i.second.second<<"\n";
		}
	}


	return 0;
}