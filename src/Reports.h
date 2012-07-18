//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef VERA_REPORT_HPP
#define VERA_REPORT_HPP

#include <string>
#include <iosfwd>
#include <map>

namespace Vera
{

class report
{
public:
    explicit report(bool omit_duplicates) :
            omit_duplicates(omit_duplicates)
    {
    }

    void add(std::string name, int lineNumber, const std::string& msg);

    typedef std::multimap<int, std::string> FileMessagesCollection;
    typedef std::map<std::string, FileMessagesCollection> MessagesCollection;

private:
    friend std::ostream& operator<<(std::ostream& os, const Vera::report& report);

public:
    bool omit_duplicates;

    MessagesCollection messages_;
};

} // namespace Vera

#endif /* VERA_REPORT_HPP */
