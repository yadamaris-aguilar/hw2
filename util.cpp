#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  //store all the key words made from parsing (2 characters +) into a set we can later look at to find searches
  set<string> keyWords;

  //to make case insensitive we can convert to lowercase
  string lowerCase= convToLower(rawWords);

  //make a temp string that will hold the characters we parse 
  string tmp;
  //iterate through the entire word to parse
  for(size_t i=0; i<lowerCase.size(); i++){
    //if the character is a valid letter then add it to the temp string
    if(lowerCase[i] >= 'a' && lowerCase[i] <= 'z'){
      tmp += lowerCase[i];
    }
    //once we reach a stop in our parsing (either b/c of a punctuation or reach the end) 
    //then we check the size if >=2 and if so add it to our keyWords set
    else{
      if(tmp.size() >= 2){
        keyWords.insert(tmp);
      }
      //make tmp empty again so we can find the next keyWord! 
      tmp = "";
    }
  }

  //debugging: once you exist the loop b/c you reach the end of the word
  //your tmp may still have a keyWord inside so just check one more time just in case

  if(tmp.size() >=2){
    keyWords.insert(tmp);
  }
    return keyWords;
}




/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
