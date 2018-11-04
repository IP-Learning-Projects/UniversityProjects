--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 9.2.04i
--  \   \         Application : sch2vhdl
--  /   /         Filename : sum4.vhf
-- /___/   /\     Timestamp : 03/03/2018 13:18:57
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx92i\bin\nt\sch2vhdl.exe -intstyle ise -family spartan3 -flat -suppress -w C:/Users/GabrielaD/Desktop/automatica/labCSO/lab3/as4/sum4.sch sum4.vhf
--Design Name: sum4
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

entity sum4 is
   port ( a  : in    std_logic_vector (3 downto 0); 
          b  : in    std_logic_vector (3 downto 0); 
          C0 : out   std_logic; 
          r  : out   std_logic_vector (3 downto 0));
end sum4;

architecture BEHAVIORAL of sum4 is
   attribute BOX_TYPE   : string ;
   signal XLXN_1 : std_logic;
   signal XLXN_3 : std_logic;
   signal XLXN_6 : std_logic;
   signal XLXN_7 : std_logic;
   component sum1g
      port ( Ci : in    std_logic; 
             Co : out   std_logic; 
             S  : out   std_logic; 
             B  : in    std_logic; 
             A  : in    std_logic);
   end component;
   
   component GND
      port ( G : out   std_logic);
   end component;
   attribute BOX_TYPE of GND : component is "BLACK_BOX";
   
begin
   XLXI_1 : sum1g
      port map (A=>a(3),
                B=>b(3),
                Ci=>XLXN_1,
                Co=>C0,
                S=>r(3));
   
   XLXI_2 : sum1g
      port map (A=>a(2),
                B=>b(2),
                Ci=>XLXN_3,
                Co=>XLXN_1,
                S=>r(2));
   
   XLXI_3 : sum1g
      port map (A=>a(1),
                B=>b(1),
                Ci=>XLXN_6,
                Co=>XLXN_3,
                S=>r(1));
   
   XLXI_4 : sum1g
      port map (A=>a(0),
                B=>b(0),
                Ci=>XLXN_7,
                Co=>XLXN_6,
                S=>r(0));
   
   XLXI_5 : GND
      port map (G=>XLXN_7);
   
end BEHAVIORAL;


