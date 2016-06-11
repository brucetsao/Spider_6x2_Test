This is a spider machine project.

## How to tune the parameters ? 
1. Define the angle resolution (PhaseAngleResolution) in file ServoPwm.h.
2. Define the maximum tick (MaxServoTick) in file ServoPwm.h, where<br>
		MaxServoTick * PhaseAngleResolution = 180
3. Adjust the task switching interval for MotorPwmTask in file Spider_6x2_Test.ino
   to get 50Hz PWM pulses. 
   
The PWM task must be the first task in the RTOS to get the highest running priority.
The other tasks should execute in one PWM task switching interval. If the generated 
PWM pulse is unstable to drive the motor, adjust the PhaseAngleResolution to release 
more running time in RTOS for other tasks. For example:<br>
	&nbsp PhaseAngleResolution = 9<br>
	&nbsp MaxServoTick = 20<br>
	&nbsp switching interval = 278<br>

## modules
>Spider_6x2_Test.ino<br>
    &nbsp;&nbsp;&nbsp; The main program.
	
>RTOS<br>
    &nbsp;&nbsp;&nbsp; A very simple real time operation system, Provides the multi-task switching capabiity.
	
>ServoPWM<br>
    &nbsp;&nbsp;&nbsp; Generate the 50Hz PWM pulse to drive the servo motors.\n
	
>CmdShell<br>
    &nbsp;&nbsp;&nbsp; Accept the input command, interpret and run. All commands should start with a dollor sign '$'
           and finished with the sharp '#' sign. Currently acceptable commands:<br>
    &nbsp;&nbsp;&nbsp; (a) $MmmAaaa#, motor mm angle aaa, <br>
    &nbsp;&nbsp;&nbsp;&nbsp;    ex. $M00A120# -> motor 0 move to angle 120 degree.<br>
    &nbsp;&nbsp;&nbsp;(b) $Aa#, spider auto action<br>
    &nbsp;&nbsp;&nbsp;&nbsp;    ex. $A1# -> auto move with aciotn 1<br>
	&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;        $A0# -> stop move<br>
			
>SpiderAuto<br>
    &nbsp;&nbsp;&nbsp; Auto move for spider action. The control data is listed in the cpp file.