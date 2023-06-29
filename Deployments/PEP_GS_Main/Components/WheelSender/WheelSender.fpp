module PEP_GS_Main {
    @ Component for sending wheel speed parameters
    active component WheelSender {

        # One async command/port is required for active components
        # This should be overridden by the developers with a useful command/port

        @ Set wheel speed
        async command SET_SPEED(
                                nodeid: U8 @< ID for wheels
                                xspeed: I16 @< Speed for x wheels
                                yspeed: I16 @< Speed for y wheels
                                zspeed: I16 @< Speed for z wheels
        )

        event RESULT(
                    result: U16 @< The wheel speed return value
        ) \
        severity activity high \
        format "Set wheel speed return value is {d}"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
