#ifndef STACKTRACE_HPP
#define STACKTRACE_HPP

#include "stacktrace/call_stack.hpp"
#include <sstream>
#include <string>
#include <vector>

struct Entry {
    Entry() : line(0) {}
    std::string file;
    size_t line;
    std::string function;

    std::string toString() const {
        std::ostringstream os;
        os << file << "(" << line << "):" << function;
        return os.str();
    }
};

class StackTrace {

public:
    // depth堆栈深度，默认32
    StackTrace(size_t = 32);

    std::string toStdString() const;
    const char *toCstring() const;

private:
    std::vector<Entry> stacks;
};

#endif // STACKTRACE_HPP
