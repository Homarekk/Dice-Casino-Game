#include "../include/Dice.h"
#include <chrono>

Dice::Dice()
    // This uses an initializer list to initialize rng (the random engine) and dist (the number distribution) before the body of the constructor runs
    : rng(static_cast<unsigned long>(
        std::chrono::high_resolution_clock::now().time_since_epoch().count())),
dist(1, 99) // This creates a uniform integer distribution that generates numbers between 1 and 99 (inclusive). It doesn’t yet generate anything — it just defines the rule
    /*
    std::chrono is the time library in C++11 and later
    high_resolution_clock gives the most precise system clock available (usually nanoseconds)
    now() gets the current point in time as a time_point object
    time_since_epoch() every clock measures time as a duration since an epoch - typically January 1, 1970 (UTC) for most system
    count() the duration object can be represented in "ticks" — an integer count of the smallest measurable unit (microseconds, nanoseconds, etc.)
    We get big integer like 1733964229382764
    That’s what we use as our seed value
    std::mt19937 expects a seed of type unsigned long and that's why we cast to this type
    */
{}

int Dice::roll() {
    return dist(rng);   // uses the random engine rng to draw a number according to dist’s rule (uniform 1–99)
}

