#include <iostream>
#include <fstream>

#define PATH "our_list.txt"


struct TRAIN {
    std::string dest;
    std::string train_num;
    std::string time;
    struct TRAIN* next;
    TRAIN() {}
    TRAIN(std::string dest, std::string time, std::string train_num) : dest(dest), time(time), train_num(train_num), next(nullptr) {}
};

void printlist( TRAIN* head);

struct list {
    int len;
    TRAIN* first;
    TRAIN* last;

    list() : first(nullptr), last(nullptr), len(0) {}

    bool is_empty() {
        return first == nullptr;
    }

    void push_back(std::string dest, std::string time, std::string train_num) {
        TRAIN* p = new TRAIN(dest, time, train_num);
        len += 1;
        if (is_empty()) {
            first = p;
            last = p;
            return;
        }
        last->next = p;
        last = p;
    }

    void print() {
        if (is_empty()) return;
        TRAIN* p = first;
        while (p) {
            std::cout << p->train_num << " " << p->dest << " " << p->time << std::endl;
            p = p->next;
        }
    }

    void insert(std::string dest, std::string time, std::string train_num, int ind) {
        if (is_empty() or ind > (len + 1)) return;
        if (ind == 1) {
            TRAIN* neww = new TRAIN(dest, time, train_num);
            neww->next = first;
            first = neww;
            return;
        }
        len += 1;
        TRAIN* cur = first;
        for (int i = 1; i < (ind - 1); i++) {
            cur = cur->next;
        }
        TRAIN* neww = new TRAIN(dest, time, train_num);
        neww->next = cur->next;
        cur->next = neww;
    }

    void remove(int ind) {
        if (is_empty() or ind > len) return;
        len -= 1;
        if (ind == 1) {
            delete first;
            first = first->next;
            return;
        }
        TRAIN* cur = first;
        for (int i = 1; i < ind - 1; i++) {
            cur = cur->next;
        }
        TRAIN* tmp;
        if (ind != len) tmp = cur->next->next;
        delete cur->next;
        if (ind == len) cur->next = nullptr;
        else cur->next = tmp;
    }

    TRAIN* search(int n, std::string val) { // 1-dest, 2-time, 3-train_num
        TRAIN* cur = first;
        for (int i = 1; i < len; i++) {
            if (n == 1) {
                if (val == cur->dest) return cur;
            }
            else if (n == 2) {
                if (val == cur->time) return cur;
            }
            else if (n == 3) {
                if (val == cur->train_num) return cur;
            }
            cur = cur->next;
        }
        return new TRAIN("0", "0", "0");
    }

    void print_by_val(int n, std::string val) {
        TRAIN* cur = search(n, val);
        if ((cur->dest == "0") && (cur->time == "0") && (cur->train_num == "0")) std::cout << "Данный элемент отсутствует" << std::endl;
        std::cout << cur->dest << " " << cur->time << " " << cur->train_num << std::endl;
    }

    void print_by_ind(int ind) {
        TRAIN* cur = first;
        for (int i = 1; i < ind; i++) {
            cur = cur->next;
        }
        std::cout << cur->dest << " " << cur->time << " " << cur->train_num << std::endl;
    }

    void edit(int ind, std::string dest, std::string time, std::string train_num) {
        TRAIN* cur = first;
        for (int i = 1; i < ind; i++) {
            cur = cur->next;
        }
        cur->dest = dest;
        cur->time = time;
        cur->train_num = train_num;
    }

    void sort(int k) {
        TRAIN *i, *j;
        std::string temp_dest, temp_time, temp_train;
        for (i = first; i->next != nullptr; i = i->next) {
            for (j = i->next; j != nullptr; j = j -> next) {
                if ((k == 1) && (i->dest > j->dest) || (k == 2) && (i->time > j->time) || (k == 3) && (i->train_num > j->train_num)) {
                    temp_dest = i->dest;
                    temp_time = i->time;
                    temp_train = i->train_num;
                    i->dest = j->dest;
                    i->time = j->time;
                    i->train_num = j->train_num;
                    j->dest = temp_dest;
                    j->time = temp_time;
                    j->train_num = temp_train;
                }
            }
        }
    }

