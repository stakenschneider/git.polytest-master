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


// wrapc file define: "d"
#define AUTOTB_TVIN_d  "../tv/cdatafile/c.foo.autotvin_d.dat"
#define AUTOTB_TVOUT_d  "../tv/cdatafile/c.foo.autotvout_d.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "d"
#define AUTOTB_TVOUT_PC_d  "../tv/rtldatafile/rtl.foo.autotvout_d.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			d_depth = 0;
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
			total_list << "{d " << d_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int d_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern "C" void foo (
int d[5]);

extern "C" void AESL_WRAP_foo (
int d[5])
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


		// output port post check: "d"
		aesl_fh.read(AUTOTB_TVOUT_PC_d, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_d, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_d, AESL_token); // data

			sc_bv<32> *d_pc_buffer = new sc_bv<32>[5];
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'd', possible cause: There are uninitialized variables in the C design." << endl;
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'd', possible cause: There are uninitialized variables in the C design." << endl;
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
					d_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_d, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_d))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: d
				{
					// bitslice(31, 0)
					// {
						// celement: d(31, 0)
						// {
							sc_lv<32>* d_lv0_0_4_1 = new sc_lv<32>[5];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: d(31, 0)
						{
							// carray: (0) => (4) @ (1)
							for (int i_0 = 0; i_0 <= 4; i_0 += 1)
							{
								if (&(d[0]) != NULL) // check the null address if the c port is array or others
								{
									d_lv0_0_4_1[hls_map_index].range(31, 0) = sc_bv<32>(d_pc_buffer[hls_map_index].range(31, 0));
									hls_map_index++;
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: d(31, 0)
						{
							// carray: (0) => (4) @ (1)
							for (int i_0 = 0; i_0 <= 4; i_0 += 1)
							{
								// sub                    : i_0
								// ori_name               : d[i_0]
								// sub_1st_elem           : 0
								// ori_name_1st_elem      : d[0]
								// output_left_conversion : d[i_0]
								// output_type_conversion : (d_lv0_0_4_1[hls_map_index]).to_uint64()
								if (&(d[0]) != NULL) // check the null address if the c port is array or others
								{
									d[i_0] = (d_lv0_0_4_1[hls_map_index]).to_uint64();
									hls_map_index++;
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] d_pc_buffer;
		}

		AESL_transaction_pc++;
	}
	else
	{
		CodeState = ENTER_WRAPC;
		static unsigned AESL_transaction;

		static AESL_FILE_HANDLER aesl_fh;

		// "d"
		char* tvin_d = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_d);
		char* tvout_d = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_d);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_d, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_d, tvin_d);

		sc_bv<32>* d_tvin_wrapc_buffer = new sc_bv<32>[5];

		// RTL Name: d
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: d(31, 0)
				{
					// carray: (0) => (4) @ (1)
					for (int i_0 = 0; i_0 <= 4; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : d[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : d[0]
						// regulate_c_name       : d
						// input_type_conversion : d[i_0]
						if (&(d[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> d_tmp_mem;
							d_tmp_mem = d[i_0];
							d_tvin_wrapc_buffer[hls_map_index].range(31, 0) = d_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 5; i++)
		{
			sprintf(tvin_d, "%s\n", (d_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_d, tvin_d);
		}

		tcl_file.set_num(5, &tcl_file.d_depth);
		sprintf(tvin_d, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_d, tvin_d);

		// release memory allocation
		delete [] d_tvin_wrapc_buffer;

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		foo(d);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_d, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_d, tvout_d);

		sc_bv<32>* d_tvout_wrapc_buffer = new sc_bv<32>[5];

		// RTL Name: d
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: d(31, 0)
				{
					// carray: (0) => (4) @ (1)
					for (int i_0 = 0; i_0 <= 4; i_0 += 1)
					{
						// sub                   : i_0
						// ori_name              : d[i_0]
						// sub_1st_elem          : 0
						// ori_name_1st_elem     : d[0]
						// regulate_c_name       : d
						// input_type_conversion : d[i_0]
						if (&(d[0]) != NULL) // check the null address if the c port is array or others
						{
							sc_lv<32> d_tmp_mem;
							d_tmp_mem = d[i_0];
							d_tvout_wrapc_buffer[hls_map_index].range(31, 0) = d_tmp_mem.range(31, 0);
                                 	       hls_map_index++;
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 5; i++)
		{
			sprintf(tvout_d, "%s\n", (d_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_d, tvout_d);
		}

		tcl_file.set_num(5, &tcl_file.d_depth);
		sprintf(tvout_d, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_d, tvout_d);

		// release memory allocation
		delete [] d_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "d"
		delete [] tvin_d;
		delete [] tvout_d;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

