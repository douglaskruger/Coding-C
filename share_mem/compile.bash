#!/bin/bash
clear
#g++ -g -o shm_reader shm_reader.c
#g++ -g -o shm_writer shm_writer.c
gcc -DSERVER -g -o shm_writer shm_reader.c
gcc -DCLIENT -g -o shm_reader shm_reader.c
