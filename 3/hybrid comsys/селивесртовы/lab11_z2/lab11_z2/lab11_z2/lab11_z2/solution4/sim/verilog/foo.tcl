
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set d_out_group [add_wave_group d_out(memory) -into $coutputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/d_out_d0 -into $d_out_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_out_we0 -into $d_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_out_ce0 -into $d_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_out_address0 -into $d_out_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set d_in_group [add_wave_group d_in(memory) -into $cinputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/d_in_q0 -into $d_in_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_in_ce0 -into $d_in_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/d_in_address0 -into $d_in_group -radix hex
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
add_wave /apatb_foo_top/LENGTH_d_in -into $tb_portdepth_group -radix hex
add_wave /apatb_foo_top/LENGTH_d_out -into $tb_portdepth_group -radix hex
set tbcoutputgroup [add_wave_group "C Outputs" -into $testbenchgroup]
set tb_d_out_group [add_wave_group d_out(memory) -into $tbcoutputgroup]
add_wave /apatb_foo_top/d_out_d0 -into $tb_d_out_group -radix hex
add_wave /apatb_foo_top/d_out_we0 -into $tb_d_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_out_ce0 -into $tb_d_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_out_address0 -into $tb_d_out_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_d_in_group [add_wave_group d_in(memory) -into $tbcinputgroup]
add_wave /apatb_foo_top/d_in_q0 -into $tb_d_in_group -radix hex
add_wave /apatb_foo_top/d_in_ce0 -into $tb_d_in_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/d_in_address0 -into $tb_d_in_group -radix hex
save_wave_config foo.wcfg
run all
quit

