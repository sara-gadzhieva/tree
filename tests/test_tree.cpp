#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <fstream>
#include <initializer_list>
#include "tree.h"

using utils::tree::Tree;

void fill(Tree<int> &t,std::ofstream &fout,std::initializer_list<int> values) {
    for (int x : values) t.add(x,fout);
}

TEST_CASE("Add and search") {
    std::ofstream fout("test_output.html");
    Tree<int> t;
    CHECK_FALSE(t.search(5));
    CHECK(t.add(5,fout));
    CHECK(t.add(3,fout));
    CHECK(t.add(8,fout));
    CHECK(t.search(5));
    CHECK(t.search(3));
    CHECK(t.search(8));
    CHECK_FALSE(t.search(100));
}

TEST_CASE("Delete") {
    std::ofstream fout("test_output.html");
    Tree<int> t;
    fill(t,fout,{5,3,8,1,4,7,9});
    REQUIRE(t.search(5));

    SUBCASE("delete a leaf") {
        CHECK(t.del(1,fout));
        CHECK_FALSE(t.search(1));
        CHECK(t.search(3));
        CHECK(t.search(4));
    }
    SUBCASE("delete a node with two children") {
        CHECK(t.del(3,fout));
        CHECK_FALSE(t.search(3));
        CHECK(t.search(1));
        CHECK(t.search(4));
    }
    SUBCASE("delete the root") {
        CHECK(t.del(5,fout));
        CHECK_FALSE(t.search(5));
        CHECK(t.search(3));
        CHECK(t.search(8));
        CHECK(t.search(1));
        CHECK(t.search(9));
    }
    SUBCASE("delete a missing element") {
        CHECK_FALSE(t.del(100,fout));
        CHECK(t.search(5));
    }
    SUBCASE("delete everything") {
        for (int x : {5,3,8,1,4,7,9}) CHECK(t.del(x,fout));
        for (int x : {5,3,8,1,4,7,9}) CHECK_FALSE(t.search(x));
    }
}

TEST_CASE("Delete a node with one child") {
    std::ofstream fout("test_output.html");
    Tree<int> t;
    fill(t,fout,{5,3,8,9});
    CHECK(t.del(8,fout));
    CHECK_FALSE(t.search(8));
    CHECK(t.search(9));
    CHECK(t.search(5));
}

TEST_CASE("Copy constructor") {
    std::ofstream fout("test_output.html");
    Tree<int> a;
    fill(a,fout,{5,3,8});
    Tree<int> b(a);

    SUBCASE("copy has the same elements") {
        CHECK(b.search(5));
        CHECK(b.search(3));
        CHECK(b.search(8));
    }
    SUBCASE("changing the copy does not change the original") {
        b.add(7,fout);
        b.del(3,fout);
        CHECK(b.search(7));
        CHECK_FALSE(b.search(3));
        CHECK_FALSE(a.search(7));
        CHECK(a.search(3));
    }
    SUBCASE("changing the original does not change the copy") {
        a.del(5,fout);
        CHECK_FALSE(a.search(5));
        CHECK(b.search(5));
    }
}

TEST_CASE("Assignment operator") {
    std::ofstream fout("test_output.html");
    Tree<int> a;
    fill(a,fout,{5,3,8});
    Tree<int> b;
    fill(b,fout,{100,200});

    SUBCASE("old content is replaced") {
        b=a;
        CHECK(b.search(5));
        CHECK_FALSE(b.search(100));
        CHECK_FALSE(b.search(200));
    }
    SUBCASE("trees stay independent") {
        b=a;
        b.add(7,fout);
        CHECK_FALSE(a.search(7));
    }
    SUBCASE("assignment to itself") {
        Tree<int> &same=a;
        a=same;
        CHECK(a.search(5));
        CHECK(a.search(3));
        CHECK(a.search(8));
    }
    SUBCASE("empty tree") {
        Tree<int> empty;
        b=empty;
        CHECK_FALSE(b.search(100));
    }
}

TEST_CASE("Tree of doubles") {
    std::ofstream fout("test_output.html");
    Tree<double> t;
    t.add(2.5,fout);
    t.add(1.5,fout);
    CHECK(t.search(1.5));
    CHECK_FALSE(t.search(9.5));
}
