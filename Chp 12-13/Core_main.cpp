#include <algorithm>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Core.h"
#include "Grad.h"
#include "Vec.h"
#include "Student_info.h"
#include "median.h"

using namespace std;

int main()
{
	vector<Core*> students; //객체가 아닌 포인터를 저장
	Core* record;
	char ch;
	string::size_type maxlen = 0;

	//데이터 읽고 저장하기
	while (cin >> ch) {
		if (cin.dof())break;

		if (ch != 'U' && ch != 'G') {
			//학생 아닌 타입이면 건너뛰기
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		if (ch == 'U')
			record = new Core;
		else if (ch == 'G')
			record = new Grad;
		record->read(cin);

		maxlen = max(maxlen, record->getName(), size());
		students.push_back(record);
	}

	//포인터로 작동하는 compare 함수를 전달
	sort(students.begin(), students.end(), compare_Core_ptrs);

	//이름과 점수 출력
	for (vector<Core*>::size_type i = 0;
		i != students.size(); i++) {

		//타입 확인
		if (dynamic_cast<Grad*>(students[i])) {
			cout << "(G) ";
		}
		else {
			cout << "(U) ";
		}
		//함수를 호출하려고 포인터를 역참조
		cout << students[i]->getName()
			<< string(maxlen + 1
				- students[i]->getName().size(), ' ');

		try {
			double final_grade = students[i]->grade();
			streamsize prec = cout.precision();
			cout << setprecision(3) << final_grade
				<< setprecision(prec) << endl;
		}

		catch (domain_error e) {
			cout << e.what() << endl;
		}
		delete students[i];
	}
}
