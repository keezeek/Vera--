/*
 * Copyright (C) 2012 Daniel Pfeifer <daniel@pfeifer-mail.de>
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef VERA_FILE_HPP
#define VERA_FILE_HPP

#include <string>
#include <vector>
#include "Tokens.h"

namespace vera
{

class file
{
public:
    file(const std::string& path);

    void report(int line, const std::string& msg)
    {
        problems_.push_back(problem(line, msg));
    }

    const std::string& path()
    {
        return path_;
    }

    const std::vector<std::string>& lines() const
    {
        return lines_;
    }

    std::size_t line_count()
    {
        return lines_.size();
    }

    const std::string& get_line(std::size_t idx) const
    {
        return lines_.at(idx);
    }

    std::vector<vera::token> get_tokens() const;

    std::vector<vera::token> get_tokens(
        int from_line, int from_column, int to_line, int to_column) const;

    std::vector<vera::token> get_tokens(
        const std::vector<std::string>& filter) const;

    std::vector<vera::token> get_tokens(
        int from_line, int from_column, int to_line, int to_column,
        const std::vector<std::string>& filter) const;

private:
    struct problem
    {
        problem(std::size_t line, std::string msg) :
                line(line), msg(msg)
        {
        }

        bool operator<(const problem& other) const
        {
            if (line < other.line)
                return true;

            if (line == other.line)
                return msg < other.msg;

            return false;
        }

        bool operator==(const problem& other) const
        {
            return line == other.line && msg == other.msg;
        }

        std::size_t line;
        std::string msg;
    };

    std::string path_;
    std::vector<std::string> lines_;
    std::vector<Vera::TokenRef> tokens_;
    std::vector<problem> problems_;
};

} // namespace vera

#endif /* VERA_FILE_HPP */
