echo "Hello, Configuring CUDA compiler"
export PATH=/Developer/NVIDIA/CUDA-9.0/bin${PATH:+:${PATH}}
export DYLD_LIBRARY_PATH=/Developer/NVIDIA/CUDA-9.0/lib${DYLD_LIBRARY_PATH:+:${DYLD_LIBRARY_PATH}}
echo "-----------"
echo "Verifiying dependencies..."
brew install sdl2
brew instal libxml2
brew install glfw3
echo "-----------"
echo "Cleaning any possible residue files..."
make fclean
echo "-----------"
echo "Compiling project..."
make -j
echo "-----------"
if [ $# -eq 1 ]
then
{
    echo "Launching app as client to IP $1..."
    ./bin/RT client $1
    echo "Done, THANK YOU FOR YOUR HELP"    
}
else
{
    echo "No IP specified. Relaunch using: ./bin/rt [Valid IP Adresss] or reconfigure everything with 'sh ./scripts/config_cluster.sh [Valid IP Adress]'"
}
fi
