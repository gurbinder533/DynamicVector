// Vector.h -- header file for Vector data structure project
/***********************************************************


  Author: Gurbinder Gill
  email : gill@cs.utexas.edu 

***********************************************************/

#pragma once
#ifndef _Vector_h
#define _Vector_h

#include <cstdint>
#include <stdexcept>

namespace epl{

#define MIN_CAPACITY 8

template <typename T>
class Vector {
private:
	T* buffer{ nullptr };
	uint64_t _length{ 0 };
	uint64_t _front{ 0 };
	uint64_t _back{ 0 };
	uint64_t _capacity{ 0 };

public:
	/* Default Constructor */
	Vector(void){
		 buffer = (T*)operator new(MIN_CAPACITY * sizeof(T));
		 _length = 0;
	 	 _front = 0;
		 _back = 0;
		_capacity = MIN_CAPACITY;
	}
    
	/* Default Destructor */
	~Vector(){
	    destroy();
	}

	/* One argument Constructor */
	explicit Vector(uint64_t n) {
		if (n == 0) {    
			 buffer = (T*)operator new(MIN_CAPACITY * sizeof(T));
			 _length = 0;
			 _front = 0;
			 _back = 0;
			_capacity = MIN_CAPACITY;
		}
		else
		{
			
			_front = 1;
			_back = n;
			_length = (_back - _front + 1); 
			buffer = (T*)operator new(n * sizeof(T));

			for (uint64_t k = (_front - 1); k < _back; ++k) {
				new(buffer + k) T{};
			}
		_capacity = n;

		}
	}

	/* Copy Constructor */

	Vector( const Vector<T>& rhs){
	    copy(rhs);
        }

	/* Copy Assignment operator */

	Vector& operator=(const Vector<T>& rhs) {

	    	if(this != &rhs) {
		     for(uint64_t k = (_front - 1) ; k < _back; ++k) {
			buffer[k].~T(); 
		    }
		//    destroy();
		    

		    copy(rhs);
		}

		return *this;

	}


        /* Move Constructor */
	Vector(Vector<T>&& rhs){
	    
	    destroy();
	    this->move(std::move(rhs));  /* std::move(rhs) is giving me rvalue reference .. it should be called rval() instead */
	    
	}

	/* Move Assignment operator */

	Vector& operator=( Vector<T>&& rhs) {
	   
	    /* for(uint64_t k = (_front - 1) ; k < _back; ++k) {
		buffer[k].~T();

		}*/
		destroy();
		
		this->move(std::move(rhs));
		return *this;

	}


	
	/* Defining operator []*/

	T& operator[](const uint64_t position){
		if ((position + _front - 1)   >= _back) throw std::out_of_range("out of range");
		else
			return buffer[position + _front - 1];
	}

	const T& operator[](const uint64_t position) const{
		if ((position + _front - 1)   >= _back) throw std::out_of_range("out of range");
		else
			return buffer[position + _front - 1];
	}


	int size() const {
		if(_back == 0)
		    return 0;
		else 
		    return (_back - _front + 1 );
	}

	int capacity() const {
		return _capacity; /* Returns the size of the storage space currently allocated for the vector, expressed in terms of elements. */
	}
	
	int front()const {
	    return _front;
	}
	
	int back()const {
	    return _back;
	}

    
    /* PUSH_BACK and POP_BACK */
    void push_back(const T& value){
	if(_back == _capacity) /* Need to allocate more space i.e _capacity = _capacityx2 */
	{
	    _capacity *= 2; /*  double the capacity */
	    T* temp_buffer = (T*)operator new(_capacity * sizeof(T));
	    
	    _length = (_back - _front + 1 );
	  
	    new(temp_buffer + _back)T(value); 
	    for(uint64_t k = (_front - 1); k < _back; ++k)
	    {
		new(temp_buffer + k)T(std::move(buffer[k]));

	    }

	    //new(temp_buffer + _back)T(value); 
	    destroy(); /* NEED TO CHECK THIS */
	  
	    buffer = temp_buffer;
	       _back += 1; //added a new element to the back 
	   
	}
	else 
	{
	    new(buffer + _back)T(value);
	    //buffer[_back] = value;
	    if(_back == 0)
		_front = 1;
	    
	     _back+=1;
	}
    }

