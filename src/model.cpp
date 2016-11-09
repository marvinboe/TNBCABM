#include "model.h"

Model::Model(const Data& data){
    //initiate the tumour with a homogenous population with the type_p=1 and type_i=1
	int i;
    double n=data.return_initial_cellnumber();
	//define a matrix whose entries is initialized with 0
	double max_num_row=data.return_max_prolif_types();
	double max_num_column=data.return_max_immune_types();
	for(i=0;i<max_num_row;i++)
	{
    std::vector<double> row(max_num_column,0);
    _cells.push_back(row);
    }
	//define the first phenotype:  type_p=1 and type_i=1 with an initial size of n
	_cells[0][0]=n;
}


double Model::return_Ccell_number(int type_p, int type_i) const
{
    return _cells[type_p][type_i];
}

void Model::set_Ccell_number(int type_p, int type_i, double number){
	double max_num_row=_cells.size();
	double max_num_column=_cells[0].size();
	if((type_p>=max_num_row)||(type_i>=max_num_column)) exit(1); 
    _cells[type_p][type_i]=number;
}

void output(double dt, std::ostream & os){
	
}