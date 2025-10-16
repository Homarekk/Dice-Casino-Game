#include "../include/Transaction.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <utility>

// static means that this function is only visible inside this file
// This function returns a string with the current date and time (2025-10-11 21:05:42)
static std::string currentTimestamp() {
    using namespace std::chrono;    // We will use chrono namespace (we don't have to type std::chrono each time we use it)
    auto now = system_clock::now(); // gives you the current system time point, like “the clock’s reading right now.”
    std::time_t t = system_clock::to_time_t(now);   // convert to time_t, because std::localtime() expects a pointer to time_t
    std::tm tm = *std::localtime(&t);   // tm is a human-readable time format and we need to dereference it because localtime() returns a pointer
    std::ostringstream oss; // std::ostringstream = output string stream, a stream that writes into a string instead of the console or file
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S"); // std::put_time formats a tm structure into a human-readable date/time string
    return oss.str();   // oss.str() extracts the entire string built in the stream
}

/*
time_t - A numeric type (usually long or long long) that stores seconds since 1970-01-01 00:00:00 UTC — called the Unix epoch
time_t comes from the standard library → so it’s std::time_t
now - current time
system_clock::to_time_t(now) - t now holds something like 1739289420 (the number of seconds since 1970-01-01 00:00 UTC)
std::localtime(&t) takes a pointer to time_t (&t), converts it to a std::tm* that represents local time (your current timezone), returns a pointer to an internal static tm object
*std::localtime(&t) gives us the tm structure itself, not a pointer
&tm is passed by pointer because that’s what put_time() expects
*/

// Transaction constructor
Transaction::Transaction(std::string type, double amount)
    : type(std::move(type)), amount(amount), timestamp(currentTimestamp()) {}

std::string Transaction::toString() const {
    std::ostringstream oss;
    oss << "[" << timestamp << "] " << type << " " << amount;
    return oss.str();
}

