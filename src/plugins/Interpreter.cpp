//
// Copyright (C) 2006-2007 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include "Interpreter.h"
#include "Exclusions.h"
#include "Reports.h"
#include "Parameters.h"
#include "../structures/SourceFiles.h"
#include "../structures/SourceLines.h"
#include "../structures/Tokens.h"
#include "cpptcl-1.1.4/cpptcl.h"
#include <fstream>
#include <iterator>

namespace Vera
{
namespace Plugins
{
namespace // unnamed
{

// helper global pointer
// - for those functions that might modify the interpreter's state

Tcl::interpreter *pInter;

void report(const std::string & fileName, int lineNumber, const std::string & message)
{
    Reports::add(fileName, lineNumber, message);
}

std::string getParameter(const std::string & name, const std::string & defaultValue)
{
    return Parameters::get(name, defaultValue);
}

Tcl::object getSourceFileNames()
{
    Tcl::object obj;

    const Structures::SourceFiles::FileNameSet & files = Structures::SourceFiles::getAllFileNames();

    typedef Structures::SourceFiles::FileNameSet::const_iterator iterator;
    const iterator end = files.end();
    for (iterator it = files.begin(); it != end; ++it)
    {
        const Structures::SourceFiles::FileName & name = *it;

        if (Exclusions::isExcluded(name) == false)
        {
            obj.append(*pInter, Tcl::object(name));
        }
    }

    return obj;
}

int getLineCount(const std::string & sourceName)
{
    return Structures::SourceLines::getLineCount(sourceName);
}

std::string getLine(const std::string & sourceName, int lineNumber)
{
    return Structures::SourceLines::getLine(sourceName, lineNumber);
}

Tcl::object getAllLines(const std::string & sourceName)
{
    Tcl::object obj;

    const Structures::SourceLines::LineCollection & lines = Structures::SourceLines::getAllLines(sourceName);

    typedef Structures::SourceLines::LineCollection::const_iterator iterator;
    const iterator end = lines.end();
    for (iterator it = lines.begin(); it != end; ++it)
    {
        obj.append(*pInter, Tcl::object(*it));
    }

    return obj;
}

Tcl::object getTokens(const std::string & sourceName, int fromLine, int fromColumn,
    int toLine, int toColumn, const Tcl::object & filter)
{
    Structures::Tokens::FilterSequence filterSeq;

    size_t filterLength = filter.length(*pInter);
    for (size_t i = 0; i != filterLength; ++i)
    {
        filterSeq.push_back(filter.at(*pInter, i).get());
    }

    Structures::Tokens::TokenSequence tokenSeq = Structures::Tokens::getTokens(sourceName,
        fromLine, fromColumn, toLine, toColumn, filterSeq);

    Tcl::object ret;
    Structures::Tokens::TokenSequence::iterator it = tokenSeq.begin();
    Structures::Tokens::TokenSequence::iterator end = tokenSeq.end();
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

void registerCommands(Tcl::interpreter & inter)
{
    pInter = &inter;

    // commands related to source files and plain source code
    inter.def("report", report);
    inter.def("getParameter", getParameter);
    inter.def("getSourceFileNames", getSourceFileNames);
    inter.def("getLineCount", getLineCount);
    inter.def("getLine", getLine);
    inter.def("getAllLines", getAllLines);
    inter.def("getTokens", getTokens);
}

} // unnamed namespace


void Interpreter::execute(const DirectoryName & root,
    ScriptType type, const ScriptName & name)
{
    std::string fileName = root + "/scripts/";
    switch (type)
    {
    case rule:
        fileName += "rules/";
        break;
    case transformation:
        fileName += "transformations/";
        break;
    }

    fileName += name;
    fileName += ".tcl";

    std::ifstream scriptFile(fileName.c_str());
    if (scriptFile.is_open() == false)
    {
        std::ostringstream ss;
        ss << "cannot open script " << fileName;
        throw ScriptError(ss.str());
    }

    std::string scriptBody;
    scriptBody.assign(std::istreambuf_iterator<char>(scriptFile), std::istreambuf_iterator<char>());

    Tcl::interpreter inter;
    registerCommands(inter);
    inter.eval(scriptBody);
}

} // namespace Plugins
} // namespace Vera
