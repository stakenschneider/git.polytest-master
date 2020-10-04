// ==============================================================
// RTL generated by Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC
// Version: 2019.1
// Copyright (C) 1986-2019 Xilinx, Inc. All Rights Reserved.
// 
// ===========================================================

`timescale 1 ns / 1 ps 

module dct_2d (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        in_block_address0,
        in_block_ce0,
        in_block_q0,
        out_block_address0,
        out_block_ce0,
        out_block_we0,
        out_block_d0
);

parameter    ap_ST_fsm_state1 = 13'd1;
parameter    ap_ST_fsm_state2 = 13'd2;
parameter    ap_ST_fsm_state3 = 13'd4;
parameter    ap_ST_fsm_state4 = 13'd8;
parameter    ap_ST_fsm_state5 = 13'd16;
parameter    ap_ST_fsm_state6 = 13'd32;
parameter    ap_ST_fsm_state7 = 13'd64;
parameter    ap_ST_fsm_state8 = 13'd128;
parameter    ap_ST_fsm_state9 = 13'd256;
parameter    ap_ST_fsm_state10 = 13'd512;
parameter    ap_ST_fsm_state11 = 13'd1024;
parameter    ap_ST_fsm_state12 = 13'd2048;
parameter    ap_ST_fsm_state13 = 13'd4096;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
output  [5:0] in_block_address0;
output   in_block_ce0;
input  [15:0] in_block_q0;
output  [5:0] out_block_address0;
output   out_block_ce0;
output   out_block_we0;
output  [15:0] out_block_d0;

reg ap_done;
reg ap_idle;
reg ap_ready;
reg in_block_ce0;
reg out_block_ce0;
reg out_block_we0;

(* fsm_encoding = "none" *) reg   [12:0] ap_CS_fsm;
wire    ap_CS_fsm_state1;
wire   [3:0] i_fu_194_p2;
reg   [3:0] i_reg_365;
wire    ap_CS_fsm_state2;
wire   [3:0] j_fu_206_p2;
reg   [3:0] j_reg_373;
wire    ap_CS_fsm_state4;
wire   [7:0] zext_ln38_fu_212_p1;
reg   [7:0] zext_ln38_reg_378;
wire   [0:0] icmp_ln35_fu_200_p2;
wire   [7:0] zext_ln37_fu_224_p1;
reg   [7:0] zext_ln37_reg_383;
wire   [3:0] i_5_fu_234_p2;
reg   [3:0] i_5_reg_391;
wire    ap_CS_fsm_state5;
wire   [0:0] icmp_ln37_fu_228_p2;
wire   [7:0] add_ln38_1_fu_266_p2;
reg   [7:0] add_ln38_1_reg_401;
wire   [15:0] row_outbuf_q0;
reg   [15:0] row_outbuf_load_reg_406;
wire    ap_CS_fsm_state6;
wire   [3:0] i_4_fu_281_p2;
reg   [3:0] i_4_reg_414;
wire    ap_CS_fsm_state8;
wire   [3:0] j_2_fu_293_p2;
reg   [3:0] j_2_reg_422;
wire    ap_CS_fsm_state10;
wire   [7:0] zext_ln49_fu_299_p1;
reg   [7:0] zext_ln49_reg_427;
wire   [0:0] icmp_ln46_fu_287_p2;
wire   [7:0] zext_ln48_fu_311_p1;
reg   [7:0] zext_ln48_reg_432;
wire   [3:0] i_6_fu_321_p2;
reg   [3:0] i_6_reg_440;
wire    ap_CS_fsm_state11;
wire   [7:0] add_ln49_fu_331_p2;
reg   [7:0] add_ln49_reg_445;
wire   [0:0] icmp_ln48_fu_315_p2;
wire   [15:0] col_outbuf_q0;
reg   [15:0] col_outbuf_load_reg_455;
wire    ap_CS_fsm_state12;
reg   [5:0] row_outbuf_address0;
reg    row_outbuf_ce0;
reg    row_outbuf_we0;
reg   [5:0] col_outbuf_address0;
reg    col_outbuf_ce0;
reg    col_outbuf_we0;
reg   [5:0] col_inbuf_address0;
reg    col_inbuf_ce0;
reg    col_inbuf_we0;
wire   [15:0] col_inbuf_q0;
wire    grp_dct_1d2_fu_173_ap_start;
wire    grp_dct_1d2_fu_173_ap_done;
wire    grp_dct_1d2_fu_173_ap_idle;
wire    grp_dct_1d2_fu_173_ap_ready;
wire   [5:0] grp_dct_1d2_fu_173_src_address0;
wire    grp_dct_1d2_fu_173_src_ce0;
reg   [15:0] grp_dct_1d2_fu_173_src_q0;
reg   [3:0] grp_dct_1d2_fu_173_src_offset;
wire   [5:0] grp_dct_1d2_fu_173_dst_address0;
wire    grp_dct_1d2_fu_173_dst_ce0;
wire    grp_dct_1d2_fu_173_dst_we0;
wire   [15:0] grp_dct_1d2_fu_173_dst_d0;
reg   [3:0] grp_dct_1d2_fu_173_dst_offset;
reg   [3:0] i_0_reg_105;
wire    ap_CS_fsm_state3;
reg   [3:0] j_0_reg_117;
wire   [0:0] icmp_ln30_fu_188_p2;
reg   [3:0] i_1_reg_128;
wire    ap_CS_fsm_state7;
reg   [3:0] i_2_reg_139;
wire    ap_CS_fsm_state9;
reg   [3:0] j_1_reg_151;
wire   [0:0] icmp_ln41_fu_275_p2;
reg   [3:0] i_3_reg_162;
wire    ap_CS_fsm_state13;
reg    grp_dct_1d2_fu_173_ap_start_reg;
wire   [63:0] zext_ln38_3_fu_261_p1;
wire   [63:0] zext_ln38_4_fu_271_p1;
wire   [63:0] zext_ln49_4_fu_353_p1;
wire   [63:0] zext_ln49_2_fu_358_p1;
wire   [6:0] tmp_2_fu_216_p3;
wire   [6:0] tmp_3_fu_244_p3;
wire   [7:0] zext_ln38_2_fu_252_p1;
wire   [7:0] add_ln38_fu_256_p2;
wire   [7:0] zext_ln38_1_fu_240_p1;
wire   [6:0] tmp_4_fu_303_p3;
wire   [7:0] zext_ln49_1_fu_327_p1;
wire   [6:0] tmp_5_fu_336_p3;
wire   [7:0] zext_ln49_3_fu_344_p1;
wire   [7:0] add_ln49_1_fu_348_p2;
reg   [12:0] ap_NS_fsm;

// power-on initialization
initial begin
#0 ap_CS_fsm = 13'd1;
#0 grp_dct_1d2_fu_173_ap_start_reg = 1'b0;
end

dct_2d_row_outbuf #(
    .DataWidth( 16 ),
    .AddressRange( 64 ),
    .AddressWidth( 6 ))
row_outbuf_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(row_outbuf_address0),
    .ce0(row_outbuf_ce0),
    .we0(row_outbuf_we0),
    .d0(grp_dct_1d2_fu_173_dst_d0),
    .q0(row_outbuf_q0)
);

dct_2d_row_outbuf #(
    .DataWidth( 16 ),
    .AddressRange( 64 ),
    .AddressWidth( 6 ))
col_outbuf_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(col_outbuf_address0),
    .ce0(col_outbuf_ce0),
    .we0(col_outbuf_we0),
    .d0(grp_dct_1d2_fu_173_dst_d0),
    .q0(col_outbuf_q0)
);

dct_2d_row_outbuf #(
    .DataWidth( 16 ),
    .AddressRange( 64 ),
    .AddressWidth( 6 ))
col_inbuf_U(
    .clk(ap_clk),
    .reset(ap_rst),
    .address0(col_inbuf_address0),
    .ce0(col_inbuf_ce0),
    .we0(col_inbuf_we0),
    .d0(row_outbuf_load_reg_406),
    .q0(col_inbuf_q0)
);

dct_1d2 grp_dct_1d2_fu_173(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(grp_dct_1d2_fu_173_ap_start),
    .ap_done(grp_dct_1d2_fu_173_ap_done),
    .ap_idle(grp_dct_1d2_fu_173_ap_idle),
    .ap_ready(grp_dct_1d2_fu_173_ap_ready),
    .src_address0(grp_dct_1d2_fu_173_src_address0),
    .src_ce0(grp_dct_1d2_fu_173_src_ce0),
    .src_q0(grp_dct_1d2_fu_173_src_q0),
    .src_offset(grp_dct_1d2_fu_173_src_offset),
    .dst_address0(grp_dct_1d2_fu_173_dst_address0),
    .dst_ce0(grp_dct_1d2_fu_173_dst_ce0),
    .dst_we0(grp_dct_1d2_fu_173_dst_we0),
    .dst_d0(grp_dct_1d2_fu_173_dst_d0),
    .dst_offset(grp_dct_1d2_fu_173_dst_offset)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_state1;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        grp_dct_1d2_fu_173_ap_start_reg <= 1'b0;
    end else begin
        if ((((icmp_ln41_fu_275_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state8)) | ((icmp_ln30_fu_188_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state2)))) begin
            grp_dct_1d2_fu_173_ap_start_reg <= 1'b1;
        end else if ((grp_dct_1d2_fu_173_ap_ready == 1'b1)) begin
            grp_dct_1d2_fu_173_ap_start_reg <= 1'b0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state3) & (grp_dct_1d2_fu_173_ap_done == 1'b1))) begin
        i_0_reg_105 <= i_reg_365;
    end else if (((1'b1 == ap_CS_fsm_state1) & (ap_start == 1'b1))) begin
        i_0_reg_105 <= 4'd0;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        i_1_reg_128 <= i_5_reg_391;
    end else if (((icmp_ln35_fu_200_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state4))) begin
        i_1_reg_128 <= 4'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln35_fu_200_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
        i_2_reg_139 <= 4'd0;
    end else if (((1'b1 == ap_CS_fsm_state9) & (grp_dct_1d2_fu_173_ap_done == 1'b1))) begin
        i_2_reg_139 <= i_4_reg_414;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state13)) begin
        i_3_reg_162 <= i_6_reg_440;
    end else if (((icmp_ln46_fu_287_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state10))) begin
        i_3_reg_162 <= 4'd0;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state2) & (icmp_ln30_fu_188_p2 == 1'd1))) begin
        j_0_reg_117 <= 4'd0;
    end else if (((icmp_ln37_fu_228_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
        j_0_reg_117 <= j_reg_373;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b1 == ap_CS_fsm_state8) & (icmp_ln41_fu_275_p2 == 1'd1))) begin
        j_1_reg_151 <= 4'd0;
    end else if (((1'b1 == ap_CS_fsm_state11) & (icmp_ln48_fu_315_p2 == 1'd1))) begin
        j_1_reg_151 <= j_2_reg_422;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln37_fu_228_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state5))) begin
        add_ln38_1_reg_401 <= add_ln38_1_fu_266_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln48_fu_315_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state11))) begin
        add_ln49_reg_445 <= add_ln49_fu_331_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state12)) begin
        col_outbuf_load_reg_455 <= col_outbuf_q0;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state8)) begin
        i_4_reg_414 <= i_4_fu_281_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        i_5_reg_391 <= i_5_fu_234_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        i_6_reg_440 <= i_6_fu_321_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state2)) begin
        i_reg_365 <= i_fu_194_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state10)) begin
        j_2_reg_422 <= j_2_fu_293_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state4)) begin
        j_reg_373 <= j_fu_206_p2;
    end
end

always @ (posedge ap_clk) begin
    if ((1'b1 == ap_CS_fsm_state6)) begin
        row_outbuf_load_reg_406 <= row_outbuf_q0;
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln35_fu_200_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state4))) begin
        zext_ln37_reg_383[6 : 3] <= zext_ln37_fu_224_p1[6 : 3];
        zext_ln38_reg_378[3 : 0] <= zext_ln38_fu_212_p1[3 : 0];
    end
end

always @ (posedge ap_clk) begin
    if (((icmp_ln46_fu_287_p2 == 1'd0) & (1'b1 == ap_CS_fsm_state10))) begin
        zext_ln48_reg_432[6 : 3] <= zext_ln48_fu_311_p1[6 : 3];
        zext_ln49_reg_427[3 : 0] <= zext_ln49_fu_299_p1[3 : 0];
    end
end

always @ (*) begin
    if ((((ap_start == 1'b0) & (1'b1 == ap_CS_fsm_state1)) | ((1'b1 == ap_CS_fsm_state10) & (icmp_ln46_fu_287_p2 == 1'd1)))) begin
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
    if (((1'b1 == ap_CS_fsm_state10) & (icmp_ln46_fu_287_p2 == 1'd1))) begin
        ap_ready = 1'b1;
    end else begin
        ap_ready = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        col_inbuf_address0 = zext_ln38_4_fu_271_p1;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        col_inbuf_address0 = grp_dct_1d2_fu_173_src_address0;
    end else begin
        col_inbuf_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        col_inbuf_ce0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        col_inbuf_ce0 = grp_dct_1d2_fu_173_src_ce0;
    end else begin
        col_inbuf_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state7)) begin
        col_inbuf_we0 = 1'b1;
    end else begin
        col_inbuf_we0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        col_outbuf_address0 = zext_ln49_4_fu_353_p1;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        col_outbuf_address0 = grp_dct_1d2_fu_173_dst_address0;
    end else begin
        col_outbuf_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state11)) begin
        col_outbuf_ce0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state9)) begin
        col_outbuf_ce0 = grp_dct_1d2_fu_173_dst_ce0;
    end else begin
        col_outbuf_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        col_outbuf_we0 = grp_dct_1d2_fu_173_dst_we0;
    end else begin
        col_outbuf_we0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        grp_dct_1d2_fu_173_dst_offset = i_2_reg_139;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        grp_dct_1d2_fu_173_dst_offset = i_0_reg_105;
    end else begin
        grp_dct_1d2_fu_173_dst_offset = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        grp_dct_1d2_fu_173_src_offset = i_2_reg_139;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        grp_dct_1d2_fu_173_src_offset = i_0_reg_105;
    end else begin
        grp_dct_1d2_fu_173_src_offset = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state9)) begin
        grp_dct_1d2_fu_173_src_q0 = col_inbuf_q0;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        grp_dct_1d2_fu_173_src_q0 = in_block_q0;
    end else begin
        grp_dct_1d2_fu_173_src_q0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        in_block_ce0 = grp_dct_1d2_fu_173_src_ce0;
    end else begin
        in_block_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state13)) begin
        out_block_ce0 = 1'b1;
    end else begin
        out_block_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state13)) begin
        out_block_we0 = 1'b1;
    end else begin
        out_block_we0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        row_outbuf_address0 = zext_ln38_3_fu_261_p1;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        row_outbuf_address0 = grp_dct_1d2_fu_173_dst_address0;
    end else begin
        row_outbuf_address0 = 'bx;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state5)) begin
        row_outbuf_ce0 = 1'b1;
    end else if ((1'b1 == ap_CS_fsm_state3)) begin
        row_outbuf_ce0 = grp_dct_1d2_fu_173_dst_ce0;
    end else begin
        row_outbuf_ce0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_state3)) begin
        row_outbuf_we0 = grp_dct_1d2_fu_173_dst_we0;
    end else begin
        row_outbuf_we0 = 1'b0;
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
            if (((1'b1 == ap_CS_fsm_state2) & (icmp_ln30_fu_188_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state3 : begin
            if (((1'b1 == ap_CS_fsm_state3) & (grp_dct_1d2_fu_173_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state3;
            end
        end
        ap_ST_fsm_state4 : begin
            if (((icmp_ln35_fu_200_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state4))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state5;
            end
        end
        ap_ST_fsm_state5 : begin
            if (((icmp_ln37_fu_228_p2 == 1'd1) & (1'b1 == ap_CS_fsm_state5))) begin
                ap_NS_fsm = ap_ST_fsm_state4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state6;
            end
        end
        ap_ST_fsm_state6 : begin
            ap_NS_fsm = ap_ST_fsm_state7;
        end
        ap_ST_fsm_state7 : begin
            ap_NS_fsm = ap_ST_fsm_state5;
        end
        ap_ST_fsm_state8 : begin
            if (((1'b1 == ap_CS_fsm_state8) & (icmp_ln41_fu_275_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state9 : begin
            if (((1'b1 == ap_CS_fsm_state9) & (grp_dct_1d2_fu_173_ap_done == 1'b1))) begin
                ap_NS_fsm = ap_ST_fsm_state8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state9;
            end
        end
        ap_ST_fsm_state10 : begin
            if (((1'b1 == ap_CS_fsm_state10) & (icmp_ln46_fu_287_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state11;
            end
        end
        ap_ST_fsm_state11 : begin
            if (((1'b1 == ap_CS_fsm_state11) & (icmp_ln48_fu_315_p2 == 1'd1))) begin
                ap_NS_fsm = ap_ST_fsm_state10;
            end else begin
                ap_NS_fsm = ap_ST_fsm_state12;
            end
        end
        ap_ST_fsm_state12 : begin
            ap_NS_fsm = ap_ST_fsm_state13;
        end
        ap_ST_fsm_state13 : begin
            ap_NS_fsm = ap_ST_fsm_state11;
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln38_1_fu_266_p2 = (zext_ln38_1_fu_240_p1 + zext_ln37_reg_383);

assign add_ln38_fu_256_p2 = (zext_ln38_reg_378 + zext_ln38_2_fu_252_p1);

assign add_ln49_1_fu_348_p2 = (zext_ln49_reg_427 + zext_ln49_3_fu_344_p1);

assign add_ln49_fu_331_p2 = (zext_ln49_1_fu_327_p1 + zext_ln48_reg_432);

assign ap_CS_fsm_state1 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_state10 = ap_CS_fsm[32'd9];

assign ap_CS_fsm_state11 = ap_CS_fsm[32'd10];

assign ap_CS_fsm_state12 = ap_CS_fsm[32'd11];

assign ap_CS_fsm_state13 = ap_CS_fsm[32'd12];

assign ap_CS_fsm_state2 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_state3 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_state4 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_state5 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_state6 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_state7 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_state8 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_state9 = ap_CS_fsm[32'd8];

assign grp_dct_1d2_fu_173_ap_start = grp_dct_1d2_fu_173_ap_start_reg;

assign i_4_fu_281_p2 = (i_2_reg_139 + 4'd1);

assign i_5_fu_234_p2 = (i_1_reg_128 + 4'd1);

assign i_6_fu_321_p2 = (i_3_reg_162 + 4'd1);

assign i_fu_194_p2 = (i_0_reg_105 + 4'd1);

assign icmp_ln30_fu_188_p2 = ((i_0_reg_105 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln35_fu_200_p2 = ((j_0_reg_117 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln37_fu_228_p2 = ((i_1_reg_128 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln41_fu_275_p2 = ((i_2_reg_139 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln46_fu_287_p2 = ((j_1_reg_151 == 4'd8) ? 1'b1 : 1'b0);

assign icmp_ln48_fu_315_p2 = ((i_3_reg_162 == 4'd8) ? 1'b1 : 1'b0);

assign in_block_address0 = grp_dct_1d2_fu_173_src_address0;

assign j_2_fu_293_p2 = (j_1_reg_151 + 4'd1);

assign j_fu_206_p2 = (j_0_reg_117 + 4'd1);

assign out_block_address0 = zext_ln49_2_fu_358_p1;

assign out_block_d0 = col_outbuf_load_reg_455;

assign tmp_2_fu_216_p3 = {{j_0_reg_117}, {3'd0}};

assign tmp_3_fu_244_p3 = {{i_1_reg_128}, {3'd0}};

assign tmp_4_fu_303_p3 = {{j_1_reg_151}, {3'd0}};

assign tmp_5_fu_336_p3 = {{i_3_reg_162}, {3'd0}};

assign zext_ln37_fu_224_p1 = tmp_2_fu_216_p3;

assign zext_ln38_1_fu_240_p1 = i_1_reg_128;

assign zext_ln38_2_fu_252_p1 = tmp_3_fu_244_p3;

assign zext_ln38_3_fu_261_p1 = add_ln38_fu_256_p2;

assign zext_ln38_4_fu_271_p1 = add_ln38_1_reg_401;

assign zext_ln38_fu_212_p1 = j_0_reg_117;

assign zext_ln48_fu_311_p1 = tmp_4_fu_303_p3;

assign zext_ln49_1_fu_327_p1 = i_3_reg_162;

assign zext_ln49_2_fu_358_p1 = add_ln49_reg_445;

assign zext_ln49_3_fu_344_p1 = tmp_5_fu_336_p3;

assign zext_ln49_4_fu_353_p1 = add_ln49_1_fu_348_p2;

assign zext_ln49_fu_299_p1 = j_1_reg_151;

always @ (posedge ap_clk) begin
    zext_ln38_reg_378[7:4] <= 4'b0000;
    zext_ln37_reg_383[2:0] <= 3'b000;
    zext_ln37_reg_383[7] <= 1'b0;
    zext_ln49_reg_427[7:4] <= 4'b0000;
    zext_ln48_reg_432[2:0] <= 3'b000;
    zext_ln48_reg_432[7] <= 1'b0;
end

endmodule //dct_2d
