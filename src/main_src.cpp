#include<iostream>
#include<unordered_map>
#include<vector>
#include<cstring>
#include<utility>
#include<fstream>
#include "main_src.h"
#include "parser/file_reader.h"
#include "processor/data_process.h"

using namespace std;

#define FLIT_SIZE 32

int main(int argc,char *argv[])
{
	/* Note : we need to combine encoded string and then make it decode in place of vector array */

	if(argc <=1)
	{
		cout<<"Please enter data trace file \n";
		return 0;
	}
	vector<string> input_to_process;
	vector<string> output_to_get;
	vector<string> decoded_output;

	/* open file */

	int file_size=open_file(argv[1]);

	ofstream myfile("output_flit.txt");

	int net_flit_input=0,net_flit_output=0;
	for(int i=0;i<file_size;i++)
	{
		float flit_count=0;
		cout<<"INPUT PROCESS NUMBER : "<<"\t"<<i+1<<"\n";
		int data_size=0;
		/* get inuput data */
		input_to_process=get_file_input(i,data_size);

		/* input processor */
	
		output_to_get=input_processor(input_to_process,flit_count);

		/* decode */
		decoded_output=decode_string(output_to_get);

		/* display decode results */

		cout<<"\n";
		cout<<"\n";

		/* compare results */

		compare_results(input_to_process,decoded_output,output_to_get);

		/* compression count */

		cout<<"______________________________________________\n";
		cout<<"---------- RATIO ------------------------------\n";
		cout<<"_______________________________________________\n";
	
		cout<<"Inpt Size bytes : \t"<<data_size<<"\t"<<"Output Size bytes : \t"<<flit_count<<"\n";
		cout<<"Inpt Size flits : \t"<<data_size/FLIT_SIZE<<"\t"<<"Output Size flit : \t"<<flit_count/FLIT_SIZE<<"\n";
		myfile<<"Inpt Size flits : \t"<<data_size/FLIT_SIZE<<"\t"<<"Output Size flit : \t"<<flit_count/FLIT_SIZE<<"\n";
		
		net_flit_input+=(data_size/FLIT_SIZE);
		net_flit_output+=(flit_count/FLIT_SIZE);
	}

	cout<<"\n";
	cout<<"\n";
	
	cout<<"======================================================\n";
	cout<<"--------------- NET COMPRESSION ----------------------\n";
	cout<<"=======================================================\n";


	cout<<"\n";	
	cout<<"Net Flit input : \t"<<net_flit_input<<"\t"<<"Net Flit output : \t"<<net_flit_output<<"\n";
	myfile<<"Net Flit input : \t"<<net_flit_input<<"\t"<<"Net Flit output : \t"<<net_flit_output<<"\n";

	system("cat output_flit.txt | sort -k 4 > sorted_output_flit.txt");
	myfile.close();
	return 0;	
	
}

/* function to compare results */

void compare_results(vector<string> input,vector<string> output,vector<string> compressed)
{
	
	cout<<"\n";
	cout<<"\n";
	
	
	
	cout<<"=======================================\n";
	cout<<" ------- COMPARE RESULTS --------------\n";
	cout<<"=======================================\n";

	cout<<"\n";
	cout<<"\n";
	
	
	cout<<"INPUT"<<"\t"<<"\t"<<"COMPRESSED"<<"\t"<<"\t"<<"OUTPUT"<<"\t"<<"\t"<<"MATCH"<<"\n";
	cout<<"________________________________________________________________\n";
	cout<<"________________________________________________________________\n";

	for(int i=0;i<input.size();i++)
	{
		if(input[i].compare(output[i])==0)
		cout<<i+1<<" :\t"<<input[i]<<"\t"<<"\t"<<compressed[i]<<"\t"<<"\t"<<output[i]<<"\t"<<"Y"<<"\n";
		else
		cout<<i+1<<" : \t"<<input[i]<<"\t"<<"\t"<<compressed[i]<<"\t"<<"\t"<<output[i]<<"\t"<<"\t"<<"Unmatch"<<"\n";
		cout<<"______________________________________________________________\n";
	}
}


