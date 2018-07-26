#ifndef TESTER_H
#define TESTER_H

/**
* Tester.h
* Author: Binyamin Appelbaum
* Date: 13.12.17
*/


class Tester {
    void TestVelodyne16();
    void TestVelodyne32();
    void TestNovatel();
    void TestTiltan();
    void TestConf();
    void TestTCP();
    void TestCAN();
    void TestIdan();
    void TestLogs();
public:
    Tester();
    ~Tester() = default;

};

#endif // TESTER_H