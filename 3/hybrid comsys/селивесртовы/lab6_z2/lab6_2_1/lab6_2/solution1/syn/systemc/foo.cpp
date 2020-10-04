// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

#include "foo.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

const sc_logic foo::ap_const_logic_1 = sc_dt::Log_1;
const sc_logic foo::ap_const_logic_0 = sc_dt::Log_0;
const sc_lv<5> foo::ap_ST_fsm_state1 = "1";
const sc_lv<5> foo::ap_ST_fsm_state2 = "10";
const sc_lv<5> foo::ap_ST_fsm_state3 = "100";
const sc_lv<5> foo::ap_ST_fsm_state4 = "1000";
const sc_lv<5> foo::ap_ST_fsm_state5 = "10000";
const sc_lv<32> foo::ap_const_lv32_0 = "00000000000000000000000000000000";
const sc_lv<32> foo::ap_const_lv32_2 = "10";
const sc_lv<32> foo::ap_const_lv32_3 = "11";
const sc_lv<64> foo::ap_const_lv64_0 = "0000000000000000000000000000000000000000000000000000000000000000";
const sc_lv<32> foo::ap_const_lv32_1 = "1";
const sc_lv<32> foo::ap_const_lv32_4 = "100";
const bool foo::ap_const_boolean_1 = true;

foo::foo(sc_module_name name) : sc_module(name), mVcdFile(0) {

    SC_METHOD(thread_ap_clk_no_reset_);
    dont_initialize();
    sensitive << ( ap_clk.pos() );

    SC_METHOD(thread_add_ln8_fu_55_p2);
    sensitive << ( acc );
    sensitive << ( d_addr_read_reg_72 );

    SC_METHOD(thread_ap_CS_fsm_state1);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state3);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state4);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_CS_fsm_state5);
    sensitive << ( ap_CS_fsm );

    SC_METHOD(thread_ap_done);
    sensitive << ( d_req_full_n );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_ap_idle);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_ap_ready);
    sensitive << ( d_req_full_n );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_d_addr_reg_66);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );

    SC_METHOD(thread_d_address);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( d_req_full_n );
    sensitive << ( d_addr_reg_66 );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_d_dataout);
    sensitive << ( d_req_full_n );
    sensitive << ( add_ln8_reg_77 );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_d_req_din);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( d_req_full_n );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_d_req_write);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( d_req_full_n );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_d_rsp_read);
    sensitive << ( d_rsp_empty_n );
    sensitive << ( ap_CS_fsm_state3 );

    SC_METHOD(thread_d_size);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( d_req_full_n );
    sensitive << ( ap_CS_fsm_state5 );

    SC_METHOD(thread_ap_NS_fsm);
    sensitive << ( ap_start );
    sensitive << ( ap_CS_fsm );
    sensitive << ( ap_CS_fsm_state1 );
    sensitive << ( d_req_full_n );
    sensitive << ( d_rsp_empty_n );
    sensitive << ( ap_CS_fsm_state3 );
    sensitive << ( ap_CS_fsm_state5 );

    SC_THREAD(thread_hdltv_gen);
    sensitive << ( ap_clk.pos() );

    ap_CS_fsm = "00001";
    acc = "00000000000000000000000000000000";
    static int apTFileNum = 0;
    stringstream apTFilenSS;
    apTFilenSS << "foo_sc_trace_" << apTFileNum ++;
    string apTFn = apTFilenSS.str();
    mVcdFile = sc_create_vcd_trace_file(apTFn.c_str());
    mVcdFile->set_time_unit(1, SC_PS);
    if (1) {
#ifdef __HLS_TRACE_LEVEL_PORT__
    sc_trace(mVcdFile, ap_clk, "(port)ap_clk");
    sc_trace(mVcdFile, ap_rst, "(port)ap_rst");
    sc_trace(mVcdFile, ap_start, "(port)ap_start");
    sc_trace(mVcdFile, ap_done, "(port)ap_done");
    sc_trace(mVcdFile, ap_idle, "(port)ap_idle");
    sc_trace(mVcdFile, ap_ready, "(port)ap_ready");
    sc_trace(mVcdFile, d_req_din, "(port)d_req_din");
    sc_trace(mVcdFile, d_req_full_n, "(port)d_req_full_n");
    sc_trace(mVcdFile, d_req_write, "(port)d_req_write");
    sc_trace(mVcdFile, d_rsp_empty_n, "(port)d_rsp_empty_n");
    sc_trace(mVcdFile, d_rsp_read, "(port)d_rsp_read");
    sc_trace(mVcdFile, d_address, "(port)d_address");
    sc_trace(mVcdFile, d_datain, "(port)d_datain");
    sc_trace(mVcdFile, d_dataout, "(port)d_dataout");
    sc_trace(mVcdFile, d_size, "(port)d_size");
#endif
#ifdef __HLS_TRACE_LEVEL_INT__
    sc_trace(mVcdFile, ap_CS_fsm, "ap_CS_fsm");
    sc_trace(mVcdFile, ap_CS_fsm_state1, "ap_CS_fsm_state1");
    sc_trace(mVcdFile, acc, "acc");
    sc_trace(mVcdFile, d_addr_reg_66, "d_addr_reg_66");
    sc_trace(mVcdFile, d_addr_read_reg_72, "d_addr_read_reg_72");
    sc_trace(mVcdFile, ap_CS_fsm_state3, "ap_CS_fsm_state3");
    sc_trace(mVcdFile, add_ln8_fu_55_p2, "add_ln8_fu_55_p2");
    sc_trace(mVcdFile, add_ln8_reg_77, "add_ln8_reg_77");
    sc_trace(mVcdFile, ap_CS_fsm_state4, "ap_CS_fsm_state4");
    sc_trace(mVcdFile, ap_CS_fsm_state5, "ap_CS_fsm_state5");
    sc_trace(mVcdFile, ap_NS_fsm, "ap_NS_fsm");
#endif

    }
    mHdltvinHandle.open("foo.hdltvin.dat");
    mHdltvoutHandle.open("foo.hdltvout.dat");
}

