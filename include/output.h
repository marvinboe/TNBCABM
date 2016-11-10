#ifndef __OUTPUT_H__
#define __OUTPUT_H__ 

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include "model.h"
#include "data.h"
class Output {
    public:
        typedef std::vector<std::vector<double>> datatype;
        Output();
        Output(const Data& data);


        void save_data(double t,const Model& model);

        int find_timepoint(double t) const;

        /** Output state matrix at specific timepoint. */
        void output_at_timpoint(double t,std::ostream & os);

        /** Output state matrix at specific timepoint. */
        void save_all_timepoints(std::string basepath);

    private:

        std::vector<datatype> _data;
        std::vector<double> _timepoints;

        double _output_interval;
        double _no_runs;


};

#endif /* ifndef __OUTPUT_H__ */