#include <iostream>
#include <Windows.h>
#include <fstream>

#define cls system("cls")
#define path "database.bin"

using namespace std;

class Program {

public:
	void cin_i_cl() {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
	}

	void cin_c_cl() {
		cin.seekg(0, ios::end);
		cin.clear();
	}

	bool check_date(int day, int month, int year) {
		if (day != 0 && month != 0 && year != 0) {
			if (1900 <= year && year <= 2022) {
				if (1 <= month && month <= 12) {
					switch (month) {

					case 1: case 3: case 5: case 7: case 8: case 10: case 12:
						if (1 <= day && day <= 31) {
							return true;
						}
						break;

					case 4: case 6: case 9: case 11:
						if (1 <= day && day <= 31) {
							return true;
						}
						break;

					case 2:
						if (year % 4 != 0 || (year % 100 == 0 && year % 400 != 0)) {
							if (1 <= day && day <= 28) {
								return true;
							}
						}
						else {
							if (1 <= day && day <= 29) {
								return true;
							}
						}
						break;

					default:
						break;
					}
				}
				else {
					cout << "ОШИБКА - Месяц должен быть от 1 до 12.\n";
					return false;
				}
			}
			else {
				cout << "ОШИБКА - Год должен быть от 1900 до 2022.\n";
				return false;
			}
		}

		cout << "ОШИБКА - Неверный формат даты.\n";
		return false;
	}

	int check_entry_year() {
		int year;
		while (true) {
			cin >> year;
			if (1900 <= year && year <= 2040) {
				cin_i_cl();
				return year;
			}
			cout << "[ERROR] >> Год поступления должен быть от 1900 до 2040 = ";
			cin_i_cl();
		}
	}

	int check_count_session() {
		int count;
		while (true) {
			cin >> count;
			if (1 <= count && count <= 9) {
				cin_i_cl();
				return count;
			}
			cout << "ОШИБКА - Количество сессий должно быть от 1 до 9 = ";
			cin_i_cl();
		}
	}

	int check_count_subject() {
		int count;
		while (true) {
			cin >> count;
			if (1 <= count && count <= 10) {
				cin_i_cl();
				return count;
			}
			cout << "ОШИБКА - Количество предметов должно быть от 1 до 10 = ";
			cin_i_cl();
		}
	}

	int check_mark() {
		int mark;
		while (true) {
			cin >> mark;
			if (2 <= mark && mark <= 5) {
				cin_i_cl();
				return mark;
			}
			cout << "ОШИБКА - Оценка должна быть от 2 до 5 = ";
			cin_i_cl();
		}
	}

	char check_gender() {
		char gender;
		while (true) {
			cin >> gender;
			if (gender == 'F' || gender == 'M') {
				cin_c_cl();
				return gender;
			}
			cout << "ОШИБКА - Пол должен быть только F для Female или М для Male = ";
			cin_c_cl();
		}
	}


	char* check_special_symbols(char* _string, int len) {
		cin_c_cl();
		char spec_symbols[90] = "[]{}+=&^:;\\|/><$#@.,!?№%()\'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		bool flag = 0;
		cin.get(_string, len);

		if (*_string == 0) {
			cout << "ОШИБКА - Введена пустая строка, вводите не пустую строку = ";
			cin_c_cl();
			check_special_symbols(_string, len);
		}

		for (int i = 0; i < str_len(_string); i++) {
			for (int j = 0; j < 90; j++) {
				if (*(_string + i) == spec_symbols[j]) {
					flag = 1;
					break;
				}
			}
			if (flag == 1) {
				break;
			}
		}

		if (flag == 0) {
			return _string;
			cin_c_cl();
		}
		else {
			cout << "ОШИБКА - Введены спецсимволы / латиница, вводите без них = ";
			cin_c_cl();
			check_special_symbols(_string, len);

		}
	}

	int str_len(char* s) {
		int i;
		for (i = 0; s[i] != '\0'; i++);
		return i;
	}

	bool str_compare(char* _s1, char* _s2) {
		int _len1 = str_len(_s1), _len2 = str_len(_s2);
		if (_len1 != _len2) {
			return false;
		}
		else {
			for (int i = 0; i < _len1; i++) {
				if (_s1[i] != _s2[i]) {
					return false;
				}
			}
			return true;
		}
	}

};

class Student : public Program {

	char* l_name = nullptr;
	char* f_name = nullptr;
	char* m_name = nullptr;

	int* day = nullptr;
	int* month = nullptr;
	int* year = nullptr;

	char* gender = nullptr;

