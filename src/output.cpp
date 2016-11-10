
#include "output.h"

Output::Output(){

}

void Output::save_data(double t, const Model& model){
    int i=t/_output_interval;
    datatype indat=model.return_all_cells();
    if (_timesteps.size()<=i){//_data[i] does not exist
        _timesteps.push_back(t);

        for (auto& x: indat){
            for (auto& y: (x)){
                (y)/=_no_runs;
            }
        }
        _data.push_back(indat);

    }
    else {
        datatype savedat=_data[i];

        for (int i =0; i< savedat.size();++i){
            for (int j=0; j<savedat[i].size();++j){
                savedat[i][j]+=indat[i][j]/_no_runs;
            }
        }

    }


}

