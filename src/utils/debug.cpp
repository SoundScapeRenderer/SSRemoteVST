#include <src/utils/debug.h>

#include <chrono>
#include <string>

/**
* Benchmark
*/
debug::benchmark::Benchmark::Benchmark()
    : begin(hrc::now())
    , end(hrc::now())
    , started(false)
    , ended(true)
{

}

debug::benchmark::Benchmark::~Benchmark()
{

}

void debug::benchmark::Benchmark::start()
{
    if (ended) {
        begin = hrc::now();
        end = hrc::now();
        ended = false;
        started = true;
    }
}
void debug::benchmark::Benchmark::stop()
{
    if (started) {
        end = hrc::now();
        started = false;
        ended = true;
    }
}

double debug::benchmark::Benchmark::result()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
}