	int* entry_year = nullptr;
	char* faculty = nullptr;
	char* department = nullptr;
	char* group = nullptr;
	char* markbook_number = nullptr;

public:
	friend class File;
	friend class Task;

	Student() {
		l_name = new char[41]();
		f_name = new char[41]();
		m_name = new char[41]();
		day = new int(0);
		month = new int(0);
		year = new int(0);
		gender = new char('\0');
		entry_year = new int(0);
		faculty = new char[21]();
		department = new char[21]();
		group = new char[21]();
		markbook_number = new char[11]();
	}

	~Student() {
		delete l_name;
		delete f_name;
		delete m_name;
		delete day;
		delete month;
		delete year;
		delete gender;
		delete entry_year;
		delete faculty;
		delete department;
		delete group;
		delete markbook_number;
	}

	void set() {
		set_l_name();
		set_f_name();
		set_m_name();
		set_date();
		set_gender();
		set_entry_year();
		set_faculty();
		set_department();
		set_group();
		set_markbook_number();
	}


	void set_l_name() {
		cout << "\nВВОД -  Введите фамилию <40> = ";
		l_name = check_special_symbols(l_name, 41);
		cin_c_cl();
	}

	void set_f_name() {
		cout << "\nВВОД -  Введите имя <40> = ";
		f_name = check_special_symbols(f_name, 41);
		cin_c_cl();
	}

	void set_m_name() {
		cout << "\nВВОД -  Введите отчество <40> = ";
		m_name = check_special_symbols(m_name, 41);
		cin_c_cl();
	}

	void set_date() {
		cout << "\nВВОД -  Введите дату рождения <dd.mm.yyyy> = ";
		char* date = new char[11];
		*day = 0;
		*month = 0;
		*year = 0;

		cin.get(date, 11);
		cin_c_cl();

		if (*date == 0) {
			cout << "\nОШИБКА - Введена пустая строка";
			cin_c_cl();
			set_date();
		}

		for (int i = 0; *(date + i) != '\0'; i++) {
			if (*(date + i) >= 48 && *(date + i) <= 57 && ((i >= 0 && i <= 1) || (i >= 3 && i <= 4) || (i >= 6 && i <= 9))) {
				switch (i) {
				case 0: case 1:
					*day = *day * 10 + *(date + i) - 0x30;
					break;
				case 3: case 4:
					*month = *month * 10 + *(date + i) - 0x30;
					break;
				case 6: case 7: case 8: case 9:
					*year = *year * 10 + *(date + i) - 0x30;
					break;
				}
			}
		}
		delete[] date;
		if (!check_date(*day, *month, *year)) {
			*day = 0;
			*month = 0;
			*year = 0;
			set_date();
		}
	}

	void set_gender() {
		cout << "\nВВОД -  Введите пол <M/F> = ";
		*gender = check_gender();
		cin_c_cl();
	}

	void set_entry_year() {
		cout << "\nВВОД -  Введите год поступления = ";
		*entry_year = check_entry_year();
		if (*entry_year <= *year) {
			cout << "ОШИБКА - Год поступления не может быть меньше или равен году рождения.\n";
			set_entry_year();
		}
	}

	void set_faculty() {
		cout << "\nВВОД -  Введите факультет <20> = ";
		faculty = check_special_symbols(faculty, 21);
		cin_c_cl();
	}

	void set_department() {
		cout << "\nВВОД -  Введите кафедру <20> = ";
		department = check_special_symbols(department, 21);
		cin_c_cl();
	}

	void set_group() {
		cout << "\nВВОД -  Введите группу <20> = ";
		group = check_special_symbols(group, 21);
		cin_c_cl();
	}

	void set_markbook_number() {
		cout << "\nВВОД -  Введите номер зачётной книжки <10> = ";
		markbook_number = check_special_symbols(markbook_number, 11);
		cin_c_cl();
		if (!check_mrbk_numb(markbook_number)) {
			cout << "ОШИБКА - Такой номер зачётной книжки уже существует.\n";
			set_markbook_number();
		}
	}

	bool check_mrbk_numb(char* _numb) {
		char* tmp_numb = new char[11];
		ifstream file;
		file.open(path, ios::binary);
		if (!file.is_open()) {
			return 1;
		}
		int* length = new int(0);
		file.seekg(0, ios::end);
		*length = file.tellg();
		if (*length == 0) {
			return 1;
		}

		int* cur = new int(0);
		file.seekg(0, ios::beg);
		while (*cur != *length) {
			file.seekg(208, ios::cur);
			*cur += 208;
			file.read(tmp_numb, 11);
			*cur += 11;
			if (str_compare(_numb, tmp_numb)) {
				return 0;
			}
			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}
		file.close();
		return 1;
	}

};

