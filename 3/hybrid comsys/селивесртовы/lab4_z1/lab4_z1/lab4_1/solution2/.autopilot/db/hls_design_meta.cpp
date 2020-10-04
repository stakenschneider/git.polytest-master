#include "hls_design_meta.h"
const Port_Property HLS_Design_Meta::port_props[]={
	Port_Property("ap_clk", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_rst", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_start", 1, hls_in, -1, "", "", 1),
	Port_Property("ap_done", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_idle", 1, hls_out, -1, "", "", 1),
	Port_Property("ap_ready", 1, hls_out, -1, "", "", 1),
	Port_Property("a", 32, hls_in, 0, "ap_hs", "in_data", 1),
	Port_Property("a_ap_vld", 1, hls_in, 0, "ap_hs", "in_vld", 1),
	Port_Property("a_ap_ack", 1, hls_out, 0, "ap_hs", "in_acc", 1),
	Port_Property("b", 32, hls_in, 1, "ap_ack", "in_data", 1),
	Port_Property("b_ap_ack", 1, hls_out, 1, "ap_ack", "in_acc", 1),
	Port_Property("c", 32, hls_in, 2, "ap_hs", "in_data", 1),
	Port_Property("c_ap_vld", 1, hls_in, 2, "ap_hs", "in_vld", 1),
	Port_Property("c_ap_ack", 1, hls_out, 2, "ap_hs", "in_acc", 1),
	Port_Property("d", 32, hls_in, 3, "ap_vld", "in_data", 1),
	Port_Property("d_ap_vld", 1, hls_in, 3, "ap_vld", "in_vld", 1),
	Port_Property("p_y", 32, hls_out, 4, "ap_ack", "out_data", 1),
	Port_Property("p_y_ap_ack", 1, hls_in, 4, "ap_ack", "out_acc", 1),
	Port_Property("ap_return", 32, hls_out, -1, "", "", 1),
};
const char* HLS_Design_Meta::dut_name = "lab4_1";
