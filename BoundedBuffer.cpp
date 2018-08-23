using namespace std;
#ifndef BOUNDEDBUFFER1_CPP
#define BOUNDEDBUFFER1_CPP
_Monitor BoundedBuffer {
		uCondition full, empty;
		int front, back, count, buf_size;
		vector<msge> elements;
	public:
		BoundedBuffer(int buf_size) : front(0), back(0), count(0), buf_size(buf_size) {
			elements.resize(buf_size);
		}
		_Nomutex int query() { 
			return count; 
		}
		// funcion para insertar elementos en el buffer
		void insert(msge elem) {			
			if (count == buf_size) empty.wait(); // buf_size
			elements[back] = elem;
			back = (back+1)% buf_size;
			count += 1;
			full.signal();
		}
		// funcion para remover elementos del buffer
		msge remove() {
			if (count == 0) full.wait();
			msge elem = elements[front];
			front = (front+1)%buf_size;
			count -= 1;
			empty.signal();
			return elem;
		}
};
#endif