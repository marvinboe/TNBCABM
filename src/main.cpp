
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
    Output output(data);
    for (int i=0 ; i< data.return_no_runs(); ++i){

        Kernel ker(data);
        ker.execute(output);
    }
    output.save_all_timepoints("./data/");
    output.print_time_evol(std::cout);
    std::cout <<"#program ended"<<std::endl;

}