    void pop_back() {
	if(_back == 0)throw std::out_of_range("out of range");
	else 
	{ 
	    buffer[_back - 1].~T(); 
	    _back -= 1;
	    if(_back < _front || _back == 0)
		_front = _back = 0;
	}
	
    }


/*********** with move construction *************/
 /* PUSH_BACK and POP_BACK */
    void push_back(T&& value){
	if(_back == _capacity) /* Need to allocate more space i.e _capacity = _capacityx2 */
	{
	    _capacity *= 2; /*  double the capacity */
	    T* temp_buffer = (T*)operator new(_capacity * sizeof(T));
	    
	    _length = (_back - _front + 1 );
	  
	    new(temp_buffer + _back)T(std::move(value)); 
	    for(uint64_t k = (_front - 1); k < _back; ++k)
	    {
		new(temp_buffer + k)T(std::move(buffer[k]));

	    }

	   // new(temp_buffer + _back)T(std::move(value)); 
	    
	    //this->move(std::move(temp_buffer));
	    destroy(); /* DO NOT NEED THIS >>CHECK THIS AGAIN */
	  
	    buffer = temp_buffer;
	    _back += 1; //added a new element to the back 
	   
	}
	else 
	{
	    new(buffer + _back)T(std::move(value));
	    //buffer[_back] = value;
	    if(_back == 0)
		_front = 1;
	    
	     _back+=1;
	}
    }


/*******************************************************************************************************/
    void push_front(const T& value){
	if(_front == 0){
	    new(buffer + _front)T(value);
	    _front = 1;
	    _back = 1; 
	}
	else if(_front == 1) {
	     uint64_t old_capacity = _capacity;
	     _capacity *= 2;
	    
	    T* temp_buffer = (T*)operator new(_capacity*sizeof(T));
	    _length = (_back - _front + 1); 

	    new(temp_buffer + old_capacity - 1)T(value);
	    for(uint64_t k = 0; k < _length; ++k)
	    {
		new(temp_buffer + k + old_capacity)T(std::move(buffer[k]));		
	    }
	    
	    

	    
	    destroy(); /* NEED TO CHECK THIS ONCE */
	    buffer = temp_buffer;
	     _front = old_capacity;
	    _back += _front; 

	   	    
	}
	else {	    
	    new(buffer + _front - 2) T(value);
	    //buffer[_front - 2] = value;
	    _front -= 1;
	}

    }
    

    void pop_front(){
	if(_front == 0)throw std::out_of_range("out of range");
	else{	
	    buffer[_front - 1].~T();
	    _front += 1;
	    if(_front > _back)  //NEED TO CHECK THIS
		_front = _back = 0;
	}
    

    }


/************************** Move push_front ***********************/

  void push_front(T&& value){
	if(_front == 0){
	    new(buffer + _front)T(value);
	    _front = 1;
	    _back = 1; 
	}
	else if(_front == 1) {
	     uint64_t old_capacity = _capacity;
	     _capacity *= 2;
	    
	    T* temp_buffer = (T*)operator new(_capacity*sizeof(T));
	    _length = (_back - _front + 1); 
	    new(temp_buffer + old_capacity - 1)T(std::move(value));
	    for(uint64_t k = 0; k < _length; ++k)
	    {
		new(temp_buffer + k + old_capacity)T(std::move(buffer[k]));		
	    }
	    
	    
	    //new(temp_buffer + old_capacity - 1)T(std::move(value));

	    
	    destroy(); /* NEED TO CHECK THIS ONCE */
		
	    buffer = temp_buffer;
	     _front = old_capacity;
	    _back += _front; 

	   	    
	}
	else {	    
	    new(buffer + _front - 2) T(std::move(value));
	    //buffer[_front - 2] = value;
	    _front -= 1;
	}

    }
    
/*****************************************************************/



    private:
	void copy(const Vector<T>& that) {
	    if (this->_capacity > that._capacity) {
	
		_front = that._front;
		_back = that._back;

	
		if(_front == 0 || _back == 0)
		    buffer = nullptr;
		else{


		for(uint64_t k = (_front - 1); k < _back; ++k)
		{
		    new(buffer + k)T(that.buffer[k]);
		}
	    }

	    }
	    else {
		
		operator delete(buffer);
		this->_front = that._front;
		this->_back = that._back;
		this->_capacity = that._capacity;
		
		_length = (_back - _front + 1);
		if(_length == 0) {
		    buffer = nullptr;	
		} 
		else {

		    this->buffer = (T*)operator new(_capacity*sizeof(T));

		    for(uint64_t k = (_front - 1); k < _back; ++k)
		    {
			new(buffer + k) T(that.buffer[k]);
		    }
	    
		}
	    }
       }
	

    /* Move semantics */ 
   /* IMP: move operation should leave the source object in a valid but unspecified state because it will evetually 
      be destroyed and the destructor cannot destroy an object left in an invalid state */

    void move( Vector<T>&& that) {

	    _front = that._front;
	    _back = that._back;
	    _capacity = that._capacity;
	    buffer = that.buffer;

	    that._back = that._front = that._capacity = 0;
	    that.buffer = nullptr;

	    
       }


	void destroy(void) { 
	    for(uint64_t k = (_front - 1) ; k < _back; ++k) {
		buffer[k].~T();
	    }
	    operator delete(buffer); 
	}


};

} //namespace epl

#endif /* _Vector_h */
