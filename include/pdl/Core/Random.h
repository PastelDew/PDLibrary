#ifndef _PDL_CORE_RANDOM_H_
#define _PDL_CORE_RANDOM_H_

#include "../Memory/Ptr.h"

#include "../libs/WELL/WELL512a.h"
#include "../libs/WELL/WELL1024a.h"
#include "../libs/WELL/WELL19937a.h"
#include "../libs/WELL/WELL44497a.h"

namespace pdl{
    PDLDLL_API class Random{
    public:
        enum Algorithm{WELL512a = 0, WELL1024a = 1, WELL19937a = 2, WELL44497a = 3, SRAND = 4};
    private:
        bool isTimeSeed;
        unsigned int seed;
        Ptr<unsigned int> initializedSeed;
        Algorithm usedAlgorithm;

    public:
        PDLDLL_API Random(Algorithm algorithm = Algorithm::SRAND);
        PDLDLL_API Random(unsigned int seed, Algorithm algorithm = Algorithm::SRAND);

        PDLDLL_API void SetAlgorithm(Algorithm algorithm);
        PDLDLL_API void SetSeed(unsigned int seed);

        PDLDLL_API double Randomize();
    };
}

#endif // End of _PDL_CORE_RANDOM_H_