    void write_in_file(std::string path) {
        std::ofstream fout;
        fout.open(path, std::ofstream::out | std::ofstream::trunc);
        if (!fout.is_open()) {
            std::cout << "Ошибка при открытии файла" << std::endl;
        }
        else {
            if (is_empty()) return;
            TRAIN* p = first;
            while (p) {
                fout << p->dest << " " << p->time << " " << p->train_num << std::endl;
                p = p->next;
            }
        }
        fout.close();
    }

    void read_from_file(std::string path, list* l) {
        std::ifstream fin;
        fin.open(path);
        std::string dest, time, train_num;
        if (!fin.is_open()) {
            std::cout << "Ошибка при открытии файла за чтения данных" << std::endl;
        }
        else {
            while (!fin.eof()) {
                fin >> train_num >> dest >> time;
                if (fin.eof()) return;
                l->push_back(dest, time, train_num);
            }
        }
        fin.close();
    }

    void del() {
        while (first != nullptr) {
            TRAIN *next = first->next;
            delete first;
            first = next;
        }
    }

    ~list() {
        while (first != nullptr) {
            TRAIN *next = first->next;
            delete first;
            first = next;
        }
    }



    // SORTINg_____________________________
    TRAIN* mergeLists(TRAIN* a, TRAIN* b) {
        TRAIN tmp;
        TRAIN *head = &tmp;
        TRAIN *c = head;
        while ((a != NULL) && (b != NULL)) {
            if (a->dest < b->dest) {
                c->next = a;
                c = a;
                a = a->next;
            } else {
                c->next = b;
                c = b;
                b = b->next;
            }
        }
        c->next = (a == NULL) ? b : a;
        //this->first = head;
        return head;

    }

    TRAIN* mergeSort(TRAIN* c) {
        if (c == NULL || c->next == NULL) return c;
        TRAIN* a = c;
        TRAIN* b = c->next;
        while ((b != NULL) && (b->next != NULL)) {
            c = c->next;
            b = b->next->next;
        }
        b = c->next;
        c->next = NULL;
        printlist(a);
        printlist(b);
        std::cout << "-----" << std::endl;
        return mergeLists(mergeSort(a), mergeSort(b));
    }

    void merge(list& a, list& b, list& result) {
        TRAIN* i = a.first;
        TRAIN* j = b.first;
        if (i->dest <= j->dest) {
            result.first = result.last = i;
            i = i->next;
        }
        else {
            result.first = result.last = j;
            j = j->next;
        }
        while (i != NULL && j != NULL) {
            if (i->dest <= j->dest) {
                result.last->next = i;
                i->next = result.last;

            }
        }
    }
};

void printlist( TRAIN* head) {
    TRAIN* it = head;
    while (true) {
        std::cout << it->train_num << " " << it->dest << " " << it->time << std::endl;
        if (it->next == NULL) break;
        it = it->next;
    }
    std::cout << std::endl;
}

void print_options() {
    std::cout << "\tВыберите действие:" << std::endl;
    std::cout << "\t1)Создание списка.(используется вначале)" << std::endl;
    std::cout << "\t2)Добавление элемента в конец списка." << std::endl;
    std::cout << "\t3)Вставка элемента в произвольное место списка." << std::endl;
    std::cout << "\t4)Удаление произвольного элемента из списка." << std::endl;
    std::cout << "\t5)Поиск элемента списка по заданному ключу." << std::endl;
    std::cout << "\t6)Сортировка списка по заданному ключу, при помощи переключения"
                 " указателей." << std::endl;
    std::cout << "\t7)Просмотр данных произвольного элемента списка." << std::endl;
    std::cout << "\t8)Редактирование данных произвольного элемента списка." << std::endl;
    std::cout << "\t9)Просмотр всего списка с выводом данных на экран." << std::endl;
    std::cout << "\t10)Уничтожение списка." << std::endl;
    std::cout << "\t11)Запись списка в файл." << std::endl;
    std::cout << "\t12)Чтение списка из файла." << std::endl;
    std::cout << "\t0)Выход из программы." << std::endl;
}

