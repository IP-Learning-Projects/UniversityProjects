--------------------------------------------------------------------------------
-- Copyright (c) 1995-2007 Xilinx, Inc.
-- All Right Reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 9.2.04i
--  \   \         Application : ISE
--  /   /         Filename : TBW.vhw
-- /___/   /\     Timestamp : Sun Mar 11 14:40:01 2018
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: 
--Design Name: TBW
--Device: Xilinx
--

library UNISIM;
use UNISIM.Vcomponents.ALL;
library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
USE IEEE.STD_LOGIC_TEXTIO.ALL;
USE IEEE.STD_LOGIC_ARITH.ALL;
USE IEEE.STD_LOGIC_UNSIGNED.ALL;
USE STD.TEXTIO.ALL;

ENTITY TBW IS
END TBW;

ARCHITECTURE testbench_arch OF TBW IS
    FILE RESULTS: TEXT OPEN WRITE_MODE IS "results.txt";

    COMPONENT as4
        PORT (
            A : In std_logic_vector (3 DownTo 0);
            B : In std_logic_vector (3 DownTo 0);
            S1A0 : In std_logic;
            C0 : Out std_logic;
            R : Out std_logic_vector (3 DownTo 0)
        );
    END COMPONENT;

    SIGNAL A : std_logic_vector (3 DownTo 0) := "0000";
    SIGNAL B : std_logic_vector (3 DownTo 0) := "0000";
    SIGNAL S1A0 : std_logic := '0';
    SIGNAL C0 : std_logic := '0';
    SIGNAL R : std_logic_vector (3 DownTo 0) := "0000";

    BEGIN
        UUT : as4
        PORT MAP (
            A => A,
            B => B,
            S1A0 => S1A0,
            C0 => C0,
            R => R
        );

        PROCESS
            BEGIN
                -- -------------  Current Time:  100ns
                WAIT FOR 100 ns;
                A <= "0101";
                B <= "0010";
                -- -------------------------------------
                -- -------------  Current Time:  200ns
                WAIT FOR 100 ns;
                A <= "1011";
                -- -------------------------------------
                -- -------------  Current Time:  300ns
                WAIT FOR 100 ns;
                A <= "0101";
                B <= "1110";
                -- -------------------------------------
                -- -------------  Current Time:  400ns
                WAIT FOR 100 ns;
                A <= "1011";
                -- -------------------------------------
                -- -------------  Current Time:  500ns
                WAIT FOR 100 ns;
                S1A0 <= '1';
                A <= "0101";
                B <= "0010";
                -- -------------------------------------
                -- -------------  Current Time:  600ns
                WAIT FOR 100 ns;
                A <= "1011";
                -- -------------------------------------
                -- -------------  Current Time:  700ns
                WAIT FOR 100 ns;
                A <= "0101";
                B <= "1110";
                -- -------------------------------------
                -- -------------  Current Time:  800ns
                WAIT FOR 100 ns;
                A <= "1011";
                -- -------------------------------------
                WAIT FOR 200 ns;

            END PROCESS;

    END testbench_arch;

