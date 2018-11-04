--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: J.40
--  \   \         Application: netgen
--  /   /         Filename: as4_timesim.vhd
-- /___/   /\     Timestamp: Sun Mar 11 15:02:46 2018
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -s 4 -pcf as4.pcf -rpw 100 -tpw 0 -ar Structure -tm as4 -insert_pp_buffers false -w -dir netgen/par -ofmt vhdl -sim as4.ncd as4_timesim.vhd 
-- Device	: 3s400ft256-4 (PRODUCTION 1.39 2007-10-19)
-- Input file	: as4.ncd
-- Output file	: H:\LAB4\as4\netgen\par\as4_timesim.vhd
-- # of Entities	: 1
-- Design Name	: as4
-- Xilinx	: C:\Xilinx92i
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Development System Reference Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library SIMPRIM;
use SIMPRIM.VCOMPONENTS.ALL;
use SIMPRIM.VPACKAGE.ALL;

entity as4 is
  port (
    S1A0 : in STD_LOGIC := 'X'; 
    C0 : out STD_LOGIC; 
    R : out STD_LOGIC_VECTOR ( 3 downto 0 ); 
    A : in STD_LOGIC_VECTOR ( 3 downto 0 ); 
    B : in STD_LOGIC_VECTOR ( 3 downto 0 ) 
  );
end as4;

architecture Structure of as4 is
  signal A_0_IBUF_0 : STD_LOGIC; 
  signal A_1_IBUF_1 : STD_LOGIC; 
  signal A_2_IBUF_2 : STD_LOGIC; 
  signal A_3_IBUF_3 : STD_LOGIC; 
  signal B_0_IBUF_4 : STD_LOGIC; 
  signal B_1_IBUF_5 : STD_LOGIC; 
  signal B_2_IBUF_6 : STD_LOGIC; 
  signal B_3_IBUF_7 : STD_LOGIC; 
  signal S1A0_IBUF_8 : STD_LOGIC; 
  signal XLXI_9_XLXN_6 : STD_LOGIC; 
  signal XLXI_9_XLXN_1 : STD_LOGIC; 
  signal XLXI_9_XLXN_3_0 : STD_LOGIC; 
  signal A_0_INBUF : STD_LOGIC; 
  signal A_1_INBUF : STD_LOGIC; 
  signal A_2_INBUF : STD_LOGIC; 
  signal A_3_INBUF : STD_LOGIC; 
  signal B_0_INBUF : STD_LOGIC; 
  signal B_1_INBUF : STD_LOGIC; 
  signal B_2_INBUF : STD_LOGIC; 
  signal B_3_INBUF : STD_LOGIC; 
  signal S1A0_INBUF : STD_LOGIC; 
  signal R_0_O : STD_LOGIC; 
  signal R_1_O : STD_LOGIC; 
  signal R_2_O : STD_LOGIC; 
  signal R_3_O : STD_LOGIC; 
  signal C0_O : STD_LOGIC; 
  signal R_1_OBUF_9 : STD_LOGIC; 
  signal C0_OBUF_10 : STD_LOGIC; 
  signal R_2_OBUF_11 : STD_LOGIC; 
  signal R_3_OBUF_12 : STD_LOGIC; 
  signal XLXI_9_XLXN_1_pack_1 : STD_LOGIC; 
  signal R_0_OBUF_13 : STD_LOGIC; 
  signal XLXI_9_XLXN_3 : STD_LOGIC; 
  signal XLXI_9_XLXN_6_pack_1 : STD_LOGIC; 
  signal VCC : STD_LOGIC; 
