#ifndef __KERNEL__
#define __KERNEL__ 

#include "model.h"
#include "reactions.h"
#include "misc.h"
#include <vector>
#include <limits>

class Kernel{
    public:
        /* constructor for Kernel. Uses data object for initialization. */
        Kernel(Data data);

        /** execute simulation run. */
        void execute();

    private:

        /** actual algorithm step. */
        double direct_update(double t);
		void deterministic(double t, double dt,double PrimaryTumourProRate,double PrimaryTumourImmRate,int c,double d_c,double delta,double ki,double kd);
		double _PrimaryTumourSize;
		double _AntiTumImmuneSize;
		double _ProTumImmuneSize;

        Model _model;
        Data _data;

        AllReactions _all_reactions;

        static std::uniform_real_distribution<double> uniform01;


};

#endif /* ifndef __KERNEL__ */
