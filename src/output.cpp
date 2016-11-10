
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
    double in_primary=model.return_primary_size();
    double in_anti=model.return_anti_immune();
    double in_pro=model.return_pro_immune();
    double in_totalcells=model.return_total_cellnumber();
    if (_timepoints.size()<=i){//_data[i] does not exist
        _timepoints.push_back(t);

        for (auto& x: indat){
            for (auto& y: (x)){
                (y)/=_no_runs;
            }
        }
        _data.push_back(indat);

        _primary_data.push_back(in_primary/_no_runs);
        _anti_data.push_back(in_anti/_no_runs);
        _pro_data.push_back(in_pro/_no_runs);
        _totalcells_data.push_back(in_totalcells/_no_runs);

    }
    else {
        datatype& savedat=_data[i];

        for (int x =0; x< savedat.size();++x){
            for (int y=0; y<savedat[x].size();++y){
                savedat[x][y]+=indat[x][y]/_no_runs;
            }
        }
        _primary_data[i]+=in_primary/_no_runs;
        _anti_data[i]+=in_anti/_no_runs;
        _pro_data[i]+=in_pro/_no_runs;
        _totalcells_data[i]+=in_totalcells/_no_runs;

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

void Output::print_time_evol(std::ostream& os){
        std::cout <<"#<time><totalcells><anti><pro>"<<std::endl;
    for (int i=0 ; i< _timepoints.size(); ++i){
        std::cout <<_timepoints[i]<<" "<<_totalcells_data[i]<<" "<<_anti_data[i]<<" "<<_pro_data[i]<<std::endl;

    }
}
