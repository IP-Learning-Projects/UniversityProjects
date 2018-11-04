--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 9.2.04i
--  \   \         Application : sch2vhdl
--  /   /         Filename : mips.vhf
-- /___/   /\     Timestamp : 03/25/2018 12:32:35
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx92i\bin\nt\sch2vhdl.exe -intstyle ise -family spartan3 -flat -suppress -w C:/Users/GabrielaD/Desktop/automatica/labCSO/lab6/mips/mips.sch mips.vhf
--Design Name: mips
--Device: spartan3
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesis and simulted, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity mips is
   port ( CLK : in    std_logic);
end mips;

architecture BEHAVIORAL of mips is
   signal Instr   : std_logic_vector (31 downto 0);
   signal New_PC  : std_logic_vector (31 downto 0);
   signal PC      : std_logic_vector (31 downto 0);
   signal RegDest : std_logic;
   signal WrReg   : std_logic_vector (4 downto 0);
   component MUX2V5
      port ( Sel : in    std_logic; 
             I0  : in    std_logic_vector (4 downto 0); 
             I1  : in    std_logic_vector (4 downto 0); 
             Y   : out   std_logic_vector (4 downto 0));
   end component;
   
   component PC_Update
      port ( PC     : in    std_logic_vector (31 downto 0); 
             New_PC : out   std_logic_vector (31 downto 0));
   end component;
   
   component ProgCnt
      port ( CLK    : in    std_logic; 
             New_PC : in    std_logic_vector (31 downto 0); 
             PC     : out   std_logic_vector (31 downto 0));
   end component;
   
   component ROM32x32
      port ( Addr : in    std_logic_vector (4 downto 0); 
             Data : out   std_logic_vector (31 downto 0));
   end component;
   
begin
   U_MUXRegD : MUX2V5
      port map (I0(4 downto 0)=>Instr(20 downto 16),
                I1(4 downto 0)=>Instr(15 downto 11),
                Sel=>RegDest,
                Y(4 downto 0)=>WrReg(4 downto 0));
   
   U_New_PC : PC_Update
      port map (PC(31 downto 0)=>PC(31 downto 0),
                New_PC(31 downto 0)=>New_PC(31 downto 0));
   
   U_PC : ProgCnt
      port map (CLK=>CLK,
                New_PC(31 downto 0)=>New_PC(31 downto 0),
                PC(31 downto 0)=>PC(31 downto 0));
   
   U_ROM : ROM32x32
      port map (Addr(4 downto 0)=>PC(6 downto 2),
                Data(31 downto 0)=>Instr(31 downto 0));
   
end BEHAVIORAL;


