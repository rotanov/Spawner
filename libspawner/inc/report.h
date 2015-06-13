#pragma once

#include <string>

#include "status.h"
#include "options.h"
#include "restrictions.h"

const char *get_exception_name(exception_t exception);
const char *get_exception_text(exception_t exception);
std::string get_exception_info(exception_t exception, std::string format);
std::string get_status_text(process_status_t process_status);
std::string get_terminate_reason(terminate_reason_t terminate_reason);

class report_class// <-- struct?
{
public:
    report_class():process_status(process_not_started), exception(exception_exception_no), terminate_reason(terminate_reason_not_terminated), peak_memory_used(0),
        write_transfer_count(0), exit_code(0), total_time(0), load_ratio(0.0), processor_time(0), user_time(0), kernel_time(0){}
    process_status_t process_status;
    exception_t exception;
    terminate_reason_t terminate_reason;
    //may be move this to different structure
    unsigned long peak_memory_used;
    unsigned long long write_transfer_count;
//  size_t read_transfer_count;
    unsigned int exit_code;
    size_t total_time;
    double load_ratio;
    unsigned long long processor_time;
    unsigned long long user_time;
    // additional info subset
    unsigned long long kernel_time;
    // options subset
    std::string application_name;
    std::wstring login;
    std::string working_directory;
};
