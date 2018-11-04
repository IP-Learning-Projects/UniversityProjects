--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 9.2.04i
--  \   \         Application : sch2vhdl
--  /   /         Filename : root.vhf
-- /___/   /\     Timestamp : 03/20/2018 18:30:53
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx92i\bin\nt\sch2vhdl.exe -intstyle ise -family spartan3 -flat -suppress -w C:/Users/GabrielaD/Desktop/automatica/labCSO/lab5/AddSum4V/root.sch root.vhf
--Design Name: root
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

entity root is
   port ( A    : in    std_logic_vector (3 downto 0); 
          B    : in    std_logic_vector (3 downto 0); 
          S1A0 : in    std_logic; 
          R    : out   std_logic_vector (3 downto 0));
end root;

architecture BEHAVIORAL of root is
   component as4v
      port ( S1A0 : in    std_logic; 
             A    : in    std_logic_vector (3 downto 0); 
             B    : in    std_logic_vector (3 downto 0); 
             R    : out   std_logic_vector (3 downto 0));
   end component;
   
begin
   XLXI_1 : as4v
      port map (A(3 downto 0)=>A(3 downto 0),
                B(3 downto 0)=>B(3 downto 0),
                S1A0=>S1A0,
                R(3 downto 0)=>R(3 downto 0));
   
end BEHAVIORAL;


