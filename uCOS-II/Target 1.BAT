SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Altium Designer Summer 09\System;C:\Program Files\TortoiseSVN\bin;C:\Program Files (x86)\Flash Magic;C:\Program Files\Lenovo\Bluetooth Software\;C:\Program Files\Lenovo\Bluetooth Software\syswow64;C:\Program Files (x86)\IDM Computer Solutions\UltraEdit\
SET CPU_TYPE=LPC1768
SET CPU_VENDOR=NXP
SET UV2_TARGET=Target 1
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_core.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_flag.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_mbox.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_mem.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_mutex.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_q.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_sem.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_task.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_time.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_tmr.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_dbg.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\project\output\os_cpu_a._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\os_cpu_c.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\app.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\app_hooks.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\project\output\startup_lpc17xx._ia"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\system_lpc17xx.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\debug_frmwrk.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\lpc17xx_adc.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\project\output\lpc17xx_can.__i"
