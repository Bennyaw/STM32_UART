STM32F429ZIT6 MCU (UART peripheral)
-----------------------------------

This practical here is to get familiar with the UART peripheral protocol by using the STM32F429ZIT6 MCU.
*ALL* the functions used are all user-defined
Here, we are going to do 2 experiments using UART protocol. First is simply send ```Hello,WORLD``` and display it on the TeraTerm, second is to type a command on PC and send it to the MCU Led to switch it on or off or blink. The full report of this practice is
documented above as ```Report.pdf```. Note that the IDE used is STM32CubeMX.

Setup Devices and Software
--------------------------
1. STM32F429ZIT6 MCU
2. CH360 Windows device driver
3. STM32CubeMX
4. TeraTerm

Configurations
--------------
We are using UART5, configurations of the UART5 are as below:
1. 115,200bps
2. Odd parity
3. 9-bit data
4. Oversampling by 16
5. 1 stop bit
6. Configure APB1 to run at 45MHz

Send a String and display
-------------------------
The purpose here is to get familiar with the transmission of data by using UART. We will be simply sending a string and display it on TeraTerm. Some discussions is attached in the report.
![hello world](STM32_UART/hello world.PNG)

Type command on PC
------------------
More complexity is added compared to the previous practice, we are going to type some commands such as
```
TURN ON LED             # To turn on the LED (PG13)
TURN OFF LED            # To turn off the LED (PG13)
BLINK LED               # To blink LED (PG13)
```
What is happening here is actually when we typed the letters, MCU will receive the data and transmit out through the driver and display it on the screen, and at the same time, we used the user-defined ```stringcompare``` function to identify the command and do the task on the MCU. The outcome is written in the report above.

Reference
---------
[Reference_Manual](https://www.st.com/content/ccc/resource/technical/document/reference_manual/3d/6d/5a/66/b4/99/40/d4/DM00031020.pdf/files/DM00031020.pdf/jcr:content/translations/en.DM00031020.pdf).
