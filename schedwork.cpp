#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool backtrack(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& curShifts,
    int curDay);

void all_combinations(const vector<bool> daily_avail,
    int dailyNeed,
    vector<vector<Worker_T>>& all_combos,
    vector<Worker_T>& cur_schedule,
    int start);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int numWorkers = avail[0].size();
    vector<int> curShifts(numWorkers, 0);
    return backtrack(avail, dailyNeed, maxShifts, sched, curShifts, 0);
}

bool backtrack(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& curShifts,
    int curDay)
{
    if (curDay == avail.size())
        return true;
    vector<vector<Worker_T>> all_combos;
    vector<bool> daily_avail = avail[curDay];
    vector<Worker_T> cur_schedule;
    all_combinations(daily_avail, dailyNeed, all_combos, cur_schedule, 0);
    for (int i = 0; i < all_combos.size(); i++)
    {
        vector<Worker_T> combo = all_combos[i];
        bool success = true;
        for (Worker_T j : combo)
        {
            curShifts[j]++;
            if (curShifts[j] > maxShifts)
                success = false;
        }
        if (success)
        {
            sched.push_back(combo);
            bool temp = backtrack(avail, dailyNeed, maxShifts, sched, curShifts, curDay + 1);
            if (temp)
                return true;
            sched.pop_back();
        }
        for (Worker_T j : combo)
            curShifts[j]--;
    }
    return false;
}

// Generate all combinations for a given day
void all_combinations(const vector<bool> daily_avail,
    int dailyNeed,
    vector<vector<Worker_T>>& all_combos,
    vector<Worker_T>& cur_schedule,
    int start)
{
    if (cur_schedule.size() == dailyNeed)
    {
        all_combos.push_back(cur_schedule);
        return;
    }
    for (int i = start; i < daily_avail.size(); i++)
    {
        if (daily_avail[i] == true)
        {
            cur_schedule.push_back(i);
            all_combinations(daily_avail, dailyNeed, all_combos, cur_schedule, i+1);
            cur_schedule.pop_back();
        }
    }
}

