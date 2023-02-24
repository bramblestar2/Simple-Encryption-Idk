#include <iostream>
#include <filesystem>
#include <string>
#include "encryp.h"

void menu();
std::string askFilePath();
//-1 doesnt exist
//0 absolute path
//1 relative path
int doesExist(const std::string path);

int main()
{
	menu();

	return EXIT_SUCCESS;
}

void menu()
{
	bool inMenu = true;

	while (inMenu)
	{
		system("cls");
		std::cout << "\t\t<=> Menu <=>\n\n\t1) Encrypt File\n\t2) Decrypt File\n\t3) Quit\n";

		int userChoice;
		std::cin >> userChoice;
		std::cin.get();

		if (userChoice == 1)
		{
			std::string target = askFilePath();
			std::filesystem::path path = target;
			std::cout << "\n\n\t<=> Targeted Encryption File: " << path.filename() << " <=>\n\n";

			std::cout << "\tPlease enter the key that you want\n\tto encrypt the file with.\n\n>> ";

			std::string key;
			std::cin >> key;

			Crypt crypt(path.string(), Crypt::Type::ENCRYPT, key);

			std::cout << "\n\n\n" << crypt << "\n";

			std::cout << "\nFile has been encrypted... Keep Changes? (Y/N)\n>> ";

			std::string keepChange;
			std::cin >> keepChange;
			std::cin.get();
			if (keepChange.size() > 0 ? std::toupper(keepChange.at(0)) : 'N' == 'Y')
			{
				std::ofstream encryptedFile(path);
				encryptedFile << crypt;
				encryptedFile.close();
			}

			system("pause");
		}
		else if (userChoice == 2)
		{
			std::string target = askFilePath();
			std::filesystem::path path = target;
			std::cout << "\n\n\t<=> Targeted Decryption File: " << path.filename() << " <=>\n\n";

			std::cout << "\tPlease enter the key that you want\n\tto decrypt the file with.\n\n>> ";

			std::string key;
			std::cin >> key;

			Crypt crypt(path.string(), Crypt::Type::DECRYPT, key);

			std::cout << "\n\n\n" << crypt << "\n";

			std::cout << "\nFile has been decrypted... Keep Changes? (Y/N)\n>> ";
			
			std::string keepChange;
			std::cin >> keepChange;
			std::cin.get();
			if (keepChange.size() > 0 ? std::toupper(keepChange.at(0)) : 'N' == 'Y')
			{
				std::ofstream decryptedFile(path);
				decryptedFile << crypt;
				decryptedFile.close();
			}

			system("pause");
		}
		else if (userChoice == 3)
		{
			std::cout << "Exiting Program\n";
			inMenu = false;
		}
		else
		{
			std::cout << "Invalid Choice, try again.\n";
			system("pause");
		}
	}
}

std::string askFilePath()
{
	bool fileExists = false;
	char f[1000];
	std::string file;

	while (!fileExists)
	{
		std::cout << "\nPlease enter a file you want to encrypt.\nIf you want to quit, type \"(QUIT)\"\n>> ";
		std::cin.getline(f, 1000);
		file = f;

		if (file == "(QUIT)")
			return "QUIT";

		fileExists = doesExist(file) != -1 ? true : false;

		if (!fileExists)
			std::cout << file + " doesn't exist!\n\n";
	}
	if (doesExist(file) == 1)
		file = std::filesystem::current_path().string() + file;

	std::cout << "\n";
	return file;
}

int doesExist(const std::string path)
{
	int result = -1;

	if (std::filesystem::exists(path))
		result = 0;
	else if (std::filesystem::exists(std::filesystem::current_path().string() + path))
		result = 1;

	return result;
}
