module PEP_GS_Main {
    @ Component for sending magnetorquer commands
    active component MagnetorquerSender {

        # General Ports
        @Port for sending Params
        output port torquerParamsOut: MagnetorquerParams

        @Port for getting return value
        async input port torquerResultIn: MagnetorquerResult

        # Commands

        @Set duty cycle
        async command SET_DUTY_CYCLE(
                                    nodeid: U8 @< ID FOr torquer
                                    torquerX: F64
                                    torquerY: F64
                                    torquerZ: F64
        )

        #events

        event RESULT(
                    result: U16 @< Torquer return value
        ) \
        severity activity high \
        format "Set torquer duuty cycle return value is {d}"


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
