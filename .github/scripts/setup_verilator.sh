#!/bin/bash
sudo apt-get update && apt-get upgrade -y
sudo apt install git help2man perl python3 make autoconf g++ flex bison ccache libgoogle-perftools-dev numactl perl-doc libfl2 libfl-dev zlibc zlib1g zlib1g-dev

git clone https://github.com/verilator/verilator
unset VERILATOR_ROOT  # For bash
cd verilator
autoconf         # Create ./configure script
./configure      # Configure and create Makefile
make -j `nproc`  # Build Verilator itself (if error, try just 'make')
sudo make install