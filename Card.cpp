#include <cassert>
#include <iostream>
#include <array>
#include "Card.hpp"

using namespace std;

/////////////// Rank operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const RANK_NAMES[] = {
  "Two",   // TWO
  "Three", // THREE
  "Four",  // FOUR
  "Five",  // FIVE
  "Six",   // SIX
  "Seven", // SEVEN
  "Eight", // EIGHT
  "Nine",  // NINE
  "Ten",   // TEN
  "Jack",  // JACK
  "Queen", // QUEEN
  "King",  // KING
  "Ace"    // ACE
};

//REQUIRES str represents a valid rank ("Two", "Three", ..., "Ace")
//EFFECTS returns the Rank correspoinding to str, for example "Two" -> TWO
Rank string_to_rank(const std::string &str) {
  for(int r = TWO; r <= ACE; ++r) {
    if (str == RANK_NAMES[r]) {
      return static_cast<Rank>(r);
    }
  }
  assert(false); // Input string didn't match any rank
  return {};
}

//EFFECTS Prints Rank to stream, for example "Two"
std::ostream & operator<<(std::ostream &os, Rank rank) {
  os << RANK_NAMES[rank];
  return os;
}

//REQUIRES If any input is read, it must be a valid rank
//EFFECTS Reads a Rank from a stream, for example "Two" -> TWO
std::istream & operator>>(std::istream &is, Rank &rank) {
  string str;
  if(is >> str) {
    rank = string_to_rank(str);
  }
  return is;
}



/////////////// Suit operator implementations - DO NOT CHANGE ///////////////

constexpr const char *const SUIT_NAMES[] = {
  "Spades",   // SPADES
  "Hearts",   // HEARTS
  "Clubs",    // CLUBS
  "Diamonds", // DIAMONDS
};

//REQUIRES str represents a valid suit ("Spades", "Hearts", "Clubs", or "Diamonds")
//EFFECTS returns the Suit correspoinding to str, for example "Clubs" -> CLUBS
Suit string_to_suit(const std::string &str) {
  for(int s = SPADES; s <= DIAMONDS; ++s) {
    if (str == SUIT_NAMES[s]) {
      return static_cast<Suit>(s);
    }
  }
  assert(false); // Input string didn't match any suit
  return {};
}

//EFFECTS Prints Suit to stream, for example "Spades"
std::ostream & operator<<(std::ostream &os, Suit suit) {
  os << SUIT_NAMES[suit];
  return os;
}

//REQUIRES If any input is read, it must be a valid suit
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is, Suit &suit) {
  string str;
  if (is >> str) {
    suit = string_to_suit(str);
  }
  return is;
}


/////////////// Write your implementation for Card below ///////////////


// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec before implementing
// the following operator overload functions:
//   operator<<
//   operator>>
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=


Card::Card() {
    rank = TWO;
    suit = SPADES;
}

Card::Card(Rank rank_in, Suit suit_in) {
    rank = rank_in;
    suit = suit_in;
}

Rank Card::get_rank() const {
    return rank;
}

Suit Card::get_suit() const {
    return suit;
}

Suit Card::get_suit(Suit trump) const {
    if(is_left_bower(trump) == true) {
        return trump;
    }
    else {
        return suit;
    }
}

bool Card::is_face_or_ace() const {
    if(rank == JACK || rank == QUEEN || rank == KING || rank == ACE) {
        return true;
    }
    else {
        return false;
    }
}

bool Card::is_right_bower(Suit trump) const {
    return (rank == JACK && suit == trump);
}
  

bool Card::is_left_bower(Suit trump) const {
    return (rank == JACK && suit == Suit_next(trump));
}
 
bool Card::is_trump(Suit trump) const {
    return (get_suit() == trump || is_left_bower(trump));
}

std::ostream & operator<<(std::ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit() ;
  return os;
}



//EFFECTS Reads a Card from a stream in the format "Two of Spades"
//NOTE The Card class declares this operator>> "friend" function,
//     which means it is allowed to access card.rank and card.suit.
std::istream & operator>>(std::istream &is, Card &card){
  std::string of;
  is >> card.rank >> of >> card.suit;
  return is;
}


//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() < rhs.get_rank()){
    return true;
  }
  else if(lhs.get_rank() == rhs.get_rank()){
      if (rhs.get_suit() > lhs.get_suit()){
        return true;
      }
      else {
        return false;
      }
  }
  else {
    return false;
  }
  
}
//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() <= rhs.get_rank()){
    return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() > rhs.get_rank()){
    return true;
  }
  else if(lhs.get_rank() == rhs.get_rank()){
      if (rhs.get_suit() < lhs.get_suit()){
        return true;
      }
      else {
        return false;
      }
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() >= rhs.get_rank()){
    return true;
  }
  else {
    return false;
  }

}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()){
    return true;
  }
  else {
    return false;
  }
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
  if (lhs.get_rank() == rhs.get_rank() && lhs.get_suit() == rhs.get_suit()){
    return false;
  }
  else {
    return true;
  }
}

//EFFECTS returns the next suit, which is the suit of the same color
Suit Suit_next(Suit suit){
if (suit == SPADES){
  return CLUBS;
}
if (suit == CLUBS){
  return SPADES;
}
if (suit == HEARTS){
  return DIAMONDS;
}
if (suit == DIAMONDS){
  return HEARTS;
}

cout << "none of the suits worked" << endl;
// assert (true);
return CLUBS;
}





//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, Suit trump) {

    if (b.is_right_bower(trump)) {
    return true;
    } else if (a.is_right_bower(trump)) {
        return false;
    }
    else if(b.is_left_bower(trump) && !(a.is_right_bower(trump))) {
        return true;
    }
    else if ((b.is_trump(trump)) && !(a.is_trump(trump))) {
        return true;
    } else if (b.is_trump(trump) && a.is_trump(trump)) {
        if (a.is_left_bower(trump)) {
            return false;
        } else {
            return a < b;
        }
    }
    else if (a.is_trump(trump) && !(b.is_trump(trump))){
      return false;
    }

    return a < b;
}
    
    
    
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card, Suit trump) {
    
    //a not in led suit and b in led suit
    if (a.get_suit(trump) != led_card.get_suit(trump) && 
    b.get_suit(trump) == led_card.get_suit(trump)) {
        if (a.is_trump(trump)) {
            return false;
        } else {
            
            return true;
        }
        // a in led suit and b not in led suit
    } else if (a.get_suit(trump) == led_card.get_suit(trump) 
    && b.get_suit(trump) != led_card.get_suit(trump)) {
        if (b.is_trump(trump)) {
            return true;
        } else {
            return false;
        }
    } else {
        return Card_less(a,b,trump);
    }
    
}