class Session : public Program {
	int* session_count = nullptr;
	int* subject_count = nullptr;
	char** subject_name = nullptr;
	int* subject_mark = nullptr;

public:
	friend class File;
	friend class Task;

	Session() {
		session_count = new int(0);
		subject_count = nullptr;
		subject_name = nullptr;
		subject_mark = new int(0);
	}

	~Session() {
		delete session_count;
		delete subject_count;
		delete subject_name;
		delete subject_mark;
	}

	void set() {
		set_session_count();
		set_subject_count();
		set_subject();
	}


	void set_session_count() {
		cout << "\nВВОД -  Введите количество сессий <1-9> = ";
		*session_count = check_count_session();
	}

	void set_subject_count() {
		subject_count = new int[*session_count];
		for (int i = 0; i < *session_count; i++) {
			cout << "\nВВОД -  Введите количество предметов в " << i + 1 << " семестре <1-10> = ";
			*(subject_count + i) = check_count_subject();
		}
	}


	void set_subject() {
		int* count = new int(0);
		for (int i = 0; i < *session_count; i++) {
			*count += *(subject_count + i);
		}

		subject_name = new char* [*count];
		subject_mark = new int[*count];
		int* numb_sess = new int(0);
		int* numb_subj = new int(0);

		for (int i = 0; i < *count; i++) {
			if (*numb_subj >= subject_count[*numb_sess]) {
				(*numb_sess)++;
				*numb_subj = 0;
			}
			(*numb_subj)++;
			*(subject_name + i) = new char[21];
			cout << "\nВВОД -  Введите название " << *numb_subj << " предмета за " << *numb_sess + 1 << " семестр = ";
			*(subject_name + i) = check_special_symbols(*(subject_name + i), 21);
			cin_c_cl();
			cout << "\nВВОД -  Введите оценку за " << *(subject_name + i) << " в " << *numb_sess + 1 << " семестре <2-5> = ";
			*(subject_mark + i) = check_mark();
		}

		delete count;
		delete numb_sess;
		delete numb_subj;

	}

};

class File : Program {
	int* length = nullptr;
	int* cur = nullptr;
	int* numb = nullptr;
	char* mrbk_numb = nullptr;
	char* mrbk_numb_t = nullptr;

public:

	File() {
		length = new int(0);
		cur = new int(0);
		numb = new int(0);
		mrbk_numb = new char[11];
		mrbk_numb_t = new char[11];
	}

	~File() {
		delete length;
		delete cur;
		delete numb;
		delete mrbk_numb;
		delete mrbk_numb_t;
	}

	int get_records() {
		int* _records = new int(0);

		ifstream file;
		file.open(path, ios::binary);

		length = new int(0);

		file.seekg(0, ios::end);
		*length = file.tellg();

		file.seekg(0, ios::beg);
		cur = new int(0);

		while (*cur != *length) {
			*_records += 1;
			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}


		file.close();
		return *_records;
	}

	void write_all_stud_ses(Student* student, Session* session, ofstream& file) {
		file.write(student->l_name, 41);
		file.write(student->f_name, 41);
		file.write(student->m_name, 41);
		file.write((char*)student->day, 4);
		file.write((char*)("\0"), 1);
		file.write((char*)student->month, 4);
		file.write((char*)("\0"), 1);
		file.write((char*)student->year, 4);
		file.write((char*)("\0"), 1);
		file.write(student->gender, 1);
		file.write((char*)("\0"), 1);
		file.write((char*)student->entry_year, 4);
		file.write((char*)("\0"), 1);
		file.write(student->faculty, 21);
		file.write(student->department, 21);
		file.write(student->group, 21);
		file.write(student->markbook_number, 11);


		file.write((char*)session->session_count, 4);
		file.write((char*)("\0"), 1);

		for (int i = 0; i < *session->session_count; i++) {
			file.write((char*)&session->subject_count[i], 4);
			file.write((char*)("\0"), 1);
		}

		numb = new int(0);
		for (int i = 0; i < *session->session_count; i++) {
			*numb += *(session->subject_count + i);
		}

		for (int i = 0; i < *numb; i++) {
			file.write((char*)&*(*(session->subject_name + i)), 21);
			file.write((char*)&(*(session->subject_mark + i)), 4);
			file.write((char*)("\0"), 1);
		}

		file.write("\n", 1);
	}

