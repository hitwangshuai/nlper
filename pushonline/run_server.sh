
export LD_LIBRARY_PATH=./third_party/lib:$LD_LIBRARY_PATH

#nohup ./run_server >>nlper.log 2>&1 &
./run_server >>nlper.log 2>&1

