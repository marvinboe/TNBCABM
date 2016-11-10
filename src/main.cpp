
#include "data.h"
#include "kernel.h"
#include <random>

//define RNGengine (declared in include/misc.h)
std::mt19937_64 rng;

int main(int argc,char ** argv){
    uint32_t random_seed=0;

    ParameterHandler parameters(argc,argv);

    if (random_seed==0){
        std::random_device sysrand;
        random_seed=sysrand();
    }
    rng.seed(random_seed); //seed RNGengine

    Data data(parameters);
    Kernel ker(data);
    ker.execute();
    std::cout <<"program indeed ended"<<std::endl;

}
