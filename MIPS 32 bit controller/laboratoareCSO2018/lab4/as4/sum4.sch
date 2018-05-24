VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL XLXN_1
        SIGNAL XLXN_3
        SIGNAL XLXN_6
        SIGNAL r(3:0)
        SIGNAL r(3)
        SIGNAL r(2)
        SIGNAL r(1)
        SIGNAL r(0)
        SIGNAL a(3:0)
        SIGNAL b(3:0)
        SIGNAL a(0)
        SIGNAL a(1)
        SIGNAL a(2)
        SIGNAL a(3)
        SIGNAL b(3)
        SIGNAL b(2)
        SIGNAL b(1)
        SIGNAL b(0)
        SIGNAL Ci
        SIGNAL C0
        PORT Output r(3:0)
        PORT Input a(3:0)
        PORT Input b(3:0)
        PORT Input Ci
        PORT Output C0
        BEGIN BLOCKDEF sum1g
            TIMESTAMP 2018 3 3 10 49 10
            RECTANGLE N 64 -192 320 0 
            LINE N 64 -32 0 -32 
            LINE N 320 -160 384 -160 
            LINE N 320 -32 384 -32 
            LINE N 64 -160 0 -160 
            LINE N 64 -96 0 -96 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 sum1g
            PIN Ci XLXN_1
            PIN Co C0
            PIN S r(3)
            PIN B b(3)
            PIN A a(3)
        END BLOCK
        BEGIN BLOCK XLXI_2 sum1g
            PIN Ci XLXN_3
            PIN Co XLXN_1
            PIN S r(2)
            PIN B b(2)
            PIN A a(2)
        END BLOCK
        BEGIN BLOCK XLXI_3 sum1g
            PIN Ci XLXN_6
            PIN Co XLXN_3
            PIN S r(1)
            PIN B b(1)
            PIN A a(1)
        END BLOCK
        BEGIN BLOCK XLXI_4 sum1g
            PIN Ci Ci
            PIN Co XLXN_6
            PIN S r(0)
            PIN B b(0)
            PIN A a(0)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN INSTANCE XLXI_1 960 976 M90
        END INSTANCE
        BEGIN INSTANCE XLXI_2 1472 992 M90
        END INSTANCE
        BEGIN INSTANCE XLXI_3 2096 976 M90
        END INSTANCE
        BEGIN INSTANCE XLXI_4 2576 976 M90
        END INSTANCE
        BEGIN BRANCH XLXN_1
            WIRE 928 912 928 976
            WIRE 928 912 1040 912
            WIRE 1040 912 1040 1456
            WIRE 1040 1456 1312 1456
            WIRE 1312 1376 1312 1456
        END BRANCH
        BEGIN BRANCH XLXN_3
            WIRE 1440 928 1440 992
            WIRE 1440 928 1536 928
            WIRE 1536 928 1536 1440
            WIRE 1536 1440 1936 1440
            WIRE 1936 1360 1936 1440
        END BRANCH
        BEGIN BRANCH XLXN_6
            WIRE 2064 880 2064 976
            WIRE 2064 880 2240 880
            WIRE 2240 880 2240 1440
            WIRE 2240 1440 2416 1440
            WIRE 2416 1360 2416 1440
        END BRANCH
        BEGIN BRANCH r(3:0)
            WIRE 416 1616 928 1616
            WIRE 928 1616 1440 1616
            WIRE 1440 1616 2064 1616
            WIRE 2064 1616 2544 1616
            WIRE 2544 1616 2976 1616
        END BRANCH
        IOMARKER 2976 1616 r(3:0) R0 28
        BUSTAP 928 1616 928 1520
        BEGIN BRANCH r(3)
            WIRE 928 1360 928 1504
            WIRE 928 1504 928 1520
            BEGIN DISPLAY 928 1504 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1440 1616 1440 1520
        BEGIN BRANCH r(2)
            WIRE 1440 1376 1440 1488
            WIRE 1440 1488 1440 1504
            WIRE 1440 1504 1440 1520
            BEGIN DISPLAY 1440 1488 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 2064 1616 2064 1520
        BEGIN BRANCH r(1)
            WIRE 2064 1360 2064 1504
            WIRE 2064 1504 2064 1520
            BEGIN DISPLAY 2064 1504 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 2544 1616 2544 1520
        BEGIN BRANCH r(0)
            WIRE 2544 1360 2544 1472
            WIRE 2544 1472 2544 1520
            BEGIN DISPLAY 2544 1472 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH a(3:0)
            WIRE 368 800 864 800
            WIRE 864 800 1376 800
            WIRE 1376 800 2000 800
            WIRE 2000 800 2480 800
            WIRE 2480 800 3008 800
        END BRANCH
        BEGIN BRANCH b(3:0)
            WIRE 384 688 800 688
            WIRE 800 688 1312 688
            WIRE 1312 688 1936 688
            WIRE 1936 688 2416 688
            WIRE 2416 688 3008 688
        END BRANCH
        IOMARKER 3008 800 a(3:0) R0 28
        IOMARKER 3008 688 b(3:0) R0 28
        BUSTAP 2480 800 2480 896
        BEGIN BRANCH a(0)
            WIRE 2480 896 2480 928
            WIRE 2480 928 2480 976
            BEGIN DISPLAY 2480 928 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 2000 800 2000 896
        BEGIN BRANCH a(1)
            WIRE 2000 896 2000 928
            WIRE 2000 928 2000 976
            BEGIN DISPLAY 2000 928 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1376 800 1376 896
        BEGIN BRANCH a(2)
            WIRE 1376 896 1376 944
            WIRE 1376 944 1376 992
            BEGIN DISPLAY 1376 944 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 864 800 864 896
        BEGIN BRANCH a(3)
            WIRE 864 896 864 944
            WIRE 864 944 864 976
            BEGIN DISPLAY 864 944 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 800 688 800 784
        BEGIN BRANCH b(3)
            WIRE 800 784 800 928
            WIRE 800 928 800 976
            BEGIN DISPLAY 800 928 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1312 688 1312 784
        BEGIN BRANCH b(2)
            WIRE 1312 784 1312 928
            WIRE 1312 928 1312 992
            BEGIN DISPLAY 1312 928 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 1936 688 1936 784
        BEGIN BRANCH b(1)
            WIRE 1936 784 1936 928
            WIRE 1936 928 1936 976
            BEGIN DISPLAY 1936 928 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BUSTAP 2416 688 2416 784
        BEGIN BRANCH b(0)
            WIRE 2416 784 2416 912
            WIRE 2416 912 2416 976
            BEGIN DISPLAY 2416 912 ATTR Name
                ALIGNMENT SOFT-TVCENTER
            END DISPLAY
        END BRANCH
        BEGIN BRANCH Ci
            WIRE 2544 896 2544 976
            WIRE 2544 896 3200 896
            WIRE 3200 896 3200 1184
        END BRANCH
        BEGIN BRANCH C0
            WIRE 800 1360 800 1392
        END BRANCH
        IOMARKER 800 1392 C0 R90 28
        IOMARKER 3200 1184 Ci R90 28
    END SHEET
END SCHEMATIC
