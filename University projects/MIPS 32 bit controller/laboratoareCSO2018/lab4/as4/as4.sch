VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL NB(3)
        SIGNAL NB(2)
        SIGNAL NB(1)
        SIGNAL NB(0)
        SIGNAL B(3:0)
        SIGNAL B(3)
        SIGNAL B(1)
        SIGNAL B(0)
        SIGNAL B(2)
        SIGNAL S1A0
        SIGNAL NB(3:0)
        SIGNAL BNB(3:0)
        SIGNAL BNB(1)
        SIGNAL BNB(0)
        SIGNAL BNB(3)
        SIGNAL BNB(2)
        SIGNAL R(3:0)
        SIGNAL C0
        SIGNAL A(3:0)
        PORT Input B(3:0)
        PORT Input S1A0
        PORT Output R(3:0)
        PORT Output C0
        PORT Input A(3:0)
        BEGIN BLOCKDEF m2_1
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 96 -64 96 -192 
            LINE N 256 -96 96 -64 
            LINE N 256 -160 256 -96 
            LINE N 96 -192 256 -160 
            LINE N 176 -32 96 -32 
            LINE N 176 -80 176 -32 
            LINE N 0 -32 96 -32 
            LINE N 320 -128 256 -128 
            LINE N 0 -96 96 -96 
            LINE N 0 -160 96 -160 
        END BLOCKDEF
        BEGIN BLOCKDEF inv
            TIMESTAMP 2000 1 1 10 10 10
            LINE N 0 -32 64 -32 
            LINE N 224 -32 160 -32 
            LINE N 64 -64 128 -32 
            LINE N 128 -32 64 0 
            LINE N 64 0 64 -64 
            CIRCLE N 128 -48 160 -16 
        END BLOCKDEF
        BEGIN BLOCKDEF sum4
            TIMESTAMP 2018 3 11 11 42 41
            RECTANGLE N 64 -192 320 0 
            RECTANGLE N 0 -172 64 -148 
            LINE N 64 -160 0 -160 
            RECTANGLE N 0 -108 64 -84 
            LINE N 64 -96 0 -96 
            LINE N 64 -32 0 -32 
            RECTANGLE N 320 -172 384 -148 
            LINE N 320 -160 384 -160 
            LINE N 320 -32 384 -32 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 m2_1
            PIN D0 B(3)
            PIN D1 NB(3)
            PIN S0 S1A0
            PIN O BNB(3)
        END BLOCK
        BEGIN BLOCK XLXI_2 m2_1
            PIN D0 B(2)
            PIN D1 NB(2)
            PIN S0 S1A0
            PIN O BNB(2)
        END BLOCK
        BEGIN BLOCK XLXI_3 m2_1
            PIN D0 B(1)
            PIN D1 NB(1)
            PIN S0 S1A0
            PIN O BNB(1)
        END BLOCK
        BEGIN BLOCK XLXI_4 m2_1
            PIN D0 B(0)
            PIN D1 NB(0)
            PIN S0 S1A0
            PIN O BNB(0)
        END BLOCK
        BEGIN BLOCK XLXI_5 inv
            PIN I B(3)
            PIN O NB(3)
        END BLOCK
        BEGIN BLOCK XLXI_6 inv
            PIN I B(2)
            PIN O NB(2)
        END BLOCK
        BEGIN BLOCK XLXI_7 inv
            PIN I B(1)
            PIN O NB(1)
        END BLOCK
        BEGIN BLOCK XLXI_8 inv
            PIN I B(0)
            PIN O NB(0)
        END BLOCK
        BEGIN BLOCK XLXI_9 sum4
            PIN a(3:0) A(3:0)
            PIN b(3:0) BNB(3:0)
            PIN Ci S1A0
            PIN r(3:0) R(3:0)
            PIN C0 C0
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        INSTANCE XLXI_1 736 1248 R90
        INSTANCE XLXI_2 1200 1280 R90
        INSTANCE XLXI_3 1664 1312 R90
        INSTANCE XLXI_4 2080 1280 R90
        INSTANCE XLXI_5 800 784 R90
        INSTANCE XLXI_6 1264 784 R90
        INSTANCE XLXI_7 1728 768 R90
        BEGIN BRANCH NB(3)
            WIRE 832 1008 832 1056
            WIRE 832 1056 832 1248
            BEGIN DISPLAY 832 1056 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH NB(2)
            WIRE 1296 1008 1296 1088
            WIRE 1296 1088 1296 1280
            BEGIN DISPLAY 1296 1088 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH NB(1)
            WIRE 1760 992 1760 1088
            WIRE 1760 1088 1760 1312
            BEGIN DISPLAY 1760 1088 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        INSTANCE XLXI_8 2144 784 R90
        BEGIN BRANCH NB(0)
            WIRE 2176 1008 2176 1072
            WIRE 2176 1072 2176 1280
            BEGIN DISPLAY 2176 1072 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B(3:0)
            WIRE 752 576 832 576
            WIRE 832 576 1296 576
            WIRE 1296 576 1760 576
            WIRE 1760 576 2176 576
            WIRE 2176 576 2336 576
        END BRANCH
        IOMARKER 2336 576 B(3:0) R0 28
        BUSTAP 832 576 832 672
        BUSTAP 1296 576 1296 672
        BUSTAP 1760 576 1760 672
        BUSTAP 2176 576 2176 672
        BEGIN BRANCH B(3)
            WIRE 832 672 832 720
            WIRE 832 720 832 752
            WIRE 832 752 832 784
            WIRE 832 752 896 752
            WIRE 896 752 896 1120
            WIRE 896 1120 896 1248
            BEGIN DISPLAY 832 720 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B(1)
            WIRE 1760 672 1760 720
            WIRE 1760 720 1760 752
            WIRE 1760 752 1760 768
            WIRE 1760 752 1824 752
            WIRE 1824 752 1824 1168
            WIRE 1824 1168 1824 1312
            BEGIN DISPLAY 1760 720 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B(0)
            WIRE 2176 672 2176 720
            WIRE 2176 720 2176 752
            WIRE 2176 752 2176 784
            WIRE 2176 752 2240 752
            WIRE 2240 752 2240 1152
            WIRE 2240 1152 2240 1280
            BEGIN DISPLAY 2176 720 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH B(2)
            WIRE 1296 672 1296 720
            WIRE 1296 720 1296 752
            WIRE 1296 752 1296 784
            WIRE 1296 752 1360 752
            WIRE 1360 752 1360 1152
            WIRE 1360 1152 1360 1280
            BEGIN DISPLAY 1296 720 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH S1A0
            WIRE 688 1104 704 1104
            WIRE 704 1104 768 1104
            WIRE 768 1104 1232 1104
            WIRE 1232 1104 1696 1104
            WIRE 1696 1104 2112 1104
            WIRE 2112 1104 2112 1152
            WIRE 2112 1152 2112 1280
            WIRE 1696 1104 1696 1168
            WIRE 1696 1168 1696 1312
            WIRE 1232 1104 1232 1168
            WIRE 1232 1168 1232 1280
            WIRE 768 1104 768 1136
            WIRE 768 1136 768 1248
            WIRE 704 1104 704 2016
            WIRE 704 2016 784 2016
            WIRE 784 2016 784 2080
        END BRANCH
        IOMARKER 688 1104 S1A0 R180 28
        BEGIN BRANCH NB(3:0)
            WIRE 464 928 512 928
            WIRE 512 928 672 928
            BEGIN DISPLAY 512 928 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BEGIN INSTANCE XLXI_9 752 2080 R90
        END INSTANCE
        BEGIN BRANCH BNB(3:0)
            WIRE 768 1952 800 1952
            WIRE 800 1952 832 1952
            WIRE 832 1952 848 1952
            WIRE 848 1952 848 2080
            WIRE 848 1952 912 1952
            WIRE 912 1952 1328 1952
            WIRE 1328 1952 1792 1952
            WIRE 1792 1952 2224 1952
            WIRE 2224 1952 2448 1952
            BEGIN DISPLAY 912 1952 ATTR Name
                ALIGNMENT SOFT-BCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 800 1952 800 1856
        BUSTAP 1328 1952 1328 1856
        BUSTAP 1792 1952 1792 1856
        BUSTAP 2224 1952 2224 1856
        BEGIN BRANCH BNB(1)
            WIRE 1792 1632 1792 1712
            WIRE 1792 1712 1792 1856
            BEGIN DISPLAY 1792 1712 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH BNB(0)
            WIRE 2208 1600 2208 1712
            WIRE 2208 1712 2208 1728
            WIRE 2208 1728 2224 1728
            WIRE 2224 1728 2224 1856
            BEGIN DISPLAY 2208 1712 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH BNB(3)
            WIRE 800 1712 800 1856
            WIRE 800 1712 864 1712
            WIRE 864 1568 864 1680
            WIRE 864 1680 864 1712
            BEGIN DISPLAY 864 1680 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH BNB(2)
            WIRE 1328 1600 1328 1728
            WIRE 1328 1728 1328 1856
            BEGIN DISPLAY 1328 1728 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH R(3:0)
            WIRE 912 2464 912 2560
        END BRANCH
        BEGIN BRANCH C0
            WIRE 784 2464 784 2576
        END BRANCH
        IOMARKER 784 2576 C0 R90 28
        IOMARKER 912 2560 R(3:0) R90 28
        BEGIN BRANCH A(3:0)
            WIRE 912 2016 912 2080
            WIRE 912 2016 1872 2016
        END BRANCH
        IOMARKER 1872 2016 A(3:0) R0 28
    END SHEET
END SCHEMATIC
