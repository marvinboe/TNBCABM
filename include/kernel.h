#ifndef __KERNEL__
#define __KERNEL__ 

#include "model.h"

class Kernel{
    public:
        Kernel();

        /** execute simulation run. */
        void execute();

    private:

        /** actual algorithm step. */
        double direct_update(double t);

        Model model;

};

#endif /* ifndef __KERNEL__ */
