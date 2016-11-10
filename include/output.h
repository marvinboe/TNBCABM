#ifndef __OUTPUT_H__
#define __OUTPUT_H__ 

#include "model.h"
class Output {
    public:
        typedef std::vector<std::vector<double>> datatype;
        Output();


        void save_data(double t,const Model& model);

        void output();

    private:

        std::vector<datatype> _data;
        std::vector<double> _timesteps;

        double _output_interval;
        double _no_runs;


};

#endif /* ifndef __OUTPUT_H__ */
