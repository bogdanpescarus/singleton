#include <iostream>
#include <mutex>
#include <thread>
#include <string>

template <typename T>
class Singleton {
	private:
		T data;
		static T* instance;

		Singleton() = default;
		~Singleton() = default;
		Singleton(T _data) {
			this->data = _data;
		}

		static std::mutex mtx;
	public:

		static T* getInstance(T _data) {
			std::unique_lock<std::mutex> ul(mtx);
			if(!instance) {
				Singleton<T>::instance = new T(_data);
			}
			ul.unlock();

			return instance;
		} 
	
		void display() {
			std::cout << instance->data << std::endl;
		}

		/* deleting the copy constructor and copy assignment operator */
		Singleton(const Singleton&) = delete;
		Singleton& operator=(const Singleton&) = delete;

		/* deleting the move constructor and move assignment operator */
		Singleton(Singleton&&) = delete;
		Singleton& operator=(Singleton&&) = delete;	
};

template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
std::mutex Singleton<T>::mtx;

int main() {

	/* test to see if it works */
	int* ab = Singleton<int>::getInstance(100);
	std::cout << ab << " " << *ab << std::endl;
	std::string* bc = Singleton<std::string>::getInstance("ABC");
	std::cout << bc << " " << *bc << std::endl;
	int* cd = Singleton<int>::getInstance(110);
	std::cout << cd << " " << *cd << std::endl;

	return 0;
}
