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
bool backtrackSchedule(const AvailabilityMatrix& avail, size_t dailyNeed, size_t maxShifts, DailySchedule& sched, size_t dayIndex, vector<size_t>& shiftsCount);
bool isValidAssignment(const AvailabilityMatrix& avail, size_t workerIndex, size_t dayIndex, size_t maxShifts, const vector<size_t>& shiftsCount);


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
    sched.resize(avail.size(), vector<Worker_T>());
    vector<size_t> shiftsCount(avail[0].size(), 0);

    return backtrackSchedule(avail, dailyNeed, maxShifts, sched, 0, shiftsCount);
}

bool backtrackSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t dayIndex, vector<size_t>& shiftsCount){
    if(dayIndex == avail.size()){
        return true;
    }

    if(sched[dayIndex].size() == dailyNeed){
        return backtrackSchedule(avail, dailyNeed, maxShifts, sched, dayIndex + 1, shiftsCount);
    }

    for(size_t workerIndex = 0; workerIndex < avail[dayIndex].size(); ++workerIndex){
        if(isValidAssignment(avail, workerIndex, dayIndex, maxShifts, shiftsCount)){
            sched[dayIndex].push_back(workerIndex);
            shiftsCount[workerIndex]++;
            if(backtrackSchedule(avail, dailyNeed, maxShifts, sched, dayIndex, shiftsCount)){
                return true;
            }
            sched[dayIndex].pop_back();
            shiftsCount[workerIndex]--;
        }
    }
    return false;
}

bool isValidAssignment(const AvailabilityMatrix& avail, size_t workerIndex, size_t dayIndex, size_t maxShifts, const vector<size_t>& shiftsCount){
    return avail[dayIndex][workerIndex] && shiftsCount[workerIndex] < maxShifts;
}