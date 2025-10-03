#include <sstream>
#include <iomanip>

//include the headers of the classes whose functions we use
#include "movie.h"
#include "product.h"
#include "util.h"

//declare the variables for the movie class, but also use the product cosntructors since
//we are using inhertiance
Movie::Movie(const std::string& name, double price, int qty, const std::string& genre, 
const std::string& rating) :
  Product("movie", name, price, qty), genre_(genre), rating_(rating)
{

}
  //first function is parsing words to be able to find the book
  //thought porcess: find the keywords of the name
  //and put them in a set of keywords along with the genre
  std::set<std::string> Movie::keywords() const{
    //decalre the set of keywords
    std::set<std::string> keywords_movie;
    //get keywords of the name of movie into the set
    keywords_movie = parseStringToWords(name_);
    //don't forget to also add the genre
    keywords_movie.insert(genre_);
    return keywords_movie;

  }
  std::string Movie::displayString() const{
    //print out the name and genre and rating and price and quantity
    std::ostringstream oss;
    oss << name_ << "\n";
    oss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    oss << std::fixed << std::setprecision(2)
        << price_ << " " << qty_ << " left." << "\n";
    return oss.str();
  }
  void Movie::dump(std::ostream& os) const{
    os<< "movie" << "\n";
    os << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << "\n";
  }