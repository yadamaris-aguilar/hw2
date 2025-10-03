#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"

#include <map>
#include <set>
#include <vector>
#include <string>

class MyDataStore: public DataStore{
  public: 
  //constructor and the destructor
    MyDataStore();
    ~MyDataStore();

//take the functions from the datastore.h but since its virtual we have our own functions in child class that will overwrite them
 /**
     * Adds a product to the data store
     */
    void addProduct(Product* p);

   //check if the user is valid, used in the add in amazon but amazon cant access the private variables
   //so make function that can access it for it 
    bool validUser(const std::string& uname) const;
    /**
     * Adds a user to the data store
     */
    void addUser(User* u);

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type);

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile);

    //fucntion to add to the users cart that passes the user's name and the product that they want in their cart
    void addToCart(const std::string& userName, Product* p);
    //function to view the cart and only passes the user's name so we can get their cart
    void viewCart(const std::string& username);
    //function to purchase the cart, and again passes the user's name
    void buyCart(const std::string& username);

    private:
      //a vector that stores pointers to all the products in the database
      std::vector<Product*> products_;
      //a vector that stores all the users  in the database
      std::vector<User*>users_;
      //a map that maps the users and their carts 
      std::map<std::string, std::vector<Product*>> carts_;
      //a map that maps the users 
      std::map<std::string, User*> userMap_;
      //a map that maps that keywrods to the products
      std::map<std::string, std::vector<Product*>>keyMap_;


};
#endif