void list_init(){
    std::cout << "Список создан."<< std::endl;
}

void push_back(list* l) {
    std::cout << "Введите информацию о поезде в формате: город время номер_поезда" << std::endl;
    std::string dest, time, train_num;
    std::cin >> dest >> time >> train_num;
    l->push_back(dest, time, train_num);
    std::cout << "Поезд добавлен в список." << std::endl;
}

void insert(list* l) {
    std::cout << "Введите информацию о поезде и номер в списке, куда его следует вставить в формате: город время номер_поезда индекс" << std::endl;
    std::string dest, time, train_num;
    int ind;
    std::cin >> dest >> time >> train_num >> ind;
    l->insert(dest, time, train_num, ind);
    std::cout << "Элемент вставлен." << std::endl;
}

void remove_elem(list* l) {
    std::cout << "Введите номер элемента, который нужно удалить:" << std::endl;
    int i;
    std::cin >> i;
    l->remove(i);
}

void search(list* l) {
    std::cout << "Введите по какому полю искать значение и само значение: city/time/number_of_train  значение" << std::endl;
    int k;
    std::string type, elem;
    std::cin >> type >> elem;
    if (type == "city") k = 1;
    else if (type == "time") k = 2;
    else if (type == "number") k = 3;
    else {
        std::cout << "wrong input" << std::endl;
        std::cout << type << std::endl;
        return;
    }
    l->print_by_val(k, elem);
}

void sort_list(list* l) {
    std::cout << "Введите по какому ключу сортировать: city/time/train_num" << std::endl;
    std::string s;
    std::cin >> s;
    int k;
    if (s == "city") k = 1;
    else if (s == "time") k = 2;
    else if (s == "train_num") k = 3;
    else {
        std::cout << "Wrong input" << std::endl;
        return;
    }
    TRAIN* tmp = l->mergeSort(l->first);
    std::cout << tmp->dest << std::endl;
}

void print_by_ind(list* l) {
    std::cout << "Введите номер элемента в списке: " << std::endl;
    int ind;
    std::cin >> ind;
    l->print_by_ind(ind);
}

void edit(list* l) {
    std::cout << "Введите номер элемента который стоит изменить и его данные: номер   город время номер поезда" << std::endl;
    int ind;
    std::string dest, time, train_num;
    std::cin >> ind >> dest >> time >> train_num;
    l->edit(ind, dest, time, train_num);
    std::cout << "Элемент изменен" << std::endl;
}

void print_list(list* l) {
    l->print();
}

void delete_list(list* l) {
    l->del();
    // delete l;
}

void write_in_file(list* l) {
    l->write_in_file(PATH);
    std::cout << "Файл записан в файл: " << PATH << std::endl;
}

void read_from_file(list* l) {
    l->read_from_file(PATH, l);
    std::cout << "Элементы из файла " << PATH << " добавлены в список" << std::endl;

}

int main() {
    int n;
    std::string s;
    do {
        std::cout << "Сперва создайте список" << std::endl;
        print_options();
        std::cout << "_________________" << std::endl;
        std::cin >> n;
    } while (n != 1);
    list* l = new list();
    list_init();
    do {
        std::getline(std::cin, s);
        std::getline(std::cin, s);
        print_options();
        std::cin >> n;
        switch (n) {
            case 1: {
                list* l = new list();
                list_init();
                break;
            }
            case 2: {
                push_back(l);
                break;
            }
            case 3: {
                insert(l);
                break;
            }
            case 4: {
                remove_elem(l);
                break;
            }
            case 5: {
                search(l);
                break;
            }
            case 6: {
                sort_list(l);
                break;
            }
            case 7: {
                print_by_ind(l);
                break;
            }
            case 8: {
                edit(l);
                break;
            }
            case 9: {
                print_list(l);
                break;
            }
            case 10: {
                delete_list(l);
                break;
            }
            case 11: {
                write_in_file(l);
                break;
            }
            case 12: {
                read_from_file(l);
                break;
            }
            case 0: {
                break;
            }
            default: {
                std::cout << "Попробуйте ввести новое значение" << std::endl;
                break;
            }
        }
    } while (n != 0);
    return 0;
}