# Power Window Control System using Tiva C and FreeRTOS

This project implements a Power Window Control System using Tiva C microcontroller running FreeRTOS. The system includes features such as manual open/close, one-touch auto open/close, window lock, and jam protection. It utilizes top and bottom limit switches, a DC motor, push buttons for operation, and an ON/OFF switch for window lock.


## System Basic Features

1. **Manual Open/Close Function**: Continuous pressing or pulling of the power window switch opens or closes the window until the switch is released.
2. **One Touch Auto Open/Close Function**: Short pressing or pulling of the power window switch fully opens or closes the window.
3. **Window Lock Function**: When the window lock switch is turned on, the opening and closing of all windows except the driver’s window is disabled.
4. **Jam Protection Function**: Automatically stops the power window and moves it downward about 0.5 seconds if foreign matter gets caught in the window during one-touch auto-close operation.

## Hardware Components Used

1. Tiva C microcontroller.
2. Limit switches.
3. DC Motor.
4. L298N Motor control board.
5. Push buttons for operation.
6. ON/OFF switch for window lock.



