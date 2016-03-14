
#ifndef __DATA_PROCESS_H__
#define __DATA_PROCESS_H__

using namespace std;
vector<string> input_processor(vector<string> input_to_process,float& flit_count);

void prepare_decode_dict(vector<string> input,unordered_map<string,string>& lcl_dict);
string get_binary(int index);
unordered_map<string,int> prepare_dict(vector<string> input_to_process,unordered_map<string,string>& lcl_dict);

string encode_data(string input,unordered_map<string,string> lcl_dict,float& flit_count,unordered_map<string,int>& occ_check);
vector<string> decode_string(vector<string> input_string);

#endif
