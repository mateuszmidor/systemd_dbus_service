#!/bin/bash

ARTIFACTS=('libCommonAPI*' 'Calc-stub.ini' 'com.mateuszmidor.calc.calcInterface.conf' 'Calc.service' 'CalcServer')
PATHS=('/usr' '/etc' '/lib' '/bin')

for path in ${PATHS[@]}; do
	for artifact in ${ARTIFACTS[@]}; do
		find $path -iname $artifact 2>/dev/null
	done
done
