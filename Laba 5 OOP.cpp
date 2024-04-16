#include <iostream>
#include <string>

using namespace std;

class Object {

public:

	Object() {};

	virtual ~Object() { "\nВызов деструктора для класса Object.\n"; }
	virtual void outPut() = 0;

};

class Person : public Object {
	
	friend istream& operator>>(istream& inPut, Person& person);
	friend ostream& operator<<(ostream& outPut, const Person& person);

protected:

	string name;
	int age;

public:

	Person() {

		cout << "\nКонструктор по умолчанию класса Person\n";
		name = "No name";
		age = 0;
	}
	
	Person(int userAge, string userName) {

		cout << "\nКонструктор с параметрами класса Person\n";
		age = userAge;
		name = userName;
	}

	Person(const Person& person) {

		cout << "\nКонструктор копирования класса Person\n";
		age = person.age;
		name = person.name;
	}

	~Person() { "\nВызов деструктора для класса Person\n"; }

	string getName() { return name; }
	int getAge() { return age; }
	
	void setName(string someName) { name = someName; }
	void setAge(int someAge) { age = someAge; }

	Person& operator=(const Person& person) {

		age = person.age;
		name = person.name;
		return *this;
	}
	void outPut() override { cout << "\nИмя: " << name << "\nВозраст: " << age << endl; }
};

class Teacher : public Person {

	friend istream& operator>>(istream& inPut, Teacher& teach);
	friend ostream& operator<<(ostream& outPut, const Teacher& teach);

protected:

	string subject;
	int hours;

public:

	Teacher() {

		cout << "\nКонуструктор по умолчанию класса Teacher\n";
		subject = "No subject";
		hours = 0;
	}

	Teacher(const Teacher& teach) : Person(teach) {

		cout << "\nКонуструктор копирования класса Teacher\n";
		subject = teach.subject;
		hours = teach.hours;
	}

	Teacher(string name, int age, string subject, int clocks) : Person(age, name) {

		cout << "\nКонструктор с параметрами класса Teacher\n";
		this->setSubject(subject);
		this->setHours(clocks);
	}

	void setSubject(string& someSubject) { subject = someSubject; }
	void setHours(int& someHours) { hours = someHours; }

	string getSubject() { return subject; }
	int getHours() { return hours; }

	Teacher operator-(const int& minus) const { return Teacher(this->name, this->age, this->subject, this->hours - minus); }
	Teacher operator+(const int& plus) const { return Teacher(this->name, this->age, this->subject, this->hours + plus); }

	void outPut() override {

		cout << "\nИмя: " << name << "\nВозраст: " << age << "\nПредмет: " << subject << "\nЧасы: " << hours << endl;
	}
};

class Vector {

	friend ostream& operator<<(ostream& outPut, const Vector& vect);

private:

	Object** beginItem;
	int size;
	int current;

public:

	Vector() {

		cout << "\nКонструктор по умолчанию для класса Vector\n";
		beginItem = 0;
		size = 0;
		current = 0;
	}

	Vector(int lin) {

		cout << "\nКонструктор с параметрами для класса Vector\n";
		beginItem = new Object* [lin];
		current = 0;
		size = lin;
	}

	void addToVector(Object* ptr) {
		if (current < size) { beginItem[current++] = ptr; }
	}
};

istream& operator>>(istream& inPut, Person& pers) {

	cout << "\nВведите имя: "; getline(inPut, pers.name);
	cout << "\nВведите возраст: "; (inPut >> pers.age).ignore();
	cout << endl << endl;
	return inPut;
}

ostream& operator<<(ostream& outPut, const Person& pers) {

	outPut << "\nИмя: " << pers.name;
	outPut << "\nВозраст: " << pers.age;
	cout << endl << endl;

	return outPut;
}

istream& operator>>(istream& inPut, Teacher& teach) {

	cout << "\nВведите имя: "; getline(inPut, teach.name);
	cout << "\nВведите возраст: "; (inPut >> teach.age).ignore();
	cout << "\nВведите предмет: "; getline(inPut, teach.subject);
	cout << "\nВведите кол-во часов: "; inPut >> teach.hours;
	cout << endl << endl;
	return inPut;
}

ostream& operator<<(ostream& outPut, const Teacher& teach) {

	outPut << "\nИмя: " << teach.name;
	outPut << "\nВозраст: " << teach.age;
	outPut << "\nПредмет: " << teach.subject;
	outPut << "\nКол-во часов: " << teach.hours;
	cout << endl << endl;

	return outPut;
}

ostream& operator<<(ostream& outPut, const Vector& vect) {

	if (vect.size == 0) {
		outPut << "\nВектор пустой.\n";
	}
	else {

		Object** ptr = vect.beginItem;
		for (int i = 0; i < vect.current; i++) {
			(*ptr)->outPut();
			ptr++;
		}
	}
	return outPut;
}

int main() {

	system("chcp 1251 > Null");

	Person someDefaultPerson;
	someDefaultPerson.outPut(); // конструктор по умолчанию

	Person someDiffPerson(25, "Василий"); // конструктор с параметрами
	someDiffPerson.outPut();

	Person someCopyPerson(someDiffPerson); // конструктор копирования
	someCopyPerson.outPut();
	

	Vector vect(3);

	Person somePerson;

	Teacher someTeacher;


	cout << "\nБазовый класс Person\n"; cin >> somePerson;
	cout << somePerson;

	cout << "\nПроизводный класс Teacher\n"; cin >> someTeacher;
	cout << someTeacher;

	cout << "\nКол-во часов - 10\n" << someTeacher - 10;
	cout << "\nКол-во часов + 7\n" << someTeacher + 7;

	Object* item = &somePerson;	

	vect.addToVector(item);
	item = &someTeacher;

	vect.addToVector(item);

	cout << "\nВектор: " << vect;

}