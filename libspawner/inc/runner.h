#pragma once

#include <string>
#include <map>
#include <memory>

#include "inc/platform.h"
#include "inc/pipes.h"
#include "inc/status.h"
#include "inc/report.h"
#include "inc/options.h"

class runner {
private:
    typedef std::list<std::pair<std::string, std::string>> env_vars_list_t;

    void copy_environment(TCHAR* dest, const WCHAR* source) const;
    void set_environment_var(TCHAR* dest, const std::string& varStr) const;

    env_vars_list_t read_environment(const WCHAR* source) const;
    env_vars_list_t set_environment_for_process() const;
    void restore_original_environment(const env_vars_list_t& original) const;
    mutex_c suspend_mutex_;
protected:
    unsigned long long creation_time;
    DWORD process_creation_flags;
    startupinfo_t si;
    bool running_async;
    options_class options;
    std::string program;
    std::map<pipes_t, std::shared_ptr<pipe_c>> pipes;
    process_info_t process_info;
    process_status_t process_status;
    bool running;
    report_class report;
    thread_t running_thread;
    handle_t init_semaphore;//rename to mutex_init_signal
    static handle_t main_job_object;
    static handle_t main_job_object_access_mutex;
    static bool allow_breakaway;
    void set_allow_breakaway(bool allow);
    bool init_process(char *cmd, const char *wd);
    bool init_process_with_logon(char *cmd, const char *wd);
    virtual void create_process();
    virtual void free();
    virtual void wait();
    virtual void debug();
    virtual void requisites();
    static thread_return_t async_body(thread_param_t param);
    void enumerate_threads_(std::function<void(handle_t)> on_thread);
public:
    runner(const std::string &program, const options_class &options);
    virtual ~runner();
    unsigned long get_exit_code();
    virtual process_status_t get_process_status();
    process_status_t get_process_status_no_side_effects();
    exception_t get_exception();
    unsigned long get_id();
    std::string get_program() const;
    options_class get_options() const;
    virtual report_class get_report();
    virtual unsigned long long get_time_since_create();
    static unsigned long long get_current_time();
    virtual handle_t get_process_handle();
    virtual void get_times(unsigned long long *_creation_time, unsigned long long *exit_time, unsigned long long *kernel_time, unsigned long long *user_time);

    virtual void run_process();
    virtual void run_process_async();
    virtual restrictions_class get_restrictions() const { return restrictions_class(); }
    bool wait_for(const unsigned long &interval = INFINITE);
    bool wait_for_init(const unsigned long &interval);
    virtual void safe_release();
    void set_pipe(const pipes_t &pipe_type, std::shared_ptr<pipe_c> pipe_object);
    std::shared_ptr<pipe_c> get_pipe(const pipes_t &pipe_type);
    std::shared_ptr<input_pipe_c> get_input_pipe();
    std::shared_ptr<output_pipe_c> get_output_pipe();
    bool start_suspended = false;
    void suspend();
    void resume();
    bool is_running();
    std::vector<std::shared_ptr<duplex_buffer_c>> duplex_buffers;
};
