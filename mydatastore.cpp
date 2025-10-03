#include "mydatastore.h" 
#include "util.h"
#include <iostream>
#include <algorithm>

using namespace std;

  MyDataStore::MyDataStore(){}
    //have the destrutor to make sure no memory leaks
    MyDataStore:: ~MyDataStore(){
      for(Product *p : products_){
        delete p;
      }
      for(User* u : users_){
        delete u;
      }
    }
    
    void MyDataStore::addProduct(Product* p){
      //add the product to the back 
      products_.push_back(p);
      //get the keywords and add them to the set of keys
      std::set<std::string> keys = p->keywords();
      //iterate throught the keys and use convToLower
      for(std::set<std::string>::iterator it = keys.begin(); it !=keys.end(); ++it){
        std::string key = convToLower(*it);
        //pushback to the actual map of key words
        keyMap_[key].push_back(p);
      }
      
    }
    //add user function that will store the user pointer to a user vector
    //then also access the user map and add user there so we can look it up quicker later
    //also creates an empty cart for that specific user
    void MyDataStore::addUser(User* u){
      users_.push_back(u);
      std::string uName = convToLower(u->getName());
      userMap_[uName] =u;
      carts_[uName] = std::vector<Product*>();
    }
    //addUser adds a user to the vector of all users and then gets their name and adds it to the map that point to that user's object
    
    //fucntion to add to the users cart that passes the user's name and the product that they want in their cart
    void MyDataStore::addToCart(const std::string& userName, Product* p){
      //get the name
      std::string n = convToLower(userName);
      //try to find the user in the map of database of users
      std::map<std::string, User*>::iterator it = userMap_.find(n);
      //if they exist then add the prodcut into their cart map
      if(it != userMap_.end()){
        carts_[n].push_back(p);
      }
    }

    //this is the function that returns true or false whether a usrname is in the store 
    bool MyDataStore::validUser(const std::string& uname) const{
      return userMap_.find(convToLower(uname)) != userMap_.end();
    }

    void MyDataStore::viewCart(const std::string& username){
      //get the user name with convToLower so we can find it in the database
      std::string nme = convToLower(username);
      std::map<std::string, std::vector<Product*>>::iterator it = carts_.find(nme);
      //if you get to the end and there is no user found, then the user is not there and invalid
      if(it == carts_.end()){
        std::cout << "Invalid username" << std::endl;
        return;
      }
      int index = 1;
      //print out the content 
      for(Product* p : it-> second){
        std::cout << "Item " << index << std::endl;
        //debug 
        //std::cout << "working" << std::endl;
        std::cout<< p->displayString() << std:: endl;
        std::cout<<std::endl;
        index++;
      }
    }

    void MyDataStore::buyCart(const std::string& username){
      //convert the username to make it easier to look up
      std::string nme = convToLower(username);
      std::map<std::string, User*>::iterator it = userMap_.find(nme);
      //again check if the user is in the database (exists) and then if not the user is invalid
      if(it == userMap_.end()){
        std::cout << "Invalid username" << std::endl;
        return;
      }

      User* current = it -> second;
      std::vector<Product*>& cart = carts_[nme];
      //make a vector that has pointer of all products that arent purchased
      //this will help if there is not enough balance and we can still keep unpurchased items for later
      std::vector<Product*> unpurchased_items;

      for(Product* p : cart){
        //get amount of stuff in cart
        int amount = p->getQty();
        //get the balance the user has
        double balance = current->getBalance();
        //get the cost of the products
        double cost = p->getPrice();
        if(amount > 0 && balance >= cost){
          //if there is enough money then purchase and withdraw the money
          current->deductAmount(cost);
          p->subtractQty(1);

        }
        else{
          //if not enough money then add to the unpurchased
          unpurchased_items.push_back(p);
        }
      }
      cart = unpurchased_items;

    }

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
      //std::vector<Product*> result;

      //check if empty, or else nothing to do 
      if(terms.empty()==true){
        return std::vector<Product*>();
      }
      //convert the search item to lowercase to look up with case-insensitive 
      std::string first = convToLower(terms[0]);
      std::set<Product*> results(keyMap_[first].begin(), keyMap_[first].end());
      
      //loop over the search items and then convert each one to lowercase
      for(size_t i =1; i<terms.size(); i++){
        std::string key = convToLower(terms[i]);
        //look up using the keywrods and then put them in the set
        std::set<Product*> current(keyMap_[key].begin(), keyMap_[key].end());

        //use the requirement of the 0 or 1 type
        if(type == 0){
          //if 0 then use the intersection
          results = setIntersection(results, current);
        }
        else{
          //if 1 then use union
          results = setUnion(results, current);
        }
      }

    return std::vector<Product*>(results.begin(), results.end());
    }

    /**
     * Reproduce the database file from the current Products and User values
     */
    void MyDataStore::dump(std::ostream& ofile){
      //prints the products
      ofile<< "<products>" << std::endl;
      //first go through all the products
      for(Product* p : products_){
        p->dump(ofile);
      }
      ofile << "</products>" << std::endl;
      //go through all the users
      ofile<< "<users>" << std::endl;
      for(User* u : users_){
        u->dump(ofile);
      }
      ofile << "</users>" << std::endl;
    }
    