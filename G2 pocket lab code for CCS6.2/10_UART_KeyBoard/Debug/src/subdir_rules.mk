################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/UART_Event.obj: ../src/UART_Event.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="D:/css/TI/ccsv7/ccs_base/msp430/include" --include_path="D:/Tongji University/电子信息工程/暑期/2017电子信息工程专业课程设计/G2 pocket lab code for CCS6.2/10_UART_KeyBoard/src" --include_path="D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/include" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="src/UART_Event.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/UART_FIFO.obj: ../src/UART_FIFO.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="D:/css/TI/ccsv7/ccs_base/msp430/include" --include_path="D:/Tongji University/电子信息工程/暑期/2017电子信息工程专业课程设计/G2 pocket lab code for CCS6.2/10_UART_KeyBoard/src" --include_path="D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/include" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="src/UART_FIFO.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/UART_Global.obj: ../src/UART_Global.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="D:/css/TI/ccsv7/ccs_base/msp430/include" --include_path="D:/Tongji University/电子信息工程/暑期/2017电子信息工程专业课程设计/G2 pocket lab code for CCS6.2/10_UART_KeyBoard/src" --include_path="D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/include" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="src/UART_Global.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/UART_init.obj: ../src/UART_init.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/bin/cl430" -vmsp --code_model=small --data_model=small --use_hw_mpy=none --include_path="D:/css/TI/ccsv7/ccs_base/msp430/include" --include_path="D:/Tongji University/电子信息工程/暑期/2017电子信息工程专业课程设计/G2 pocket lab code for CCS6.2/10_UART_KeyBoard/src" --include_path="D:/css/TI/ccsv7/tools/compiler/ti-cgt-msp430_16.9.1.LTS/include" -g --define=__MSP430G2553__ --diag_warning=225 --display_error_number --abi=eabi --printf_support=minimal --preproc_with_compile --preproc_dependency="src/UART_init.d" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