	void read_all_stud_ses(Student* student, Session* session, ifstream& file) {
		file.read(student->l_name, 41);
		file.read(student->f_name, 41);
		file.read(student->m_name, 41);
		file.read((char*)student->day, 4);
		file.seekg(1, ios::cur);
		file.read((char*)student->month, 4);
		file.seekg(1, ios::cur);
		file.read((char*)student->year, 4);
		file.seekg(1, ios::cur);
		file.read(student->gender, 1);
		file.seekg(1, ios::cur);
		file.read((char*)student->entry_year, 4);
		file.seekg(1, ios::cur);
		file.read(student->faculty, 21);
		file.read(student->department, 21);
		file.read(student->group, 21);
		file.read(student->markbook_number, 11);
		file.read((char*)session->session_count, 4);
		file.seekg(1, ios::cur);
		session->subject_count = new int[*session->session_count];
		numb = new int(0);
		for (int i = 0; i < *session->session_count; i++) {
			file.read((char*)&*(session->subject_count + i), 4);
			file.seekg(1, ios::cur);
			*numb += *(session->subject_count + i);
		}
		session->subject_name = new char* [*numb];
		session->subject_mark = new int[*numb];
		for (int i = 0; i < *numb; i++) {
			*(session->subject_name + i) = new char[21];
			file.read((char*)&*(*(session->subject_name + i)), 21);
			file.read((char*)&(*(session->subject_mark + i)), 4);
			file.seekg(1, ios::cur);
		}
		file.seekg(1, ios::cur);

	}

	void cout_all_info(Student* student, Session* session) {
		cout << "\n"; for (int i = 0; i < 144; i++) cout << "_"; cout << "\n\n";
		cout << "|_______________Фамилия__________________|__________________Имя___________________|_______________Отчество_________________|_П_|_Дата_Рождения_|\n";
		cout << "|" << student->l_name;
		for (int i = 0; i < 40 - str_len(student->l_name); i++) cout << ' ';
		cout << "|" << student->f_name;
		for (int i = 0; i < 40 - str_len(student->f_name); i++) cout << ' ';
		cout << "|" << student->m_name;
		for (int i = 0; i < 40 - str_len(student->m_name); i++) cout << ' ';
		cout << "|" << *student->gender;
		for (int i = 0; i < 2; i++) cout << ' ';
		cout << "|" << *student->day;
		cout << "." << *student->month;
		cout << "." << *student->year;
		for (int i = 0; i < 5; i++) cout << ' ';
		cout << "|\n|";
		for (int i = 0; i < 142; i++) cout << "-"; cout << "|\n";
		cout << "|__Год_Поступления__|______Факультет_____|______Кафедра_______|_______Группа_______|_Номер_Зачётной_Книжки_|";
		for (int i = 0; i < 35; i++) cout << '_'; cout << "|\n";
		cout << '|' << *student->entry_year;
		for (int i = 0; i < 15; i++) cout << ' ';
		cout << "|" << student->faculty;
		for (int i = 0; i < 20 - str_len(student->faculty); i++) cout << ' ';
		cout << "|" << student->department;
		for (int i = 0; i < 20 - str_len(student->department); i++) cout << ' ';
		cout << "|" << student->group;
		for (int i = 0; i < 20 - str_len(student->group); i++) cout << ' ';
		cout << "|" << student->markbook_number;
		for (int i = 0; i < 23 - str_len(student->markbook_number); i++) cout << ' '; cout << "|";
		for (int i = 0; i < 35; i++) cout << ' '; cout << "|\n|";
		for (int i = 0; i < 142; i++) cout << "-"; cout << "|\n";

		int* temp = new int(0);
		for (int i = 0; i < *session->session_count; i++) {
			int* tmp = new int(0);
			*tmp = *(session->subject_count + i);
			cout << "|Сессия_№|______Предмет_1_____|О|______Предмет_2_____|О|______Предмет_3_____|О|______Предмет_4_____|О|______Предмет_5_____|О|__________________|\n";
			cout << "|" << i + 1 << "       ";

			for (int j = 0; j < 5; j++) {
				if (j < *tmp) {
					cout << "|" << *(session->subject_name + (*temp + j));
					for (int l = 0; l < 20 - str_len((*(session->subject_name + (*temp + j)))); l++) cout << ' '; cout << '|';
					cout << *(session->subject_mark + (*temp + j));

				}
				else {
					cout << "|********************|#";
				}
			}
			cout << "|                  |\n";

			cout << "|Сессия_№|______Предмет_6_____|О|______Предмет_7_____|О|______Предмет_8_____|О|______Предмет_9_____|О|______Предмет_10____|О|__________________|\n";
			cout << "|" << i + 1 << "       ";

			for (int j = 0; j < 5; j++) {
				if (j + 5 < *tmp) {
					cout << "|" << *(session->subject_name + (*temp + j + 5));
					for (int l = 0; l < 20 - str_len((*(session->subject_name + (*temp + j + 5)))); l++) cout << ' '; cout << '|';
					cout << *(session->subject_mark + (*temp + j + 5));

				}
				else {
					cout << "|********************|#";
				}
			}

			cout << "|                  |\n";
			cout << "|"; for (int l = 0; l < 142; l++) cout << '-'; cout << "|\n";
			*temp += *(session->subject_count + i);
			delete tmp;
		}
		delete temp;
		cout << '\n'; for (int i = 0; i < 144; i++) cout << "_"; cout << '\n';
	}

