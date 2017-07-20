#define CATCH_CONFIG_MAIN

#include <vector>

#include "catch.hpp"
#include <deque>
#include <dbhc/algorithm.h>

using namespace std;

namespace dbhc {

  TEST_CASE("min / max / sorting") {

    vector<int> v{1, 3, 1, 4, 2, -69, 32};

    SECTION("Vector") {

      SECTION("min_e vector") {
	int me = min_e(v, [](const int i) { return i; });
	REQUIRE(me == -69);
      }

      SECTION("min_e vector default") {
	int me = min_e(v);
	REQUIRE(me == -69);
      }

      SECTION("max_e vector") {
	int me = max_e(v, [](const int i) { return i; });
	REQUIRE(me == 32);
      }

      SECTION("max_e vector default") {
	int me = max_e(v);
	REQUIRE(me == 32);
      }


      SECTION("sort_lt vector") {
	sort_lt(v, [](const int i) { return i; });

	REQUIRE(v[0] == -69);
	REQUIRE(v[1] == 1);
      }
    
    }

    SECTION("Deque") {
      // SECTION("min_e") {
      // 	deque<int> s(v.begin(), v.end());
      // 	int me = min_e(s, [](const int i) { return -i; });
      // 	REQUIRE(me == 32);
      // }

      // SECTION("min_e deque default") {
      // 	deque<int> s(v.begin(), v.end());
      // 	int me = min_e(s);
      // 	REQUIRE(me == -69);
      // }

      // SECTION("max_e deque") {
      // 	deque<int> s(v.begin(), v.end());
      // 	int me = max_e(s, [](const int i) { return -i; });
      // 	REQUIRE(me == -69);
      // }

      // SECTION("max_e deque default") {
      // 	deque<int> s(v.begin(), v.end());
      // 	int me = max_e(s);
      // 	REQUIRE(me == 32);
      // }

    }

    SECTION("set") {

      SECTION("min_e set") {
	set<int> s(v.begin(), v.end());
	int me = min_e(s, [](const int i) { return -i; });
	REQUIRE(me == 32);
      }

      SECTION("min_e set default") {
	set<int> s(v.begin(), v.end());
	int me = min_e(s);
	REQUIRE(me == -69);
      }

      SECTION("max_e set") {
	set<int> s(v.begin(), v.end());
	int me = max_e(s, [](const int i) { return -i; });
	REQUIRE(me == -69);
      }

      SECTION("max_e set default") {
	set<int> s(v.begin(), v.end());
	int me = max_e(s);
	REQUIRE(me == 32);
      }
    }

  }

  TEST_CASE("elem") {

    SECTION("unordered_set<int>") {
      unordered_set<int> s{1, 2, 3, 4, 93, -9, 0};
      REQUIRE(elem(3, s));
    }

    SECTION("set<int>") {
      set<int> s{1, 2, 3, 4, 93, -9, 0};
      REQUIRE(elem(3, s));
    }

  }

  TEST_CASE("Intersection") {
    vector<int> a{1, 2, 5, 234, 9};
    vector<int> b{1, 2321, 5};

    SECTION("Two vectors") {
      vector<int> it =
	intersection(a, b);

      REQUIRE(it.size() == 2);
      REQUIRE(it[0] == 1);
      REQUIRE(it[1] == 5);
    }

    SECTION("Two sets") {
      set<int> set_a(a.begin(), a.end());
      set<int> set_b(b.begin(), b.end());

      set<int> it = intersection(set_a, set_b);

      REQUIRE(it.size() == 2);
      REQUIRE(elem(1, it));
      REQUIRE(elem(5, it));
    }

    SECTION("Two unorderedsets") {
      unordered_set<int> set_a(a.begin(), a.end());
      unordered_set<int> set_b(b.begin(), b.end());

      unordered_set<int> it = intersection(set_a, set_b);

      REQUIRE(it.size() == 2);
      REQUIRE(elem(1, it));
      REQUIRE(elem(5, it));
    }
    
  }
      

  TEST_CASE("greedy_adjacent_chains") {

    SECTION("Empty vector") {
      vector<int> v{};
      greedy_adjacent_chains(v.begin(), v.end(),
			     [](int i, int j) { return j == i + 1; });
      vector<int> correct{};
      REQUIRE(v == correct);
    }

    SECTION("One chain") {
      vector<int> v{13, 8, 14};
      greedy_adjacent_chains(v.begin(), v.end(),
			     [](int i, int j) { return j == i + 1; });
      vector<int> correct{13, 14, 8};
      REQUIRE(v == correct);
    }

    SECTION("Prefix of 3 chains") {
      vector<int> v{3, 13, 8, 4, 14};
      greedy_adjacent_chains(v.begin(), v.end(),
			     [](int i, int j) { return j == i + 1; });
      vector<int> correct{3, 4, 8, 13, 14};
      REQUIRE(v == correct);
    }
    
    SECTION("3 chains") {
      vector<int> v{1, 13, 2, 3, 8, 4, 14};
      // 1 13 2 3 8 4 14
      // 1 2 13 3 8 4 14
      // 1 2 3 13 8 4 14
      // 1 2 3 4 8 13 14
      greedy_adjacent_chains(v.begin(), v.end(),
			     [](int i, int j) { return j == i + 1; });
      vector<int> correct{1, 2, 3, 4, 8, 13, 14};
      REQUIRE(v == correct);
    }
  }

  TEST_CASE("Drop while tests") {

    SECTION("") {
      vector<int> v{};
      drop_while(v, [](int i) { return i < 0; });
      vector<int> correct;
      REQUIRE(v == correct);
    }

    SECTION("Several values") {
      vector<int> v{1, 3, 5, 2, 8, 34, 2};
      drop_while(v, [](int i) { return i < 5; });
      vector<int> correct{5, 2, 8, 34, 2};
      REQUIRE(v == correct);
    }

    SECTION("Drop the entire sequence") {
      vector<int> v{1, 3, 5, 2, 8, 34, 2};
      drop_while(v, [](int i) { return i < 500; });
      vector<int> correct;
      REQUIRE(v == correct);
    }
  }

  TEST_CASE("Split unary tests") {

    SECTION("Empty vector") {
      vector<int> v{};
      vector<vector<int>> res = group_unary(v, [](int i) { return i < 0; });
      vector<vector<int>> correct{};
      REQUIRE(res == correct);
    }

    SECTION("Several elements") {
      vector<int> v{1, 5, 1, 7, 3, 10, 1, 2};
      auto res = group_unary(v, [](int i) { return i < 3; });
      vector<vector<int>> correct{{1}, {5}, {1}, {7, 3, 10}, {1, 2}};
      REQUIRE(res == correct);
    }
  }

  TEST_CASE("Take while") {

    SECTION("Take the whole list") {
      vector<int> v{1, 3, 5, 2, 8, 34, 2};
      take_while(v, [](int i) { return i < 500; });
      vector<int> correct{1, 3, 5, 2, 8, 34, 2};
      REQUIRE(v == correct);
    }
    
    SECTION("Several values") {
      vector<int> v{1, 3, 5, 2, 8, 34, 2};
      take_while(v, [](int i) { return i < 5; });
      vector<int> correct{1, 3};
      REQUIRE(v == correct);
    }
  }
}
