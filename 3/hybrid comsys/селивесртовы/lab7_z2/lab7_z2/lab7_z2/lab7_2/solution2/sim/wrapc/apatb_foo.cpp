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
// wrapc file define: "out_r"
#define AUTOTB_TVOUT_out_r  "../tv/cdatafile/c.foo.autotvout_out_r.dat"
#define AUTOTB_TVIN_out_r  "../tv/cdatafile/c.foo.autotvin_out_r.dat"

#define INTER_TCL  "../tv/cdatafile/ref.tcl"

// tvout file define: "out_r"
#define AUTOTB_TVOUT_PC_out_r  "../tv/rtldatafile/rtl.foo.autotvout_out_r.dat"

class INTER_TCL_FILE {
	public:
		INTER_TCL_FILE(const char* name) {
			mName = name;
			in1_depth = 0;
			in2_depth = 0;
			out_r_depth = 0;
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
			total_list << "{out_r " << out_r_depth << "}\n";
			return total_list.str();
		}

		void set_num (int num , int* class_num) {
			(*class_num) = (*class_num) > num ? (*class_num) : num;
		}
	public:
		int in1_depth;
		int in2_depth;
		int out_r_depth;
		int trans_num;

	private:
		ofstream mFile;
		const char* mName;
};

extern "C" void foo (
int in1[10][10],
int in2[10][10],
int out[10][10]);

