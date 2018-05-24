#ifndef TESTER_H
#define TESTER_H

/**
* Tester.h
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/


class Tester {
    void TestVLP();
    void TestNovatel();
    void TestIns();
    void TestConf();
    void TestTCP();
    void TestCAN();
    void TestIdan();
    void TestIbeo();
    void TestIpon();
public:
    Tester();
    ~Tester() = default;

};

#endif // TESTER_H