///////////////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                               //
// ver 3.4                                                                   //
// Language:    C++, Visual Studio 2015                                      //
// Application: Lexical Scanner, CSE687 - Object Oriented Design, SP16       //
//              Alienware R15, Core i5, Windows 10                           //
// Author:      Saathvik Shashidhar Gowrapura, SUID: 450734672               //
//              sgowrapu@syr.edu, (315)-751-1059                             //
// Original author: Jim Fawcett, CST 4-187, Syracuse University              // 
//              jfawcett@twcny.rr.com, (315)-443-3948                        //
//////////////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a
* sequence of tokens that ends in {.  This will be extended to use the
* full set of terminators: {, }, ;, and '\n' if the line begins with #.
*
* This is a new version for students in CSE687 - OOD, Spring 2016 to use
* for Project #1.
*
*  Public Interface:
*  ---------------------------------
*  size_t length() - to obtain the length of the vector containg tokens
*
*  void push_back(const std::string& tok) - to push the string into the vector containing tokens
*
*  bool remove(const std::string& tok) - to remove token from the vector upon matching of the string passed as argument
*
* remove(size_t n) - function to remove the token at index n
*
*  toLower() - Convert all the upper case leeters in the semi expression to lower case
*
* trimFront() - Remove all leading newline characters in the semi expression
*
* clear() - Remove all the existing tokens in the semi expression
*
* bool get_for(std::string& tok) - to get semiexpression when for loop is encountered
*
* Maintenance History:
* --------------------
* ver 3.4 : 10 Feb 2016
* - Implemented the interface ITokCollection
* - added public :, protected :, private : as terminators
* - provided a rule to termination of collection of tokens on certian cases
* ver 3.3 : 08 Feb 2016
* - New comments and functions are added
* ver 3.2 : 02 Feb 2016
* - declared SemiExp copy structor and assignment operator = delete
* - added default argument for Toker pointer to nullptr so SemiExp
*   can be used like a container of tokens.
* - if pToker is nullptr then get() will throw logic_error exception
* ver 3.1 : 30 Jan 2016
* - changed namespace to Scanner
* - fixed bug in termination due to continually trying to read
*   past end of stream if last tokens didn't have a semiExp termination
*   character
* ver 3.0 : 29 Jan 2016
* - built in help session, Friday afternoon
*
* Build Process:
* --------------
* Required Files:
*   SemiExpression.h, SemiExpression.cpp, Tokenizer.h, Tokenizer.cpp,ITokCollection.h
*
* Build Command: devenv Project1.sln /rebuild debug
*
*/
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"

using namespace Scanner;

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

 bool SemiExp::get(bool clear){															//to get tokens and make turn them into semi expressions 
  if (_pToker == nullptr)
    throw(std::logic_error("no Toker reference"));
  _tokens.clear();
  while (true)  {
    std::string token = _pToker->getTok();												//to get token from getTok() method
    if (token == "")
      break;
	_tokens.push_back(token);
	if (token == "#")	{																
		while (token.size() > 0)		{
			if (isspace(token.at(0)))
				break;
			token = _pToker->getTok();
			_tokens.push_back(token);		}
		return true;
	}
	if (token == "{" || token == ";" || token == "}")									
		return true;
	if (token == "public" || token == "private" || token == "protected")				
	{   token = _pToker->getTok();
		_tokens.push_back(token);
		return true;	}
	if (token == "for")
		get_for(token);
  }
  return false;
 }

 bool SemiExp::get_for(std::string& tok)														//to get semi expressions when token for is encountered
 {
	 std::string token1 = tok;
	 int count = 0;
	 while (token1.size() > 0) {
		 if (token1 == "(")
			 count++;
		 if (token1 == ")")
			 count--;
		 if ((token1 == ")" && count == 0))
		 {
			 token1 = _pToker->getTok();
			 //token1 = _pToker->getTok();
			 _tokens.push_back(token1);
			 if (token1 == "{")
				 return true;
			 return true;
		 }
		 token1 = _pToker->getTok();
		 _tokens.push_back(token1);
	 }
	 return true;
 }
 size_t SemiExp::find(const std::string& tok)											//to find the position of the string token in vector. Returns the position when the string passed as argument is found in the vector 
 {
	 size_t findPostion;
	 for (unsigned int i = 0; i < length(); i++)
		 if (_tokens.at(i) == tok)
		 {
			 findPostion = i;
			 break;
		 }
			 return findPostion;
 }
 void SemiExp::push_back(const std::string& tok)										//push the string passed as argument into the vector
 {
	 _tokens.push_back(tok);
 }
 bool SemiExp::remove(size_t i)															//remove the token from the vector at position which is passed as argument
 {
	 if (i<0 || i>length()) return false;
	 std::vector<Token>::iterator it = _tokens.begin() + i;
	 _tokens.erase(it);
	 return true;
 }
 bool SemiExp::remove(const std::string& tok)										   //remove the string token passed as argument from the vector
 {
	 int pos;
	 pos = find(tok);
	 _tokens.erase(_tokens.begin() + pos);
	 return true;
 }
 void SemiExp::toLower()															  //convert the token in the vector into lower case
 {
	 
	 for (unsigned int i = 0;i < length();i++) {
		 std::string& token1 = _tokens[i];
		for (unsigned int j = 0; j < token1.size(); j++)
		    token1[j] = tolower(token1.at(j));
	 }
 }
 void SemiExp::trimFront()															//to trim the leading whitespaces
 {
	 while (length() > 1)
	 {
		 if (_tokens[0] == "\n") this->remove(0);
		 else break;
	 }
 }
 void SemiExp::clear()																	//to clear the vector containing tokens
 {
	 _tokens.clear();
 }
std::string& SemiExp::operator[](int n)															//to get the tokens at position n from the vector
{
  if (n < 0 || n >= (int)_tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}

size_t SemiExp::length()																		//returns the length of the vector containing the tokens
{
  return _tokens.size();
}

std::string SemiExp::show(bool showNewLines)													//to display the tokens in the vector and to display new lines based on a boolean value passed as argument
{
	std::cout << "\n  ";
	std::string str;
	for (auto token : _tokens)
	{
		str.append(token);
		if (token != "\n")
			std::cout << token << " ";
		else {
			if(showNewLines == true)  std::cout << "new line ";
		}

	}
	std::cout << "\n";
	return str;
}

int submain()
{
  Toker toker;
  std::string fileSpec = "../Tokenizer/semitest.txt";
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);

  SemiExp semi(&toker);
  while(semi.get())
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
  }
  /*
     May have collected tokens, but reached end of stream
     before finding SemiExp terminator.
   */
  if (semi.length() > 0)
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
    std::cout << "\n\n";
  }
  return 0;
}