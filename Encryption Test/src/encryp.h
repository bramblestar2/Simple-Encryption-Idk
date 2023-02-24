#pragma once
#include <iostream>
#include <fstream>

class Crypt
{
public:
	enum class Type
	{
		ENCRYPT,
		DECRYPT
	};

public:
	Crypt(const std::string file, const Type type, const std::string key);

	friend std::ostream& operator<<(std::ostream& out, const Crypt& crypt);
private:
	void encrypt(const std::string key);
	void decrypt(const std::string key);
	int keyDifference(const std::string key);
	bool alreadyEncrypted(const std::string data);

	std::string m_target_file;
	
	//Encryption/Decryption info will be stored here.
	//Its up to the user where they want the data to be.
	std::string m_info;
};