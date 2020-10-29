#!/bin/bash

files=${1:-files}

wget -nH -x -nc -B https://challengecybersec.fr -i ${files}

