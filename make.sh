#!/bin/bash

if [ $# -eq 0 ]; 
  then echo "make";
    make -C cbmc/src;
    make -C hw-cbmc/src;
    make -C src;
    cp src/v2c/v2c ./bin/
  elif [ $1 == "all" ];
    then echo "make all";
    make -C cbmc/src;
    make -C hw-cbmc/src;
    make -C src;
    cp src/v2c/v2c ./bin/
  elif [ $1 == "clean" ];
    then echo "make clean";
    make clean -C cbmc/src;
    make clean -C hw-cbmc/src;
    make clean -C src;
	elif [ $1 == "cbmc" ];
		then echo "make cbmc" ];
		make -C cbmc/src;
	elif [ $1 == "hw-cbmc" ];
    then echo "make hw-cbmc";
    make -C cbmc/src;
    make -C hw-cbmc/src;
	else 
		echo "invalid argument";
fi
    