	void set_all_to_file() {
		ofstream file;
		file.open(path, ios::app | ios::binary);

		Student* student = new Student;
		Session* session = new Session;

		student->set();
		session->set();

		write_all_stud_ses(student, session, file);

		delete student;
		delete session;

		file.close();

	}

	void get_min_from_file() {
		ifstream file;
		file.open(path, ios::binary);

		if (!file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			return;
		}

		length = new int(0);

		file.seekg(0, ios::end);
		*length = file.tellg();

		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			file.close();
			return;
		}

		cur = new int(0);
		file.seekg(0, ios::beg);
		cout << "\n|_______________Фамилия__________________|__________________Имя___________________|_П_|_Номер_Зачётной_Книжки_|\n";

		while (*cur != *length) {
			Student* student = new Student;

			file.read(student->l_name, 41);
			file.read(student->f_name, 41);
			file.seekg(56, ios::cur);
			file.read(student->gender, 1);
			file.seekg(69, ios::cur);
			file.read(student->markbook_number, 11);

			*cur += 219;

			cout << "|" << student->l_name;
			for (int i = 0; i < 40 - str_len(student->l_name); i++) cout << ' ';
			cout << "|" << student->f_name;
			for (int i = 0; i < 40 - str_len(student->f_name); i++) cout << ' ';
			cout << "|" << *student->gender;
			for (int i = 0; i < 2; i++) cout << ' ';
			cout << "|" << student->markbook_number;
			for (int i = 0; i < 23 - str_len(student->markbook_number); i++) cout << ' ';
			cout << "|\n";

			delete student;

			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}

