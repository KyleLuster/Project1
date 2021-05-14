
//Kyle Luster
//This is my work; with help from Prof Sarlo and the ACE center.
//1-18-2021

#include <iostream>

using namespace std;

class MyString {
  private:
    char* myArray;
  int curr_length = 0;
  int capacity = 10;

  void ensureCapacity() {
    if (curr_length < capacity) return;
    // this is O(n) as it must check one int against another
    capacity *= 2;
    char * tempArray = new char[capacity];
    // as more arrays are created, the algorithm grows logrithmically
    // this is visualized as O(logn)
    for (int i = 0; i < curr_length; i++) {
      tempArray[i] = myArray[i];
    }
    //this references tempArray as the new myArray
    myArray = tempArray;
  }

  public:
    MyString() {
      myArray = new char[capacity];
    }

  MyString(string words) {
    myArray = new char[capacity];
    curr_length = 0; 
    //This alg is O(n) as it loops through each char
    for (int i = 0; i < words.length(); i++) { 
      // ensureCapacity here
      ensureCapacity();
      myArray[i] = words[i];
      curr_length++;
    }
  }

  MyString(MyString & copy) {
    capacity = copy.capacity;
    curr_length = copy.curr_length;
    myArray = new char[capacity];
    //This alg is O(n) as it loops through each index
    for (int i = 0; i < curr_length; i++) { 
      myArray[i] = copy.myArray[i]; 
    }
  }

  char get(int i) {
    return myArray[i];
  }

  int length() {
    return curr_length;
  }

  friend ostream & operator << (ostream &out, const MyString &s) {
    for (int i = 0; i < s.curr_length; i++) {
      out << s.myArray[i];
    }
    return out;
  }

//point of interest
  MyString operator + (MyString & s) {
    ensureCapacity();
    MyString str;
    str.curr_length = s.length() + curr_length;
    str.capacity = s.length() + curr_length;
    str.myArray = new char[str.capacity];
    //setting the size of temp[] to be big enough for the current and the future addition
    char temp[s.length() + curr_length];
    //This alg is O(n) as it loops through each index
    for (int i = 0; i < curr_length; i++) {
      str.myArray[i] = get(i); 
    }
    //This alg is O(n)
    for (int i = 0; i < s.length(); i++) { 
      str.myArray[curr_length + i] = s.get(i);
    }
    return str;
  }

  bool operator == (MyString & s) {
    if (curr_length != s.curr_length) return false;
    //here we are getting the value at position i from s
    //This alg is also O(n) 
    for (int i = 0; i < curr_length; i++)
      if (s.get(i) != myArray[i])
        return false;
    return true;
  }

  int indexOf(MyString search) {
    int j = 0;
    for (int i = 0; i < curr_length; i++) {
      if (myArray[i] == search.get(j)) {
        j++;
    //this uses the valuie of j to indicate the position a match was found
        if (j == search.length()) return i - search.length() + 1;
      } else {
        j = 0;
      }
    }
    return -1;
  } 

//this works similarlly to indexOf()
  int lastIndexOf(MyString search) {
    int j = search.length() - 1;
    for (int i = curr_length - 1; i >= 0 ; i--) {
      if (myArray[i] == search.get(j)) {
        j--;
    //we can simply retun i in this search because we are counting back to front
    //as this is the case, we will not be tripped up by the array starting at zero
        if (j == -1) return i;
      } else {
        j = search.length() - 1;
      }
    }
    return -1;
  }

  MyString substring(int a) {
    return substring(a, curr_length);
    
  }

  MyString substring(int a, int b) {
    //the index cannot be out of bounds
    //this || operator ensures it is kept in bounds
     if (a < 0 || a >= curr_length || a > b || b > curr_length) return MyString();
    MyString str;
    //this for loop would have an O(n)^2 since ensure capacity has a loop inside it
    for (int i = a; i < b; i++) {
      str.ensureCapacity();
      str.myArray[str.curr_length] = myArray[i];
      str.curr_length++;
    }
    return str;
  }

