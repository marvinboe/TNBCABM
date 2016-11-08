#ifndef __KERNEL__
#define __KERNEL__ 

#include "model.h"
#include "reactions.h"
#include "misc.h"

class Kernel{
    public:
        Kernel();

        /** execute simulation run. */
        void execute();

    private:

        /** actual algorithm step. */
        double direct_update(double t);

        Model model;

        AllReactions _all_reactions;

        static std::uniform_real_distribution<double> uniform01;


};

#endif /* ifndef __KERNEL__ */
