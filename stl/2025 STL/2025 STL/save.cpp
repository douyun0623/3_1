//-----------------------------------------------------------------
// save.cpp											2025년 3월 11일
// 
// 한 학기 강의를 덧붙여 저장하는 함수 입니다.
//-----------------------------------------------------------------


#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>

//-----------------------------
void save(std::string_view fileName)
//-----------------------------
{
	// fileName을 읽기 모드로 연다
	std::ifstream in{ fileName.data() };		// RAII
	if (not in) {
		std::cout << fileName << "을 열 수 없습니다." << std::endl;
		exit(20250306);
	}

	// 쓰기 모드로 저장할 파일을 연다.
	std::string nameToSave{ "2025 1 STL 화56목78 강의저장.txt" };
	std::ofstream out{ nameToSave, std::ios::app };

	// 저장했다고 화면에 출력한다.
	auto size = std::filesystem::file_size(fileName);
	std::cout << nameToSave << "에 " << fileName << "를 덧붙였습니다. - "
		<< size << " bytes" << std::endl;

	// 저장한 시간을 파일에 기록하자
	auto now = std::chrono::system_clock::now();			// time_point를 얻는다, epoch
	auto utc = std::chrono::system_clock::to_time_t(now);	// UTC 시간으로 변경
	auto lt = std::localtime(&utc);							// 지역달력시간으로
	auto old = out.imbue(std::locale("ko_KR"));

	out << '\n' << '\n';
	out << "======================================" << '\n';
	out << "저장한 시간: " << std::put_time(lt, "%c %A") << '\n';
	out << "======================================" << '\n';
	out << '\n';

	out.imbue(old);		// 원래 locale로 복귀

	// 읽을 파일에 있는 모든 내용을 읽어 쓸 파일에 덧붙여 쓴다
	std::copy(std::istreambuf_iterator{ in }, {}, std::ostreambuf_iterator{ out });
}