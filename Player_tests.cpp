#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    Player * steve = Player_factory("Steve", "Simple");
    ASSERT_EQUAL("Steve", steve->get_name());

    Player * nick = Player_factory("Nick", "Human");
    ASSERT_EQUAL("Nick", nick->get_name());

    delete steve;
    delete nick;
    delete alice;
    
}


TEST(test_make_trump_invalid_card) { 
  //bobjazzy tries to call trump with a card not in bobjazzy's hand
  Player * bobjazzy = Player_factory("Bobjazzy", "Simple");
  bobjazzy->add_card(Card(JACK, CLUBS));
  bobjazzy->add_card(Card(TEN, CLUBS));
  bobjazzy->add_card(Card(QUEEN, DIAMONDS));
  bobjazzy->add_card(Card(KING, SPADES));
  bobjazzy->add_card(Card(ACE, HEARTS));

  Card upcard(QUEEN, CLUBS);
  Suit trump;
  bool orderup = bobjazzy->make_trump(
    upcard,
    false,
    1,
    trump
  );
  ASSERT_FALSE(orderup);

  delete bobjazzy;

}



TEST(test_make_trump) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob makes trump
  Card nine_spades(NINE, SPADES);
  Suit trump;
  bool orderup = bob->make_trump(
    nine_spades,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES);

  delete bob;
}
TEST(test_make_trump_second_round) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(ACE, HEARTS));
    bob->add_card(Card(ACE, DIAMONDS));

    // Alice makes trump
    Card jack_diamonds(JACK, DIAMONDS);
    Suit trump;
    bool orderup = bob->make_trump(
    jack_diamonds,  // Upcard
    false,          // Bob is not the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
  );

    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, HEARTS);

    delete bob;
}


TEST(test_make_trump_third_round) {
    // Alice's hand
    Player * alice = Player_factory("Alice", "Simple");
    alice->add_card(Card(JACK, CLUBS));
    alice->add_card(Card(TEN, CLUBS));
    alice->add_card(Card(QUEEN, DIAMONDS));
    alice->add_card(Card(KING, SPADES));
    alice->add_card(Card(ACE, HEARTS));

    
    // Alice cannot order up in the first round
    Card queen_clubs(QUEEN, CLUBS);
    Suit trump;
    bool orderup = alice->make_trump(
    queen_clubs,    // Upcard
    false,          // Alice is not the dealer
    1,              // first round
    trump           // Suit ordered up (if any)
 );
    //ASSERT_FALSE(orderup);

    // Alice can order up in the second round
    orderup = alice->make_trump(
    queen_clubs,    // Upcard
    false,          // Alice is not the dealer
    2,              // Second round
    trump           // Suit ordered up (if any)
);
    
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);
    
    delete alice;
}

TEST(test_simple_player_lead_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, HEARTS) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(HEARTS);

  // Verify the card Bob selected to lead
  Card ace_spades(ACE, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_simple_player_lead_card_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(NINE, DIAMONDS));
  bob->add_card(Card(TEN, DIAMONDS));



  // Bob leads
  Card card_led = bob->lead_card(DIAMONDS);

  // Verify the card Bob selected to lead
  Card ace_spades(JACK, SPADES);
  ASSERT_EQUAL(card_led, ace_spades); //check led card

  delete bob;
}

TEST(test_lead_card_small_hand){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(ACE, DIAMONDS));

  Card card_led = bob->lead_card(DIAMONDS);

  Card jack_spades(JACK, SPADES);
  ASSERT_EQUAL(card_led, jack_spades)

  delete bob;
}

TEST(test_play_card_small_hand_2){
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(JACK, SPADES));
  bob->add_card(Card(NINE, HEARTS));

  Card nine_hearts (NINE, HEARTS);
  Card jack_hearts (JACK, HEARTS);
  Card jack_spades(JACK, SPADES);

  Card card_played = bob->lead_card(HEARTS);

  ASSERT_EQUAL(card_played, jack_spades)

  Card card_played_2 = bob->play_card(jack_hearts, HEARTS);
  ASSERT_EQUAL(card_played_2, nine_hearts);

  
  delete bob;
}

