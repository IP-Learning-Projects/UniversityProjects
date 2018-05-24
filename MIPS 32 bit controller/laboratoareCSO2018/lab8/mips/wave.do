onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/clk
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/pc
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/instr
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_regs/rdreg1
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/rddata1
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_regs/rdreg2
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/rddata2
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_alu/seaddr
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/u_alu/alusrc
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_alu/aluop
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/alu_out
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/memwr
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/regwr
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/mem2reg
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/wrdata
add wave -noupdate -format Logic -radix hexadecimal /tb_mips/uut/regdest
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_regs/wrreg
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/inw0
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/inw1
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/outw0
add wave -noupdate -format Literal -radix hexadecimal /tb_mips/uut/u_regs/s32regs32
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {100911 ps} 0}
configure wave -namecolwidth 188
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
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {525 ns}