  MyString toUpper() {
    MyString str(*this);
    for (int i = 0; i < curr_length; i++) {
      char c = str.get(i);
      //checking for ascii values that denote lowercase
      if (c >= 97 && c <= 122) {
        str.myArray[i] = c - 32;
      } else {
        str.myArray[i] = c;
      }
    }
    return str;
  }

  MyString toLower() {
    MyString str(*this);
    for (int i = 0; i < curr_length; i++) {
      char c = str.get(i);
      //checking for ascii values that denote uppercase
      if (c >= 65 && c <= 90) {
        str.myArray[i] = c + 32;
      } else {
        str.myArray[i] = c;
      }
    }
    return str;
  }

  int operator < (MyString & s) { 
    //this will assign the min length to either curr_length or s.length
    int minLen = curr_length < s.length() ? curr_length : s.length();
    for (int i = 0; i < minLen; i++) {
      if (myArray[i] != s.myArray[i]) {
        return myArray[i] < s.myArray[i] ? 1 : -1;
      }
    }

    if (curr_length == s.length()) return 0;
    return curr_length < s.length() ? 1 : -1;
  }

  int operator > (MyString & s) { 
   //this will assign the max length to either curr_length or s.length
   int maxLen = curr_length > s.length() ? curr_length : s.length();
    for (int i = 0; i < maxLen; i++) {
      if (myArray[i] != s.myArray[i]) {
        return myArray[i] > s.myArray[i] ? 1 : -1;
      }
    }

    if (curr_length == s.length()) return 0;
    return curr_length > s.length() ? 1 : -1;
  }

};



int main() {
  cout << "--This is the word I put in--" << endl;
  MyString words("Hello");
  cout << words << endl;
  cout << "--This prints out the length of the word I put in--" << endl;
  cout << words.length() << endl;

  MyString hi("Hi");
  MyString dude(" dude");
  cout << "--Testing the concatinating method--" << endl;
  cout << hi + dude << endl;
  cout << "--'Hi' has been appended to ' dude'--" << endl;

  cout << endl;

  cout << "--String for testing naive method--" << endl;
  MyString kyle("Kyle Luster");
  cout << kyle << endl;
  cout << "--What we are looking for --" << endl;
  MyString search("ste");
  cout << "ste" << endl;
   cout << "--The first instance of this moving from to back begins at index--" << endl;
  cout << kyle.indexOf(search) << endl; 
  cout << "--The first instance of this moving from back to front begins at index--" << endl;
  cout << kyle.lastIndexOf(search) << endl; 
  cout << "--These are the chars following index 0--" << endl;
  cout << kyle.substring(0) << endl;
  cout << "--The method does not work if the index is out of bounds; as seen below--" << endl;
  cout << kyle.substring(-2) << endl;
  cout << "--These are the chars from start to end --" << endl;
  cout << kyle.substring(0, 11) << endl;
  
  MyString alpha("Alpha");
  MyString beta("Beta");
  MyString bet("Bet");
  MyString charlie("Charlie");

  cout<< "--This evaluates the alphabetic order of different strings--" << endl;
  cout<< "--If the total value is greater, then 1 is returned--" << endl;
  cout<< "--If the total value is less than, then -1 is returned--" << endl;
  cout<< "alpha > beta" << endl;
  cout << (alpha > beta) << endl;
  cout<< "alpha < beta" << endl;
  cout << (alpha < beta) << endl;
  cout<< "beta > bet" << endl;
  cout << (beta > bet) << endl;

  cout<< "The inital string is wHat . iS ? goInG ON!" << endl;
  cout<< "Here we are tesing toUpper" << endl;
  MyString spongebob("wHat . iS ? goInG ON!");
  cout << spongebob.toUpper() << endl;
  cout<< "Here we are tesing toLower" << endl;
  cout << spongebob.toLower() << endl;


}