// Bob has no cards of the leading suit
TEST(test_player_lead_card_no_suit) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, CLUBS));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob adds a card to his hand and discards one card
  bob->add_and_discard(
    Card(NINE, SPADES) // upcard
  );

  // Bob leads
  Card card_led = bob->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card ace_hearts(ACE, HEARTS);
  ASSERT_EQUAL(card_led, ace_hearts); // check led card

  delete bob;
}

// Bob has one card of the leading suit
TEST(test_player_lead__mixed_hand_of_four_cards) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, HEARTS));

  // Bob leads
  Card card_led = bob->lead_card(SPADES);

  // Verify the card Bob selected to lead
  Card king_hearts(KING, HEARTS);
  ASSERT_EQUAL(card_led, king_hearts); // check led card

  delete bob;
}

TEST(test_simple_player_play_card) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(NINE, SPADES));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(NINE, SPADES));
  delete bob;
}


TEST(test_simple_player_play_card_mixed_hand) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(ACE, CLUBS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(ACE, SPADES));

  // Bob plays a card
  Card led_card(NINE, DIAMONDS);
  Card card_played = bob->play_card(
  led_card,  // Nine of Diamonds is led
  HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(TEN, SPADES));

led_card = Card(KING, DIAMONDS);
  card_played = bob->play_card(
  led_card,  // Nine of Diamonds is led
  HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(KING, SPADES));


led_card = Card(TEN, HEARTS);
  card_played = bob->play_card(
  led_card,  // Nine of Diamonds is led
  HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

led_card = Card(TEN, DIAMONDS);
  card_played = bob->play_card(
  led_card,  // Nine of Diamonds is led
  HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(ACE, SPADES));

led_card = Card(JACK, DIAMONDS);
  card_played = bob->play_card(
  led_card,  // Nine of Diamonds is led
  HEARTS    // Trump suit
  ); 
  ASSERT_EQUAL(card_played, Card(ACE, CLUBS));

  delete bob;
}

TEST(test_simple_player_play_cards_full_hand) {
  // Bob's hand
  Player * steve = Player_factory("Bob", "Simple");
  steve->add_card(Card(NINE, CLUBS));
  steve->add_card(Card(JACK, DIAMONDS));
  steve->add_card(Card(JACK, CLUBS));
  steve->add_card(Card(KING, HEARTS));
  steve->add_card(Card(TEN, CLUBS));

  // Bob plays a card
  Card card_played = steve->lead_card(DIAMONDS);
  
  ASSERT_EQUAL(card_played, Card(KING, HEARTS));

  Card led_card = Card(JACK, HEARTS);
  card_played = steve->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

  led_card = Card(JACK, SPADES);
  card_played = steve->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(NINE, CLUBS));

  led_card = Card(ACE, CLUBS);
  card_played = steve->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(JACK, CLUBS));

  led_card = Card(QUEEN, HEARTS);
  card_played = steve->play_card(led_card, HEARTS);

  ASSERT_EQUAL(card_played, Card(TEN, CLUBS));
  delete steve;
}

TEST(test_simple_player_play_card_trump_hand) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(JACK, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob plays a card
  Card nine_diamonds(NINE, HEARTS);
  Card card_played = bob->play_card(
    nine_diamonds,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, HEARTS));

  Card ten_spades(TEN, SPADES);
  Card card_played2 = bob->play_card(
    ten_spades,  // ten of spades is led
    HEARTS    // Trump suit
  ); 

  ASSERT_EQUAL(card_played2, Card(TEN, HEARTS));
  delete bob;
}

TEST(test_simple_player_play_card_mixed_hand_2) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(QUEEN, SPADES));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(JACK, CLUBS));
  bob->add_card(Card(ACE, HEARTS));
  bob->add_card(Card(TEN, CLUBS));

  // Bob plays a card
  Card nine_hearts(NINE, HEARTS);
  Card card_played = bob->play_card(
    nine_hearts,  // Nine of Diamonds is led
    HEARTS    // Trump suit
  ); 

  //ASSERT_EQUAL(hand.size(), 1);

  // Verify the card Bob played
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

  Card ten_spades(TEN, SPADES);
  Card card_played2 = bob->play_card(
    ten_spades,  // ten of spades is led
    HEARTS    // Trump suit
  ); 

  ASSERT_EQUAL(card_played2, Card(QUEEN, SPADES));

  Card nine_diamonds(NINE, DIAMONDS);
  Card card_played3 = bob->play_card(
    nine_diamonds,  // nine of diamonds is led
    HEARTS    // Trump suit
  ); 

  ASSERT_EQUAL(card_played3, Card(TEN, CLUBS));



  delete bob;
}

