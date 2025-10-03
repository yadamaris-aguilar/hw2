#ifndef MOVIE_H
#define MOVIE_H


#include <string>
#include <set>
#include "product.h"

//use inhertiance for movie since movie "is a" product and can use the functions
class Movie: public Product{
  public: 
    Movie(const std::string& name, double price, int qty, 
    const std::string& genre, const std::string& rating);

    //copy the virtual functions of the product class to override them 
    //since movie "has a" realtionship with these functions. It has its own keywords
    //its own display and its own dump
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;


  private:
  //make the genre and rating private since they should not be changed 
    std::string genre_;
    std::string rating_;
};
#endif