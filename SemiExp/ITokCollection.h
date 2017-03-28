#ifndef ITOKCOLLECTION_H
#define ITOKCOLLECTION_H
///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                               //
// ver 1.1                                                                   //
// Language:    C++, Visual Studio 2015                                      //
// Application: Lexical Scanner, CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*
Module Purpose:
===============
ITokCollection is an interface that supports substitution of different
types of scanners for parsing.  In this solution, we illustrate that
by binding two different types of collections, SemiExp and XmlParts,
to this interface.  This is illustrated in the test stubs for the
SemiExpression and XmlElementParts modules.

Maintenance History:
====================
ver 1.1 : 02 Jun 11
- added merge, remove overload, and default param in get
ver 1.0 : 17 Jan 09
- first release
*/
#include<string>
struct ITokCollection
{
	virtual bool get(bool clear = true) = 0;
	virtual size_t length() = 0;
	virtual std::string& operator[](int n) = 0;
	virtual size_t find(const std::string& tok) = 0;
	virtual void push_back(const std::string& tok) = 0;
	//virtual bool merge(const std::string& firstTok, const std::string& secondTok) = 0;
	virtual bool remove(const std::string& tok) = 0;
	virtual bool remove(size_t i) = 0;
	virtual void toLower() = 0;
	virtual void trimFront() = 0;
	virtual void clear() = 0;
	virtual std::string show(bool showNewLines = false) = 0;
	virtual ~ITokCollection() {};
};

#endif