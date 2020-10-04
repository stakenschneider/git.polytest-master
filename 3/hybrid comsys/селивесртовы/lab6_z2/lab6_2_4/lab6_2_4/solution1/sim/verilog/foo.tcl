
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set d_group [add_wave_group d(bus) -into $cinputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/d_size -into $d_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_dataout -into $d_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_datain -into $d_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_address -into $d_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_rsp_read -into $d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_rsp_empty_n -into $d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_req_write -into $d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_req_full_n -into $d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_req_din -into $d_group -radix hex
set blocksiggroup [add_wave_group "Block-level IO Handshake" -into $designtopgroup]
add_wave /apatb_foo_top/AESL_inst_foo/ap_start -into $blocksiggroup
add_wave /apatb_foo_top/AESL_inst_foo/ap_done -into $blocksiggroup
add_wave /apatb_foo_top/AESL_inst_foo/ap_idle -into $blocksiggroup
add_wave /apatb_foo_top/AESL_inst_foo/ap_ready -into $blocksiggroup
set resetgroup [add_wave_group "Reset" -into $designtopgroup]
add_wave /apatb_foo_top/AESL_inst_foo/ap_rst -into $resetgroup
set clockgroup [add_wave_group "Clock" -into $designtopgroup]
add_wave /apatb_foo_top/AESL_inst_foo/ap_clk -into $clockgroup
set testbenchgroup [add_wave_group "Test Bench Signals"]
set tbinternalsiggroup [add_wave_group "Internal Signals" -into $testbenchgroup]
set tb_simstatus_group [add_wave_group "Simulation Status" -into $tbinternalsiggroup]
set tb_portdepth_group [add_wave_group "Port Depth" -into $tbinternalsiggroup]
add_wave /apatb_foo_top/AUTOTB_TRANSACTION_NUM -into $tb_simstatus_group -radix hex
add_wave /apatb_foo_top/ready_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_foo_top/done_cnt -into $tb_simstatus_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_d_group [add_wave_group d(bus) -into $tbcinputgroup]
add_wave /apatb_foo_top/d_size -into $tb_d_group -radix hex
add_wave /apatb_foo_top/d_dataout -into $tb_d_group -radix hex
add_wave /apatb_foo_top/d_datain -into $tb_d_group -radix hex
add_wave /apatb_foo_top/d_address -into $tb_d_group -radix hex
add_wave /apatb_foo_top/d_rsp_read -into $tb_d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_rsp_empty_n -into $tb_d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_req_write -into $tb_d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_req_full_n -into $tb_d_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_req_din -into $tb_d_group -radix hex
save_wave_config foo.wcfg
run all
quit

