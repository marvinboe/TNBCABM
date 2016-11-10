
#include "output.h"

Output::Output(){


    _output_interval=1.;
    _no_runs=1;
}

Output::Output(const Data& data){
    _output_interval=data.return_output_interval();
    _no_runs=data.return_no_runs();

}

void Output::save_data(double t, const Model& model){
    int i=t/_output_interval;
    // std::cout <<"debug: "<<t<<" "<<i<<" "<<_timepoints.size()<<" "<<_data.size()<<std::endl;
    datatype indat=model.return_all_cells();
    if (_timepoints.size()<=i){//_data[i] does not exist
        _timepoints.push_back(t);

        for (auto& x: indat){
            for (auto& y: (x)){
                (y)/=_no_runs;
            }
        }
        _data.push_back(indat);

    }
    else {
        datatype savedat=_data[i];

        for (int x =0; x< savedat.size();++x){
            for (int y=0; y<savedat[x].size();++y){
                savedat[x][y]+=indat[x][y]/_no_runs;
            }
        }

    }


}


void Output::output_at_timpoint(double time,std::ostream & os){

    int i=find_timepoint(time);
    if (i<0 || i >= _data.size()) throw std::invalid_argument( "invalid timpoint" );
    datatype outdata=_data[i];
        for (auto& x: outdata){
            for (auto& y: (x)){
                os <<y<<" ";
            }
            os <<std::endl;;
        }
}


int Output::find_timepoint(double t) const{
    int i =_timepoints.size()-1;
    while (i > 0 && _timepoints[i] > t) --i; 
    return i;
}

void Output::save_all_timepoints(std::string basepath){
    if (basepath.empty()) basepath="./";
    // std::cout <<"debug output: "<<basepath<<std::endl;

    for (auto & t: _timepoints){
        std::stringstream filnamestream;
        filnamestream <<basepath<<t<<".dat";
        std::ofstream output;
        output.open(filnamestream.str().c_str());
        if (output.is_open()){
            output_at_timpoint(t,output);
            output.close();
        }
        else {
            std::cout <<"#cannot open "<<filnamestream.str()<<std::endl;
        }

    }

}
