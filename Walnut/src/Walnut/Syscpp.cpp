#include "Syscpp.h"

//return from system command as string and executes it
std::string execute(const std::string& command) {
    system((command + " > temp.txt").c_str());
    std::ifstream ifs("temp.txt");
    std::string ret{
      std::istreambuf_iterator <char>(ifs), std::istreambuf_iterator <char>()
    };
    ifs.close(); // must close the inout stream so the file can be cleaned up
    if (std::remove("temp.txt") != 0) { 
        perror("error deleting temporary file");
    }
    return ret;
}




void Forget(std::string wifi_name) {

    std::string command_user = "netsh wlan delete profile name=\u0022" + wifi_name + "\u0022";
    std::string username_string = execute(command_user);

}

//return saved wifi names
std::vector<std::string> UserName() {
    std::vector<std::string> vec_username;
    std::string password;
    std::string command_user = "netsh wlan show profile";
    std::string username_string = execute(command_user);
    std::istringstream iss(username_string);
    std::string line, key, value, username;

    //get username from the command_user and print
    while (std::getline(iss, line)) {
        std::replace(line.begin(), line.end(), ' ', '╜');
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "╜╜╜╜All╜User╜Profile╜╜╜╜╜") {
                std::replace(value.begin(), value.end(), '╜', ' ');
                username = value;
                username.erase(0, 1);
                vec_username.push_back(username);
            }
        }
    }
    return vec_username;
}

//return passwords of saved wifis
std::vector<std::string> Password() {

    std::vector<std::string> vec_password;
    std::string password;
    std::string command_user = "netsh wlan show profile";
    std::string username_string = execute(command_user);
    std::istringstream iss(username_string);
    std::string line, key, value, username;

    //get username from the command_user and print
    while (std::getline(iss, line)) {
        std::replace(line.begin(), line.end(), ' ', '╜');
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> value) {
            if (key == "╜╜╜╜All╜User╜Profile╜╜╜╜╜") {
                std::replace(value.begin(), value.end(), '╜', ' ');
                username = value;
                username.erase(0, 1);

                // add the gotten username to the command for finding password
                std::string command_pass = "netsh wlan show profile \u0022" + username + "\u0022 key = clear";

                std::string user_details_string = execute(command_pass);
                std::istringstream is(user_details_string);
                std::string line, key, value, value2;

                //find password and print
                while (std::getline(is, line)) {
                    std::replace(line.begin(), line.end(), ':', ' ');
                    std::istringstream linestream(line);
                    while (linestream >> key >> value >> value2) {
                        if (key == "Security" && value == "key" && value2 == "Absent") {
                            password = " ";
                            vec_password.push_back(password);
                        }

                        if (key == "Key" && value == "Content") {

                            password = value2;
                            vec_password.push_back(password);
                            break;

                        }
                    }
                }
            }
        }
    }
    return vec_password;
}