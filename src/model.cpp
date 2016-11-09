#include "model.h"

Model::Model(int initial_pt_size,int initial_mt_size,double num_micromets,double initial_pt_birthRate,double initial_mt_birthRate)
{
	int i,j;
	j=1.0;
	for(i=0;i<initial_pt_size;i++)
	{
		std::vector<double> row;
		row.push_back(initial_pt_birthRate);//the initial proliferation size
		row.push_back(j);//primary tumour = 1
	   Tumour.push_back(row);
    }
	for(j=2.0;j<=2.0+num_micromets;j++)
	for(i=0;i<initial_mt_size;i++)
	{
		std::vector<double> row;
		row.push_back(initial_mt_birthRate);//the initial proliferation size
		row.push_back(j);//micromet tumour compartment
	    Tumour.push_back(row);	
	}
	
	
}

double Model::get_Ccell_number(int comp, int type) const
{
	int TotalTumourSize,CompTumourSize;
	TotalTumourSize=Tumour.size();
	int i;
	for(i=0;i<TotalTumourSize;i++)
		if(Tumour[i][2]==(double)comp) CompTumourSize++;
	return CompTumourSize;
}
