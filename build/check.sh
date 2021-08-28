#!/bin/bash

valgrind --leak-check=full --show-reachable=yes --trace-children=yes ./run_check 2>check.log

