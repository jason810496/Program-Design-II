#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct employee{
	unsigned int id;
	bool status;
	unsigned int timestamp;
	employee(unsigned int id, bool status, unsigned int timestamp):id(id),status(status),timestamp(timestamp){}
};

int main(int argc, char** argv){
	// employee_id, #overloading_days, #sign_forget_days
	ios_base::sync_with_stdio(0);cin.tie(0);
	//const string SIGNIN = "sign-in";
	//const string SIGNOUT = "sign-out";

	string csvFile(argv[1]);
	fstream readStream (csvFile, ios::in);

	vector< employee > sorted;
	stringstream str;
	if(readStream.is_open())
	{
		string line;
		while(getline(readStream, line))
		{

			str<<line;
			string word;

			short row = 0;
			unsigned int id;
			bool status;
			unsigned int timestamp;

			while(getline(str, word, ',')){
				if( row == 0 ){
					id = stoll(word);
				}
				else if( row == 1){
					status = (word[5] == 99 );
				}
				else{
					timestamp = stoll(word);
				}
				row++;
			}
			str.clear();
			sorted.push_back(employee(id,status,timestamp));

		}
	}

	sort(sorted.begin(),sorted.end(),[&](const employee &a,const employee &b){
			return (a.id == b.id ? a.timestamp < b.timestamp : a.id < b.id );
	});

	unsigned int overloading_days = 0;
	unsigned int sign_forget_days = 0;

	int lastId = sorted[0].id;
	unsigned int lastSignIn = 0;
	unsigned int last = 0;
	for(const employee & row : sorted){

		unsigned int id = row.id;
		if( lastId != id ){
			if( lastSignIn != 0 ){
				sign_forget_days++;
			}
			cout<<lastId<<","<<overloading_days<<","<<sign_forget_days<<"\n";

			overloading_days = 0;
			sign_forget_days = 0;
			lastSignIn = 0;
		}
		lastId = id;

		bool status = row.status;
		unsigned int cur  = row.timestamp;
		unsigned int date = row.timestamp / 10000;
		unsigned int time = row.timestamp % 10000;

		unsigned int last = lastSignIn;
		unsigned int lastDate = last / 10000;
		unsigned int lastTime = last % 10000;

		if( status ){
			if( date != lastDate && lastDate != 0 ){
				sign_forget_days++;
			}
			lastSignIn = cur;
		}
		else{
			if( date == lastDate ){
				if( cur - last > 800){
					overloading_days++;
				}
			}
			else{
				if( lastDate == 0 ){
					sign_forget_days++;
				}
				else{
					sign_forget_days+=2;
				}
			}
			lastSignIn=0;
		}
	}

	if( lastSignIn != 0 ){
		sign_forget_days++;
	}
	cout<<lastId<<","<<overloading_days<<","<<sign_forget_days<<"\n";

	return 0;
}