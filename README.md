# sls
`sls` is a new beautiful and light alternative to built in `ls` command in linux
# Screenshot
![](https://raw.githubusercontent.com/SolindekDev/sls/main/screenshot.png)
# Build
To get it on you're computer you need to compile it for you self! Don't be mad it's very very easy.
### With clang
```
git clone https://github.com/solindekdev/sls
cd sls
sudo apt-get install clang
make 
sls # It's working
```
### With out clang
```
git clone https://github.com/solindekdev/sls
cd sls
```
Now change the defualt compiler, edit `Makefile` and change variable `COMPILER_CPP` to `g++` or other compiler you wan't to use
```
make
sls # It's working
```
# Supported operating systems
For now sls is compilable only for Linux.
