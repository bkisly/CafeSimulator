#include "../../includes/controller/DataService.h"
#include "../../includes/model/helpers/exceptions.h"
#include <filesystem>
#include <fstream>

void DataService::ReadMenu(MenuDatabase &menuDb, string filename, bool syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << cloud.GET_REQUEST("https://caffe-simualtion.herokuapp"
                                           ".com/getmenu");
        ss >> menuDb;

    }
    else{
        filename = "../textFiles/" + filename;
        validatePath(filename);
        ifstream file;
        file.open(filename);
        file >> menuDb;
        file.close();
    }

}

void DataService::validatePath(string filename) {
    if(!(std::filesystem::exists(filename))){
        throw FileException("non existing file");
    }
}

void DataService::WriteMenu(MenuDatabase &menuDb, string filename, bool syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << menuDb;
        cloud.POST_REQUEST("https://caffe-simualtion.herokuapp"
                                ".com/postmenu", ss.str());

    }
    else{
        filename = "../textFiles/" + filename;
        ofstream file;
        file.open(filename);
        file << menuDb;
        file.close();
    }
}

void DataService::ReadTables(CustomTableDb &tablesDb, string filename, bool syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << cloud.GET_REQUEST("https://caffe-simualtion.herokuapp"
                                ".com/gettables");
        ss >> tablesDb;

    }
    else{
        filename = "../textFiles/" + filename;
        validatePath(filename);
        ifstream file;
        file.open(filename);
        file >> tablesDb;
        file.close();
    }
}

void DataService::WriteTables(MenuDatabase &tablesDb, string filename, bool syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << tablesDb;
        cloud.POST_REQUEST("https://caffe-simualtion.herokuapp"
                           ".com/posttables", ss.str());

    }
    else{
        filename = "../textFiles/" + filename;
        ofstream file;
        file.open(filename);
        file << tablesDb;
        file.close();
    }
}

void DataService::ReadEmployees(CustomEmployeesDb &employeesDb, string filename, bool
syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << cloud.GET_REQUEST("https://caffe-simualtion.herokuapp"
                                ".com/getemployess");
        ss >> employeesDb;

    }
    else{
        filename = "../textFiles/" + filename;
        validatePath(filename);
        ifstream file;
        file.open(filename);
        file >> employeesDb;
        file.close();
    }
}

void DataService::WriteEmployees(CustomEmployeesDb &employeesDb, string filename, bool
syncCloud) {
    if (syncCloud){
        stringstream ss;
        ss << employeesDb;
        cloud.POST_REQUEST("https://caffe-simualtion.herokuapp"
                           ".com/postemployes", ss.str());

    }
    else{
        filename = "../textFiles/" + filename;
        ofstream file;
        file.open(filename);
        file << employeesDb;
        file.close();
    }

}

DataService::DataService() {
    cloud = OnlineService();
}

