#include <iostream>
#include <cstring>
#include <string>
#include <chrono>
#include <thread>
#include <vector>
#include <atomic>
#include "md5.h"

using namespace std;
using namespace std::chrono;

atomic<bool> passFound(false);
atomic<int> numHashes(0);
string base64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

string HexToString(string hex) {
	
	string temp = "";

	return temp;
}

string checkPassUp(string &password){

	if(password[5] == 'z') {
			if(password[4] == 'z') {
				if(password[3] == 'z') {
					if(password[2] == 'z') {
						if(password[1] == 'z'){
							password[0]++;
							password[1] = 'a';
							password[2] = 'a';
							password[3] = 'a';
							password[4] = 'a';
							password[5] = 'a';
						} else {
							password[1]++;
							password[2] = 'a';
							password[3] = 'a';
							password[4] = 'a';
							password[5] = 'a';
						}
					} else {
						password[2]++;
						password[3] = 'a';
						password[4] = 'a';
						password[5] = 'a';
					}
				} else {
					password[3]++;
					password[4] = 'a';
					password[5] = 'a';
				}
			} else {
				password[4]++;
				password[5] = 'a';
			}
		} else {
			password[5]++;
		}

	return password;
}
// TODO: implement more threads to use this
// kinda lazy cuz kills cpu
// std::string checkPassDown(string &password){

// 	if(password[5] == 'a') {
// 			if(password[4] == 'a') {
// 				if(password[3] == 'a') {
// 					if(password[2] == 'a') {
// 						if(password[1] == 'a'){
// 							password[0]--;
// 							password[1] = 'z';
// 							password[2] = 'z';
// 							password[3] = 'z';
// 							password[4] = 'z';
// 							password[5] = 'z';
// 						} else {
// 							password[1]--;
// 							password[2] = 'z';
// 							password[3] = 'z';
// 							password[4] = 'z';
// 							password[5] = 'z';
// 						}
// 					} else {
// 						password[2]--;
// 						password[3] = 'z';
// 						password[4] = 'z';
// 						password[5] = 'z';
// 					}
// 				} else {
// 					password[3]--;
// 					password[4] = 'z';
// 					password[5] = 'z';
// 				}
// 			} else {
// 				password[4]--;
// 				password[5] = 'z';
// 			}
// 		} else {
// 			password[5]--;
// 		}

// 	return password;
// }
// Error check: 
// to64 returning wrong 64
// ERRORFIX: changed from toint -> string
string to64(unsigned int holder, int length){
	string ret = "";

	for (int i = 0; i < length; i++){
		ret += base64[holder&0x3f];
		holder >>= 6;
	}
	return ret;
}

string crackpot (string encrypted){ //team40 : $1$  4fTgjp6q$  dAWRGFC9ioSIQsJ6tCRTA. switching to team53: V04wTfbgvUGa4aY0xtvq2/
	//error: skips periods sometimes? dunno why
	//ERRORFIX: Fixed to64 function
	string HASH = "V04wTfbgvUGa4aY0xtvq2/"; 
	string password = encrypted;
	string salt = "4fTgjp6q"; 
	string magic = "$1$";
	bool found = false;

	while(password != "zzzzz" && !found) {
		unsigned char* alt_sum = MD5(password + salt + password).digest;
		string temp = "";
		for(unsigned int i = 0; i < 6; i++) {
			temp.push_back(alt_sum[i]);
		}
		unsigned char* h = MD5(password + magic + salt + temp  + password[0] + '\0' + '\0').digest;
		for(unsigned int j = 0; j < 1000; j++) {
			string intermediate = "";

			for(unsigned int k = 0; k < 16; k++) {
				intermediate.push_back(h[k]);
			}

			string str = "";

			if(j % 2 == 0) {
				str += intermediate;
			}
			if(j % 2 == 1) {
				str += password;
			}
			if(!(j % 3 == 0)) {
				str += salt;
			}
			if(!(j % 7 == 0)) {
				str += password;
			}
			if(j % 2 == 0) {
				str += password;
			}
			if(j % 2 == 1) {
				str += intermediate;
			}

			h = MD5(str).digest;
		}
		//cout << magic + salt + "$";
		//fix: added better to64 to finally detect periods
		string result = to64((h[0] << 16) | (h[6] << 8) | h[12], 4) +
            to64((h[1] << 16) | (h[7] << 8) | h[13], 4) + 
            to64((h[2] << 16) | (h[8] << 8) | h[14], 4) +
            to64((h[3] << 16) | (h[9] << 8) | h[15], 4) +
            to64((h[4] << 16) | (h[10] << 8) | h[5], 4) +
            to64(h[11], 2);;
		
		//cout << result << endl << endl;
		
		//1ms virtually nothing, 3 sweet spot for ~80% cpu usage on my cpu, anything higher is too slow
		this_thread::sleep_for(3ms);
		if(result == HASH) {
			cout << "Cracking success" << endl;
			cout << "Found in thread: " << this_thread::get_id() << endl;
			cout << "Password: " << password << endl;
			found = true;
			passFound = true;
			return password;
		} else if (passFound == true){
			//ERROR CHECK: FATAL ERROR FROM EXIT
			//TODO: FIND OUT HOW TO CLOSE THREAD
			//std::terminate();
			//FIX: literally just return...
			return "Returned from thread";
		}
		numHashes++;
		checkPassUp(password);
	}
	return password;
}

int main() {
	vector< string > passwords = {"aaaaaa", "baaaaa", "caaaaa", "daaaaa"
		, "eaaaaa", "faaaaa" , "gaaaaa" , "haaaaa" , "iaaaaa" , "jaaaaa" , "kaaaaa"
		, "laaaaa", "maaaaa" , "naaaaa" , "oaaaaa" , "paaaaa" , "qaaaaa" , "raaaaa"
		, "saaaaa", "taaaaa" , "uaaaaa" , "vaaaaa" , "waaaaa" , "xaaaaa" , "yaaaaa"
		, "zaaaaa"};
	vector< thread > threads;
	
	cout << "Threads instantiated, running cracker..." << endl;
	auto start = high_resolution_clock::now();
	for(int i = 0; i < passwords.size(); i++){
		threads.push_back(thread(crackpot, passwords[i]));
	}
	for(auto &th : threads){
		th.join();
	}
	auto stop = high_resolution_clock::now(); 
	auto duration = duration_cast<milliseconds>(stop - start); 
	cout << "Time taken: " << duration.count() << " ms" << endl;
	cout << "Number of hashes checked: " << numHashes << endl;
	cout << "The program has finished" << endl;

	return 0;
}
