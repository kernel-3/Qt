#include "stacktrace.h"

#ifdef __GNUC__

#endif

#ifdef _MSC_VER
#include "stacktrace/stackwalker.cc"

#include "stacktrace/call_stack_msvc.cc"
#endif

StackTrace::StackTrace(size_t) {}

std::string StackTrace::toStdString() const {
    std::ostringstream os;
    for (std::vector<Entry>::const_iterator it = stacks.begin();
         it != stacks.end(); ++it) {
        os << it->toString() << std::endl;
    }
    return os.str();
}
const char *StackTrace::toCstring() const {
    return toStdString().c_str();
}
