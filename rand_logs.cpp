#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <iomanip>

#define pair std::pair<uint32_t, uint32_t>

struct Date{
    int32_t year;
    int32_t month;
    int32_t day;
    int32_t hour;
    int32_t minute;
    int32_t sec;
};

struct User{
    std::string name;
    std::string id;
    uint32_t err;
    Date date;
};

struct Names{
    std::string* nms = nullptr;
    uint32_t size = 0; 
    uint32_t mx_len = 0;
};

void init_my_names(Names& names){
    names.size = 9;
    names.mx_len = 7;
    names.nms = new std::string[9];

    names.nms[0] = "Razor";
    names.nms[1] = "Bull";
    names.nms[2] = "Ronnie";
    names.nms[3] = "JV";
    names.nms[4] = "Webster";
    names.nms[5] = "Ming";
    names.nms[6] = "Kaze";
    names.nms[7] = "Jewels";
    names.nms[8] = "Earl";
}

void clear_nms(Names& names){
    delete[] names.nms;
    names.nms = nullptr;
    names.size = 0;
    names.mx_len = 0;
}

uint8_t count_dig(uint16_t num){
    uint8_t count = 0;
    while(num != 0){
        num /= 10;
        ++count;
    }
    
    return count;
}

void genere_id(std::string& lg){
    uint16_t id = rand() % 99 + 1;

    lg += "user";

    uint8_t count = count_dig(id);
    for (uint8_t i = 0; i < 2 - count; ++i){
        lg += "0";
    }

    lg += std::to_string(id);
}   

void genere_name(std::string& lg, const Names& names){
    std::string name = names.nms[rand() % names.size];
    for (uint16_t i = 0; i < names.mx_len - name.length(); ++i){
        lg += " ";
    }
    lg += name;
}

void genere_err(std::string& lg){
    uint16_t err = rand() % 1000;
    for (uint8_t i = 0; i < 3 - count_dig(err); ++i){
        lg += "0";
    }
    lg += std::to_string(err);
    
}

uint64_t genere_date(){
    uint64_t date = (uint64_t)(rand()) % (uint64_t)(time(0));
    return date;
}

void date_to_log(std::string& lg){
    int32_t year = 1960;
    int64_t date = genere_date();
    int32_t is_viskos = 0;

    year += 4 * (date / 126230400);
    date = date % 126220400;

    if (date < 31436000){
        is_viskos = 1;
    }

    year += date / 31536000;
    date = date % 31536000;

    int32_t month = 0;
    int32_t days = date / 86400; //Дни без месяца

    date %= 86400;

    int32_t monthes[]{31, 28 + is_viskos, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (days > monthes[month]){
        days -= monthes[month++];
    }

    int32_t hours = date / 3600;
    date %= 3600;
    int32_t minutes = date / 60;
    date %= 60;
    int32_t seconds = date;

    lg += std::to_string(days) + "." + std::to_string(month) + "." + std::to_string(year);
    lg += " " + std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);

}

void date_to_struct(Date& dt){
        int32_t year = 1960;
    int64_t date = genere_date();
    int32_t is_viskos = 0;

    year += 4 * (date / 126230400);
    date = date % 126220400;

    if (date < 31436000){
        is_viskos = 1;
    }

    year += date / 31536000;
    date = date % 31536000;

    int32_t month = 0;
    int32_t days = date / 86400; //Дни без месяца

    date %= 86400;

    int32_t monthes[]{31, 28 + is_viskos, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    while (days > monthes[month]){
        days -= monthes[month++];
    }

    int32_t hours = date / 3600;
    date %= 3600;
    int32_t minutes = date / 60;
    date %= 60;
    int32_t seconds = date;

    dt.day = days;
    dt.hour = hours;
    dt.month = month;
    dt.minute = minutes;
    dt.sec = seconds;
    dt.year = year;
}

void str_date_to_struct(std::string& str_date, Date& dt){
    size_t idx_strt = 0;
    size_t idx_end = 0;

    idx_end = str_date.find(".", idx_strt);
    dt.day = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt));

    idx_strt = idx_end + 1;
    idx_end = str_date.find(".", idx_strt);
    dt.month = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt));

    idx_strt = idx_end + 1;
    idx_end = str_date.find(" ", idx_strt);
    dt.year = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt));

    idx_strt = idx_end + 1;
    idx_end = str_date.find(":", idx_strt);
    dt.hour = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt));

    idx_strt = idx_end + 1;
    idx_end = str_date.find(":", idx_strt);
    dt.minute = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt));

    idx_strt = idx_end + 1;
    idx_end = str_date.length() - 1;
    dt.sec = std::stoi(str_date.substr(idx_strt, idx_end - idx_strt + 1));

}

