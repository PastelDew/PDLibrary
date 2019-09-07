#ifndef TEST_RANDOM_H
#define TEST_RANDOM_H

#include "TestBase.h"

#include <pdl/Core/Random.h>

using namespace pdl;
using namespace std;

class TestRandom : public TestBase {
protected:
	const char* GetTestName() { return "Random"; }

	void DoRun() {
        Random rand;

        cout << "Randomizing 10 times_" << endl;
        for(int i = 0; i < 10; i++)
            cout << rand.Randomize() << endl;

        cout << endl << "Randomizing 10 times with seeding_" << endl;
        for(int i = 0; i < 10; i++){
            rand.SetSeed(1000);
            cout << rand.Randomize() << endl;
        }

        cout << endl << "Randomizing 10 times with WELL512a_" << endl;
        rand.SetAlgorithm(Random::Algorithm::WELL512a);
        for(int i = 0; i < 10; i++){
            cout << rand.Randomize() << endl;
        }

        cout << endl << "Randomizing 10 times with WELL1024a_" << endl;
        rand.SetAlgorithm(Random::Algorithm::WELL1024a);
        for(int i = 0; i < 10; i++){
            cout << rand.Randomize() << endl;
        }

        cout << endl << "Randomizing 10 times with WELL19937a_" << endl;
        rand.SetAlgorithm(Random::Algorithm::WELL19937a);
        for(int i = 0; i < 10; i++){
            cout << rand.Randomize() << endl;
        }

        cout << endl << "Randomizing 10 times with WELL44497a_" << endl;
        rand.SetAlgorithm(Random::Algorithm::WELL44497a);
        for(int i = 0; i < 10; i++){
            cout << rand.Randomize() << endl;
        }
	}
};

#endif // End of TEST_RANDOM_H