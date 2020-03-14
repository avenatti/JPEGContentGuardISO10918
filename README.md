# JPEGContentGuardISO10918
Filtering JPEG Files Utilizing ISO/IEC 10918 Based Software Content Guard


# Build dependencies.
cmake      # Ubuntu:  sudo apt-get install cmake
cxxtest    # Ubuntu:  sudo apt-get install cxxtest
doxygen    # Ubuntu:  sudo apt-get install doxygen


# Scripting deependencies.
pip        # Ubuntu:  sudo apt install python-pip
patch      # sudo pip install patch
Pygments   # sudo pip install Pygments
lcov       # Ubuntu:  sudo apt-get install lcov
cppcheck   # Ubuntu:  sudo apt-get install cppcheck

# Stack dependencies
pkg-config # Ubuntu:  sudo apt-get install pkg-config
autoconf   # Ubuntu:  sudo apt-get install autoconf
automake   # Ubuntu:  sudo apt-get install automake
libtool    # Ubuntu:  sudo apt-get install libtool   
nasm       # Ununtu:  sudo apt-get install nasm


# How to build Guard.
cd guard
cmake .
make 