TEST(lead_card_all_trump) {
   Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(JACK, DIAMONDS));
  bob->add_card(Card(NINE, HEARTS));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  Card card_played = bob->lead_card(HEARTS);
  
  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));

  delete bob;
}

TEST(screw_the_dealer) {
   Player * jazzybob = Player_factory("Jazzybob", "Simple");
   Card up_cardi_b(QUEEN, SPADES);

  jazzybob->add_card(Card(TEN, DIAMONDS));
  jazzybob->add_card(Card(JACK, DIAMONDS));
  jazzybob->add_card(Card(NINE, CLUBS));
  jazzybob->add_card(Card(KING, HEARTS));
  jazzybob->add_card(Card(ACE, HEARTS));

  Suit trump;
  jazzybob->make_trump(up_cardi_b, true, 2, trump);

  ASSERT_EQUAL(trump, CLUBS);

  Card cards_led = Card(KING, SPADES);
  Card card_played = jazzybob->play_card(cards_led, HEARTS);

  ASSERT_EQUAL(card_played, Card(NINE, CLUBS))
  
  cards_led = Card(NINE, HEARTS);
  card_played = jazzybob->play_card(cards_led, HEARTS);

  ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS))

  cards_led = Card(ACE, DIAMONDS);
  card_played = jazzybob->play_card(cards_led, HEARTS);

  ASSERT_EQUAL(card_played, Card(TEN, DIAMONDS))

  cards_led = Card(QUEEN, SPADES);
  card_played = jazzybob->play_card(cards_led, HEARTS);

  ASSERT_EQUAL(card_played, Card(KING, HEARTS))

  jazzybob->add_card(Card(KING, HEARTS));

  cards_led = Card(QUEEN, HEARTS);
  card_played = jazzybob->play_card(cards_led, HEARTS);

  ASSERT_EQUAL(card_played, Card(ACE, HEARTS))


  delete jazzybob;

}
    
TEST(test_simple_player_lead_trump_card) {
    Player * player = Player_factory("Bob", "Simple");
    player->add_card(Card(TEN, SPADES));
    player->add_card(Card(ACE, HEARTS));

    Card led_card = player->lead_card(HEARTS);
    ASSERT_EQUAL(led_card.get_suit(), HEARTS);
    ASSERT_EQUAL(led_card.get_rank(), ACE);
    delete player;
}

TEST(test_simple_player_lead_high_trump_card) {
    Player * player = Player_factory("Bob", "Simple");
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(ACE, HEARTS));

    Card led_card = player->lead_card(HEARTS);
    ASSERT_EQUAL(led_card.get_suit(), HEARTS);
    ASSERT_EQUAL(led_card.get_rank(), ACE);
    delete player;
}

TEST(test_simple_player_higher_trump) {
    Player * player = Player_factory("Bob", "Simple");
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(KING, HEARTS));
    player->add_card(Card(ACE, HEARTS));

    Card led_card = Card(TEN, HEARTS);
    Card card_played = player->play_card(led_card, HEARTS);
    ASSERT_EQUAL(card_played.get_suit(), HEARTS);
    ASSERT_EQUAL(card_played.get_rank(), KING);
    delete player;
}

TEST(test_simple_player_low_trump) {
    Player * player = Player_factory("Bob", "Simple");
    player->add_card(Card(TEN, HEARTS));
    player->add_card(Card(ACE, HEARTS));
    player->add_card(Card(KING, SPADES));

    Card led_card = Card(TEN, HEARTS);
    Card card_played = player->play_card(led_card, HEARTS);
    ASSERT_EQUAL(card_played.get_suit(), HEARTS);
    ASSERT_EQUAL(card_played.get_rank(), TEN);
    delete player;
}



    
TEST_MAIN()
