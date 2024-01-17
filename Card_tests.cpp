#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

// Add more test cases here
TEST(test_default_ctor) {
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}


TEST(card_ctor_normal_test) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());

    Card b(NINE, SPADES);
    ASSERT_EQUAL(NINE, b.get_rank());
    ASSERT_EQUAL(SPADES, b.get_suit());

    Card a(KING, CLUBS);
    ASSERT_EQUAL(KING, a.get_rank());
    ASSERT_EQUAL(CLUBS, a.get_suit());

    Card f(QUEEN, DIAMONDS);
    ASSERT_EQUAL(QUEEN, f.get_rank());
    ASSERT_EQUAL(DIAMONDS, f.get_suit());
    ASSERT_EQUAL(DIAMONDS, f.get_suit(DIAMONDS));


    Card d(JACK, CLUBS);
    ASSERT_EQUAL(JACK, d.get_rank());
    ASSERT_EQUAL(CLUBS, d.get_suit());
    ASSERT_EQUAL(SPADES, d.get_suit(SPADES));
    ASSERT_EQUAL(CLUBS, d.get_suit(CLUBS));



    Card n(JACK, HEARTS);
    ASSERT_EQUAL(JACK, n.get_rank());
    ASSERT_EQUAL(HEARTS, n.get_suit());
    ASSERT_EQUAL(DIAMONDS, n.get_suit(DIAMONDS));


    Card v(TEN, SPADES);
    ASSERT_EQUAL(TEN, v.get_rank());
    ASSERT_EQUAL(SPADES, v.get_suit());

    Card e(THREE, SPADES);
    ASSERT_EQUAL(THREE, e.get_rank());
    ASSERT_EQUAL(SPADES, e.get_suit());
}


TEST(card_suit_and_rank_normal_test) {
    Card two_spades = Card();
    ASSERT_EQUAL(two_spades.get_rank(), TWO);
    ASSERT_EQUAL(two_spades.get_suit(), SPADES);

    Card ace_diamonds = Card(ACE, DIAMONDS);
    Card nine_clubs = Card(NINE, CLUBS);
    ASSERT_EQUAL(ace_diamonds.get_rank(), ACE);
    ASSERT_EQUAL(ace_diamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(ace_diamonds.is_face_or_ace(), true);

    ASSERT_EQUAL(nine_clubs.get_rank(), NINE);
    ASSERT_EQUAL(nine_clubs.get_suit(), CLUBS);
    ASSERT_EQUAL(nine_clubs.is_face_or_ace(), false);

}


TEST(test_card_type_normal_test) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));

    Card king_diamonds = Card(KING, DIAMONDS);
    ASSERT_TRUE(king_diamonds.is_face_or_ace());
    ASSERT_FALSE(king_diamonds.is_right_bower(CLUBS));
    ASSERT_FALSE(king_diamonds.is_left_bower(CLUBS));
    ASSERT_TRUE(king_diamonds.is_trump(DIAMONDS));
    ASSERT_FALSE(king_diamonds.is_trump(SPADES));


    Card ace_hearts = Card(ACE, HEARTS);
    ASSERT_TRUE(ace_hearts.is_face_or_ace());
    ASSERT_FALSE(ace_hearts.is_right_bower(CLUBS));
    ASSERT_FALSE(ace_hearts.is_left_bower(CLUBS));
    ASSERT_TRUE(ace_hearts.is_trump(HEARTS));

    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_TRUE(jack_clubs.is_face_or_ace());
    ASSERT_TRUE(jack_clubs.is_right_bower(CLUBS));
    ASSERT_FALSE(jack_clubs.is_left_bower(CLUBS));
    ASSERT_TRUE(jack_clubs.is_trump(CLUBS));
    ASSERT_TRUE(jack_clubs.is_trump(SPADES));


    Card jack_spades = Card(JACK, SPADES);
    ASSERT_TRUE(jack_spades.is_face_or_ace());
    ASSERT_FALSE(jack_spades.is_right_bower(CLUBS));
    ASSERT_TRUE(jack_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(jack_clubs.is_trump(HEARTS));
    ASSERT_FALSE(jack_clubs.is_trump(DIAMONDS));


    Card ten_diamonds = Card(TEN, DIAMONDS);
    ASSERT_FALSE(ten_diamonds.is_face_or_ace());
    ASSERT_FALSE(ten_diamonds.is_right_bower(HEARTS));
    ASSERT_FALSE(ten_diamonds.is_left_bower(HEARTS));
    ASSERT_FALSE(ten_diamonds.is_trump(HEARTS));
    ASSERT_TRUE(ten_diamonds.is_trump(DIAMONDS));
}