foo::~foo() {
    if (mVcdFile) 
        sc_close_vcd_trace_file(mVcdFile);

    mHdltvinHandle << "] " << endl;
    mHdltvoutHandle << "] " << endl;
    mHdltvinHandle.close();
    mHdltvoutHandle.close();
}

void foo::thread_ap_clk_no_reset_() {
    if ( ap_rst.read() == ap_const_logic_1) {
        ap_CS_fsm = ap_ST_fsm_state1;
    } else {
        ap_CS_fsm = ap_NS_fsm.read();
    }
    if (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state4.read())) {
        acc = add_ln8_fu_55_p2.read();
        add_ln8_reg_77 = add_ln8_fu_55_p2.read();
    }
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state3.read()) && esl_seteq<1,1,1>(d_rsp_empty_n.read(), ap_const_logic_1))) {
        d_addr_read_reg_72 = d_datain.read();
    }
}

void foo::thread_add_ln8_fu_55_p2() {
    add_ln8_fu_55_p2 = (!acc.read().is_01() || !d_addr_read_reg_72.read().is_01())? sc_lv<32>(): (sc_biguint<32>(acc.read()) + sc_biguint<32>(d_addr_read_reg_72.read()));
}

void foo::thread_ap_CS_fsm_state1() {
    ap_CS_fsm_state1 = ap_CS_fsm.read()[0];
}

void foo::thread_ap_CS_fsm_state3() {
    ap_CS_fsm_state3 = ap_CS_fsm.read()[2];
}

void foo::thread_ap_CS_fsm_state4() {
    ap_CS_fsm_state4 = ap_CS_fsm.read()[3];
}

void foo::thread_ap_CS_fsm_state5() {
    ap_CS_fsm_state5 = ap_CS_fsm.read()[4];
}

void foo::thread_ap_done() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1))) {
        ap_done = ap_const_logic_1;
    } else {
        ap_done = ap_const_logic_0;
    }
}

void foo::thread_ap_idle() {
    if ((esl_seteq<1,1,1>(ap_const_logic_0, ap_start.read()) && 
         esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()))) {
        ap_idle = ap_const_logic_1;
    } else {
        ap_idle = ap_const_logic_0;
    }
}

