/*
Author: Vincent Navarro (vincent@vincentnavarro.com)

Date created: October 28,2017

Topics covered:
   - Object Oriented C++
      - Class creation
      - Inheritance
      - Default constructors
      - Destructors
      - LinkedLists

Program Description:
   - Instantiates object from Clothes class
   - User enters the temperature in degrees
      - Gets stored into a temperature variable
   - setTemp method called, with temperature as a passed in parameter
      - temperature stored into the class variable temp
   - Prints out the current temperature by calling getTemp
   - Calls shouldWear which grabs the temp and compares it to preset temperature ranges
      - When a range is hit, addClothes is called and passed a string parameter
         - It is then added into a new Node
         - The new Node is added to the current linked list (closet)
   - PrintsClothes is called, which prints out the entire linked list called closet
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Weather class
class Weather{

public:
   Weather();
   Weather(double);
   void setTemp(double);
   double getTemp() const;
private:
   double temp;
};


// Clothes class
class Clothes : public Weather{

struct Node{
   string item;
   Node *next;
};

public:
   Clothes();
   ~Clothes();
   void shouldWear();
   void addClothes(const string);
   void printClothes();
private:
   Node *closet;        // closet node
   Node *currCloset;    // current closet item
};

// =========================================================== //
// ===================== WEATHER METHODS ===================== //
// =========================================================== //

// default constructor
Weather::Weather(){
   temp = 0;
}

// default constructor w/ temp passed in
Weather::Weather(double newTemp){
   temp = 0;
   setTemp(newTemp);
}

// Sets the temperature variable to the passed in temperature
void Weather::setTemp(double newTemp){
   temp = newTemp;
}

// Gets temp and returns it as a double
double Weather::getTemp() const{
   return temp;
}

// =========================================================== //
// ===================== CLOTHES METHODS ===================== //
// =========================================================== //

// default constructor than also initializes closet
Clothes::Clothes(){
   closet = new Node;
   currCloset = new Node;

   closet = NULL;
   currCloset = closet;
}

// destructor for closet
Clothes::~Clothes(){
   Node *current;
   currCloset = closet;
   while (closet != NULL) {
      current = closet->next;
      delete closet;
      closet = current;
   }

}

// Based off the temperature, tells you what you should wear
   // Grabs temperature and compares it
   // If triggered, passes the clothing item as a string into the method addClothes
void Clothes::shouldWear(){

   // Grab temp from parent class
   int theTemp = int(getTemp());

   // If the temp is >= 150
   if(theTemp > 110)
      addClothes("nothing");

   // 110 to 90
   else if(theTemp <= 110 && theTemp > 90)
      addClothes("a tank top");

   // 89 to 79
   else if(theTemp <= 89 && theTemp > 79)
      addClothes("a T-Shirt");

   // 78 to 69
   else if(theTemp <= 78 && theTemp > 69)
      addClothes("a long sleeve");

   // Start the layers of multiple clothes
   // 68 and below
   if(theTemp <= 68){
      // -10 and below
      if(theTemp < -10)
         addClothes("a space heater");
      else{

         // -10 to 31
         if(theTemp >= -10 && theTemp < 32)
            addClothes("a super heavy jacket");

         // 32 to -9
         else if(theTemp >= 32 && theTemp < 45)
            addClothes("a heavy jacket");

         // 45 to 68
         else
            addClothes("a jacket");

         // If the temp is less than 45 wear mittens also
         if(theTemp < 45)
            addClothes("some mittens");

      }
   }
}

// Add clothes into the closet
// Technically this adds a string item into the linkedlist
void Clothes::addClothes(const string newClothes){

   Node *newItem = new Node;           // Initializes temporary node;
   newItem->item = newClothes;         // Sets item to passed in string
   newItem->next = NULL;               // sets the next to NULL

   // Base Case: Theres no clothes in the closet so the item passed is the first
   if(closet == NULL){
      closet = newItem;                // Closet gets the temp node
      currCloset = closet;             // The current closet spot is set to closet
   }
   else{
      currCloset->next = newItem;      // Else the new item is passed into the next spot
      currCloset = currCloset->next;   // and the current spot is changed
   }

}

// Prints the linkedlist closet
void Clothes::printClothes(){
   Node *holder;             // Temporary node of closet
   holder = closet;          // initializes holder as closet

   cout << "You should probably wear:" << endl;

   // Loops until it hits null
   while(closet != NULL){
      cout << "   - " << closet->item << endl;

      closet = closet->next;
   }
   cout << endl;

   closet = holder;          // Sets closet back to it's original position
}

// client code
int main(){

   Clothes clothes;     // Create clothes object
   double temp;         //temp variable in fahrenheit

   cout << string(60, '=') << endl;
   cout << "Please enter the weather in fahrenheit and press Enter when finished" << endl;
   cin >> temp;
   cout << string(60, '=') << endl;

   clothes.setTemp(temp);

   cout << endl << "In this " << clothes.getTemp() << " degree weather." << endl << endl;

   clothes.shouldWear();
   clothes.printClothes();

   return 0;
}
