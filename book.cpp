#include <sstream>
#include <iomanip>

//include the headers of the classes whose functions we use
#include "book.h"
#include "product.h"
#include "util.h"

//declare the variables for the book class, but also use the product cosntructors since
//we are using inhertiance 
Book::Book(const std::string& name, double price, int qty, const std::string& isbn, 
const std::string& author) :
  Product("book", name, price, qty), isbn_(isbn), author_(author)
{

}
  //first function is parsing words to be able to find the book
  //thought porcess: find the keywords of the authors name, and the name of the book
  //and put them in a set of keywords along with the isbn (full number) 

  std::set<std::string> Book::keywords() const{
    //decalre the set of keywords
    std::set<std::string> keywords_book;
    //get keywords of the name of book into the set
    keywords_book = parseStringToWords(name_);
    
    //create a temp set to hold key words for author's name
    std::set<std::string> temp;
    temp = parseStringToWords(author_);

    //insert all keywords into the set
    keywords_book.insert(temp.begin(), temp.end());
    //don't forget to also add the isbn
    keywords_book.insert(isbn_);
    return keywords_book;

  }
  //write a display string that overwrites the virtual one in the product.h 
   std::string Book::displayString() const{
    std::ostringstream oss;
    //print out the name and then author, isbn, price, and quantity
    oss << name_ << "\n";
    oss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    oss << std::fixed << std::setprecision(2)
        << price_ << " " << qty_ << " left.";
    return oss.str();
  }
  void Book::dump(std::ostream& os) const{
    //print out the book and then the same info as above
    os<< "book" << "\n";
    os << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << "\n";
  }