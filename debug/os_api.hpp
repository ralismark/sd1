#pragma once

#include <system_error>

std::system_error os_lasterr();

void hit_prompt();
