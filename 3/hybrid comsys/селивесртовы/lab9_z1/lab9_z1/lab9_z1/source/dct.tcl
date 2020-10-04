# Insert the command to create new project
open_project -reset dct_prj
# Insert the command to specify the top-level function
set_top dct
# Insert the command to add design file named dct.c
add_files dct.c
# Insert the command to add testbench files named dct_test.c, in.dat and out.golden.dat
add_files -tb dct_test.c
add_files -tb in.dat
add_files -tb out.golden.dat
# Insert the command to create the solution named solution1 
open_solution solution1 -reset
# Insert the command to associate xczu7ev-ffvc1156-2-e device to the solution1
set_part {xczu7ev-ffvc1156-2-e}
# Insert the command to associate clock with 10ns period to the solution1
create_clock -period 10ns
# Insert the comamnd to run C simulaiton

# Insert the comamnd to Synthesize the design

# Insert the comamnd to perform C/RTL Cosimmulation 

# Insert the comamnd to Export RTL as IP 