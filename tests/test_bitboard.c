#include "bitboard.h"
#include "tests.h"

void tests_is_empty_cell() {
  __uint128_t bitboard = 4;
  /*
   *  - - o
   *  - - -
   *  - - -
   */
  print_bits(bitboard, 3);
  display_test("Test empty cell (L0,C1)", is_empty_cell(bitboard,0,1,3));
  print_bits(bitboard, 3);
  display_test("Test not empty cell (L0,C2)", !(is_empty_cell(bitboard,0,2,3)));
  display_test("1) Returns error : trying to reach a cell not on the bitboard",!(is_empty_cell(bitboard,-1,2,3)));
  display_test("2) Returns error : trying to reach a cell not on the bitboard",!(is_empty_cell(bitboard,5,12,3)));
  bitboard = 0;
  /*
   *  -
   */
  print_bits(bitboard, 1);
  display_test("Test empty bitboard with size one: Success",is_empty_cell(bitboard,0,0,1));
  bitboard = 1;
  /*
   *  o
   */
  print_bits(bitboard, 1);
  display_test("Test full bitboard with size one: Success",!(is_empty_cell(bitboard,0,0,1)));
}

//Tests "operation_on_token" function in order to add a token on a bitboard
void tests_add_token(){
  __uint128_t bitboard = 0;
  /*
   *  - - -
   *  - - -
   *  - - -
   */
  print_bits(bitboard, 3);
  display_test("Test empty cell (L0,C1) before adding",is_empty_cell(bitboard,0,1,3));
  bitboard = operation_on_token(bitboard,0,1,3,'+');
  /*
   *  - o -
   *  - - -
   *  - - -
   */
  print_bits(bitboard, 3);
  display_test("Test full cell (L0,C1) after adding",!is_empty_cell(bitboard,0,1,3));
}

void tests_is_won() {
  size_t size = 10;
  /*
   *  - - - - - - - - - -
   *  - - o - - - - - - -
   *  - - - - - - o - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - o o o o o - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  __uint128_t bitboard = 139611588515598336;
  print_bits(bitboard, size);
  display_test("Test is won (line)", is_won(bitboard, size));

  /*
   *  - - - - - o o o o o
   *  - - o - - - - - - -
   *  - - - - - - o - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 67113952;
  print_bits(bitboard, size);
  display_test("Test is won (line)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - o - - - - - - -
   *  o o o o o - o - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 99618816;
  print_bits(bitboard, size);
  display_test("Test is won (line)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - o - - - - - - -
   *  o o o o o o - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 66064384;
  print_bits(bitboard, size);
  display_test("Test is won (line)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - o - - - - - - -
   *  o o o o - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 15732736;
  print_bits(bitboard, size);
  display_test("Test is won (line)", !is_won(bitboard, size));

  /*
   *  o - - - - - - - - -
   *  - o - - o - - - - -
   *  - - - - o - - - - -
   *  - - - - o - - - - -
   *  - - - - o - - - - -
   *  - - - - o - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 18032007892191233;
  print_bits(bitboard, size);
  display_test("Test is won (column)", is_won(bitboard, size));

  /*
   *  o o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 2201172838403;
  print_bits(bitboard, size);
  display_test("Test is won (column)", is_won(bitboard, size));

  /*
   *  o o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - o - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 2254000986523651;
  print_bits(bitboard, size);
  display_test("Test is won (column)", is_won(bitboard, size));

  /*
   *  o - - - - - - - - -
   *  - o - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  o - - - - - - - - -
   *  o - - - - - - - - -
   *  o - - - - - - - - -
   *  o - - - - - - - - -
   *  o - - - - - - - - -
   */
  bitboard = I128(8598331400, 144115188075857921);
  print_bits(bitboard, size);
  display_test("Test is won (column)", is_won(bitboard, size));

  /*
   *  o - - - - - - - - -
   *  - o - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  o - - - - - - - - -
   *  - - - - - - - - - -
   *  o - - - - - - - o -
   *  - - - - - - - - o -
   *  - - - - - - - - o -
   *  - - - - - - - - - -
   */
  bitboard = I128(16793616, 1152922604118476801);
  print_bits(bitboard, size);
  display_test("Test is won (column)", !is_won(bitboard, size));

  /*
   *  o - - - - - - - - -
   *  - o - - - - - - - -
   *  - - o - - - - - - -
   *  - - - o - - - - - -
   *  - - - - o - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 17600780175361;
  print_bits(bitboard, size);
  display_test("Test is won (diag t2b)", is_won(bitboard, size));

  /*
   *  - - - - - o - - - -
   *  - - - - - - o - - -
   *  - - - - - - - o - -
   *  - - - - - - - - o -
   *  - - - - - - - - - o
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 563224965611552;
  print_bits(bitboard, size);
  display_test("Test is won (diag t2b up right)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  o - - - - - - - - -
   *  - o - - - - - - - -
   *  - - o - - - - - - -
   *  - - - o - - - - - -
   *  - - - - o - - - - -
   */
  bitboard = I128(1074266368, 2306968909120536576);
  print_bits(bitboard, size);
  display_test("Test is won (diag t2b bot left)", is_won(bitboard, size));

  /*
   *  - - - - - o - - - -
   *  - - - - o - - - - -
   *  - - - o - - - - - -
   *  - - o - - - - - - -
   *  - o - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = I128(0, 2203326627872);
  print_bits(bitboard, size);
  display_test("Test is won (diag b2t up right)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - o - -
   *  - - - - - - o - - -
   *  - - - - - o - - - -
   *  - - - - o - - - - -
   *  - - - o - - - - - -
   */
  bitboard = I128(537921540, 144115188075855872);
  print_bits(bitboard, size);
  display_test("Test is won (diag b2t bot left)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - o - - - - - - -
   *  - - o - - - - o - -
   *  - - - - - - o - - -
   *  - - - - - o - - - -
   *  - - - - o - - o - -
   *  - - - o - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = I128(0, 9385536876670095360);
  print_bits(bitboard, size);
  display_test("Test is won (diag b2t)", is_won(bitboard, size));

  /*
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   *  - - - - - - - - - -
   */
  bitboard = 0;
  print_bits(bitboard, size);
  display_test("Test is won (empty)", !is_won(bitboard, size));
}


int main(){
  tests_is_empty_cell();
  tests_add_token();
  tests_is_won();
  return 0;
}
