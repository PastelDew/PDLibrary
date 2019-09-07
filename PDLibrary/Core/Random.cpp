#include "Random.h"
#include "../Memory/MemoryPool.h"
#include <iostream>
#include <ctime>

pdl::Random::Random(Algorithm algorithm) : isTimeSeed(true), usedAlgorithm(algorithm) {
    this->seed = static_cast<unsigned int>(std::time(NULL));
    this->SetAlgorithm(this->usedAlgorithm);
}

pdl::Random::Random(unsigned int seed, Algorithm algorithm) : isTimeSeed(true), usedAlgorithm(algorithm) {
    this->seed = seed;
    this->SetAlgorithm(this->usedAlgorithm);
}

void pdl::Random::SetAlgorithm(Algorithm algorithm){
    int seedLength = 0;
    srand(this->seed);
    switch(algorithm){
        case Algorithm::WELL512a:
            seedLength = 16;
        break;
        case Algorithm::WELL1024a:
            seedLength = 32;
        break;
        case Algorithm::WELL19937a:
            seedLength = 624;
        break;
        case Algorithm::WELL44497a:
            seedLength = 1391;
        break;
        default:
            seedLength = 1;
    }
    if(algorithm <= Algorithm::WELL44497a){
        this->initializedSeed = memory::CreateArray<unsigned int>(seedLength);
        for(int i = 0; i < seedLength; i++)
            this->initializedSeed[i] = rand();
        switch(algorithm){
            case Algorithm::WELL512a:
                InitWELLRNG512a(this->initializedSeed.Referer());
            break;
            case Algorithm::WELL1024a:
                InitWELLRNG1024a(this->initializedSeed.Referer());
            break;
            case Algorithm::WELL19937a:
                InitWELLRNG19937a(this->initializedSeed.Referer());
            break;
            case Algorithm::WELL44497a:
                InitWELLRNG44497a(this->initializedSeed.Referer());
            break;
            default:
            break;
        }
    }
}

void pdl::Random::SetSeed(unsigned int seed){
    this->seed = seed;
    this->SetAlgorithm(this->usedAlgorithm);
}

double pdl::Random::Randomize(){
    switch(this->usedAlgorithm){
        case Algorithm::WELL512a:
            return WELLRNG512a();
        case Algorithm::WELL1024a:
            return WELLRNG1024a();
        case Algorithm::WELL19937a:
            return WELLRNG19937a();
        case Algorithm::WELL44497a:
            return WELLRNG44497a();
        default:
            return (double)rand() / RAND_MAX;
    }
}