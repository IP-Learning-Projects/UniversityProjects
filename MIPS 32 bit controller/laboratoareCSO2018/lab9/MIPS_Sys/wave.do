onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic /tb_sys/btn0
add wave -noupdate -format Logic /tb_sys/clk
add wave -noupdate -format Literal -radix hexadecimal /tb_sys/swa
add wave -noupdate -format Literal -radix hexadecimal /tb_sys/swb
add wave -noupdate -format Logic /tb_sys/a
add wave -noupdate -format Literal -radix hexadecimal /tb_sys/an
add wave -noupdate -format Logic /tb_sys/b
add wave -noupdate -format Logic /tb_sys/c
add wave -noupdate -format Logic /tb_sys/d
add wave -noupdate -format Logic /tb_sys/e
add wave -noupdate -format Logic /tb_sys/f
add wave -noupdate -format Logic /tb_sys/g
add wave -noupdate -format Literal -radix hexadecimal /tb_sys/uut/outw
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {1050 ns}
