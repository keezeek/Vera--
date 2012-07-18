//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Interpreter.h"
#include "Reports.h"
#include "Parameters.h"
#include "SourceLines.h"
#include "Tokens.h"
#include "cpptcl-1.1.4/cpptcl.h"
#include "globals.hpp"

#include <iostream>
#include <fstream>
#include <iterator>
#include <boost/foreach.hpp>
#include <luabind/luabind.hpp>
#include <luabind/iterator_policy.hpp>

extern "C"
{
#include "lualib.h"
}

namespace Vera
{
namespace // unnamed
{

// helper global pointer
// - for those functions that might modify the interpreter's state

Tcl::interpreter *pInter;

void report_(const std::string& fileName, int lineNumber, const std::string& message)
{
    vera::report.add(fileName, lineNumber, message);
}

std::string getParameter(const std::string& name, const std::string& defaultValue)
{
    return Parameters::get(name, defaultValue);
}

const std::vector<std::string>& get_files()
{
    return vera::input_files;
}

const std::vector<std::string>& get_lines(const std::string& sourceName)
{
    return SourceLines::getAllLines(sourceName);
}

Tcl::object getSourceFileNames()
{
    Tcl::object obj;

    BOOST_FOREACH(std::string name, vera::input_files)
    {
        obj.append(*pInter, Tcl::object(name));
    }

    return obj;
}

int getLineCount(const std::string& sourceName)
{
    return SourceLines::getLineCount(sourceName);
}

std::string getLine(const std::string& sourceName, int lineNumber)
{
    return SourceLines::getLine(sourceName, lineNumber);
}

Tcl::object getAllLines(const std::string& sourceName)
{
    Tcl::object obj;

    BOOST_FOREACH(std::string line, SourceLines::getAllLines(sourceName))
    {
        obj.append(*pInter, Tcl::object(line));
    }

    return obj;
}

Tcl::object getTokens(const std::string& sourceName, int fromLine, int fromColumn,
    int toLine, int toColumn, const Tcl::object& filter)
{
    std::vector<std::string> filterSeq;

    size_t filterLength = filter.length(*pInter);
    for (size_t i = 0; i != filterLength; ++i)
    {
        filterSeq.push_back(filter.at(*pInter, i).get());
    }

    Tokens::TokenSequence tokenSeq = Tokens::getTokens(sourceName,
        fromLine, fromColumn, toLine, toColumn, filterSeq);

    Tcl::object ret;
    Tokens::TokenSequence::iterator it = tokenSeq.begin();
    Tokens::TokenSequence::iterator end = tokenSeq.end();
    for ( ; it != end; ++it)
    {
        Tcl::object singleToken;
        singleToken.append(*pInter, Tcl::object(it->value_));
        singleToken.append(*pInter, Tcl::object(it->line_));
        singleToken.append(*pInter, Tcl::object(it->column_));
        singleToken.append(*pInter, Tcl::object(it->name_));

        ret.append(*pInter, singleToken);
    }

    return ret;
}

void registerCommands(Tcl::interpreter& inter)
{
    pInter =&inter;

    // commands related to source files and plain source code
    inter.def("report", report_);
    inter.def("getParameter", getParameter);
    inter.def("getSourceFileNames", getSourceFileNames);
    inter.def("getLineCount", getLineCount);
    inter.def("getLine", getLine);
    inter.def("getAllLines", getAllLines);
    inter.def("getTokens", getTokens);
}

} // unnamed namespace


void Interpreter::execute(const std::string& name)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    luabind::open(L);

    luabind::module(L, "vera")
    [
        luabind::def("input_files", &get_files, luabind::return_stl_iterator),
        luabind::def("get_lines", &get_lines, luabind::return_stl_iterator),
        luabind::def("report", &report_),
        luabind::def("line_count", &SourceLines::getLineCount),
        luabind::def("get_line", &SourceLines::getLine)
    ];

	boost::filesystem::path fileName(vera::root_dir / "scripts" / (name + ".lua"));
    if (luaL_dofile(L, fileName.string().c_str()))
    {
        throw std::runtime_error(lua_tostring(L, lua_gettop(L)));
    }

    lua_close(L); // TODO: fix leak!
}

} // namespace Vera
