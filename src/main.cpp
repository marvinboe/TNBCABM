
#include "data.h"
#include "kernel.h"
#include <random>

//define RNGengine (declared in include/misc.h)
std::mt19937_64 rng;

int main(){
    uint32_t random_seed=0;

    if (random_seed==0){
        std::random_device sysrand;
        random_seed=sysrand();
    }
    rng.seed(random_seed); //seed RNGengine

    std::cout <<"hello world"<<std::endl;

}
