VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_2
        SIGNAL XLXN_4
        SIGNAL A
        SIGNAL B
        SIGNAL Ci
        SIGNAL Co
        SIGNAL XLXN_12
        SIGNAL XLXN_13
        SIGNAL XLXN_14
        SIGNAL S
        PORT Input A
        PORT Input B
        PORT Input Ci
        PORT Output Co
        PORT Output S
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
        BEGIN BLOCK XLXI_1 xor3
            PIN I0 Ci
            PIN I1 B
            PIN I2 A
            PIN O S
        END BLOCK
        BEGIN BLOCK XLXI_2 and2
            PIN I0 B
            PIN I1 A
            PIN O XLXN_14
        END BLOCK
        BEGIN BLOCK XLXI_3 and2
            PIN I0 Ci
            PIN I1 A
            PIN O XLXN_13
        END BLOCK
        BEGIN BLOCK XLXI_4 and2
            PIN I0 Ci
            PIN I1 B
            PIN O XLXN_12
        END BLOCK
        BEGIN BLOCK XLXI_5 or3
            PIN I0 XLXN_12
            PIN I1 XLXN_13
            PIN I2 XLXN_14
            PIN O Co
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 1232 800 R0
        INSTANCE XLXI_2 1232 1264 R0
        INSTANCE XLXI_3 1232 1600 R0
        INSTANCE XLXI_4 1232 1984 R0
        INSTANCE XLXI_5 2336 1424 R0
        BEGIN BRANCH A
            WIRE 848 608 1216 608
            WIRE 1216 608 1232 608
        END BRANCH
        BEGIN BRANCH B
            WIRE 864 672 1216 672
            WIRE 1216 672 1232 672
        END BRANCH
        BEGIN BRANCH Ci
            WIRE 864 736 1216 736
            WIRE 1216 736 1232 736
        END BRANCH
        BEGIN BRANCH Co
            WIRE 2592 1296 2624 1296
        END BRANCH
        IOMARKER 2624 1296 Co R0 28
        BEGIN BRANCH XLXN_12
            WIRE 1488 1888 2336 1888
            WIRE 2336 1360 2336 1888
        END BRANCH
        BEGIN BRANCH XLXN_13
            WIRE 1488 1504 1904 1504
            WIRE 1904 1296 1904 1504
            WIRE 1904 1296 2336 1296
        END BRANCH
        BEGIN BRANCH XLXN_14
            WIRE 1488 1168 2336 1168
            WIRE 2336 1168 2336 1232
        END BRANCH
        BEGIN BRANCH S
            WIRE 1488 672 1504 672
            WIRE 1504 672 2672 672
        END BRANCH
        BEGIN BRANCH A
            WIRE 1008 1136 1040 1136
            WIRE 1040 1136 1232 1136
            BEGIN DISPLAY 1008 1136 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B
            WIRE 1008 1200 1232 1200
            BEGIN DISPLAY 1008 1200 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH A
            WIRE 960 1472 1232 1472
            BEGIN DISPLAY 960 1472 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B
            WIRE 912 1856 1232 1856
            BEGIN DISPLAY 912 1856 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Ci
            WIRE 896 1920 1232 1920
            BEGIN DISPLAY 896 1920 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Ci
            WIRE 960 1536 1232 1536
            BEGIN DISPLAY 960 1536 ATTR Name
                ALIGNMENT SOFT-RIGHT
            END DISPLAY
        END BRANCH
        IOMARKER 864 736 Ci R180 28
        IOMARKER 864 672 B R180 28
        IOMARKER 2672 672 S R0 28
        IOMARKER 848 608 A R180 28
    END SHEET
END SCHEMATIC
