################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../lm4f120h5qr.cmd 

CFG_SRCS += \
../app.cfg 

C_SRCS += \
../Clock.c \
../Encoder.c \
../Font.c \
../Graphics_Bmp.c \
../Ps2Keyboard.c \
../buttons.c \
../graphics.c \
../main.c \
../scancodes.c \
../st7565.c 

OBJS += \
./Clock.obj \
./Encoder.obj \
./Font.obj \
./Graphics_Bmp.obj \
./Ps2Keyboard.obj \
./buttons.obj \
./graphics.obj \
./main.obj \
./scancodes.obj \
./st7565.obj 

GEN_SRCS += \
./configPkg/compiler.opt \
./configPkg/linker.cmd 

C_DEPS += \
./Clock.pp \
./Encoder.pp \
./Font.pp \
./Graphics_Bmp.pp \
./Ps2Keyboard.pp \
./buttons.pp \
./graphics.pp \
./main.pp \
./scancodes.pp \
./st7565.pp 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

GEN_SRCS__QUOTED += \
"configPkg\compiler.opt" \
"configPkg\linker.cmd" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"Clock.pp" \
"Encoder.pp" \
"Font.pp" \
"Graphics_Bmp.pp" \
"Ps2Keyboard.pp" \
"buttons.pp" \
"graphics.pp" \
"main.pp" \
"scancodes.pp" \
"st7565.pp" 

OBJS__QUOTED += \
"Clock.obj" \
"Encoder.obj" \
"Font.obj" \
"Graphics_Bmp.obj" \
"Ps2Keyboard.obj" \
"buttons.obj" \
"graphics.obj" \
"main.obj" \
"scancodes.obj" \
"st7565.obj" 

C_SRCS__QUOTED += \
"../Clock.c" \
"../Encoder.c" \
"../Font.c" \
"../Graphics_Bmp.c" \
"../Ps2Keyboard.c" \
"../buttons.c" \
"../graphics.c" \
"../main.c" \
"../scancodes.c" \
"../st7565.c" 

GEN_OPTS__FLAG += \
--cmd_file="./configPkg/compiler.opt" 

GEN_CMDS__FLAG += \
-l"./configPkg/linker.cmd" 


