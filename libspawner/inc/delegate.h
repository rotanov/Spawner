#pragma once

#include <fstream>
#include <string>

#include "inc/securerunner.h"

class delegate_runner: public runner
{
private:
    std::string program_to_run;
    restrictions_class restrictions;
protected:
    virtual void create_process();
public:
    delegate_runner(const std::string &program, const options_class &options,
        const restrictions_class &restrictions);
};
