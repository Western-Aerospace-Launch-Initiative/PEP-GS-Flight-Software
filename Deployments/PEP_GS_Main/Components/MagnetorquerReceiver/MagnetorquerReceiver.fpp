module PEP_GS_Main {
    @ Component for receiving magnetorquer commands
    active component MagnetorquerReceiver {

        async command TODO opcode 0

        # General Ports
        output port torquerResultOut: MagnetorquerResult @< Port for sending result

        async input port torquerParamsIn: MagnetorquerParams @< Port for receiving params

        #Telemetry

        telemetry X_TORQUE: I16
        telemetry Y_TORQUE: I16
        telemetry Z_TORQUE: I16
        telemetry X_SPEED: I16
        telemetry Y_SPEED: I16
        telemetry Z_SPEED: I16

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
