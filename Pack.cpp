#include "Pack.hpp"
#include <array>
#include <string>

using namespace std;

  // EFFECTS: Initializes the Pack to be in the following standard order:
  //          the cards of the lowest suit arranged from lowest rank to
  //          highest rank, followed by the cards of the next lowest suit
  //          in order from lowest to highest rank, and so on.
  // NOTE: The standard order is the same as that in pack.in.
  // NOTE: Do NOT use pack.in in your implementation of this function
Pack::Pack() {
    next = 0;
    int l = 0;
    //outer loop to go through suits
    for (int i = 0; i < 4; i++) {
        for (int j = 7; j < 13; j++) {
            cards[l] = Card(static_cast<Rank>(j),static_cast<Suit>(i));
            l++;
        }
    }
}

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    next = 0;
    string r;
    string junk;
    string s;
    
    int l = 0;
    while (pack_input >> r >> junk >> s) {
        cards[l] = Card(string_to_rank(r), string_to_suit(s));
        l++;
    }
}

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    Card temp = cards[next];
    next++;
    return temp;
    
}

  // EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void Pack::shuffle(){
    Card temp_pack [PACK_SIZE/2];
    Card temp_pack2 [PACK_SIZE/2];
    int l = 0;



    int index_by_one = 0;
    int i = 0;
    for (int z = 0; z < 7; z++){
      //cout << "shuffling " << z << " time" << endl;

      while (l < (PACK_SIZE/2)){
        temp_pack[l] = cards[l];
        l++;
      }

      int newCounter = 0;

      while (l < PACK_SIZE){
        temp_pack2[newCounter] = cards[l];
        l++;
        newCounter++;
      }  

      l = 0;

        while (i < PACK_SIZE){
          cards[i] = temp_pack2[index_by_one];
          i++;
          cards[i] = temp_pack[index_by_one];
          i++;
          index_by_one++;
        }
        i = 0;
        index_by_one = 0;
    }
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
    if (next >= PACK_SIZE){
      return true;
    }
    return false;
  }


