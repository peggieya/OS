cd ~/ece344/os161
./configure --ostree=$HOME/ece344/root
#rm -f -r ~/ece344/root
make
rm -f -r ~/ece344/os161/kern/compile/ASST1
#rm -f -r ~/ece344/os161/kern/compile/ASST0
cd ~/ece344/os161/kern/conf
./config ASST1
cd ~/ece344/os161/kern/compile/ASST1
make depend
make
make install
cd ~/ece344/root
#cp /cad2/ece344s/cs161/bin/sys161.conf.sample sys161.conf
sys161 kernel
