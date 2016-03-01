#!/bin/bash

g++ main.cpp printerImp.cpp -Wall -o make
./make | tee output.txt