std::string struct_to_str_date(Date& dt){
    std::string str_date;

    str_date += std::to_string(dt.day) + "." + std::to_string(dt.month) + "." + std::to_string(dt.year);
    str_date += " " + std::to_string(dt.hour) + ":" + std::to_string(dt.minute) + ":" + std::to_string(dt.sec);

    return str_date;
}

void genere_log(std::string& lg, const Names& names){
    lg.clear();
    genere_id(lg);
    lg += "  ";
    genere_name(lg, names);
    lg += "  ";
    genere_err(lg);
    lg += "  ";
    date_to_log(lg);
    lg += "\n";
}

void logs_to_file(uint32_t num_of_logs ,const Names& names_lst){
    std::ofstream log_out("logs.txt", std::ios::app);
    std::string lg;

    for (uint32_t i = 0; i < num_of_logs; ++i){
        genere_log(lg, names_lst);
        std::cout << lg;
        log_out << lg;
    }


    log_out.close();
}

int compare_dates(const Date& dt1, const Date& dt2){
    if (dt1.year < dt2.year){
        return 1;
    }
    else if (dt1.year > dt2.year){
        return -1;
    }
    else if (dt1.month < dt2.month){
        return 1;
    }   
    else if (dt1.month > dt2.month){
        return -1;
    }
    else if (dt1.day < dt2.day){
        return 1;
    }   
    else if (dt1.day > dt2.day){
        return -1;
    }
    else if (dt1.hour < dt2.hour){
        return 1;
    }   
    else if (dt1.hour > dt2.hour){
        return -1;
    }else if (dt1.minute < dt2.minute){
        return 1;
    }   
    else if (dt1.minute > dt2.minute){
        return -1;
    }
    else if (dt1.sec < dt2.sec){
        return 1;
    }   
    else if (dt1.sec > dt2.sec){
        return -1;
    }
    return 0;
}

int comparator(const void* str1, const void* str2){
    const std::string* s1 = reinterpret_cast<const std::string*>(str1);
    const std::string* s2 = reinterpret_cast<const std::string*>(str2);

    Date dt1;
    std::string str_date1 = (*s1).substr(22, (*s1).length() - 22);
    str_date_to_struct(str_date1, dt1);

    Date dt2;
    std::string str_date2 = (*s2).substr(22, (*s2).length() - 22);
    str_date_to_struct(str_date2, dt2);

    return !compare_dates(dt1, dt2);
}

void sort_file_date(const std::string& filename){
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }

    uint32_t line_count = 0;
    std::string line;

    while (std::getline(fin, line)){
        ++line_count;
    }

    fin.clear();
    fin.seekg(0, std::ios::beg);

    std::string* logs_lst = new std::string[line_count];

    for (uint32_t i = 0 ;std::getline(fin, line) && i < line_count; ++i){
        logs_lst[i] = line;
    }

    fin.close();

    qsort(logs_lst, line_count, sizeof(std::string), comparator);

    std::ofstream fout(filename);
    if (!fout.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }

    for (uint32_t i = 0; i < line_count; ++i){
        fout << logs_lst[i] << '\n';
    }

    fout.close();

    delete[] logs_lst;
}

int comp(const void* obj1, const void* obj2){
    const pair* el1 = reinterpret_cast<const pair*>(obj1);
    const pair* el2 = reinterpret_cast<const pair*>(obj2);

    if ((el2->second) > (el1->second)) return 1;
    else if ((el2->second) < (el1->second)) return -1;
    else return 0;
}

void top_n_active_users(const std::string& filename, uint32_t n){
    pair* active_board = new pair[99]{};

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }

    std::string line;

    for (uint32_t i = 0; i < 99; ++i){
        active_board[i].first = i + 1;
    }

    while (std::getline(fin, line)){
        if (std::stoi(line.substr(17, 1)) < 4){ 
            ++active_board[std::stoi(line.substr(5, 2))].second;
        }
    }


    qsort(active_board, 99, sizeof(pair), comp);

    for (uint32_t i = 0; i < n; ++i){
        std::cout << "user" << active_board[i].first << " logs count: " << active_board[i].second << '\n';
    }
    
    delete[] active_board;
}

