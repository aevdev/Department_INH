#include<iostream>
#include<fstream>
#include<string>
using namespace std;

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, unsigned int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	std::string last_name;
	std::string first_name;
	unsigned int age;
public:
	const std::string& get_last_name()const
	{
		return last_name;
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	unsigned int get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(unsigned int age)
	{
		this->age = age;
	}

	//					Constructors:
	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}

	//				Methods:
	virtual std::ostream& print(std::ostream& os)const
	{
		//return os << last_name << " " << first_name << " " << age << " years";
		os.left; //задает выравнивание выводимой информации в поле определенной ширины.
		os.width(10); //определяет шириун поля в которую будет произведен вывод.(измеряется в знакопозициях)
		//width - метод класса ios_base
		//left - манипулятор (как endl), который задает выравнивание
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age << " years";
		return os;
	}
	virtual std::ofstream& print(std::ofstream& os)const
	{
		os.left;
		os.width(10);
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age;
		return os;
	}
	virtual ifstream& scan(ifstream& is)
	{
		is >> last_name >> first_name >> age;
		return is;
	}

};

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.print(os);
}

ofstream& operator<<(ofstream & os, const Human& obj)
{
	return obj.print(os);
}
ifstream& operator>>(ifstream& is, Human& obj)
{
	return obj.scan(is);
}

#define EMPLOYEE_TAKE_PARAMETERS	const std::string& position
#define EMPLOYEE_GIVE_PARAMETERS	position

class Employee :public Human	
{
	std::string position;	
public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;

	Employee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS) :Human(HUMAN_GIVE_PARAMETERS)
	{
		set_position(position);
		cout << "EConstructor:\t" << this << endl;
	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& os)const
	{
		Human::print(os) << " ";
		return os << position;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os) << " ";
		os.width(10);
		os << position;
		return os;
	}
	ifstream& scan(ifstream& is)
	{
		Human::scan(is);
		is >> position;
		return is;
	}

};

#define PERMANENT_EMPLOYEE_TAKE_PARAMETERS double salary
#define PERMANENT_EMPLOYEE_GIVE_PARAMETERS salary

class PermanentEmployee : public Employee
{
	double salary;
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}

	PermanentEmployee
	(
		HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS, PERMANENT_EMPLOYEE_TAKE_PARAMETERS
	) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_salary(salary);
		cout << "PEConstructor:\t" << this << endl;
	}
	~PermanentEmployee()
	{
		cout << "PEDestructor:\t" << this << endl;
	}

	std::ostream& print(std::ostream& os)const
	{
		Employee::print(os) << " ";
		os.width(10);
		os << right;
		return os << salary;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Employee::print(os) << " ";
		os.width(10);
		os << right;
		os << salary;

		return os;
	}
	ifstream& scan(ifstream& is)
	{
		Employee::scan(is);
		is >> salary;
		return is;
	}
};

#define HOURLY_EMPLOYEE_TAKE_PARAMETERS double rate, int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETERS rate, hours

class HourlyEmployee :public Employee
{
	double rate;	
	int hours;	
public:
	double get_rate()const
	{
		return rate;
	}
	int get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate * hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}

	HourlyEmployee
	(
		HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS, HOURLY_EMPLOYEE_TAKE_PARAMETERS
	) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HEConstructor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}
	std::ostream& print(std::ostream& os)const
	{
		Employee::print(os) << " ";
		os << "rate:";
		os.width(10);
		os << right;
		os << rate;
		os << ",Hours:";
		os.width(3);
		os << hours << " Salary:" << get_salary();

		return os;
	}

	std::ofstream& print(std::ofstream& os)const
	{
		Employee::print(os) << " ";
		os.width(10);
		os << right;
		os << rate;
		os.width(3);
		os << hours;

		return os;
	}
	ifstream& scan(ifstream& is)
	{
		Employee::scan(is);
		is >> rate;
		is >> hours;
		return is;
	}
};

Employee* EmployeeFactory(const string& type)
{
	//Employee* employee; чтобы обойти ограничение в случае ошибки (правда нужно сначала будет присвоить new, а потом вернуть employee.
	if (type.find("PermanentEmployee") != std::string::npos) return new PermanentEmployee("", "", 0, "", 0);
	if (type.find("HourlyEmployee") != std::string::npos) return new HourlyEmployee("", "", 0, "", 0, 0);
}

//#define SAVE_TO_FILE

void main()
{
#ifdef SAVE_TO_FILE
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;;
	cout << typeid(str.c_str()).name() << endl;

	setlocale(LC_ALL, "");
	Employee* department[] =
	{
		new PermanentEmployee("Rosenberg", "Ken", 30, "Lawyer", 2000),
		new PermanentEmployee("Diaz", "Ricardo", 50, "Boss", 50000),
		new HourlyEmployee("Vercetty", "Tomas", 30, "Security", 500, 8)
	};

	double total_salary = 0;
	//sizeof(department) / sizeof(Employee*) 
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		cout << "\n--------------------------------------\n";
		//department[i]->print();
		cout << *department[i] << endl;
		total_salary += department[i]->get_salary();
	}
	cout << "\n--------------------------------------\n";
	cout << "Total salary of all department: " << total_salary << endl;
	cout << "\n--------------------------------------\n";

	ofstream fout("file.txt");
	for (int i = 0; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		fout.left;
		fout.width(25);
		fout << string(typeid(*department[i]).name()) + ":";
		fout << *department[i] << endl; //чтобы перегруженный fout работал, это нужно вызывать отдельным выражением.
	}
	fout.close();
	system("start notepad file.txt");

	for (int i = 0; i < sizeof(department) / sizeof(Employee*); i++)
	{
		delete department[i];
	}
#endif // SAVE_TO_FILE
	Employee** department = nullptr;
	int n = 0; //размер массива

	ifstream fin("file.txt");

	if (fin.is_open())
	{
		//1)Определяем количество записей в файле, для того, чтобы выделить память под массив сотрудников.
		string employee_type;
		for (; !fin.eof(); ++n)
		{
			getline(fin, employee_type);
		}
		n--; //можно просто заранее учитывать то, что создается одна пустая строка
		cout << n << endl; 
		//2) Выделяем память под массив:
		department = new Employee * [n] {};
		//3) Возвращаем курсор в начало файла:

		cout << fin.tellg() << endl;

		fin.clear(); //нужно перед этим очистить потоу и только потом задать позицию.
		fin.seekg(0); //задаем расположение курсора

		cout << fin.tellg() << endl;
		//4) Загружаем данные из файла в массив:
		for (int i = 0; i < n; ++i)
		{
			getline(fin, employee_type, ':'); //по умолчанию гетлайн читает строку до знака возврата коретки(новой строки), но 3м параметром можно задать разделитель.
			department[i] = EmployeeFactory(employee_type);
			fin >> *department[i];
		}

	}
	else
	{
		cerr << "Error: File not found!" << endl;
	}

	for (int i = 0; i < n; ++i)
	{
		cout << *department[i] << endl;
	}
	for (int i = 0; i < n; ++i)
	{
		delete[] department[i];
	}
	delete[] department;
	fin.close();

}