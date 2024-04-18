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

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
);

bool backtrackSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t dayIndex, std::vector<size_t>& shiftsCount);

bool isValidAssignment(const AvailabilityMatrix& avail, const size_t workerIndex, const size_t dayIndex, const size_t maxShifts, DailySchedule& sched, const std::vector<size_t>& shiftsCount);

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) 
{
    if (avail.empty()) {
        return false;
    }
    sched.clear();
    sched.resize(avail.size());
    std::vector<size_t> shiftsCount(avail[0].size(), 0);

    return backtrackSchedule(avail, dailyNeed, maxShifts, sched, 0, shiftsCount);
}

bool backtrackSchedule(const AvailabilityMatrix& avail, const size_t dailyNeed, const size_t maxShifts, DailySchedule& sched, size_t dayIndex, std::vector<size_t>& shiftsCount) {
    if (dayIndex == avail.size()) {
        return true;
    }

    for (size_t workerIndex = 0; workerIndex < avail[dayIndex].size(); ++workerIndex) {
        if (isValidAssignment(avail, workerIndex, dayIndex, maxShifts, sched, shiftsCount)) {
            sched[dayIndex].push_back(workerIndex);
            shiftsCount[workerIndex]++;
            if (backtrackSchedule(avail, dailyNeed, maxShifts, sched, dayIndex + 1, shiftsCount)) {
                return true;
            }
            sched[dayIndex].pop_back();
            shiftsCount[workerIndex]--;
        }
    }

    if (dayIndex == 0 && !sched[0].empty()) {
        return false;
    } else if (dayIndex > 0 && sched[dayIndex - 1].empty()) {
        return false;
    }

    return false;
}

bool isValidAssignment(const AvailabilityMatrix& avail, const size_t workerIndex, const size_t dayIndex, const size_t maxShifts, DailySchedule& sched, const std::vector<size_t>& shiftsCount) {
    return avail[dayIndex][workerIndex] && shiftsCount[workerIndex] < maxShifts;
}
