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
#include <queue>
#include <ctime>
#include <cstring>
using namespace std;

struct employee
{
    long id;
    long timestamp;
    employee(long id,long timestamp) : id(id), timestamp(timestamp) {}
};

long countDaysBetweenDates(long date1, long date2) {
    // Convert date1 string to struct tm
    struct tm tm1;
    std::memset(&tm1, 0, sizeof(struct tm));
    tm1.tm_year = (date1 / 10000) - 1900;
    tm1.tm_mon = ((date1 / 100) % 100) - 1;
    tm1.tm_mday = date1 % 100;
    time_t time1 = mktime(&tm1);

    // Convert date2 string to struct tm
    struct tm tm2;
    std::memset(&tm2, 0, sizeof(struct tm));
    tm2.tm_year = (date2 / 10000) - 1900;
    tm2.tm_mon = ((date2 / 100) % 100) - 1;
    tm2.tm_mday = date2 % 100;
    time_t time2 = mktime(&tm2);

    // Calculate difference in seconds
    double diffSeconds = std::difftime(time1, time2);

    // Convert difference in seconds to difference in days
    long diffDays = static_cast<long>(diffSeconds / 86400);

    return diffDays;
}


long shiftDays(long origDate, int n) {
    // Convert origDate string to struct tm
    struct tm tm1;
    std::memset(&tm1, 0, sizeof(struct tm));
    tm1.tm_year = (origDate / 10000) - 1900;
    tm1.tm_mon = ((origDate / 100) % 100) - 1;
    tm1.tm_mday = origDate % 100;
    time_t time1 = mktime(&tm1);

    // Calculate number of seconds to add
    int secondsInDay = 86400;
    int secondsToAdd = n * secondsInDay;

    // Add seconds to time1
    time1 += secondsToAdd;

    // Convert modified time_t to struct tm
    struct tm* tm2 = std::localtime(&time1);

    // Convert struct tm to long integer in YYYYMMDD format
    long shiftedDate = ((tm2->tm_year + 1900) * 10000) + ((tm2->tm_mon + 1) * 100) + tm2->tm_mday;

    return shiftedDate;
}

int main(int argc, char **argv)
{
    // employee_id, #overloading_days, #sign_forget_days
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    // const string SIGNIN = "sign-in";
    // const string SIGNOUT = "sign-out";

    string csvFile(argv[1]);
    fstream readStream(csvFile, ios::in);

    vector<employee> sorted;
    stringstream str;
    if (readStream.is_open())
    {
        string line;
        while (getline(readStream, line))
        {

            str << line;
            string word;

            short row = 0;
            long  id;
            bool status;
            long  timestamp;

            while (getline(str, word, ','))
            {
                if (row == 0)
                {
                    id = stoll(word);
                }
                else if (row == 1)
                {
                    status = (word[5] == 99);
                }
                else
                {
                    timestamp = stoll(word);
                }
                row++;
            }
            str.clear();
            sorted.push_back(employee(id, timestamp/10000));
        }
    }

    sort(sorted.begin(), sorted.end(), [&](const employee &a, const employee &b){ 
        return (a.id == b.id ? a.timestamp < b.timestamp : a.id < b.id);
    });

    // for(int i = 0; i < sorted.size(); i++){
    //     cout << sorted[i].id << " " << sorted[i].timestamp << endl;
    // }

    int lastId = sorted[0].id;
    long  lastDate =  sorted[0].timestamp;
    int continueWork = 1;
    long  startDate = lastDate;
    int curContinueWork = 1;
    long  curStartDate = startDate;

    // priority_queue<pair<int, pair<int, long >>, vector<pair<int, pair<int, long >>>, greater<pair<int, pair<int, long >>>> pq;
    
    // day , id , start date
    vector<pair<int, pair<int, long > > > ans;
    for (const employee &row : sorted)
    {

        int  id = row.id;
        if (lastId != id)
        {
            if (curContinueWork >= continueWork)
            {
                continueWork = curContinueWork;
                startDate = curStartDate;
            }
            ans.push_back(make_pair(continueWork, make_pair(lastId, startDate)));
            // pq.push(make_pair(continueWork, make_pair(lastId, startDate)));
            // if (pq.size() > 3)
            // {
            //     pq.pop();
            // }
            curContinueWork = 1;
            continueWork = 1;
        }
        lastId = id;

        long  cur = row.timestamp;
        long  date = row.timestamp;
        int status = countDaysBetweenDates(date, lastDate);
        // cout<<status<<"\n";

        if (status == 1)
        {
            curContinueWork++;
        }
        else if( status == 0 ) continue;
        else
        {
            if (curContinueWork >= continueWork)
            {
                continueWork = curContinueWork;
                startDate = curStartDate;
            }
            curContinueWork = 1;
            curStartDate = date;
        }
        lastDate = date;
    }
    // pq.push(make_pair(continueWork, make_pair(lastId, startDate)));
    // if (pq.size() > 3)
    // {
    //     pq.pop();
    // }
    ans.push_back(make_pair(continueWork, make_pair(lastId, startDate)));


    // pair<int, pair<int, long >> ans[3];
    // int i = 2;
    // while (pq.size())
    // {
    //     ans[i--] = pq.top();
    //     pq.pop();
    // }

    sort(begin(ans), end(ans), [&](pair<int, pair<int, long >> &a,pair<int, pair<int, long >> &b){ 
        return (a.first == b.first ? a.second.first < b.second.first : a.first > b.first);
    });

    for (int i=0;i<3;i++)
    {
        const pair<int, pair<int, long >> cur = ans[i];
        cout << cur.second.first << "," << cur.first << "," << cur.second.second << "," << shiftDays(cur.second.second,cur.first -1) << "\n";
    }

    return 0;
}