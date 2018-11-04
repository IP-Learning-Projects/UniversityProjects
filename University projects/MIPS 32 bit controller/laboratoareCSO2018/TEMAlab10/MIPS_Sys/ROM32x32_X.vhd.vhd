
-- The following code must appear before the "begin" keyword in the architecture
-- body.

    
					----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    12:19:49 03/25/2018 
-- Design Name: 
-- Module Name:    ROM32x32 - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

---- Uncomment the following library declaration if instantiating
---- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity ROM32x32 is
    Port ( Addr : in  STD_LOGIC_VECTOR (4 downto 0);
           Data : out  STD_LOGIC_VECTOR (31 downto 0));
end ROM32x32;

architecture Behavioral of ROM32x32 is
-- The following code must appear before the "begin" keyword in the architecture
-- body.


   type tROM is array ( 0 to 31) of std_logic_vectoR(31 downto 0);
    constant ROM : tROM :=(
	x"8c020040", --0	rep: lw $2, 0x40($0)
	x"8c030044", --1  lw $3, 0x44($0)
	x"00432022", --2  sub $4, $2, $3
	x"10620001", --3  beq $3, $2, display
	x"00432020", --4  add $4, $2, $3
	x"ac040048", --5  display: sw $4 ,0x48($0)
	x"1000fff9", --6  beq $0, $0, rep
	x"00000000", --7  
	x"00000000", --8  
	x"00000000", --9  
	x"00000000", --10 
	x"00000000", --11 
	x"00000000", --12 
	x"00000000", --13 
	x"00000000", --14
	x"00000000", --15
	x"00000000", --16
	x"00000000", --17
	x"00000000", --18
	x"00000000", --19
	x"00000000", --20
	x"00000000", --21
	x"00000000", --22
	x"00000000", --23
	x"00000000", --24
	x"00000000", --25
	x"00000000", --26
	x"00000000", --27
	x"00000000", --28
	x"00000000", --29
	x"00000000", --30
	x"00000000"  --31

	
	
	);



begin

Data <= ROM(conv_integer(Addr));

end Behavioral;

