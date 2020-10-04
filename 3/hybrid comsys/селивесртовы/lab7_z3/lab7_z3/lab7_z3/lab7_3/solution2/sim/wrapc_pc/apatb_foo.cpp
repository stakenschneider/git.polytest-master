// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2019.1 (64-bit)
// Copyright 1986-2019 Xilinx, Inc. All Rights Reserved.
// ==============================================================

#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;


// [dump_struct_tree [build_nameSpaceTree] dumpedStructList] ---------->


// [dump_enumeration [get_enumeration_list]] ---------->


// wrapc file define: "in1"
#define AUTOTB_TVIN_in1  "../tv/cdatafile/c.foo.autotvin_in1.dat"
// wrapc file define: "in2"
#define AUTOTB_TVIN_in2  "../tv/cdatafile/c.foo.autotvin_in2.dat"
// wrapc file define: "out_data"
#define AUTOTB_TVOUT_out_data  "../tv/cdatafile/c.foo.autotvout_out_data.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "out_data"
#define AUTOTB_TVOUT_PC_out_data  "../tv/rtldatafile/rtl.foo.autotvout_out_data.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			in1_depth = 0;
			in2_depth = 0;
			out_data_depth = 0;
			trans_num =0;
		}

		~INTER_TCL_FILE() {
			mFile.open(mName);
			if (!mFile.good()) {
				cout << "Failed to open file ref.tcl" << endl;
				exit (1);
			}
			string total_list = get_depth_list();
			mFile << "set depth_list {\n";
			mFile << total_list;
			mFile << "}\n";
			mFile << "set trans_num "<<trans_num<<endl;
			mFile.close();
		}

		string get_depth_list () {
			stringstream total_list;
			total_list << "{in1 " << in1_depth << "}\n";
			total_list << "{in2 " << in2_depth << "}\n";
			total_list << "{out_data " << out_data_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int in1_depth;
		int in2_depth;
		int out_data_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern "C" void foo (
int in1,
int in2,
int* out_data);

extern "C" void AESL_WRAP_foo (
int in1,
int in2,
int* out_data)
{
	refine_signal_handler();
	fstream wrapc_switch_file_token;
	wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
	int AESL_i;
	if (wrapc_switch_file_token.good())
	{
		CodeState = ENTER_WRAPC_PC;
		static unsigned AESL_transaction_pc = 0;
		string AESL_token;
		string AESL_num;
		static AESL_FILE_HANDLER aesl_fh;


		// output port post check: "out_data"
		aesl_fh.read(AUTOTB_TVOUT_PC_out_data, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_out_data, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_out_data, AESL_token); // data

			sc_bv<32> *out_data_pc_buffer = new sc_bv<32>[1];
			int i = 0;

			while (AESL_token != "[[/transaction]]")
			{
				bool no_x = false;
				bool err = false;

				// search and replace 'X' with "0" from the 1st char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('X');
					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_data', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				no_x = false;

				// search and replace 'x' with "0" from the 3rd char of token
				while (!no_x)
				{
					size_t x_found = AESL_token.find('x', 2);

					if (x_found != string::npos)
					{
						if (!err)
						{
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_data', possible cause: There are uninitialized variables in the C design." << endl;
							err = true;
						}
						AESL_token.replace(x_found, 1, "0");
					}
					else
					{
						no_x = true;
					}
				}

				// push token into output port buffer
				if (AESL_token != "")
				{
					out_data_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_out_data, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_out_data))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: out_data
				{
					// bitslice(31, 0)
					// {
						// celement: out_data(31, 0)
						// {
							sc_lv<32>* out_data_lv0_0_0_1 = new sc_lv<32>[1];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out_data(31, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								if (&(out_data[0]) != NULL) // check the null address if the c port is array or others
								{
									out_data_lv0_0_0_1[hls_map_index].range(31, 0) = sc_bv<32>(out_data_pc_buffer[hls_map_index].range(31, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out_data(31, 0)
						{
							// carray: (0) => (0) @ (1)
							for (int i_0 = 0; i_0 <= 0; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : out_data[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : out_data[0]
								// output_left_conversion : out_data[i_0]
								// output_type_conversion : (out_data_lv0_0_0_1[hls_map_index]).to_uint64()
								if (&(out_data[0]) != NULL) // check the null address if the c port is array or others
								{
									out_data[i_0] = (out_data_lv0_0_0_1[hls_map_index]).to_uint64();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] out_data_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "in1"
		char* tvin_in1 = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_in1);

		// "in2"
		char* tvin_in2 = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_in2);

		// "out_data"
		char* tvout_out_data = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_out_data);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_in1, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);

		sc_bv<32> in1_tvin_wrapc_buffer;

		// RTL Name: in1
		{
			// bitslice(31, 0)
			{
				// celement: in1(31, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : in1
						// sub_1st_elem          : 
						// ori_name_1st_elem     : in1
						// regulate_c_name       : in1
						// input_type_conversion : in1
						if (&(in1) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> in1_tmp_mem;
							in1_tmp_mem = in1;
							in1_tvin_wrapc_buffer.range(31, 0) = in1_tmp_mem.range(31, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_in1, "%s\n", (in1_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);
		}

		tcl_file.set_num(1, &tcl_file.in1_depth);
		sprintf(tvin_in1, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);

		// [[transaction]]
		sprintf(tvin_in2, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);

		sc_bv<32> in2_tvin_wrapc_buffer;

		// RTL Name: in2
		{
			// bitslice(31, 0)
			{
				// celement: in2(31, 0)
				{
					// carray: (0) => (0) @ (0)
					{
						// sub                   : 
						// ori_name              : in2
						// sub_1st_elem          : 
						// ori_name_1st_elem     : in2
						// regulate_c_name       : in2
						// input_type_conversion : in2
						if (&(in2) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> in2_tmp_mem;
							in2_tmp_mem = in2;
							in2_tvin_wrapc_buffer.range(31, 0) = in2_tmp_mem.range(31, 0);
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvin_in2, "%s\n", (in2_tvin_wrapc_buffer).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);
		}

		tcl_file.set_num(1, &tcl_file.in2_depth);
		sprintf(tvin_in2, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		foo(in1, in2, out_data);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_out_data, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_out_data, tvout_out_data);

		sc_bv<32>* out_data_tvout_wrapc_buffer = new sc_bv<32>[1];

		// RTL Name: out_data
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: out_data(31, 0)
				{
					// carray: (0) => (0) @ (1)
					for (int i_0 = 0; i_0 <= 0; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : out_data[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : out_data[0]
						// regulate_c_name       : out_data
						// input_type_conversion : out_data[i_0]
						if (&(out_data[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> out_data_tmp_mem;
							out_data_tmp_mem = out_data[i_0];
							out_data_tvout_wrapc_buffer[hls_map_index].range(31, 0) = out_data_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 1; i++)
		{
			sprintf(tvout_out_data, "%s\n", (out_data_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_out_data, tvout_out_data);
		}

		tcl_file.set_num(1, &tcl_file.out_data_depth);
		sprintf(tvout_out_data, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_out_data, tvout_out_data);

		// release memory allocation
		delete [] out_data_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "in1"
		delete [] tvin_in1;
		// release memory allocation: "in2"
		delete [] tvin_in2;
		// release memory allocation: "out_data"
		delete [] tvout_out_data;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

