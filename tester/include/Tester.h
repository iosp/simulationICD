#ifndef TESTER_H
#define TESTER_H

/**
* Tester.h
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/


class Tester {
    void TestVelodyne();
    void TestNovatel();
    void TestTiltan();
    void TestConf();
    void TestTCP();
    void TestCAN();
    void TestIdan();
public:
    Tester();
    ~Tester() = default;

};

#endif // TESTER_H