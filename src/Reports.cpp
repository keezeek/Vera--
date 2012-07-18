//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Reports.h"
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>

void Vera::report::add(std::string name, int lineNumber, const std::string& msg)
{
    name = boost::filesystem::absolute(name).string();
    messages_[name].insert(std::make_pair(lineNumber, msg));
}

std::ostream& Vera::operator<<(std::ostream& os, const Vera::report& report)
{
    BOOST_FOREACH(const Vera::report::MessagesCollection::value_type& it, report.messages_)
    {
        const std::string& name = it.first;

        int lastLineNumber = 0;
        std::string lastMsg;

        BOOST_FOREACH(const Vera::report::FileMessagesCollection::value_type& fit, it.second)
        {
            int lineNumber = fit.first;
            const std::string& msg = fit.second;

            if (!report.omit_duplicates || lineNumber != lastLineNumber || msg != lastMsg)
            {
                //os << name << ':' << lineNumber << ": " << msg << '\n';
                os << name << '(' << lineNumber << ") : " << msg << '\n';

                lastLineNumber = lineNumber;
                lastMsg = msg;
            }
        }
    }

    return os;
}
