
#include "kernel.h"
#include <fstream>
#include <ostream>  

Kernel::Kernel(Data data):_data(data),_model(data),_all_reactions(_model,data){
    // and here some even more funny stuff will come in
        
}

std::uniform_real_distribution<double> Kernel::uniform01(0.,1.);

double Kernel::direct_update(double t){

    double total_prop=0.;
    for (std::vector<Reaction*>::iterator it=_all_reactions.begin(); it!=_all_reactions.end(); ++it){
        total_prop+=(*it)->update_propensity(_model);
    }
    if (total_prop<=1e-20) return std::numeric_limits<double>::infinity();

    _all_reactions.set_total_propensity(total_prop);

    double tau=-1./_all_reactions.return_total_propensity() * std::log(uniform01(rng));

    double randchoice=_all_reactions.return_total_propensity() * uniform01(rng);
    double wheightsum=0.;
    int i=-1;
    while (wheightsum<randchoice){
        ++i;
        wheightsum+=_all_reactions[i]->propensity();
    }
    Reaction* reaction= _all_reactions[i];
    reaction->apply(_model, _data);
    // std::cout <<"test "<<_model.return_Ccell_number(0,0)<<" "<<total_prop<<" "<<tau<<" "<<randchoice<<" "<<i<<std::endl;

    return t+tau;
}



void Kernel::execute(){
    double t_max=100;
    double dt=0.1;
    double output_step=1.;
    double next_t_output=0.;

    double t=0;
    double t_stoch=0;
	
	char arq1[200];//name of the file to store the total cell number over time
	std::ofstream outputMatrx;
	std::ofstream outputTotalCell;
	outputTotalCell.open("/Users/huang01/Desktop/Micromet_TotalTumourCellNumberOverTime.txt");
	std::ostream* outputA= &outputTotalCell;
	
    while (t<t_max){
        //output stuff (TODO maybe extra class for that)
        while (next_t_output < t){
			//print matrix to new files every time
			std::sprintf(arq1,"/Users/huang01/Desktop/Micromet_TumourCellNumberForEachPhenotype_MatrixFormat_Time_%d.txt",(int)next_t_output);
			std::cout<<arq1<<"\n";
			outputMatrx.open(arq1);
			std::ostream* outputB= &outputMatrx;
			_model.output(next_t_output,*outputB,*outputA);
			outputMatrx.close();//close the file storing the matrix 
            next_t_output+=output_step;
        }
        while (t_stoch<t){
            t_stoch=direct_update(t_stoch);
        }
        t=t+dt;
    }
 outputTotalCell.close();//close the file storing the total cell number over time
}
