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
    _cells[data.return_start_prolif_type()][data.return_start_immune_type()]=n;

    _PrimaryTumourSize=data.get_initial_primary_tumour_cellnumber();
    _AntiTumImmuneSize=data.get_initial_anti_tumour_immune_cellnumber();
    _ProTumImmuneSize=data.get_initial_pro_tumour_immune_cellnumber();
    _ChemoState=data.get_chemo_state();
}


double Model::return_Ccell_number(int type_p, int type_i) const
{
    double max_num_row=_cells.size();
    double max_num_column=_cells[0].size();
    if((type_p>=max_num_row)||(type_i>=max_num_column)) exit(1); 
    return _cells[type_p][type_i];
}

void Model::set_Ccell_number(int type_p, int type_i, double number){
    double max_num_row=_cells.size();
    double max_num_column=_cells[0].size();
    if((type_p>=max_num_row)||(type_i>=max_num_column)) exit(1); 
    _cells[type_p][type_i]=number;
}

void Model::increment_Ccell_number(int type_p, int type_i, double number){
    double max_num_row=_cells.size();
    double max_num_column=_cells[0].size();
    if((type_p>=max_num_row)||(type_i>=max_num_column)) {
        throw std::invalid_argument("inc error");
    }
    _cells[type_p][type_i] += number;
}

void Model::output(double dt, std::ostream & os1, std::ostream & os2) const{
    int i,j;
    double totalCellNum=0.;
    double max_num_row=_cells.size();
    double max_num_column=_cells[0].size();
    //print number of cells of all phenotypes in a 2 dimentional matrix format(2 traits)
    for(i=0;i<max_num_row;i++)
    {    
        for(j=0;j<max_num_column-1;j++)
        {
            os1<<_cells[i][j]<<"\t";
            totalCellNum=totalCellNum+_cells[i][j];
        }	
        os1<<_cells[i][j]<<"\n";
        totalCellNum=totalCellNum+_cells[i][j];
    }
    //print the total cells at time dt
    os2<<dt<<"\t"<<totalCellNum<<"\n";
}

double Model::return_total_cellnumber() const{
    double n_return=0.;
        for (const auto& x: _cells){
            for (const auto& y: (x)){
                n_return+=y;
            }
        }
    return n_return;
}
