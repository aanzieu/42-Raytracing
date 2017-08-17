echo "Hello, Configuring CUDA compiler"
export PATH=/Developer/NVIDIA/CUDA-8.0/bin${PATH:+:${PATH}}
export DYLD_LIBRARY_PATH=/Developer/NVIDIA/CUDA-8.0/lib${DYLD_LIBRARY_PATH:+:${DYLD_LIBRARY_PATH}}
echo "Compiling project..."
make -j
echo "Launching app as client to IP 10.11.12.18..."
./bin/RT testfiles/tunnel.xml client 10.11.12.18
echo "Done, THANK YOU FOR YOUR HELP"