TEST(test_card_self_comparison_normal) {
    Card three_spades = Card(THREE, SPADES);
    Card jack_hearts = Card(JACK, HEARTS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);
    Card ace_diamonds = Card(ACE, DIAMONDS);
    Card ten_hearts = Card(TEN, HEARTS);
    Card ten_clubs = Card(TEN, CLUBS);
    Card nine_clubs = Card(NINE, CLUBS);


    ASSERT_TRUE(jack_clubs < ace_diamonds);
    ASSERT_FALSE(jack_clubs < ten_hearts);
    ASSERT_TRUE(jack_clubs < jack_diamonds);

    ASSERT_TRUE(jack_spades <= jack_diamonds);
    ASSERT_TRUE(nine_clubs <= nine_clubs);
    ASSERT_FALSE(jack_clubs <= nine_clubs);

    ASSERT_TRUE(jack_clubs > three_spades);
    ASSERT_FALSE(nine_clubs > ten_hearts);
    ASSERT_TRUE(jack_diamonds > jack_clubs);

    ASSERT_TRUE(ace_diamonds >= jack_diamonds);
    ASSERT_TRUE(ace_diamonds >= ace_diamonds);
    ASSERT_FALSE(ten_hearts >= jack_clubs);

    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_TRUE(jack_clubs == jack_clubs);
    ASSERT_FALSE(jack_clubs == jack_diamonds);
    ASSERT_FALSE(jack_spades == jack_hearts);
    ASSERT_FALSE(ten_hearts == ten_clubs);


    ASSERT_FALSE(jack_clubs != jack_clubs);
    ASSERT_TRUE(three_spades != ace_diamonds);
    ASSERT_TRUE(jack_diamonds != jack_hearts);


    ASSERT_TRUE(jack_clubs > jack_spades);
}


TEST(Suit_next_normal_test) {
    ASSERT_EQUAL(Suit_next(CLUBS), SPADES);
    ASSERT_EQUAL(Suit_next(DIAMONDS), HEARTS);
    ASSERT_EQUAL(Suit_next(HEARTS), DIAMONDS);
    ASSERT_EQUAL(Suit_next(SPADES), CLUBS);
}

TEST(is_card_right_or_left_bower_test){
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);   
    ASSERT_TRUE(jack_diamonds.is_left_bower(HEARTS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(DIAMONDS));
    ASSERT_TRUE(jack_diamonds.is_right_bower(DIAMONDS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(CLUBS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(SPADES));


    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_right_bower(HEARTS));
    ASSERT_FALSE(jack_hearts.is_left_bower(CLUBS));
    ASSERT_FALSE(jack_hearts.is_left_bower(SPADES));

    ASSERT_TRUE(jack_clubs.is_left_bower(SPADES));
    ASSERT_TRUE(jack_clubs.is_right_bower(CLUBS));
    ASSERT_FALSE(jack_clubs.is_left_bower(HEARTS));
    ASSERT_FALSE(jack_clubs.is_left_bower(DIAMONDS));

    ASSERT_TRUE(jack_spades.is_left_bower(CLUBS));
    ASSERT_TRUE(jack_spades.is_right_bower(SPADES));
    ASSERT_FALSE(jack_spades.is_left_bower(HEARTS));
    ASSERT_FALSE(jack_spades.is_left_bower(DIAMONDS));
}

TEST(card_get_suit_left_bower_test){
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS); 

    ASSERT_TRUE(jack_diamonds.get_suit(HEARTS));    
    ASSERT_TRUE(jack_hearts.get_suit(DIAMONDS));    
    ASSERT_TRUE(jack_spades.get_suit(CLUBS));    
    ASSERT_EQUAL(jack_clubs.get_suit(SPADES), SPADES);    

}


