VERSION 6
BEGIN SCHEMATIC
    BEGIN ATTR DeviceFamilyName "spartan3"
        DELETE all:0
        EDITNAME all:0
        EDITTRAIT all:0
    END ATTR
    BEGIN NETLIST
        SIGNAL S1A0
        SIGNAL A(3:0)
        SIGNAL B(3:0)
        SIGNAL R(3:0)
        PORT Input S1A0
        PORT Input A(3:0)
        PORT Input B(3:0)
        PORT Output R(3:0)
        BEGIN BLOCKDEF as4v
            TIMESTAMP 2018 3 20 16 27 37
            RECTANGLE N 64 -192 320 0 
            LINE N 64 -160 0 -160 
            RECTANGLE N 0 -108 64 -84 
            LINE N 64 -96 0 -96 
            RECTANGLE N 0 -44 64 -20 
            LINE N 64 -32 0 -32 
            RECTANGLE N 320 -172 384 -148 
            LINE N 320 -160 384 -160 
        END BLOCKDEF
        BEGIN BLOCK XLXI_1 as4v
            PIN S1A0 S1A0
            PIN A(3:0) A(3:0)
            PIN B(3:0) B(3:0)
            PIN R(3:0) R(3:0)
        END BLOCK
    END NETLIST
    BEGIN SHEET 1 3520 2720
        BEGIN INSTANCE XLXI_1 1264 1264 R0
        END INSTANCE
        BEGIN BRANCH S1A0
            WIRE 1120 1104 1264 1104
        END BRANCH
        BEGIN BRANCH A(3:0)
            WIRE 1120 1168 1264 1168
        END BRANCH
        BEGIN BRANCH B(3:0)
            WIRE 1120 1232 1264 1232
        END BRANCH
        BEGIN BRANCH R(3:0)
            WIRE 1648 1104 1760 1104
        END BRANCH
        IOMARKER 1120 1104 S1A0 R180 28
        IOMARKER 1120 1168 A(3:0) R180 28
        IOMARKER 1120 1232 B(3:0) R180 28
        IOMARKER 1760 1104 R(3:0) R0 28
    END SHEET
END SCHEMATIC
