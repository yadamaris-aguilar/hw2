#include <sstream>
#include <iomanip>

//include the headers of the classes whose functions we use
#include "clothing.h"
#include "product.h"
#include "util.h"

//declare the variables for the clothing class, but also use the product cosntructors since
//we are using inhertiance 
Clothing::Clothing(const std::string& name, double price, int qty, 
const std::string& size, const std::string& brand):
  Product("Clothing", name, price, qty), size_(size), brand_(brand)
  {

  }

  //get the keywords for the clothing 
  std::set<std::string> Clothing::keywords() const{

    //first create a set of the keywords for clothing specifically and then maybe put them in a map?
    std::set<std::string> keywords_clothing;
    //add the keywords from the brand 
    keywords_clothing = parseStringToWords(brand_);
    //create a temp set that has keywords for the name 
    std::set<std::string> temp;
    temp = parseStringToWords(name_);

    //add the keywords from the name to the set with the keywords from the brand
    //basically have one set for all keywords
    keywords_clothing.insert(temp.begin(), temp.end());
    return keywords_clothing;
  }

  //write a display function that overwrites the virtual one given
  std::string Clothing::displayString() const{
    std::ostringstream oss;
    //print out the name, brand, price, and quantity
    oss<< name_ << "\n";
    oss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    oss << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";

    return oss.str();
  }
    
    void Clothing::dump(std::ostream& os) const{
      //dump and print the samer thing
      os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << "\n";
  }