void foo::thread_ap_ready() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1))) {
        ap_ready = ap_const_logic_1;
    } else {
        ap_ready = ap_const_logic_0;
    }
}

void foo::thread_d_addr_reg_66() {
    d_addr_reg_66 =  (sc_lv<32>) (ap_const_lv64_0);
}

void foo::thread_d_address() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1))) {
        d_address = d_addr_reg_66.read();
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
        d_address =  (sc_lv<32>) (ap_const_lv64_0);
    } else {
        d_address = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    }
}

void foo::thread_d_dataout() {
    d_dataout = add_ln8_reg_77.read();
}

void foo::thread_d_req_din() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
         esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1))) {
        d_req_din = ap_const_logic_1;
    } else if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
                esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
        d_req_din = ap_const_logic_0;
    } else {
        d_req_din = ap_const_logic_0;
    }
}

void foo::thread_d_req_write() {
    if (((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && 
          esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1)) || 
         (esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && 
          esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1)))) {
        d_req_write = ap_const_logic_1;
    } else {
        d_req_write = ap_const_logic_0;
    }
}

void foo::thread_d_rsp_read() {
    if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state3.read()) && 
         esl_seteq<1,1,1>(d_rsp_empty_n.read(), ap_const_logic_1))) {
        d_rsp_read = ap_const_logic_1;
    } else {
        d_rsp_read = ap_const_logic_0;
    }
}

void foo::thread_d_size() {
    d_size = ap_const_lv32_1;
}

void foo::thread_ap_NS_fsm() {
    switch (ap_CS_fsm.read().to_uint64()) {
        case 1 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state1.read()) && esl_seteq<1,1,1>(ap_start.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state2;
            } else {
                ap_NS_fsm = ap_ST_fsm_state1;
            }
            break;
        case 2 : 
            ap_NS_fsm = ap_ST_fsm_state3;
            break;
        case 4 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state3.read()) && esl_seteq<1,1,1>(d_rsp_empty_n.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state4;
            } else {
                ap_NS_fsm = ap_ST_fsm_state3;
            }
            break;
        case 8 : 
            ap_NS_fsm = ap_ST_fsm_state5;
            break;
        case 16 : 
            if ((esl_seteq<1,1,1>(ap_const_logic_1, ap_CS_fsm_state5.read()) && esl_seteq<1,1,1>(d_req_full_n.read(), ap_const_logic_1))) {
                ap_NS_fsm = ap_ST_fsm_state1;
            } else {
                ap_NS_fsm = ap_ST_fsm_state5;
            }
            break;
        default : 
            ap_NS_fsm =  (sc_lv<5>) ("XXXXX");
            break;
    }
}

void foo::thread_hdltv_gen() {
    const char* dump_tv = std::getenv("AP_WRITE_TV");
    if (!(dump_tv && string(dump_tv) == "on")) return;

    wait();

    mHdltvinHandle << "[ " << endl;
    mHdltvoutHandle << "[ " << endl;
    int ap_cycleNo = 0;
    while (1) {
        wait();
        const char* mComma = ap_cycleNo == 0 ? " " : ", " ;
        mHdltvinHandle << mComma << "{"  <<  " \"ap_rst\" :  \"" << ap_rst.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"ap_start\" :  \"" << ap_start.read() << "\" ";
        mHdltvoutHandle << mComma << "{"  <<  " \"ap_done\" :  \"" << ap_done.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_idle\" :  \"" << ap_idle.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_ready\" :  \"" << ap_ready.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_req_din\" :  \"" << d_req_din.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"d_req_full_n\" :  \"" << d_req_full_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_req_write\" :  \"" << d_req_write.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"d_rsp_empty_n\" :  \"" << d_rsp_empty_n.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_rsp_read\" :  \"" << d_rsp_read.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_address\" :  \"" << d_address.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"d_datain\" :  \"" << d_datain.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_dataout\" :  \"" << d_dataout.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"d_size\" :  \"" << d_size.read() << "\" ";
        mHdltvinHandle << "}" << std::endl;
        mHdltvoutHandle << "}" << std::endl;
        ap_cycleNo++;
    }
}

}