TEST(Card_less_self_normal_test) {
    Card ace_diamonds = Card(ACE, DIAMONDS);
    Card ace_hearts = Card(ACE, HEARTS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    Card jack_hearts = Card(JACK, HEARTS);
    Card jack_spades = Card(JACK, SPADES);
    Card jack_clubs = Card(JACK, CLUBS);
    Card ten_spades = Card(TEN, SPADES);
    Card ten_clubs = Card(TEN, CLUBS);
    Card ten_diamonds = Card(TEN, DIAMONDS);
    Card nine_clubs = Card (NINE, CLUBS);
    Card nine_spades = Card (NINE, SPADES);
    Card king_clubs = Card (KING, CLUBS);
    Card queen_hearts = Card (QUEEN, HEARTS);

    //Card nine_diamonds = Card (NINE, DIAMONDS);



    ASSERT_FALSE(Card_less(ace_diamonds, ace_diamonds, CLUBS));
    ASSERT_TRUE(Card_less(ace_diamonds, jack_diamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(jack_diamonds, ace_diamonds, DIAMONDS));
    ASSERT_FALSE(Card_less(jack_diamonds, jack_diamonds, SPADES));
    ASSERT_TRUE(Card_less(nine_spades, ten_clubs, CLUBS));
    ASSERT_TRUE(Card_less(nine_spades, ten_clubs, CLUBS));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_hearts, HEARTS));
    ASSERT_FALSE(Card_less(jack_hearts, jack_diamonds, HEARTS));



    ASSERT_FALSE(Card_less(jack_diamonds, ace_diamonds, DIAMONDS));
    ASSERT_TRUE(Card_less(jack_diamonds, jack_spades, CLUBS));

    ASSERT_TRUE(Card_less(nine_spades, ten_spades, jack_spades, CLUBS));
    ASSERT_TRUE(Card_less(ten_spades, ten_diamonds, DIAMONDS));

    ASSERT_FALSE(Card_less(jack_diamonds, jack_spades, ace_diamonds, DIAMONDS));
    ASSERT_TRUE(Card_less(jack_spades, jack_clubs, nine_spades, CLUBS));
    ASSERT_FALSE(Card_less(jack_spades, jack_clubs, nine_spades, SPADES));
    ASSERT_TRUE(Card_less(jack_hearts, jack_diamonds, ace_diamonds, DIAMONDS));


    ASSERT_TRUE(Card_less(ten_spades, ten_clubs, nine_clubs, HEARTS));
    ASSERT_FALSE(Card_less(ten_spades, ten_clubs, nine_spades, HEARTS));

    ASSERT_FALSE(Card_less(king_clubs, jack_clubs, king_clubs, DIAMONDS));
    ASSERT_FALSE(Card_less(king_clubs, queen_hearts, king_clubs, DIAMONDS));
    ASSERT_TRUE(Card_less(king_clubs, ace_hearts, DIAMONDS));

}


TEST(card_insertion_normal_test) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");

    Card jack_diamonds = Card(JACK, DIAMONDS);
    ostringstream os;
    os << jack_diamonds;
    ASSERT_EQUAL(os.str(), "Jack of Diamonds");

    Card two_diamonds = Card(TWO, DIAMONDS);
    ostringstream os3;
    os3 << two_diamonds;
    ASSERT_EQUAL(os3.str(), "Two of Diamonds");

    Card king_hearts = Card(KING, HEARTS);
    ostringstream os2;
    os2 << king_hearts;
    ASSERT_EQUAL(os2.str(), "King of Hearts");

    Card ace_clubs = Card(KING, CLUBS);
    ostringstream os4;
    os4 << ace_clubs;
    ASSERT_EQUAL(os4.str(), "King of Clubs");

    Card ten_spades = Card(TEN, SPADES);
    ostringstream os5;
    os5 << ten_spades;
    ASSERT_EQUAL(os5.str(), "Ten of Spades");
}


TEST(card_extraction_test) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));

    istringstream is("King of Diamonds");
    Card b;
    is >> b;
    ASSERT_EQUAL(b, Card(KING, DIAMONDS));

    istringstream is5("Queen of Spades");
    Card n;
    is5 >> n;
    ASSERT_EQUAL(n, Card(QUEEN, SPADES));

    istringstream isss("Jack of Clubs");
    Card s;
    isss >> s;
    ASSERT_EQUAL(s, Card(JACK, CLUBS));

    istringstream is2("Ace of Hearts");
    Card a;
    is2 >> a;
    ASSERT_EQUAL(a, Card(ACE, HEARTS));

    istringstream is3("Ten of Clubs");
    Card d;
    is3 >> d;
    ASSERT_EQUAL(d, Card(TEN, CLUBS));

    istringstream is4("Nine of Diamonds");
    Card v;
    is4 >> v;
    ASSERT_EQUAL(v, Card(NINE, DIAMONDS));
}


TEST_MAIN()

