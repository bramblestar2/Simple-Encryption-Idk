#include "encryp.h"

std::ostream& operator<<(std::ostream& out, const Crypt& crypt)
{
    out << crypt.m_info;

    return out;
}

Crypt::Crypt(const std::string file, const Type type, const std::string key)
{
    m_target_file = file;

    switch (type)
    {
    case Type::DECRYPT:
        decrypt(key);
        break;

    case Type::ENCRYPT:
        encrypt(key);
        break;
    }
}

void Crypt::encrypt(const std::string key)
{
    std::ifstream input(m_target_file);

    std::istreambuf_iterator<char> eos;
    std::string data(std::istreambuf_iterator<char>(input), eos);

    input.close();
    if (!alreadyEncrypted(data))
    {
        std::string::const_iterator keyIndex = key.begin();
        std::string::iterator dataIndex = data.begin();

        bool reverse = false;

        while (dataIndex != data.end())
        {
            int changeAmount = ((int)*keyIndex) + keyDifference(key);

            *dataIndex += changeAmount;


            if (!reverse)
            {
                keyIndex++;

                if (keyIndex == key.end())
                    reverse = true;
            }
            if (reverse)
            {
                keyIndex--;

                if (keyIndex == key.begin())
                    reverse = false;
            }

            dataIndex++;
        }

        data = "!1&" + data;
    }

    //Data should be encrypted
    //Store it in m_info
    m_info = data;
}

void Crypt::decrypt(const std::string key)
{
    std::ifstream input(m_target_file);

    std::istreambuf_iterator<char> eos;
    std::string data(std::istreambuf_iterator<char>(input), eos);

    input.close();
    
    if (alreadyEncrypted(data))
    {   
        data = data.substr(3, data.size());

        std::string::const_iterator keyIndex = key.begin();
        std::string::iterator dataIndex = data.begin();

        bool reverse = false;

        while (dataIndex != data.end())
        {
            int changeAmount = ((int)*keyIndex) + keyDifference(key);

            *dataIndex -= changeAmount;


            if (!reverse)
            {
                keyIndex++;

                if (keyIndex == key.end())
                    reverse = true;
            }
            if (reverse)
            {
                keyIndex--;

                if (keyIndex == key.begin())
                    reverse = false;
            }

            dataIndex++;
        }
    }

    //Data should be decrypted
    //Store it in m_info
    m_info = data;
}

int Crypt::keyDifference(const std::string key)
{
    int result = 0;
    for (int i = 0; i < key.size(); i++)
    {
        result += (int)key.at(i) / 7;
    }
    return result;
}

bool Crypt::alreadyEncrypted(const std::string data)
{
    if (data.size() > 2)
    {
        if (data.at(0) == '!' && data.at(1) == '1' && data.at(2) == '&')
            return true;
    }

    return false;
}
