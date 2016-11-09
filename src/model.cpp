#include "model.h"

Model::Model(const Data& data){
    //and here we go again
    double n=data.return_initial_cellnumber();
    std::vector<double> row(1,n);
    _cells.push_back(row);
}


double Model::return_Ccell_number(int type_p, int type_i) const
{
    return _cells[0][0];
}

void Model::set_Ccell_number(int comp, int type, double number){
    //do some funny stuff
    _cells[0][0]=number;

}
