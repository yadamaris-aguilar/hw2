#ifndef CLOTHING_H
#define CLOTHING_H
//include the same as with the book class
#include <string>
#include <set>
#include "product.h"

class Clothing: public Product{
  public: 
  //initalize the size and brand for clothing
    Clothing(const std::string& name, double price, int qty, 
    const std::string& size, const std::string& brand);

    //same functions also done in the book.h
    std::set<std::string> keywords() const;
    std::string displayString() const;
    void dump(std::ostream& os) const;

    private:
    //specific variables for clothing include size and brand which are private
      std::string size_;
      std::string brand_;
};
#endif
