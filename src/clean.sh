#!/bin/sh

log="/dev/null"

if [ $# == 0 ]; then
	rm File1.in File1.out File2.in File2.out File3.in File3.out File4.in File4.out ResultFunc.csv ResultSys.csv ResultCriar.csv 2> $log
	echo "Arquivos removidos"
	exit 0
elif [ $# == 1 ]; then
	mkdir $1
	rm File1.in File1.out File2.in File2.out File3.in File3.out File4.in File4.out 2> $log
	mv ResultFunc.csv ResultSys.csv ResultCriar.csv  $1 2> $log
	echo "Arquivos movidos para $1"
	exit 0
else 
	echo "Parametros invalidos"
	exit 0
fi
