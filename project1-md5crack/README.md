# CS165 MD5Crypt

Program made by Kristian De Castro, 862025678

To compile: g++ md5crack.cpp md5.cpp -o a.exe
To run: ./a 

## Show the correct password for your team user

team53:\$1\$4fTgjp6q\$V04wTfbgvUGa4aY0xtvq2/:16653:0:99999:7::: 
Password cracked: hfhugt

## Source Code

The source code is found in md5crack.cpp
Md5.cpp and md5.h are helper files found from http://www.zedwood.com/article/cpp-md5-function

## The number of threads/processes is used

I used 26 threads (which almost killed my cpu lol)

## CPU Model

AMD Ryzen7 2700x 1.3V, overclocked to 3.9GHz

## The throughput of password cracking

My program goes through about 5300 candidate passwords per second.

# WARNING

Improperly closing the program will result in a ghost executable file running in the backround. 

If this happens, you must compile with a different executable name, such as g++ md5crack.cpp md5.cpp -o b.exe.

The only known temporary fix is to restart your computer.