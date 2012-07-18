/*
 * Copyright (C) 2012 Daniel Pfeifer <daniel@pfeifer-mail.de>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef VERA_GLOBALS_HPP
#define VERA_GLOBALS_HPP

#include "Reports.h"
#include <string>
#include <vector>
#include <boost/filesystem/path.hpp>

namespace vera
{

extern Vera::report report;
extern std::string profile;
extern boost::filesystem::path root_dir;
extern std::vector<std::string> input_files;

} // namespace vera

#endif /* VERA_GLOBALS_HPP */