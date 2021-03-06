#ifndef __KERNEL__
#define __KERNEL__ 

#include "model.h"
#include "reactions.h"
#include "output.h"
#include "misc.h"
#include <vector>
#include <limits>

class Kernel{
    public:
        /* constructor for Kernel. Uses data object for initialization. */
        Kernel(Data data);

        /** execute simulation run. */
        void execute(Output& output);

    private:

        /** actual algorithm step. */
        double direct_update(double t);
        void deterministic(double dt);

        void switch_chemo_state(double t);

        Data _data;
        Model _model;
        AllReactions _all_reactions;



        static std::uniform_real_distribution<double> uniform01;


};

#endif /* ifndef __KERNEL__ */