		file.close();
	}

	void get_all_from_file() {
		ifstream file;
		file.open(path, ios::binary);

		if (!file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			return;
		}

		length = new int(0);

		file.seekg(0, ios::end);
		*length = file.tellg();
		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			file.close();
			return;
		}

		cur = new int(0);
		file.seekg(0, ios::beg);
		while (*cur != *length) {
			Student* student = new Student;
			Session* session = new Session;


			read_all_stud_ses(student, session, file);

			*cur += 219;
			*cur += 5;
			*cur += *session->session_count * 5;
			*cur += *numb * 26;
			*cur += 1;

			cout_all_info(student, session);

			delete student;
			delete session;
		}
		file.close();
	}

	void get_mrbk_from_file() {
		ifstream file;
		file.open(path, ios::binary);

		if (!file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			return;
		}
		length = new int(0);
		file.seekg(0, ios::end);
		*length = file.tellg();
		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			file.close();
			return;
		}

		cout << "\nВВОД -  Введите номер зачётной книжки <10> = ";
		mrbk_numb = check_special_symbols(mrbk_numb, 11);
		cin_c_cl();

		cur = new int(0);
		file.seekg(0, ios::beg);
		while (*cur != *length) {
			file.seekg(208, ios::cur);
			*cur += 208;
			file.read(mrbk_numb_t, 11);
			*cur += 11;
			if (str_compare(mrbk_numb, mrbk_numb_t)) {
				file.seekg(-219, ios::cur);
				Student* student = new Student;
				Session* session = new Session;

				read_all_stud_ses(student, session, file);

				*cur += 219;
				*cur += 5;
				*cur += *session->session_count * 5;
				*cur += *numb * 26;
				*cur += 1;

				cout_all_info(student, session);

				delete student;
				delete session;

				return;
			}
			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}
		file.close();
		cout << "ОШИБКА - Такого студента не существует.\n";
	}

	void delete_mrbk_from_file() {
		ifstream old_file;
		old_file.open(path, ios::binary);

		ofstream new_file;
		new_file.open("new_database.bin", ios::app | ios::binary);

		if (!old_file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			new_file.close();
			remove("new_database.bin");
			return;
		}
		length = new int(0);
		old_file.seekg(0, ios::end);
		*length = old_file.tellg();
		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			old_file.close();
			new_file.close();
			remove("new_database.bin");
			return;
		}

		cout << "\nВВОД -  Введите номер зачётной книжки <10> = ";
		mrbk_numb = check_special_symbols(mrbk_numb, 11);
		cin_c_cl();

		int* begin = new int(0);
		int* end = new int(0);
		cur = new int(0);
		old_file.seekg(0, ios::beg);
		while (*cur != *length) {
			old_file.seekg(208, ios::cur);
			*cur += 208;
			old_file.read(mrbk_numb_t, 11);
			*cur += 11;
			if (str_compare(mrbk_numb, mrbk_numb_t)) {
				*begin = old_file.seekg(-219, ios::cur).tellg();
				cur = new int(0);
				char* tmp = new char('\0');
				while (*tmp != '\n' && *cur < *length) {
					old_file.read(tmp, 1);
					*cur += 1;
				}
				*end = *begin + *cur;
				delete tmp;
				break;
			}
			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				old_file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}

		if (*begin == 0 && *end == 0) {
			cout << "ОШИБКА - Такого студента не существует.\n";
			old_file.close();
			new_file.close();
			remove("new_database.bin");
			return;
		}

		cur = new int(0);
		old_file.seekg(0, ios::beg);
		while (*cur != *length) {
			if (*cur != *begin) {
				Student* student = new Student;
				Session* session = new Session;

				read_all_stud_ses(student, session, old_file);

				*cur += 219;
				*cur += 5;
				*cur += *session->session_count * 5;
				*cur += *numb * 26;
				*cur += 1;

				write_all_stud_ses(student, session, new_file);
			}
			else {
				int* tmp_1 = new int(*end - *begin);
				*cur += *tmp_1;
				if (*cur >= *length) {
					break;
				}
				old_file.seekg(*tmp_1, ios::cur);
				delete tmp_1;
			}
		}
		old_file.close();
		new_file.close();

		if (rename(path, "delete.bin")) cout << "ОШИБКА - Невозможно исходный переименовать файл.\n";
		if (rename("new_database.bin", path)) cout << "ОШИБКА - Невозможно новый переименовать файл.\n";
		remove("delete.bin");
	}

	void edit_all_from_mrbk() {
		delete_mrbk_from_file();
		set_all_to_file();
	}

	void edit_all_use_mrbk_from_file(bool type) {
		ifstream old_file;
		old_file.open(path, ios::binary);

		ofstream new_file;
		new_file.open("new_database.bin", ios::app | ios::binary);

		if (!old_file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			new_file.close();
			remove("new_database.bin");
			return;
		}
		length = new int(0);
		old_file.seekg(0, ios::end);
		*length = old_file.tellg();
		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			old_file.close();
			new_file.close();
			remove("new_database.bin");
			return;
		}

		cout << "\nВВОД -  Введите номер зачётной книжки <10> = ";
		mrbk_numb = check_special_symbols(mrbk_numb, 11);
		cin_c_cl();

		int* begin = new int(0);
		int* end = new int(0);
		cur = new int(0);
		old_file.seekg(0, ios::beg);
		while (*cur != *length) {
			old_file.seekg(208, ios::cur);
			*cur += 208;
			old_file.read(mrbk_numb_t, 11);
			*cur += 11;
			if (str_compare(mrbk_numb, mrbk_numb_t)) {
				if (type == 0) {
					*end = *cur;
					*begin = old_file.seekg(-219, ios::cur).tellg();
					break;
				}
				else {
					*begin = *cur;
					char* tmp = new char('\0');
					while (*tmp != '\n' && *cur < *length) {
						old_file.read(tmp, 1);
						*cur += 1;
					}
					*end = *cur - 1;
					delete tmp;
				}
			}
			char* tmp = new char('\0');
			while (*tmp != '\n' && *cur < *length) {
				old_file.read(tmp, 1);
				*cur += 1;
			}
			delete tmp;
		}

		if (*begin == 0 && *end == 0) {
			cout << "ОШИБКА - Такого студента не существует.\n";
			old_file.close();
			new_file.close();
			remove("new_database.bin");
			return;
		}

		cur = new int(0);
		old_file.seekg(0, ios::beg);
		while (*cur != *length) {
			Student* student = new Student;
			Session* session = new Session;

			read_all_stud_ses(student, session, old_file);

			if (*cur == *begin && type == 0) {
				student->set();
			}

			*cur += 219;

			if (*cur == *begin && type == 1) {
				session->set_subject();
			}

			*cur += 5;
			*cur += *session->session_count * 5;
			*cur += *numb * 26;
			*cur += 1;

			write_all_stud_ses(student, session, new_file);

			if (*cur >= *length) {
				break;
			}
		}
		old_file.close();
		new_file.close();

		if (rename(path, "delete.bin")) cout << "ОШИБКА -  Невозможно исходный переименовать файл.\n";
		if (rename("new_database.bin", path)) cout << "ОШИБКА -  Невозможно новый переименовать файл.\n";
		remove("delete.bin");
	}

	void cout_by_pos(int pos) {
		ifstream file;
		file.open(path, ios::binary);
		file.seekg(pos, ios::beg);

		length = new int(0);
		char* tmp = new char('\0');
		while (*tmp != '\n') {
			file.read(tmp, 1);
			*length += 1;
		}
		delete tmp;
		*length += pos - 1;

		cur = new int(pos);
		file.seekg(pos, ios::beg);
		while (*cur - 1 != *length) {
			Student* student = new Student;
			Session* session = new Session;

			read_all_stud_ses(student, session, file);

			*cur += 219;
			*cur += 5;
			*cur += *session->session_count * 5;
			*cur += *numb * 26;
			*cur += 1;

			cout_all_info(student, session);
			delete student;
			delete session;
		}
		file.close();
	}
};

