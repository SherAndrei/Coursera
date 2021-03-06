#include <iostream>
#include <exception>
#include <string>
using namespace std;

string AskTimeServer() {

}

class TimeServer {
 public:
    string GetCurrentTime() {
        string tmp;
        try {
            tmp = AskTimeServer();
            last_fetched_time = tmp;
        }
        catch (system_error& ex) {
            cout << ex.code() << ex.what() << endl;
        }
        return last_fetched_time;
    }

 private:
    string last_fetched_time = "00:00:00";
};


int main() {
    // ����� ���������� ������� AskTimeServer, ���������, ��� ��� ��� �������� ���������
    TimeServer ts;
    try {
        cout << ts.GetCurrentTime() << endl;
    }
    catch (exception& e) {
        cout << "Exception got: " << e.what() << endl;
    }
    return 0;
}
