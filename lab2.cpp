#include <iostream>
#include <cstring>
#include <cstdio>

using std::cout;
using std::cin;
using std::endl;

const int NAME_SIZE = 20;
const int HEADER_SIZE = 5 * sizeof(int); // 20 байт
const int RECORD_SIZE = 1 + NAME_SIZE + sizeof(int); // 1 + 20 + 4 = 25 байт

struct Header {
    int activeCount;      // количество активных элементов
    int deletedCount;     // количество удалённых
    int firstActive;      // указатель на первый активный элемент
    int firstDeleted;     // указатель на первый элемент в очереди удалённых
    int lastDeleted;      // указатель на последний элемент в очереди удалённых
};

struct Record {
    unsigned char deleted;      // бит удаления (1 - удалён, 0 - активен)
    char name[NAME_SIZE];       // наименование
    int next;                   // указатель на следующий элемент
};

int removeByName(const char* filename, const char* name) {
    
    FILE* file = fopen(filename, "rb+");
    if (!file) {
        return -1; 
    }
    
    Header header;
    if (fread(&header, sizeof(Header), 1, file) != 1) {
        fclose(file);
        return -1;
    }
    
    // Проверяем, есть ли активные элементы
    if (header.activeCount == 0) {
        fclose(file);
        return 0; 
    }
    
    // Поиск элемента и предыдущего в списке активных
    int current = header.firstActive;
    int previous = 0;
    Record currRecord;
    
    while (current != 0) {
        if (fseek(file, current, SEEK_SET) != 0) {
            fclose(file);
            return -1;
        }
        
        // Читаем текущую запись
        if (fread(&currRecord, sizeof(Record), 1, file) != 1) {
            fclose(file);
            return -1;
        }
        
        if (strcmp(currRecord.name, name) == 0) {
            // Исключаем из списка активных
            if (previous == 0) {
                header.firstActive = currRecord.next;
            } else {
                // Удаляем не первый элемент - обновляем указатель next у предыдущего
                if (fseek(file, previous, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                Record prevRecord;
                if (fread(&prevRecord, sizeof(Record), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                prevRecord.next = currRecord.next;
                
                if (fseek(file, previous, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                if (fwrite(&prevRecord, sizeof(Record), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
            }
            
            header.activeCount--;
            
            // Помечаем запись как удалённую
            currRecord.deleted = 1;
            currRecord.next = 0;
            
            // Записываем обновлённую запись
            if (fseek(file, current, SEEK_SET) != 0) {
                fclose(file);
                return -1;
            }
            
            if (fwrite(&currRecord, sizeof(Record), 1, file) != 1) {
                fclose(file);
                return -1;
            }
            
            // Добавляем в очередь удалённых
            if (header.deletedCount == 0) {
                header.firstDeleted = current;
                header.lastDeleted = current;
            } else {
                // Добавляем в конец очереди
                if (fseek(file, header.lastDeleted, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                Record lastRecord;
                if (fread(&lastRecord, sizeof(Record), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                lastRecord.next = current;
                
                if (fseek(file, header.lastDeleted, SEEK_SET) != 0) {
                    fclose(file);
                    return -1;
                }
                
                if (fwrite(&lastRecord, sizeof(Record), 1, file) != 1) {
                    fclose(file);
                    return -1;
                }
                
                header.lastDeleted = current;
            }
            
            header.deletedCount++;
            
            // Сохраняем обновлённый заголовок
            if (fseek(file, 0, SEEK_SET) != 0) {
                fclose(file);
                return -1;
            }
            
            if (fwrite(&header, sizeof(Header), 1, file) != 1) {
                fclose(file);
                return -1;
            }
            
            fflush(file);
            fclose(file);
            return 1; // Успешное удаление
        }
        
        previous = current;
        current = currRecord.next;
    }
    
    fclose(file);
    return 0; // Элемент не найден
}

int main() {
    const char* filename = "test.dat";
    const char* nameToRemove = "Второй";
    
    int result = removeByName(filename, nameToRemove);
    
    if (result == 1) {
        cout << "Элемент '" << nameToRemove << "' успешно удалён\n";
    } else if (result == 0) {
        cout << "Элемент '" << nameToRemove << "' не найден\n";
    } else {
        cout << "Ошибка при работе с файлом\n";
    }
    
    return 0;
}