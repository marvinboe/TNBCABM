#include "model.h"

Model::Model(const Data& data){
    //initiate the tumour with a homogenous population with the type_p=1 and type_i=1
    double n=data.return_initial_cellnumber();
    std::vector<double> row(1,n);
    _cells.push_back(row);
}


double Model::return_Ccell_number(int type_p, int type_i) const
{
    return _cells[type_p][type_i];
}

void Model::set_Ccell_number(int type_p, int type_i, double number){
    _cells[type_p][type_i]=number;
}
