// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

(* CORE_GENERATION_INFO="foo,hls_ip_2019_1,{HLS_INPUT_TYPE=c,HLS_INPUT_FLOAT=0,HLS_INPUT_FIXED=0,HLS_INPUT_PART=xa7a12t-csg325-1Q,HLS_INPUT_CLOCK=10.000000,HLS_INPUT_ARCH=others,HLS_SYN_CLOCK=9.900000,HLS_SYN_LAT=4,HLS_SYN_TPT=none,HLS_SYN_MEM=0,HLS_SYN_DSP=0,HLS_SYN_FF=101,HLS_SYN_LUT=87,HLS_VERSION=2019_1}" *)

module foo (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        d_req_din,
        d_req_full_n,
        d_req_write,
        d_rsp_empty_n,
        d_rsp_read,
        d_address,
        d_datain,
        d_dataout,
        d_size
);

parameter    ap_ST_fsm_state1 = 5'd1;
parameter    ap_ST_fsm_state2 = 5'd2;
parameter    ap_ST_fsm_state3 = 5'd4;
parameter    ap_ST_fsm_state4 = 5'd8;
parameter    ap_ST_fsm_state5 = 5'd16;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output   d_req_din;
input   d_req_full_n;
output   d_req_write;
input   d_rsp_empty_n;
output   d_rsp_read;
output  [31:0] d_address;
input  [31:0] d_datain;
output  [31:0] d_dataout;
output  [31:0] d_size;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg d_req_din;
reg d_req_write;
reg d_rsp_read;
reg[31:0] d_address;

(* fsm_encoding = "none" *) reg   [4:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
reg   [31:0] acc;
wire   [31:0] d_addr_reg_66;
reg   [31:0] d_addr_read_reg_72;
wire    ap_CS_fsm_state3;
wire   [31:0] add_ln8_fu_55_p2;
reg   [31:0] add_ln8_reg_77;
wire    ap_CS_fsm_state4;
wire    ap_CS_fsm_state5;
reg   [4:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 5'd1;
#0 acc = 32'd0;
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        acc <= add_ln8_fu_55_p2;
        add_ln8_reg_77 <= add_ln8_fu_55_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((d_rsp_empty_n == 1'b1) & (1'b1 == ap_CS_fsm_state3))) begin
        d_addr_read_reg_72 <= d_datain;
    end
end

always @ (*) begin
    if (((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
        ap_done = 1'b1;
    end else begin
        ap_done = 1'b0;
    end
end

always @ (*) begin
    if (((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if (((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
        d_address = d_addr_reg_66;
    end else if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        d_address = 64'd0;
    end else begin
        d_address = 'bx;
    end
end

always @ (*) begin
    if (((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
        d_req_din = 1'b1;
    end else if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        d_req_din = 1'b0;
    end else begin
        d_req_din = 1'b0;
    end
end

always @ (*) begin
    if ((((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5)) | ((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1)))) begin
        d_req_write = 1'b1;
    end else begin
        d_req_write = 1'b0;
    end
end

always @ (*) begin
    if (((d_rsp_empty_n == 1'b1) & (1'b1 == ap_CS_fsm_state3))) begin
        d_rsp_read = 1'b1;
    end else begin
        d_rsp_read = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_state1 : begin
            if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end
        end
        ap_ST_fsm_state2 : begin
            ap_NS_fsm = ap_ST_fsm_state3;
        end
        ap_ST_fsm_state3 : begin
            if (((d_rsp_empty_n == 1'b1) & (1'b1 == ap_CS_fsm_state3))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state5 : begin
            if (((d_req_full_n == 1'b1) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln8_fu_55_p2 = (acc + d_addr_read_reg_72);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign d_addr_reg_66 = 64'd0;

assign d_dataout = add_ln8_reg_77;

assign d_size = 32'd1;

endmodule //foo
