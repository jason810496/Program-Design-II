#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#define all(x) begin(x),end(x)
using namespace std;

int main(int argc, char** argv){
	// employee_id, #overloading_days, #sign_forget_days
	ios_base::sync_with_stdio(0);cin.tie(0);
	const string SIGNIN = "sign-in";
	const string SIGNOUT = "sign-out";

	string csvFile(argv[1]);
	fstream readStream (csvFile, ios::in);

	vector< vector<long long> > sorted;
	if(readStream.is_open())
	{
		string line;
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
	}

	sort(all(sorted),[&](const vector<long long> &a,const vector<long long> &b){
			return (a[0] == b[0] ? a[2] < b[2] : a[0] < b[0] );
	});

	pair<int,int> ans;
	int lastId = -1;
	long long lastSignIn = 0;
	long long last = 0;
	for(const auto & row : sorted){

		int id = row[0];
		if( lastId!=-1 && lastId != id ){
			if( lastSignIn != 0 ){
				ans.second++;
			}
			cout<<lastId<<","<<ans.first<<","<<ans.second<<"\n";
			ans = {0,0};
			lastSignIn = 0;
		}
		lastId = id;

		int status = row[1];
		long long cur  = row[2];
		int date = row[2] / 10000;
		int time = row[2] % 10000;

		long long last = lastSignIn;
		int lastDate = last / 10000;
		int lastTime = last % 10000;

		if( status ){
			if( date != lastDate && lastDate != 0 ){
				ans.second++;
			}
			lastSignIn = cur;
		}
		else{
			if( date == lastDate ){
				if( cur - last > 800){
					ans.first++;
				}
			}
			else{
				if( lastDate == 0 ){
					ans.second++;
				}
				else{
					ans.second+=2;
				}

			}
			lastSignIn=0;
		}
	}

	if( lastSignIn != 0 ){
		ans.second++;
	}
	cout<<lastId<<","<<ans.first<<","<<ans.second<<"\n";

	return 0;
}