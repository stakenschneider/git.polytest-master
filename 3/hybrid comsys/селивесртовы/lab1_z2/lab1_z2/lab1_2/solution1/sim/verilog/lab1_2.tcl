
log_wave -r /
set designtopgroup [add_wave_group "Design Top Signals"]
set coutputgroup [add_wave_group "C Outputs" -into $designtopgroup]
set out_group [add_wave_group out(memory) -into $coutputgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/out_r_d0 -into $out_group -radix hex
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/out_r_we0 -into $out_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/out_r_ce0 -into $out_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/out_r_address0 -into $out_group -radix hex
set cinputgroup [add_wave_group "C Inputs" -into $designtopgroup]
set c_group [add_wave_group c(wire) -into $cinputgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/c -into $c_group -radix hex
set b_group [add_wave_group b(wire) -into $cinputgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/b -into $b_group -radix hex
set a_group [add_wave_group a(wire) -into $cinputgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/a -into $a_group -radix hex
set in_group [add_wave_group in(memory) -into $cinputgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/in_r_q0 -into $in_group -radix hex
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/in_r_ce0 -into $in_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/in_r_address0 -into $in_group -radix hex
set blocksiggroup [add_wave_group "Block-level IO Handshake" -into $designtopgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_start -into $blocksiggroup
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_done -into $blocksiggroup
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_idle -into $blocksiggroup
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_ready -into $blocksiggroup
set resetgroup [add_wave_group "Reset" -into $designtopgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_rst -into $resetgroup
set clockgroup [add_wave_group "Clock" -into $designtopgroup]
add_wave /apatb_lab1_2_top/AESL_inst_lab1_2/ap_clk -into $clockgroup
set testbenchgroup [add_wave_group "Test Bench Signals"]
set tbinternalsiggroup [add_wave_group "Internal Signals" -into $testbenchgroup]
set tb_simstatus_group [add_wave_group "Simulation Status" -into $tbinternalsiggroup]
set tb_portdepth_group [add_wave_group "Port Depth" -into $tbinternalsiggroup]
add_wave /apatb_lab1_2_top/AUTOTB_TRANSACTION_NUM -into $tb_simstatus_group -radix hex
add_wave /apatb_lab1_2_top/ready_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_lab1_2_top/done_cnt -into $tb_simstatus_group -radix hex
add_wave /apatb_lab1_2_top/LENGTH_in_r -into $tb_portdepth_group -radix hex
add_wave /apatb_lab1_2_top/LENGTH_a -into $tb_portdepth_group -radix hex
add_wave /apatb_lab1_2_top/LENGTH_b -into $tb_portdepth_group -radix hex
add_wave /apatb_lab1_2_top/LENGTH_c -into $tb_portdepth_group -radix hex
add_wave /apatb_lab1_2_top/LENGTH_out_r -into $tb_portdepth_group -radix hex
set tbcoutputgroup [add_wave_group "C Outputs" -into $testbenchgroup]
set tb_out_group [add_wave_group out(memory) -into $tbcoutputgroup]
add_wave /apatb_lab1_2_top/out_r_d0 -into $tb_out_group -radix hex
add_wave /apatb_lab1_2_top/out_r_we0 -into $tb_out_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/out_r_ce0 -into $tb_out_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/out_r_address0 -into $tb_out_group -radix hex
set tbcinputgroup [add_wave_group "C Inputs" -into $testbenchgroup]
set tb_c_group [add_wave_group c(wire) -into $tbcinputgroup]
add_wave /apatb_lab1_2_top/c -into $tb_c_group -radix hex
set tb_b_group [add_wave_group b(wire) -into $tbcinputgroup]
add_wave /apatb_lab1_2_top/b -into $tb_b_group -radix hex
set tb_a_group [add_wave_group a(wire) -into $tbcinputgroup]
add_wave /apatb_lab1_2_top/a -into $tb_a_group -radix hex
set tb_in_group [add_wave_group in(memory) -into $tbcinputgroup]
add_wave /apatb_lab1_2_top/in_r_q0 -into $tb_in_group -radix hex
add_wave /apatb_lab1_2_top/in_r_ce0 -into $tb_in_group -color #ffff00 -radix hex
add_wave /apatb_lab1_2_top/in_r_address0 -into $tb_in_group -radix hex
save_wave_config lab1_2.wcfg
run all
quit

