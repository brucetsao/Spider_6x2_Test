This is a spider machine project.

## How to tune the parameters ? 
1. Define the angle resolution (PhaseAngleResolution) in file ServoPwm.h.
2. Define the maximum tick (MaxServoTick) in file ServoPwm.h, where
		MaxServoTick * PhaseAngleResolution = 180
3. Adjust the task switching interval for MotorPwmTask in file Spider_6x2_Test.ino
   to get 50Hz PWM pulses. 
   
The PWM task must be the first task in the RTOS to get the highest running priority.
The other tasks should execute in one PWM task switching interval. If the generated 
PWM pulse is unstable to drive the motor, adjust the PhaseAngleResolution to release 
more running time in RTOS for other tasks. For example:
	PhaseAngleResolution = 9
	MaxServoTick = 20
	switching interval = 278

## modules
>Spider_6x2_Test.ino
    The main program.
	
>RTOS\n
    A very simple real time operation system, Provides the multi-task switching capabiity.
	
>ServoPWM
    Generate the 50Hz PWM pulse to drive the servo motors.\n
	
>CmdShell
    Accept the input command, interpret and run. All commands should start with a dollor sign '$'
    and finished with the sharp '#' sign. Currently acceptable commands:
    (a) $MmmAaaa#, motor mm angle aaa, 
        ex. $M00A120# -> motor 0 move to angle 120 degree.
    (b) $Aa#, spider auto action
        ex. $A1# -> auto move with aciotn 1
	        $A0# -> stop move		   
			
>SpiderAuto
    Auto move for spider action. The control data is listed in the cpp file.