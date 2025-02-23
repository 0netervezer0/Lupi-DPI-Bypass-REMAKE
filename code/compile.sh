echo "Deleting build cache..."
rm -rf build
echo "Compiling..."
mkdir build && cd build
cmake ..
make
echo "================"
echo "Compile finished"