class Task : public Program {
	int* answer = nullptr;
	int* length = nullptr;
	int* cur = nullptr;

public:
	Task() {
		answer = new int(0);
		cur = new int(0);
		length = new int(0);
	}
	~Task() {
		delete answer;
		delete length;
		delete cur;
	}

	void first_start(int _answer) {
		*answer = _answer;
		sort();
	}

	void sort() {
		File* f = new File;
		ifstream file;
		file.open(path, ios::binary);
		if (!file.is_open()) {
			cout << "ОШИБКА - Файл не существует.\n";
			return;
		}
		length = new int(0);
		file.seekg(0, ios::end);
		*length = file.tellg();
		if (*length == 0) {
			cout << "ОШИБКА - В файле нет данных.\n";
			file.close();
			return;
		}

		int count = 0;
		float** possition = new float* [f->get_records()]();

		for (int i = 0; i < f->get_records(); i++) {
			*(possition + i) = new float[2];
		}

		for (int i = 0; i < f->get_records(); i++) {
			*(*(possition + i) + 0) = 5;
			*(*(possition + i) + 1) = 0;
		}

		file.seekg(0, ios::beg);
		cur = new int(0);
		while (*cur != *length) {
			Session* session = new Session;

			file.seekg(219, ios::cur);
			file.read((char*)session->session_count, 4);
			file.seekg(1, ios::cur);
			*cur += 224;
			

			if (*session->session_count == *answer || *answer == 11) {

				int* sum_mark = new int(0);
				int* tmp = new int(*cur);
				*tmp -= 224;
				*(*(possition + count) + 0) = (int)*tmp;
				session->subject_count = new int[*session->session_count];
				int* numb = new int(0);
				for (int i = 0; i < *session->session_count; i++) {
					file.read((char*)&*(session->subject_count + i), 4);
					file.seekg(1, ios::cur);
					*numb += *(session->subject_count + i);
				}


				int* subj_count = new int(0);
				session->subject_name = new char* [*numb];
				session->subject_mark = new int[*numb];
				for (int i = 0; i < *numb; i++) {
					*(session->subject_name + i) = new char[21];
					file.read((char*)&*(*(session->subject_name + i)), 21);
					file.read((char*)&(*(session->subject_mark + i)), 4);
					file.seekg(1, ios::cur);
				}
				file.seekg(1, ios::cur);
				*cur += *session->session_count * 5;
				*cur += *numb * 26;
				*cur += 1;
				
				int* session_num = new int(0);
				int* subject_num = new int(0);

				for (int i = 0; i < *numb; i++) {
					if (*subject_num >= *(session->subject_count + *session_num)) {
						*session_num += 1;
						*subject_num = 0;
					}
					*subject_num += 1;
					if (*session_num + 1 == *answer || *answer == 11) {
						*sum_mark += *(session->subject_mark + i);
						*subj_count += 1;
					}
				}
				
				if (*sum_mark != 0 && *subj_count != 0) {
					*(*(possition + count) + 1) = (float)*sum_mark / *subj_count;
					count++;
				}

				delete numb;
				delete tmp;
				delete sum_mark;
				delete subj_count;
				delete subject_num;
				delete session_num;
			}
			else {
				char* tmp = new char('\0');
				while (*tmp != '\n' && *cur < *length) {
					file.read(tmp, 1);
					*cur += 1;
				}
				delete tmp;
			}

			delete session;
		}
		file.close();

		
		int* _tmp = new int(0);
		int* _flt_tmp = new int(0);

		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {
				if ((float)*(*(possition + j) + 1) < (float)*(*(possition + j + 1) + 1)) {
					*_tmp = *(*(possition + j) + 0);
					*_flt_tmp = (float)*(*(possition + j) + 1);
					*(*(possition + j) + 0) = *(*(possition + j + 1) + 0);
					*(*(possition + j) + 1) = (float)*(*(possition + j + 1) + 1);
					*(*(possition + j + 1) + 0) = *_tmp;
					*(*(possition + j + 1) + 1) = (float)*_flt_tmp;
				}
			}
		}
		delete _tmp;
		delete _flt_tmp;


