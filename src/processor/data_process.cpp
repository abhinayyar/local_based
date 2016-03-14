/* file for processing data input */

#include<iostream>
#include<vector>
#include<unordered_map>
#include<cstring>
#include<utility>
#include<cmath>
#include<algorithm>
#include<unordered_set>
#include "data_process.h"

using namespace std;

#define BIT_WORD 2
#define PATTERN_SIZE 4
#define MAX_DICT_SIZE 32

void display_dict(unordered_map<string,string>  lcl_dict)
{
	cout<<" DITC -----------------------\n";
	for(pair<string,string> p : lcl_dict)
	{
		cout<<p.first<<"\t"<<p.second<<"\n";
		cout<<"---------------------------\n";
	}
}
vector<string> input_processor(vector<string> input_to_process,float& flit_count)
{

	vector<string> output_to_get;
	
	// local dict for the input
	unordered_map<string,string> lcl_dict;
	unordered_map<string,int> occ_check;

	occ_check=prepare_dict(input_to_process,lcl_dict);

//	display_dict(lcl_dict);
	for(string lcl_input : input_to_process)
	{
		output_to_get.push_back(encode_data(lcl_input,lcl_dict,flit_count,occ_check));
	}		
			
	return output_to_get;	
}
/* function to encode data */
string encode_data(string input,unordered_map<string,string> lcl_dict,float& flit_count,unordered_map<string,int>& occ_check)
{

	string output;
	if(lcl_dict.find(input)!=lcl_dict.end())
	{
		// word found in dict
		// can be of category 01 -> raw data used , 10 -> raw data pointed to

		if(occ_check[input]==1)
		{
			// first occurance of dict word
			output.assign("01"+input);
			occ_check[input]++;
			flit_count+=(0.25+4);	
		}
		else
		{
			// repeated occurance
			output.assign("10"+lcl_dict[input]);
			
			flit_count+=(0.25+(log2(MAX_DICT_SIZE)/8));	
		}	
	}
	else
	{
		// category -> raw data unused
		output.assign("00"+input);
		flit_count+=(0.25+4);	
	}

	return output;	
}

/* function to prepare dict 1 cycle */

unordered_map<string,int> prepare_dict(vector<string> input_to_process,unordered_map<string,string>& lcl_dict)
{

	unordered_map<string,int> occ_check;
	vector<pair<string,int> > order_check;
	
	unordered_map<string,int> tracker;
	for(string s : input_to_process)
	{
		if(occ_check.find(s)!=occ_check.end())
		{
			tracker[s]++;		
		}
		else
		{
			occ_check.insert(make_pair(s,1));
			order_check.push_back(make_pair(s,1));
			tracker.insert(make_pair(s,1));
		}
	}
	/* update dict */
	
	for(string s : input_to_process)
	{
		if(tracker.find(s)!=tracker.end() && tracker[s]>1)
		{
			int index=lcl_dict.size();
			lcl_dict.insert(make_pair(s,get_binary(index)));
		}
	}
	
	return occ_check;
}

/* function to convert index to binary */
string get_binary(int index)
{
	string output;
	int max_size=log2(MAX_DICT_SIZE);
	int a=index;	
	while(max_size>0)
	{
		output=to_string(index%2)+output;
		index=index/2;
		max_size--;
	}
	return output;
}

/* function to prepare decode dict */

void prepare_decode_dict(vector<string> input,unordered_map<string,string>& lcl_dict)
{
	for(string s : input)
	{
		if(s.substr(0,2).compare("01")==0)
		{
			int index=lcl_dict.size();
			lcl_dict.insert(make_pair(get_binary(index),s.substr(2)));
		}
	}	
}

/* function to decode data */

vector<string> decode_string(vector<string> input_string)
{
	vector<string> output_string;
	unordered_map<string,string> lcl_dict;

	prepare_decode_dict(input_string,lcl_dict);

	
//	display_dict(lcl_dict);
	for(string s : input_string)
	{
		if(s.substr(0,2).compare("00")==0 || s.substr(0,2).compare("01")==0)
		{
			// raw data unused
			output_string.push_back(s.substr(2));
		}
		else if(s.substr(0,2).compare("10")==0)
		{
			output_string.push_back(lcl_dict[s.substr(2)]);
		}
		else
		{
			/* Do Nothing */
		}
	}

	return output_string;
}

