// ==============================================================
// File generated on Sun May 05 14:55:33 +0300 2019
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
// SW Build 2405991 on Thu Dec  6 23:38:27 MST 2018
// IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
// Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
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


// wrapc file define: "d_in"
#define AUTOTB_TVIN_d_in  "../tv/cdatafile/c.foo.autotvin_d_in.dat"
// wrapc file define: "d_out"
#define AUTOTB_TVOUT_d_out  "../tv/cdatafile/c.foo.autotvout_d_out.dat"
#define AUTOTB_TVIN_d_out  "../tv/cdatafile/c.foo.autotvin_d_out.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "d_out"
#define AUTOTB_TVOUT_PC_d_out  "../tv/rtldatafile/rtl.foo.autotvout_d_out.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			d_in_depth = 0;
			d_out_depth = 0;
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
			total_list << "{d_in " << d_in_depth << "}\n";
			total_list << "{d_out " << d_out_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int d_in_depth;
		int d_out_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern "C" void foo (
int d_in[3],
int d_out[3]);

extern "C" void AESL_WRAP_foo (
int d_in[3],
int d_out[3])
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


		// output port post check: "d_out"
		aesl_fh.read(AUTOTB_TVOUT_PC_d_out, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_d_out, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_d_out, AESL_token); // data

			sc_bv<32> *d_out_pc_buffer = new sc_bv<32>[3];
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'd_out', possible cause: There are uninitialized variables in the C design." << endl;
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'd_out', possible cause: There are uninitialized variables in the C design." << endl;
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
					d_out_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_d_out, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_d_out))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: d_out
				{
					// bitslice(31, 0)
					// {
						// celement: d_out(31, 0)
						// {
							sc_lv<32>* d_out_lv0_0_2_1 = new sc_lv<32>[3];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: d_out(31, 0)
						{
							// carray: (0) => (2) @ (1)
							for (int i_0 = 0; i_0 <= 2; i_0 += 1)
							{
								if (&(d_out[0]) != NULL) // check the null address if the c port is array or others
								{
									d_out_lv0_0_2_1[hls_map_index].range(31, 0) = sc_bv<32>(d_out_pc_buffer[hls_map_index].range(31, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: d_out(31, 0)
						{
							// carray: (0) => (2) @ (1)
							for (int i_0 = 0; i_0 <= 2; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : d_out[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : d_out[0]
								// output_left_conversion : d_out[i_0]
								// output_type_conversion : (d_out_lv0_0_2_1[hls_map_index]).to_uint64()
								if (&(d_out[0]) != NULL) // check the null address if the c port is array or others
								{
									d_out[i_0] = (d_out_lv0_0_2_1[hls_map_index]).to_uint64();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] d_out_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "d_in"
		char* tvin_d_in = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_d_in);

		// "d_out"
		char* tvin_d_out = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_d_out);
		char* tvout_d_out = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_d_out);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_d_in, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_d_in, tvin_d_in);

		sc_bv<32>* d_in_tvin_wrapc_buffer = new sc_bv<32>[3];

		// RTL Name: d_in
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: d_in(31, 0)
				{
					// carray: (0) => (2) @ (1)
					for (int i_0 = 0; i_0 <= 2; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : d_in[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : d_in[0]
						// regulate_c_name       : d_in
						// input_type_conversion : d_in[i_0]
						if (&(d_in[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> d_in_tmp_mem;
							d_in_tmp_mem = d_in[i_0];
							d_in_tvin_wrapc_buffer[hls_map_index].range(31, 0) = d_in_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 3; i++)
		{
			sprintf(tvin_d_in, "%s\n", (d_in_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_d_in, tvin_d_in);
		}

		tcl_file.set_num(3, &tcl_file.d_in_depth);
		sprintf(tvin_d_in, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_d_in, tvin_d_in);

		// release memory allocation
		delete [] d_in_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_d_out, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_d_out, tvin_d_out);

		sc_bv<32>* d_out_tvin_wrapc_buffer = new sc_bv<32>[3];

		// RTL Name: d_out
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: d_out(31, 0)
				{
					// carray: (0) => (2) @ (1)
					for (int i_0 = 0; i_0 <= 2; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : d_out[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : d_out[0]
						// regulate_c_name       : d_out
						// input_type_conversion : d_out[i_0]
						if (&(d_out[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> d_out_tmp_mem;
							d_out_tmp_mem = d_out[i_0];
							d_out_tvin_wrapc_buffer[hls_map_index].range(31, 0) = d_out_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 3; i++)
		{
			sprintf(tvin_d_out, "%s\n", (d_out_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_d_out, tvin_d_out);
		}

		tcl_file.set_num(3, &tcl_file.d_out_depth);
		sprintf(tvin_d_out, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_d_out, tvin_d_out);

		// release memory allocation
		delete [] d_out_tvin_wrapc_buffer;

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		foo(d_in, d_out);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_d_out, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_d_out, tvout_d_out);

		sc_bv<32>* d_out_tvout_wrapc_buffer = new sc_bv<32>[3];

		// RTL Name: d_out
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: d_out(31, 0)
				{
					// carray: (0) => (2) @ (1)
					for (int i_0 = 0; i_0 <= 2; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : d_out[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : d_out[0]
						// regulate_c_name       : d_out
						// input_type_conversion : d_out[i_0]
						if (&(d_out[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> d_out_tmp_mem;
							d_out_tmp_mem = d_out[i_0];
							d_out_tvout_wrapc_buffer[hls_map_index].range(31, 0) = d_out_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 3; i++)
		{
			sprintf(tvout_d_out, "%s\n", (d_out_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_d_out, tvout_d_out);
		}

		tcl_file.set_num(3, &tcl_file.d_out_depth);
		sprintf(tvout_d_out, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_d_out, tvout_d_out);

		// release memory allocation
		delete [] d_out_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "d_in"
		delete [] tvin_d_in;
		// release memory allocation: "d_out"
		delete [] tvout_d_out;
		delete [] tvin_d_out;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