		if (*(*(possition + 0) + 0) == 5) {
			cout << '\n' << "ОШИБКА - Таких студентов нет.\n";
		}else{
			for (int i = 0; i < count; i++) {
				f->cout_by_pos((int)*(*(possition + i) + 0));
			}
		}
		
		for (int i = 0; i < f->get_records(); i++) {
			delete[] * (possition + i);
		}
		delete[] possition;
		delete f;
	}
};

class Menu : public Program {
	int* answer = nullptr;
public:
	Menu() {
		answer = new int(0);
		cls;
		menu();
	}
	~Menu() {
		delete answer;
	}

	void menu() {
		File* file = new File;
		Task* task = new Task;

		cout << '\n'; for (int i = 0; i < 145; i++) cout << "="; cout << '\n';
		cout << "Выберите вариант\n";
		cout << "1) - Добавить студента\n";
		cout << "2) - Изменить данные студента\n";
		cout << "3) - Удалить студента\n";
		cout << "4) - Найти студента по зачетке\n";
		cout << "5) - Вывести всю базу студентов\n";
		cout << "6) - Выполнение задачи\n";
		cout << "7) - Очистка консоли\n";
		cout << "9) - Выйти из программы\n";
		cout << "ВВОД -  ";
		cin >> *answer;
		cin_i_cl();
		switch (*answer) {
		case 1:
			file->set_all_to_file();
			break;
		case 2:
			cout << "Выберите вариант\n";
			cout << "1) - Полное редактирование\n";
			cout << "2) - Редактирование данных о студенте\n";
			cout << "3) - Редактирование данных о предметах и оценках\n";
			cout << "9) - Назад в меню\n";
			cout << "ВВОД -  ";
			cin >> *answer;
			cin_i_cl();
			switch (*answer) {
			case 1:
				file->edit_all_from_mrbk();

				break;
			case 2:
				file->edit_all_use_mrbk_from_file(0);
				break;
			case 3:
				file->edit_all_use_mrbk_from_file(1);
				break;
			case 9:
				cls;
				menu();
				return;
			default:
				cls;
				cout << "ОШИБКА - Вы выбрали неправильный вариант.\n";
				menu();
			}
			break;
		case 3:
			file->delete_mrbk_from_file();
			break;
		case 4:
			file->get_mrbk_from_file();
			break;
		case 5:
			cout << "Выберите вариант\n";
			cout << "1) - Вывести всю информацию\n";
			cout << "2) - Вывести часть информации\n";
			cout << "9) - Назад в меню\n";
			cout << "ВВОД -  ";
			cin >> *answer;
			cin_i_cl();
			switch (*answer) {
			case 1:
				file->get_all_from_file();
				break;
			case 2:
				file->get_min_from_file();
				break;
			case 9:
				cls;
				menu();
				return;
			default:
				cls;
				cout << "ОШИБКА - Вы выбрали неправильный вариант.\n";
				menu();
			}
			break;
		case 6:
			cout << "Выберите вариант\n";
			cout << "1) - Сортировка по определенной сессии\n";
			cout << "2) - Сортировка по всем сессиям\n";
			cout << "9) - Назад в меню\n";
			cout << "ВВОД -  ";
			cin >> *answer;
			cin_i_cl();
			switch (*answer) {
			case 1:
				cout << "Введите номер сессии\n";
				cout << "ВВОД -  ";
				*answer = check_count_session();
				task->first_start(*answer);
				break;
			case 2:
				task->first_start(11);
				break;
			case 9:
				cls;
				menu();
				return;
			default:
				cls;
				cout << "ОШИБКА - Вы выбрали неправильный вариант.\n";
				menu();
			}
			break;
		case 7:
			cls;
			break;
		case 9:
			cls;
			return;
		default:
			cls;
			cout << "ОШИБКА - Вы выбрали неправильный вариант.\n";
			break;
		}
		delete file;
		delete task;
		menu();
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Menu* menu = new Menu;
	delete menu;

	return 0;
}