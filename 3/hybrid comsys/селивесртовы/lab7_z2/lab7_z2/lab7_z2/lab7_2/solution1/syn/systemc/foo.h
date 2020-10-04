// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#ifndef _foo_HH_
#define _foo_HH_

#include "systemc.h"
#include "AESL_pkg.h"


namespace ap_rtl {

struct foo : public sc_module {
    // Port declarations 16
    sc_in_clk ap_clk;
    sc_in< sc_logic > ap_rst;
    sc_in< sc_logic > ap_start;
    sc_out< sc_logic > ap_done;
    sc_out< sc_logic > ap_idle;
    sc_out< sc_logic > ap_ready;
    sc_out< sc_lv<7> > in1_address0;
    sc_out< sc_logic > in1_ce0;
    sc_in< sc_lv<32> > in1_q0;
    sc_out< sc_lv<7> > in2_address0;
    sc_out< sc_logic > in2_ce0;
    sc_in< sc_lv<32> > in2_q0;
    sc_out< sc_lv<7> > out_r_address0;
    sc_out< sc_logic > out_r_ce0;
    sc_out< sc_logic > out_r_we0;
    sc_out< sc_lv<32> > out_r_d0;


    // Module declarations
    foo(sc_module_name name);
    SC_HAS_PROCESS(foo);

    ~foo();

    sc_trace_file* mVcdFile;

    ofstream mHdltvinHandle;
    ofstream mHdltvoutHandle;
    sc_signal< sc_lv<4> > ap_CS_fsm;
    sc_signal< sc_logic > ap_CS_fsm_state1;
    sc_signal< sc_lv<4> > i_fu_109_p2;
    sc_signal< sc_lv<4> > i_reg_182;
    sc_signal< sc_logic > ap_CS_fsm_state2;
    sc_signal< sc_lv<8> > add_ln5_1_fu_139_p2;
    sc_signal< sc_lv<8> > add_ln5_1_reg_187;
    sc_signal< sc_lv<1> > icmp_ln3_fu_103_p2;
    sc_signal< sc_lv<4> > j_fu_151_p2;
    sc_signal< sc_lv<4> > j_reg_195;
    sc_signal< sc_logic > ap_CS_fsm_state3;
    sc_signal< sc_lv<64> > zext_ln5_3_fu_166_p1;
    sc_signal< sc_lv<64> > zext_ln5_3_reg_200;
    sc_signal< sc_lv<1> > icmp_ln4_fu_145_p2;
    sc_signal< sc_lv<4> > i_0_reg_81;
    sc_signal< sc_lv<4> > j_0_reg_92;
    sc_signal< sc_logic > ap_CS_fsm_state4;
    sc_signal< sc_lv<7> > tmp_1_fu_115_p3;
    sc_signal< sc_lv<5> > tmp_2_fu_127_p3;
    sc_signal< sc_lv<8> > zext_ln5_1_fu_135_p1;
    sc_signal< sc_lv<8> > zext_ln5_fu_123_p1;
    sc_signal< sc_lv<8> > zext_ln5_2_fu_157_p1;
    sc_signal< sc_lv<8> > add_ln5_2_fu_161_p2;
    sc_signal< sc_lv<4> > ap_NS_fsm;
    static const sc_logic ap_const_logic_1;
    static const sc_logic ap_const_logic_0;
    static const sc_lv<4> ap_ST_fsm_state1;
    static const sc_lv<4> ap_ST_fsm_state2;
    static const sc_lv<4> ap_ST_fsm_state3;
    static const sc_lv<4> ap_ST_fsm_state4;
    static const sc_lv<32> ap_const_lv32_0;
    static const sc_lv<32> ap_const_lv32_1;
    static const sc_lv<1> ap_const_lv1_0;
    static const sc_lv<32> ap_const_lv32_2;
    static const sc_lv<4> ap_const_lv4_0;
    static const sc_lv<1> ap_const_lv1_1;
    static const sc_lv<32> ap_const_lv32_3;
    static const sc_lv<4> ap_const_lv4_A;
    static const sc_lv<4> ap_const_lv4_1;
    static const sc_lv<3> ap_const_lv3_0;
    static const bool ap_const_boolean_1;
    // Thread declarations
    void thread_ap_clk_no_reset_();
    void thread_add_ln5_1_fu_139_p2();
    void thread_add_ln5_2_fu_161_p2();
    void thread_ap_CS_fsm_state1();
    void thread_ap_CS_fsm_state2();
    void thread_ap_CS_fsm_state3();
    void thread_ap_CS_fsm_state4();
    void thread_ap_done();
    void thread_ap_idle();
    void thread_ap_ready();
    void thread_i_fu_109_p2();
    void thread_icmp_ln3_fu_103_p2();
    void thread_icmp_ln4_fu_145_p2();
    void thread_in1_address0();
    void thread_in1_ce0();
    void thread_in2_address0();
    void thread_in2_ce0();
    void thread_j_fu_151_p2();
    void thread_out_r_address0();
    void thread_out_r_ce0();
    void thread_out_r_d0();
    void thread_out_r_we0();
    void thread_tmp_1_fu_115_p3();
    void thread_tmp_2_fu_127_p3();
    void thread_zext_ln5_1_fu_135_p1();
    void thread_zext_ln5_2_fu_157_p1();
    void thread_zext_ln5_3_fu_166_p1();
    void thread_zext_ln5_fu_123_p1();
    void thread_ap_NS_fsm();
    void thread_hdltv_gen();
};

}

using namespace ap_rtl;

#endif