begin
  A_0_IBUF : X_BUF
    generic map(
      LOC => "PAD83",
      PATHPULSE => 757 ps
    )
    port map (
      I => A(0),
      O => A_0_INBUF
    );
  A_0_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD83",
      PATHPULSE => 757 ps
    )
    port map (
      I => A_0_INBUF,
      O => A_0_IBUF_0
    );
  A_1_IBUF : X_BUF
    generic map(
      LOC => "PAD87",
      PATHPULSE => 757 ps
    )
    port map (
      I => A(1),
      O => A_1_INBUF
    );
  A_1_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD87",
      PATHPULSE => 757 ps
    )
    port map (
      I => A_1_INBUF,
      O => A_1_IBUF_1
    );
  A_2_IBUF : X_BUF
    generic map(
      LOC => "PAD100",
      PATHPULSE => 757 ps
    )
    port map (
      I => A(2),
      O => A_2_INBUF
    );
  A_2_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD100",
      PATHPULSE => 757 ps
    )
    port map (
      I => A_2_INBUF,
      O => A_2_IBUF_2
    );
  A_3_IBUF : X_BUF
    generic map(
      LOC => "PAD99",
      PATHPULSE => 757 ps
    )
    port map (
      I => A(3),
      O => A_3_INBUF
    );
  A_3_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD99",
      PATHPULSE => 757 ps
    )
    port map (
      I => A_3_INBUF,
      O => A_3_IBUF_3
    );
  B_0_IBUF : X_BUF
    generic map(
      LOC => "PAD105",
      PATHPULSE => 757 ps
    )
    port map (
      I => B(0),
      O => B_0_INBUF
    );
  B_0_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD105",
      PATHPULSE => 757 ps
    )
    port map (
      I => B_0_INBUF,
      O => B_0_IBUF_4
    );
  B_1_IBUF : X_BUF
    generic map(
      LOC => "PAD106",
      PATHPULSE => 757 ps
    )
    port map (
      I => B(1),
      O => B_1_INBUF
    );
  B_1_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD106",
      PATHPULSE => 757 ps
    )
    port map (
      I => B_1_INBUF,
      O => B_1_IBUF_5
    );
  B_2_IBUF : X_BUF
    generic map(
      LOC => "PAD115",
      PATHPULSE => 757 ps
    )
    port map (
      I => B(2),
      O => B_2_INBUF
    );
  B_2_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD115",
      PATHPULSE => 757 ps
    )
    port map (
      I => B_2_INBUF,
      O => B_2_IBUF_6
    );
  B_3_IBUF : X_BUF
    generic map(
      LOC => "PAD116",
      PATHPULSE => 757 ps
    )
    port map (
      I => B(3),
      O => B_3_INBUF
    );
  B_3_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD116",
      PATHPULSE => 757 ps
    )
    port map (
      I => B_3_INBUF,
      O => B_3_IBUF_7
    );
  S1A0_IBUF : X_BUF
    generic map(
      LOC => "PAD104",
      PATHPULSE => 757 ps
    )
    port map (
      I => S1A0,
      O => S1A0_INBUF
    );
  S1A0_IFF_IMUX : X_BUF
    generic map(
      LOC => "PAD104",
      PATHPULSE => 757 ps
    )
    port map (
      I => S1A0_INBUF,
      O => S1A0_IBUF_8
    );
  R_0_OBUF : X_OBUF
    generic map(
      LOC => "PAD117"
    )
    port map (
      I => R_0_O,
      O => R(0)
    );
  R_1_OBUF : X_OBUF
    generic map(
      LOC => "PAD130"
    )
    port map (
      I => R_1_O,
      O => R(1)
    );
  R_2_OBUF : X_OBUF
    generic map(
      LOC => "PAD118"
    )
    port map (
      I => R_2_O,
      O => R(2)
    );
  R_3_OBUF : X_OBUF
    generic map(
      LOC => "PAD126"
    )
    port map (
      I => R_3_O,
      O => R(3)
    );
  C0_OBUF : X_OBUF
    generic map(
      LOC => "PAD135"
    )
    port map (
      I => C0_O,
      O => C0
    );
  XLXI_9_XLXI_1_XLXI_5 : X_LUT4
    generic map(
      INIT => X"8EE8",
      LOC => "SLICE_X55Y22"
    )
    port map (
      ADR0 => A_3_IBUF_3,
      ADR1 => XLXI_9_XLXN_1,
      ADR2 => B_3_IBUF_7,
      ADR3 => S1A0_IBUF_8,
      O => C0_OBUF_10
    );
  XLXI_9_XLXI_2_XLXI_1 : X_LUT4
    generic map(
      INIT => X"6996",
      LOC => "SLICE_X54Y22"
    )
    port map (
      ADR0 => S1A0_IBUF_8,
      ADR1 => XLXI_9_XLXN_3_0,
      ADR2 => B_2_IBUF_6,
      ADR3 => A_2_IBUF_2,
      O => R_2_OBUF_11
    );
  R_3_OBUF_YUSED : X_BUF
    generic map(
      LOC => "SLICE_X54Y23",
      PATHPULSE => 757 ps
    )
    port map (
      I => XLXI_9_XLXN_1_pack_1,
      O => XLXI_9_XLXN_1
    );
  XLXI_9_XLXI_2_XLXI_5 : X_LUT4
    generic map(
      INIT => X"DE48",
      LOC => "SLICE_X54Y23"
    )
    port map (
      ADR0 => S1A0_IBUF_8,
      ADR1 => XLXI_9_XLXN_3_0,
      ADR2 => B_2_IBUF_6,
      ADR3 => A_2_IBUF_2,
      O => XLXI_9_XLXN_1_pack_1
    );
  XLXI_9_XLXI_4_XLXI_1 : X_LUT4
    generic map(
      INIT => X"3C3C",
      LOC => "SLICE_X54Y28"
    )
    port map (
      ADR0 => VCC,
      ADR1 => B_0_IBUF_4,
      ADR2 => A_0_IBUF_0,
      ADR3 => VCC,
      O => R_0_OBUF_13
    );
  XLXI_9_XLXN_3_XUSED : X_BUF
    generic map(
      LOC => "SLICE_X55Y29",
      PATHPULSE => 757 ps
    )
    port map (
      I => XLXI_9_XLXN_3,
      O => XLXI_9_XLXN_3_0
    );
  XLXI_9_XLXN_3_YUSED : X_BUF
    generic map(
      LOC => "SLICE_X55Y29",
      PATHPULSE => 757 ps
    )
    port map (
      I => XLXI_9_XLXN_6_pack_1,
      O => XLXI_9_XLXN_6
    );
  XLXI_9_XLXI_4_XLXI_5 : X_LUT4
    generic map(
      INIT => X"CFC0",
      LOC => "SLICE_X55Y29"
    )
    port map (
      ADR0 => VCC,
      ADR1 => A_0_IBUF_0,
      ADR2 => B_0_IBUF_4,
      ADR3 => S1A0_IBUF_8,
      O => XLXI_9_XLXN_6_pack_1
    );
  XLXI_9_XLXI_3_XLXI_1 : X_LUT4
    generic map(
      INIT => X"6996",
      LOC => "SLICE_X55Y22"
    )
    port map (
      ADR0 => S1A0_IBUF_8,
      ADR1 => XLXI_9_XLXN_6,
      ADR2 => A_1_IBUF_1,
      ADR3 => B_1_IBUF_5,
      O => R_1_OBUF_9
    );
  XLXI_9_XLXI_1_XLXI_1 : X_LUT4
    generic map(
      INIT => X"6996",
      LOC => "SLICE_X54Y23"
    )
    port map (
      ADR0 => S1A0_IBUF_8,
      ADR1 => B_3_IBUF_7,
      ADR2 => XLXI_9_XLXN_1,
      ADR3 => A_3_IBUF_3,
      O => R_3_OBUF_12
    );
  XLXI_9_XLXI_3_XLXI_5 : X_LUT4
    generic map(
      INIT => X"BE28",
      LOC => "SLICE_X55Y29"
    )
    port map (
      ADR0 => A_1_IBUF_1,
      ADR1 => S1A0_IBUF_8,
      ADR2 => B_1_IBUF_5,
      ADR3 => XLXI_9_XLXN_6,
      O => XLXI_9_XLXN_3
    );
  R_0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD117",
      PATHPULSE => 757 ps
    )
    port map (
      I => R_0_OBUF_13,
      O => R_0_O
    );
  R_1_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD130",
      PATHPULSE => 757 ps
    )
    port map (
      I => R_1_OBUF_9,
      O => R_1_O
    );
  R_2_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD118",
      PATHPULSE => 757 ps
    )
    port map (
      I => R_2_OBUF_11,
      O => R_2_O
    );
  R_3_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD126",
      PATHPULSE => 757 ps
    )
    port map (
      I => R_3_OBUF_12,
      O => R_3_O
    );
  C0_OUTPUT_OFF_OMUX : X_BUF
    generic map(
      LOC => "PAD135",
      PATHPULSE => 757 ps
    )
    port map (
      I => C0_OBUF_10,
      O => C0_O
    );
  NlwBlock_as4_VCC : X_ONE
    port map (
      O => VCC
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => GSR);
  NlwBlockTOC : X_TOC
    port map (O => GTS);

end Structure;

