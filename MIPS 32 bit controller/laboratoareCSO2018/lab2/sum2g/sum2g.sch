VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL B1
        SIGNAL A1
        SIGNAL S1
        SIGNAL XLXN_12
        SIGNAL XLXN_13
        SIGNAL XLXN_14
        SIGNAL XLXN_16
        SIGNAL XLXN_17
        SIGNAL XLXN_18
        SIGNAL Cout
        SIGNAL S0
        SIGNAL B0
        SIGNAL A0
        SIGNAL Cin
        SIGNAL XLXN_25
        SIGNAL XLXN_26
        SIGNAL XLXN_27
        SIGNAL XLXN_28
        SIGNAL XLXN_30
        PORT Input B1
        PORT Input A1
        PORT Output S1
        PORT Output Cout
        PORT Output S0
        PORT Input B0
        PORT Input A0
        PORT Input Cin
        BEGIN BLOCKDEF xor3
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 48 -64 
            LINE N 0 -128 72 -128 
            LINE N 0 -192 48 -192 
            LINE N 256 -128 208 -128 
            ARC N -40 -184 72 -72 48 -80 48 -176 
            ARC N -24 -184 88 -72 64 -80 64 -176 
            ARC N 44 -176 220 0 208 -128 128 -176 
            LINE N 48 -64 48 -80 
            LINE N 48 -192 48 -176 
            LINE N 128 -80 64 -80 
            LINE N 128 -176 64 -176 
            ARC N 44 -256 220 -80 128 -80 208 -128 
        END BLOCKDEF
        BEGIN BLOCKDEF and2
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 64 -64 
            LINE N 0 -128 64 -128 
            LINE N 256 -96 192 -96 
            ARC N 96 -144 192 -48 144 -48 144 -144 
            LINE N 144 -48 64 -48 
            LINE N 64 -144 144 -144 
            LINE N 64 -48 64 -144 
        END BLOCKDEF
        BEGIN BLOCKDEF or3
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -64 48 -64 
            LINE N 0 -128 72 -128 
            LINE N 0 -192 48 -192 
            LINE N 256 -128 192 -128 
            ARC N 28 -256 204 -80 112 -80 192 -128 
            ARC N -40 -184 72 -72 48 -80 48 -176 
            LINE N 48 -64 48 -80 
            LINE N 48 -192 48 -176 
            LINE N 112 -80 48 -80 
            ARC N 28 -176 204 0 192 -128 112 -176 
            LINE N 112 -176 48 -176 
        END BLOCKDEF
        BEGIN BLOCK XLXI_2 xor3
            PIN I0 B0
            PIN I1 A0
            PIN I2 Cin
            PIN O S0
        END BLOCK
        BEGIN BLOCK XLXI_3 and2
            PIN I0 A1
            PIN I1 B1
            PIN O XLXN_13
        END BLOCK
        BEGIN BLOCK XLXI_9 or3
            PIN I0 XLXN_13
            PIN I1 XLXN_12
            PIN I2 XLXN_14
            PIN O Cout
        END BLOCK
        BEGIN BLOCK XLXI_10 or3
            PIN I0 XLXN_26
            PIN I1 XLXN_16
            PIN I2 XLXN_17
            PIN O XLXN_30
        END BLOCK
        BEGIN BLOCK XLXI_11 xor3
            PIN I0 B1
            PIN I1 A1
            PIN I2 XLXN_30
            PIN O S1
        END BLOCK
        BEGIN BLOCK XLXI_12 and2
            PIN I0 A1
            PIN I1 XLXN_30
            PIN O XLXN_12
        END BLOCK
        BEGIN BLOCK XLXI_13 and2
            PIN I0 B1
            PIN I1 XLXN_30
            PIN O XLXN_14
        END BLOCK
        BEGIN BLOCK XLXI_14 and2
            PIN I0 A0
            PIN I1 B0
            PIN O XLXN_26
        END BLOCK
        BEGIN BLOCK XLXI_15 and2
            PIN I0 A0
            PIN I1 Cin
            PIN O XLXN_16
        END BLOCK
        BEGIN BLOCK XLXI_16 and2
            PIN I0 B0
            PIN I1 Cin
            PIN O XLXN_17
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_12 1520 832 R180
        INSTANCE XLXI_3 1536 608 R180
        INSTANCE XLXI_13 1520 1104 R180
        INSTANCE XLXI_14 1504 1904 R180
        INSTANCE XLXI_15 1504 2160 R180
        INSTANCE XLXI_16 1504 2384 R180
        INSTANCE XLXI_11 1056 352 R180
        INSTANCE XLXI_10 576 2112 R180
        INSTANCE XLXI_9 656 848 R180
        BEGIN BRANCH B1
            WIRE 1056 416 1264 416
        END BRANCH
        BEGIN BRANCH A1
            WIRE 1056 480 1264 480
        END BRANCH
        BEGIN BRANCH S1
            WIRE 576 480 800 480
        END BRANCH
        BEGIN BRANCH XLXN_12
            WIRE 656 976 960 976
            WIRE 960 928 960 976
            WIRE 960 928 1264 928
        END BRANCH
        BEGIN BRANCH XLXN_13
            WIRE 656 704 1280 704
            WIRE 656 704 656 912
        END BRANCH
        BEGIN BRANCH XLXN_14
            WIRE 656 1040 656 1200
            WIRE 656 1200 1264 1200
        END BRANCH
        BEGIN BRANCH XLXN_16
            WIRE 576 2240 912 2240
            WIRE 912 2240 912 2256
            WIRE 912 2256 1248 2256
        END BRANCH
        BEGIN BRANCH XLXN_17
            WIRE 576 2304 576 2480
            WIRE 576 2480 1248 2480
        END BRANCH
        INSTANCE XLXI_2 1072 1600 R180
        BEGIN BRANCH Cout
            WIRE 240 976 400 976
        END BRANCH
        IOMARKER 576 480 S1 R180 28
        IOMARKER 1264 416 B1 R0 28
        IOMARKER 1264 480 A1 R0 28
        IOMARKER 240 976 Cout R180 28
        BEGIN BRANCH S0
            WIRE 784 1728 816 1728
        END BRANCH
        IOMARKER 784 1728 S0 R180 28
        BEGIN BRANCH B0
            WIRE 1072 1664 1104 1664
        END BRANCH
        IOMARKER 1104 1664 B0 R0 28
        BEGIN BRANCH A0
            WIRE 1072 1728 1104 1728
        END BRANCH
        IOMARKER 1104 1728 A0 R0 28
        BEGIN BRANCH Cin
            WIRE 1072 1792 1712 1792
            WIRE 1712 1792 1712 2288
            WIRE 1712 2288 1712 2512
            WIRE 1504 2288 1712 2288
            WIRE 1504 2512 1680 2512
            WIRE 1680 2512 1680 2640
            WIRE 1680 2512 1712 2512
        END BRANCH
        IOMARKER 1680 2640 Cin R90 28
        BEGIN BRANCH XLXN_26
            WIRE 576 2000 1248 2000
            WIRE 576 2000 576 2176
        END BRANCH
        BEGIN BRANCH XLXN_30
            WIRE 304 1424 320 1424
            WIRE 320 1424 1728 1424
            WIRE 304 1424 304 2240
            WIRE 304 2240 320 2240
            WIRE 1056 544 1728 544
            WIRE 1728 544 1728 576
            WIRE 1728 576 1728 960
            WIRE 1728 960 1728 1232
            WIRE 1728 1232 1728 1424
            WIRE 1520 960 1728 960
            WIRE 1520 1232 1728 1232
        END BRANCH
        BEGIN BRANCH A0
            WIRE 1504 1968 1536 1968
            WIRE 1536 1968 1584 1968
            BEGIN DISPLAY 1536 1968 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B0
            WIRE 1504 2032 1552 2032
            WIRE 1552 2032 1584 2032
            BEGIN DISPLAY 1552 2032 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH A0
            WIRE 1504 2224 1536 2224
            WIRE 1536 2224 1568 2224
            BEGIN DISPLAY 1536 2224 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B0
            WIRE 1504 2448 1584 2448
            WIRE 1584 2448 1600 2448
            BEGIN DISPLAY 1584 2448 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B1
            WIRE 1520 1168 1584 1168
            WIRE 1584 1168 1616 1168
            BEGIN DISPLAY 1584 1168 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH A1
            WIRE 1520 896 1584 896
            WIRE 1584 896 1632 896
            BEGIN DISPLAY 1584 896 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B1
            WIRE 1536 736 1616 736
            WIRE 1616 736 1632 736
            BEGIN DISPLAY 1616 736 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH A1
            WIRE 1536 672 1600 672
            WIRE 1600 672 1648 672
            BEGIN DISPLAY 1600 672 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
    END SHEET
END SCHEMATIC
