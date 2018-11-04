--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 9.2.04i
--  \   \         Application : sch2vhdl
--  /   /         Filename : sum2g.vhf
-- /___/   /\     Timestamp : 03/01/2018 09:07:44
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: C:\Xilinx92i\bin\nt\sch2vhdl.exe -intstyle ise -family spartan3 -flat -suppress -w D:/ce21b/sum2g/sum2g.sch sum2g.vhf
--Design Name: sum2g
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

entity sum2g is
   port ( A0   : in    std_logic; 
          A1   : in    std_logic; 
          B0   : in    std_logic; 
          B1   : in    std_logic; 
          Cin  : in    std_logic; 
          Cout : out   std_logic; 
          S0   : out   std_logic; 
          S1   : out   std_logic);
end sum2g;

architecture BEHAVIORAL of sum2g is
   attribute BOX_TYPE   : string ;
   signal XLXN_12 : std_logic;
   signal XLXN_13 : std_logic;
   signal XLXN_14 : std_logic;
   signal XLXN_16 : std_logic;
   signal XLXN_17 : std_logic;
   signal XLXN_26 : std_logic;
   signal XLXN_30 : std_logic;
   component XOR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of XOR3 : component is "BLACK_BOX";
   
   component AND2
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of AND2 : component is "BLACK_BOX";
   
   component OR3
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             O  : out   std_logic);
   end component;
   attribute BOX_TYPE of OR3 : component is "BLACK_BOX";
   
begin
   XLXI_2 : XOR3
      port map (I0=>B0,
                I1=>A0,
                I2=>Cin,
                O=>S0);
   
   XLXI_3 : AND2
      port map (I0=>A1,
                I1=>B1,
                O=>XLXN_13);
   
   XLXI_9 : OR3
      port map (I0=>XLXN_13,
                I1=>XLXN_12,
                I2=>XLXN_14,
                O=>Cout);
   
   XLXI_10 : OR3
      port map (I0=>XLXN_26,
                I1=>XLXN_16,
                I2=>XLXN_17,
                O=>XLXN_30);
   
   XLXI_11 : XOR3
      port map (I0=>B1,
                I1=>A1,
                I2=>XLXN_30,
                O=>S1);
   
   XLXI_12 : AND2
      port map (I0=>A1,
                I1=>XLXN_30,
                O=>XLXN_12);
   
   XLXI_13 : AND2
      port map (I0=>B1,
                I1=>XLXN_30,
                O=>XLXN_14);
   
   XLXI_14 : AND2
      port map (I0=>A0,
                I1=>B0,
                O=>XLXN_26);
   
   XLXI_15 : AND2
      port map (I0=>A0,
                I1=>Cin,
                O=>XLXN_16);
   
   XLXI_16 : AND2
      port map (I0=>B0,
                I1=>Cin,
                O=>XLXN_17);
   
end BEHAVIORAL;