void top_n_err_users(const std::string& filename, uint32_t n){
    pair* active_board = new pair[99]{};

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }

    std::string line;

    for (uint32_t i = 0; i < 99; ++i){
        active_board[i].first = i + 1;
    }

    while (std::getline(fin, line)){
        if (std::stoi(line.substr(17, 1)) > 3){ 
            ++active_board[std::stoi(line.substr(5, 2))].second;
        }
    }


    qsort(active_board, 99, sizeof(pair), comp);

    for (uint32_t i = 0; i < n; ++i){
        std::cout << "user" << active_board[i].first << " logs count: " << active_board[i].second << '\n';
    }
    
    delete[] active_board;
}

//График активности всего приложения
void create_plot(const std::string& filename){
    std::cout << "Periods of app activity:\n";
    std::cout << '\n';

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }
    
    int32_t active_logs[12]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::string line;
    std::string dt_line;
    Date dt;
    
    while(std::getline(fin, line)){
        dt_line = line.substr(22, line.length() - 22);
        str_date_to_struct(dt_line, dt);
        ++active_logs[(dt.year - 1960) / 5];
    }

    int32_t max = active_logs[0];
    for (uint32_t i = 1; i < 12; ++i){
        if (active_logs[i] >  max) max = active_logs[i];
    }

    for (int32_t i = 0; i <= 15; ++i){
        std::cout << std::setw(3) << max - i * (max / 12) << " | ";
        for (int32_t j = 0; j < 12; ++j){
            if (active_logs[j] > max - i * (max / 12) && active_logs[j] < max - (i - 1) * (max / 12)){
                std::cout << "  *****";
            }
            else{
                std::cout << "       ";
            }
        }
        std::cout << '\n';
    }
    for (uint32_t i = 0; i < 93; ++i){
        std::cout << '_';
    }

    std::cout << '\n';

    uint32_t year = 1960;
    std::cout << "      ";
    for (;year < 2020; year += 5){
        std::cout << std::setw(7) << year;
    }

    std::cout << '\n';

    fin.close();
}

void create_user_plot(const std::string& filename, uint32_t id){
    if (id > 99 && id == 0){
        std::cout << "Wrong id" << '\n';
        return;
    }


    std::cout << "Periods of user" << id << " activity:\n";
    std::cout << '\n';

    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Не удалось открыть файл: " << filename.c_str() << "\n";
        return;
    }
    
    int32_t active_logs[12]{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::string line;
    std::string dt_line;
    Date dt;
    
    while(std::getline(fin, line)){
        if (std::stoi(line.substr(4, 2)) != id){
            continue;
        }
        dt_line = line.substr(22, line.length() - 22);
        str_date_to_struct(dt_line, dt);
        ++active_logs[(dt.year - 1960) / 5];
    }

    int32_t max = active_logs[0];
    for (uint32_t i = 1; i < 12; ++i){
        if (active_logs[i] >  max) max = active_logs[i];
    }

    for (int32_t i = 0; i <= 15; ++i){
        std::cout << std::setw(3) << max - i * (max / 12) << " | ";
        for (int32_t j = 0; j < 12; ++j){
            if (active_logs[j] > max - i * (max / 12) && active_logs[j] < max - (i - 1) * (max / 12)){
                std::cout << "  *****";
            }
            else{
                std::cout << "       ";
            }
        }
        std::cout << '\n';
    }
    for (uint32_t i = 0; i < 93; ++i){
        std::cout << '_';
    }

    std::cout << '\n';

    uint32_t year = 1960;
    std::cout << "      ";
    for (;year < 2020; year += 5){
        std::cout << std::setw(7) << year;
    }

    std::cout << '\n';
    std::cout << '\n';

    fin.close();

}

int main(){
    srand(time(0));
    
    Names black_list{};
    init_my_names(black_list);
    
    logs_to_file(100, black_list);
    
    sort_file_date("logs.txt");
    top_n_active_users("logs.txt", 5);
    top_n_err_users("logs.txt", 5);


    create_plot("logs.txt");
    clear_nms(black_list);
    return 0;
}
