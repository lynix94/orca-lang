
# first, git clone like below to get orca project
sudo apt install git  
git clone https://github.com/lynix94/orca-lang  


# then install required libraries like below
sudo apt install libtool  
sudo apt install autoconf  
sudo apt install flex  
sudo apt install bison  

sudo apt install libboost-all-dev  
sudo apt install libreadline-dev  
sudo apt install libgmp-dev  
sudo apt install libgtk2.0-dev  
sudo apt install libsqlite3-dev  


# configure & build like below
./autogen.sh  
./configure --prefix=$HOME/orca  
make  
make install  


# add this environment to .bashrc
export PATH=$HOME/orca/bin:/usr/local/go/bin:$PATH  
export ORCA_PATH=$HOME/orca/lib/orca  
export ORCA_HOME=$HOME/orca  




