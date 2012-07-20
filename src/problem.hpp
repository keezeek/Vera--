/*
 * Copyright (C) 2012 Daniel Pfeifer <daniel@pfeifer-mail.de>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef VERA_PROBLEM_HPP
#define VERA_PROBLEM_HPP

#include <string>

namespace vera
{

struct problem
{
    problem(std::string file, std::size_t line, std::string msg) :
            file(file), line(line), msg(msg)
    {
    }

    bool operator<(const problem& other) const
    {
        if (file < other.file)
            return true;

        if (file == other.file)
        {
            if (line < other.line)
                return true;

            if (line == other.line)
                return msg < other.msg;
        }

        return false;
    }

    bool operator==(const problem& other) const
    {
        return file == other.file && line == other.line && msg == other.msg;
    }

    std::string file;
    std::size_t line;
    std::string msg;
};

} // namespace

#endif /* VERA_PROBLEM_HPP */
