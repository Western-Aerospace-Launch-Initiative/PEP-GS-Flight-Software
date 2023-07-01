module PEP_GS_Main {

    port WheelParams(
                    Nodeid: U8 @< node id for wheels
                    Xspeed: I16 @< Speed for x wheels
                    Yspeed: I16 @< Speed for Y wheels
                    Zspeed: I16 @< Speed for z wheels
    )

    port WheelResult(
                    WheelReturnVal: U16 @< Return value for set wheel speed command
    )

    port MagnetorquerParams(
                    Nodeid: U8 @< Node id for torquer
                    TorquerX: F64 @< X torquer duty cycle
                    TorquerY: F64 @< Y Torquer duty cycle
                    TorquerZ: F64 @< Z torquer duty cycle
    )

    port MagnetorquerResult(
                    TorquerReturnVal: U16 @< Return value for torquer command
    )
}
