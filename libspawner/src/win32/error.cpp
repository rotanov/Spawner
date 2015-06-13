#include "error.h"

#include <sstream>
#include <windows.h>
#include <dbghelp.h>

#include "stack_walker.h"

void abort_at_panic_();
void begin_panic_();
bool do_we_panic_();
void exec_on_panic_action_();

void panic_(const std::string& error_message, char* filename, int line_number) {
    std::stringstream error_text;
    error_text << filename <<  ":"
               << line_number << ":"
               << error_message;
    set_error_text(error_text.str());
    if (!do_we_panic_()) {
        begin_panic_();
        exec_on_panic_action_();
        abort_at_panic_();
    }
}

void abort_at_panic_()
{
#if defined(_DEBUG)
    throw std::runtime_error("");
#elif defined(WIN32)
    ExitProcess(1);
#else
    ::abort();
#endif
}

std::string get_win_last_error_string() {
    DWORD error_code = GetLastError();
    char* error_text = nullptr;

    auto format_message = [&](const DWORD lang_id) -> DWORD {
        return FormatMessageA(
            FORMAT_MESSAGE_FROM_SYSTEM
            | FORMAT_MESSAGE_ALLOCATE_BUFFER
            | FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            error_code,
            lang_id,
            (LPSTR)&error_text,
            0, NULL);
    };

    if (format_message(MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US)) == 0) {
        format_message(MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL));
    }

    std::stringstream r;
    r << "error code: " << error_code;
    if (error_text != nullptr) {
        r << ": " << error_text;
    }
    LocalFree(error_text);
    return r.str();
}

static std::function<void()> on_panic_action_ = nullptr;
static std::string error_text_ = "<none>";
static bool we_do_panic_ = false;

void begin_panic_() {
    // TODO: use atomic
    we_do_panic_ = true;
}

bool do_we_panic_() {
    return we_do_panic_;
}

void set_error_text(const std::string& error_text) {
    if (do_we_panic_()) {
        error_text_ = error_text_ + ", " + error_text;
    }
    else {
        error_text_ = error_text;
    }
}

const std::string& get_error_text() {
    return error_text_;
}

void set_on_panic_action(const std::function<void()> action) {
    on_panic_action_ = action;
}

void exec_on_panic_action_() {
    if (on_panic_action_) {
        on_panic_action_();
    }
}

std::string get_stacktrace_string() {
    std::stringstream r;
    auto collect = [&](const char* s) {
        r << s;
    };
    class StackWalkerToString : public StackWalker {
        std::function<void(const char*)> f_;
    public:
        StackWalkerToString(std::function<void(const char*)> f) :f_(f) {}
    protected:
        virtual void OnOutput(LPCSTR szText) {
            f_(szText);
        }
    } sw(collect);
    sw.ShowCallstack();
    return r.str();
}
