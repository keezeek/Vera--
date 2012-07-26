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

    void print_report(std::ostream&);

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

    const std::string& get_line(int number) const
    {
       if (number < 1 || number > static_cast<int>(lines_.size()))
        {
            std::cerr << "Requested wrong line number: " << number << '\n';
            std::cerr << "lines.size in " << path_ << " is " << lines_.size() << '\n';
            throw std::runtime_error("requested line number is out of range");
        }

        return lines_[number - 1];
    }

    std::vector<vera::token> get_tokens() const;

    std::vector<vera::token> get_tokens2(
        int from_line, int from_column, int to_line, int to_column) const;

    std::vector<vera::token> get_tokens3(
        const std::vector<std::string>& filter) const;

    std::vector<vera::token> get_tokens4(
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
