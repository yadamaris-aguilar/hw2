#ifndef BOOK_H
#define BOOK_H


//copy same #includes from the product class
#include <string>
#include <set>
#include "product.h"

//use inhertiance for book since book "is a" product and can use the fucntions
class Book: public Product{
  public: 
    Book(const std::string& name, double price, int qty, 
    const std::string& isbn, const std::string& author);

    //copy the virtual functions of the product class to override them 
    //since book "has a" realtionship with these functions. It has its own keywords
    //its own display and its own dump
    std::set<std::string> keywords() const;
    //this is overwriting the one given to us in the product.h class
    std::string displayString() const;
    void dump(std::ostream& os) const;


  private:
  //make the isbn and author private since they should not be changed 
    std::string isbn_;
    std::string author_;
};
#endif