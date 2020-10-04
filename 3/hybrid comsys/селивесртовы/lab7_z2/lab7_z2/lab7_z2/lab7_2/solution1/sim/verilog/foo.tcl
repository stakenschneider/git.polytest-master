
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set out_group [add_wave_group out(memory) -into $coutputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/out_r_d0 -into $out_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/out_r_we0 -into $out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/out_r_ce0 -into $out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/out_r_address0 -into $out_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set in2_group [add_wave_group in2(memory) -into $cinputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/in2_q0 -into $in2_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/in2_ce0 -into $in2_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/in2_address0 -into $in2_group -radix hex
set in1_group [add_wave_group in1(memory) -into $cinputgroup]
add_wave /apatb_foo_top/AESL_inst_foo/in1_q0 -into $in1_group -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/in1_ce0 -into $in1_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/AESL_inst_foo/in1_address0 -into $in1_group -radix hex
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
add_wave /apatb_foo_top/LENGTH_in1 -into $tb_portdepth_group -radix hex
add_wave /apatb_foo_top/LENGTH_in2 -into $tb_portdepth_group -radix hex
add_wave /apatb_foo_top/LENGTH_out_r -into $tb_portdepth_group -radix hex
set tbcoutputgroup [add_wave_group "C Outputs" -into $testbenchgroup]
set tb_out_group [add_wave_group out(memory) -into $tbcoutputgroup]
add_wave /apatb_foo_top/out_r_d0 -into $tb_out_group -radix hex
add_wave /apatb_foo_top/out_r_we0 -into $tb_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/out_r_ce0 -into $tb_out_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/out_r_address0 -into $tb_out_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_in2_group [add_wave_group in2(memory) -into $tbcinputgroup]
add_wave /apatb_foo_top/in2_q0 -into $tb_in2_group -radix hex
add_wave /apatb_foo_top/in2_ce0 -into $tb_in2_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/in2_address0 -into $tb_in2_group -radix hex
set tb_in1_group [add_wave_group in1(memory) -into $tbcinputgroup]
add_wave /apatb_foo_top/in1_q0 -into $tb_in1_group -radix hex
add_wave /apatb_foo_top/in1_ce0 -into $tb_in1_group -color #ffff00 -radix hex
add_wave /apatb_foo_top/in1_address0 -into $tb_in1_group -radix hex
save_wave_config foo.wcfg
run all
quit