extern "C" void AESL_WRAP_foo (
int in1[10][10],
int in2[10][10],
int out[10][10])
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


		// output port post check: "out_r"
		aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // [[transaction]]
		if (AESL_token != "[[transaction]]")
		{
			exit(1);
		}
		aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_num); // transaction number

		if (atoi(AESL_num.c_str()) == AESL_transaction_pc)
		{
			aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // data

			sc_bv<32> *out_r_pc_buffer = new sc_bv<32>[100];
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_r', possible cause: There are uninitialized variables in the C design." << endl;
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
							cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'X' on port 'out_r', possible cause: There are uninitialized variables in the C design." << endl;
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
					out_r_pc_buffer[i] = AESL_token.c_str();
					i++;
				}

				aesl_fh.read(AUTOTB_TVOUT_PC_out_r, AESL_token); // data or [[/transaction]]

				if (AESL_token == "[[[/runtime]]]" || aesl_fh.eof(AUTOTB_TVOUT_PC_out_r))
				{
					exit(1);
				}
			}

			// ***********************************
			if (i > 0)
			{
				// RTL Name: out_r
				{
					// bitslice(31, 0)
					// {
						// celement: out(31, 0)
						// {
							sc_lv<32>* out_lv0_0_9_1_lv1_0_9_1 = new sc_lv<32>[100];
						// }
					// }

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out(31, 0)
						{
							// carray: (0) => (9) @ (1)
							for (int i_0 = 0; i_0 <= 9; i_0 += 1)
							{
								// carray: (0) => (9) @ (1)
								for (int i_1 = 0; i_1 <= 9; i_1 += 1)
								{
									if (&(out[0][0]) != NULL) // check the null address if the c port is array or others
									{
										out_lv0_0_9_1_lv1_0_9_1[hls_map_index].range(31, 0) = sc_bv<32>(out_r_pc_buffer[hls_map_index].range(31, 0));
										hls_map_index++;
									}
								}
							}
						}
					}

					// bitslice(31, 0)
					{
						int hls_map_index = 0;
						// celement: out(31, 0)
						{
							// carray: (0) => (9) @ (1)
							for (int i_0 = 0; i_0 <= 9; i_0 += 1)
							{
								// carray: (0) => (9) @ (1)
								for (int i_1 = 0; i_1 <= 9; i_1 += 1)
								{
									// sub                    : i_0 i_1
									// ori_name               : out[i_0][i_1]
									// sub_1st_elem           : 0 0
									// ori_name_1st_elem      : out[0][0]
									// output_left_conversion : out[i_0][i_1]
									// output_type_conversion : (out_lv0_0_9_1_lv1_0_9_1[hls_map_index]).to_uint64()
									if (&(out[0][0]) != NULL) // check the null address if the c port is array or others
									{
										out[i_0][i_1] = (out_lv0_0_9_1_lv1_0_9_1[hls_map_index]).to_uint64();
										hls_map_index++;
									}
								}
							}
						}
					}
				}
			}

			// release memory allocation
			delete [] out_r_pc_buffer;
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

		// "out_r"
		char* tvin_out_r = new char[50];
		aesl_fh.touch(AUTOTB_TVIN_out_r);
		char* tvout_out_r = new char[50];
		aesl_fh.touch(AUTOTB_TVOUT_out_r);

		CodeState = DUMP_INPUTS;
		static INTER_TCL_FILE tcl_file(INTER_TCL);
		int leading_zero;

		// [[transaction]]
		sprintf(tvin_in1, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);

		sc_bv<32>* in1_tvin_wrapc_buffer = new sc_bv<32>[100];

		// RTL Name: in1
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: in1(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// carray: (0) => (9) @ (1)
						for (int i_1 = 0; i_1 <= 9; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : in1[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : in1[0][0]
							// regulate_c_name       : in1
							// input_type_conversion : in1[i_0][i_1]
							if (&(in1[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> in1_tmp_mem;
								in1_tmp_mem = in1[i_0][i_1];
								in1_tvin_wrapc_buffer[hls_map_index].range(31, 0) = in1_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 100; i++)
		{
			sprintf(tvin_in1, "%s\n", (in1_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);
		}

		tcl_file.set_num(100, &tcl_file.in1_depth);
		sprintf(tvin_in1, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_in1, tvin_in1);

		// release memory allocation
		delete [] in1_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_in2, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);

		sc_bv<32>* in2_tvin_wrapc_buffer = new sc_bv<32>[100];

		// RTL Name: in2
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: in2(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// carray: (0) => (9) @ (1)
						for (int i_1 = 0; i_1 <= 9; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : in2[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : in2[0][0]
							// regulate_c_name       : in2
							// input_type_conversion : in2[i_0][i_1]
							if (&(in2[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> in2_tmp_mem;
								in2_tmp_mem = in2[i_0][i_1];
								in2_tvin_wrapc_buffer[hls_map_index].range(31, 0) = in2_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 100; i++)
		{
			sprintf(tvin_in2, "%s\n", (in2_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);
		}

		tcl_file.set_num(100, &tcl_file.in2_depth);
		sprintf(tvin_in2, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_in2, tvin_in2);

		// release memory allocation
		delete [] in2_tvin_wrapc_buffer;

		// [[transaction]]
		sprintf(tvin_out_r, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);

		sc_bv<32>* out_r_tvin_wrapc_buffer = new sc_bv<32>[100];

		// RTL Name: out_r
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: out(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// carray: (0) => (9) @ (1)
						for (int i_1 = 0; i_1 <= 9; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : out[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : out[0][0]
							// regulate_c_name       : out
							// input_type_conversion : out[i_0][i_1]
							if (&(out[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> out_tmp_mem;
								out_tmp_mem = out[i_0][i_1];
								out_r_tvin_wrapc_buffer[hls_map_index].range(31, 0) = out_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 100; i++)
		{
			sprintf(tvin_out_r, "%s\n", (out_r_tvin_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);
		}

		tcl_file.set_num(100, &tcl_file.out_r_depth);
		sprintf(tvin_out_r, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVIN_out_r, tvin_out_r);

		// release memory allocation
		delete [] out_r_tvin_wrapc_buffer;

// [call_c_dut] ---------->

		CodeState = CALL_C_DUT;
		foo(in1, in2, out);

		CodeState = DUMP_OUTPUTS;

		// [[transaction]]
		sprintf(tvout_out_r, "[[transaction]] %d\n", AESL_transaction);
		aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);

		sc_bv<32>* out_r_tvout_wrapc_buffer = new sc_bv<32>[100];

		// RTL Name: out_r
		{
			// bitslice(31, 0)
			{
				int hls_map_index = 0;
				// celement: out(31, 0)
				{
					// carray: (0) => (9) @ (1)
					for (int i_0 = 0; i_0 <= 9; i_0 += 1)
					{
						// carray: (0) => (9) @ (1)
						for (int i_1 = 0; i_1 <= 9; i_1 += 1)
						{
							// sub                   : i_0 i_1
							// ori_name              : out[i_0][i_1]
							// sub_1st_elem          : 0 0
							// ori_name_1st_elem     : out[0][0]
							// regulate_c_name       : out
							// input_type_conversion : out[i_0][i_1]
							if (&(out[0][0]) != NULL) // check the null address if the c port is array or others
							{
								sc_lv<32> out_tmp_mem;
								out_tmp_mem = out[i_0][i_1];
								out_r_tvout_wrapc_buffer[hls_map_index].range(31, 0) = out_tmp_mem.range(31, 0);
                                 		       hls_map_index++;
							}
						}
					}
				}
			}
		}

		// dump tv to file
		for (int i = 0; i < 100; i++)
		{
			sprintf(tvout_out_r, "%s\n", (out_r_tvout_wrapc_buffer[i]).to_string(SC_HEX).c_str());
			aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);
		}

		tcl_file.set_num(100, &tcl_file.out_r_depth);
		sprintf(tvout_out_r, "[[/transaction]] \n");
		aesl_fh.write(AUTOTB_TVOUT_out_r, tvout_out_r);

		// release memory allocation
		delete [] out_r_tvout_wrapc_buffer;

		CodeState = DELETE_CHAR_BUFFERS;
		// release memory allocation: "in1"
		delete [] tvin_in1;
		// release memory allocation: "in2"
		delete [] tvin_in2;
		// release memory allocation: "out_r"
		delete [] tvout_out_r;
		delete [] tvin_out_r;

		AESL_transaction++;

		tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
	}
}

