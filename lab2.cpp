#include <iostream>
#include <cstring>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

const int NAME_SIZE = 20;
const int HEADER_SIZE = 5 * sizeof(int); // 20 байт
const int RECORD_SIZE = 1 + NAME_SIZE + sizeof(int); // 1 + 20 + 4 = 25 байт

typedef struct Header {
    int act_cnt;      // количество активных элементов
    int del_cnt;     // количество удалённых
    int ft_act;      // указатель на первый активный элемент
    int ft_del;     // указатель на первый элемент в очереди удалённых
    int lt_del;      // указатель на последний элемент в очереди удалённых
}hd;

typedef struct Record {
    unsigned char deleted;      // бит удаления (1 - удалён, 0 - активен)
    char name[NAME_SIZE];       // наименование
    int next;                   // указатель на следующий элемент
}rec;

int remove_name(const char* filename, const char* name) {
    
    FILE* file = fopen(filename, "rb+");
    if (!file) {
        return -1; 
    }
    
    hd header;
    if (fread(&header, sizeof(hd), 1, file) != 1) {
        fclose(file);
        return -1;
    }
    
    // Проверяем, есть ли активные элементы
    if (header.act_cnt == 0) {
        fclose(file);
        return 0; 
    }
    
    // Поиск элемента и предыдущего в списке активных
    int current = header.ft_act;
    int previous = 0;
    rec currrec;
    
    while (current != 0) {
        if (fseek(file, current, SEEK_SET) != 0) {
            fclose(file);
            return -1;
        }
        
        // Читаем текущую запись
        if (fread(&currrec, sizeof(rec), 1, file) != 1) {
            fclose(file);
            return -1;
        }
        
        if (strcmp(currrec.name, name) == 0) {
            // Исключаем из списка активных
            if (previous == 0) {
                header.ft_act = currrec.next;
            } else {
                // Удаляем не первый элемент - обновляем указатель next у предыдущего
                if (fseek(file, previous, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                rec prevrec;
                if (fread(&prevrec, sizeof(rec), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                prevrec.next = currrec.next;
                
                if (fseek(file, previous, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                if (fwrite(&prevrec, sizeof(rec), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
            }
            
            header.act_cnt--;
            
            // Помечаем запись как удалённую
            currrec.deleted = 1;
            currrec.next = 0;
            
            // Записываем обновлённую запись
            if (fseek(file, current, SEEK_SET) != 0) {
                fclose(file);
                return -1;
            }
            
            if (fwrite(&currrec, sizeof(rec), 1, file) != 1) {
                fclose(file);
                return -1;
            }
            
            // Добавляем в очередь удалённых
            if (header.del_cnt == 0) {
                header.ft_del = current;
                header.lt_del = current;
            } else {
                // Добавляем в конец очереди
                if (fseek(file, header.lt_del, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                rec lastrec;
                if (fread(&lastrec, sizeof(rec), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                lastrec.next = current;
                
                if (fseek(file, header.lt_del, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                if (fwrite(&lastrec, sizeof(rec), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                header.lt_del = current;
            }
            
            header.del_cnt++;
            
            // Сохраняем обновлённый заголовок
            if (fseek(file, 0, SEEK_SET) != 0) {
                fclose(file);
                return -1;
            }
            
            if (fwrite(&header, sizeof(hd), 1, file) != 1) {
                fclose(file);
                return -1;
            }
            
            fflush(file);
            fclose(file);
            return 1; // Успешное удаление
        }
        
        previous = current;
        current = currrec.next;
    }
    
    fclose(file);
    return 0; // Элемент не найден
}

int main() {
    const char* filename = "test.dat";
    const char* name_rem = "Второй";
    
    int result = remove_name(filename, name_rem);
    
    if (result == 1) {
        cout << "Элемент '" << name_rem << "' успешно удалён\n";
    } else if (result == 0) {
        cout << "Элемент '" << name_rem << "' не найден\n";
    } else {
        cout << "Ошибка при работе с файлом\n";
    }
    
    return 0;
}