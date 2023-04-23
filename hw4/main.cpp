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
#include <cmath>
using namespace std;

struct employee
{
    long id;
    long timestamp;
    employee(long id,long timestamp) : id(id), timestamp(timestamp) {}
};

long addDaysToDate(long date, int days) {
    // Extract year, month, and day from the date string
    int year = date / 10000;
    int month = date / 100 % 100;
    int day = date % 100;

    // Add the desired number of days
    day += days;

    // Check if the resulting day is greater than the number of days in the resulting month
    int daysInMonth;
    switch (month) {
        case 2:
            if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) {
                daysInMonth = 29;
            } else {
                daysInMonth = 28;
            }
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            daysInMonth = 30;
            break;
        default:
            daysInMonth = 31;
            break;
    }
    if (day > daysInMonth) {
        day -= daysInMonth;
        month++;
    }

    // Check if the resulting month is greater than 12
    if (month > 12) {
        month = 1;
        year++;
    }

    // Convert year, month, and day back into a date string
    long newDate = year * 10000 + month * 100 + day;

    return newDate;
}

int dateDifference(long  date1, long  date2)
{
    // Extract year, month, and day from the date
    long  year1 = date1 / 10000;
    long  month1 = (date1 % 10000) / 100;
    long  day1 = date1 % 100;
    long  year2 = date2 / 10000;
    long  month2 = (date2 % 10000) / 100;
    long  day2 = date2 % 100;

    // Calculate the Julian day number for each date
    long a = (14 - month1) / 12;
    long y1 = year1 + 4800 - a;
    long m1 = month1 + 12 * a - 3;
    long jd1 = day1 + (153 * m1 + 2) / 5 + 365 * y1 + y1 / 4 - y1 / 100 + y1 / 400 - 32045;

    long b = (14 - month2) / 12;
    long y2 = year2 + 4800 - b;
    long m2 = month2 + 12 * b - 3;
    long jd2 = day2 + (153 * m2 + 2) / 5 + 365 * y2 + y2 / 4 - y2 / 100 + y2 / 400 - 32045;

    return jd1 - jd2;
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
            sorted.push_back(employee(id, timestamp));
        }
    }

    sort(sorted.begin(), sorted.end(), [&](const employee &a, const employee &b){ 
        return (a.id == b.id ? a.timestamp < b.timestamp : a.id < b.id);
    });

    int lastId = sorted[0].id;
    long  lastDate =  sorted[0].timestamp/10000;
    int continueWork = 1;
    long  startDate = lastDate;
    int curContinueWork = 1;
    long  curStartDate = startDate;

    // for (const employee &row : sorted)
    // {
    //     cout << row.id  << "," << row.timestamp << endl;
    // }

    priority_queue<pair<int, pair<int, long >>, vector<pair<int, pair<int, long >>>, greater<pair<int, pair<int, long >>>> pq;
    for (const employee &row : sorted)
    {

        int  id = row.id;
        if (lastId != id)
        {
            if (curContinueWork > continueWork)
            {
                continueWork = curContinueWork;
                startDate = curStartDate;
            }
            pq.push(make_pair(continueWork, make_pair(lastId, startDate)));
            if (pq.size() > 3)
            {
                pq.pop();
            }
            curContinueWork = 1;
            continueWork = 1;
        }
        lastId = id;

        long  cur = row.timestamp;
        long  date = row.timestamp / 10000;
        int status = dateDifference(date, lastDate);

        if (status == 1)
        {
            curContinueWork++;
        }
        else if (status > 1)
        {
            if (curContinueWork > continueWork)
            {
                continueWork = curContinueWork;
                startDate = curStartDate;
            }
            curContinueWork = 0;
            curStartDate = date;
        }
        lastDate = date;
    }
    pq.push(make_pair(continueWork, make_pair(lastId, startDate)));
    if (pq.size() > 3)
    {
        pq.pop();
    }

    pair<int, pair<int, long >> ans[3];
    int i = 2;
    while (pq.size())
    {
        ans[i--] = pq.top();
        pq.pop();
    }

    sort(begin(ans), end(ans), [&](pair<int, pair<int, long >> &a,pair<int, pair<int, long >> &b){ 
        return (a.first == b.first ? a.second.first < b.second.first : a.first > b.first);
    });

    for (const pair<int, pair<int, long >> &cur : ans)
    {
        cout << cur.second.first << "," << cur.first << "," << cur.second.second << "," << addDaysToDate(cur.second.second,cur.first -1) << "\n";
    }

    return 0;
}