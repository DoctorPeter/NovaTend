/****************************************************************

   Solution : NovaTend

   Project : z-systembase-01.dll

   Module : SpecialDataStructures.h

   Description :  Special data structures classes.

*****************************************************************/
#include "stdafx.h"
#include "CriticalSection.h"


#ifndef SPECIAL_DATA_STRUCTURES_H
#define SPECIAL_DATA_STRUCTURES_H

#include <map>
#include <vector>
#include <queue>

/****************************************************************

   Class : SafeQueue

   Description : thread safe queue template
                
*****************************************************************/
template <class KT> class SafeQueue 
{
    private:
		
		// STL queue
		std :: queue<KT> _queue;

		// Critical section
        CriticalSection * criticalSection; 

    public:

		// Constructor
		SafeQueue(void) {criticalSection = new CriticalSection();}

		// Destructor
		virtual ~SafeQueue(void) {delete criticalSection;}

		// Push value to queue
        void Push(KT value) 
		{
			LOCK_SECTION(criticalSection);
			this -> _queue.push(value);
		}

		// Move back
        KT Back(void)  
		{
			LOCK_SECTION(criticalSection);
			return this -> _queue.back();
		}

		// Is queue empty?
        bool empty(void) 
		{
			LOCK_SECTION(criticalSection);
			return this -> _queue.empty();
		}
		
		// Pop value from queue
		void Pop(void) 
		{
			LOCK_SECTION(criticalSection);
			_queue.pop();
		}

		// Move front
		KT Front(void) 
		{
			LOCK_SECTION(criticalSection);
			return _queue.front();
		}
};

/****************************************************************

   Class : SafeMap

   Description : thread safe queue template
                
*****************************************************************/
template <class KT, class VT> class SafeMap 
{
    private:
        
		// STL map
		std :: map<KT, VT> _map;

        // Critical section
        CriticalSection * criticalSection; 

    public:

		// Constructor
		SafeMap(void) {criticalSection = new CriticalSection();}

		// Destructor
		virtual ~SafeMap(void) {delete criticalSection;}

		// Operator []
		VT & operator [](const KT & _Keyval)
		{	
			LOCK_SECTION(criticalSection);
			auto it = _map.find(_Keyval);
			if(_map.end() == it)
			{
				return _map[_Keyval];
			}

			return it -> second;
		}
		
		// Operator (). Get key by index
		KT operator ()(const int index)
		{	
			LOCK_SECTION(criticalSection);
			int counter = 0;
			for(auto it = _map.begin(); it != _map.end(); it++) 
			{
				if (counter == index)
					return it -> first;
			}

			return NULL;
		}
		
		// Has the map some value?
		bool Has(KT k)
		{
			LOCK_SECTION(criticalSection);
			return _map.find(k) != _map.end();
		}

		// Set value by key
        void Set(KT key, VT value) 
		{
			LOCK_SECTION(criticalSection);
			this->_map[key] = value;
		}

		// Set value by key
        VT & Get(KT key)  
		{
			LOCK_SECTION(criticalSection);
			return this -> _map[key];
		}

		// Get and remove value
		VT Pop(KT key)  
		{
			LOCK_SECTION(criticalSection);
			auto res = this -> _map[key];
			this -> _map.erase(key);
			return res;
		}

		// Is map empty
        bool Empty(void) 
		{
			LOCK_SECTION(criticalSection);
			return this -> _map.empty();
		}

		// Remove value by key
		void Erase(KT key) 
		{
			LOCK_SECTION(criticalSection);
			this -> _map.erase(key);
		}
		
		// Get map size
		int GetSize(void) 
		{
			LOCK_SECTION(criticalSection);
			return _map.size();
		}
};

#endif