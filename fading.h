/*
 *	fading.h
 *	Fading class
 *
 *	@author		Nikolai Tikhonov aka Dragon_Knight <dubki4132@mail.ru>, https://vk.com/globalzone_edev
 *	@licenses	MIT https://opensource.org/licenses/MIT
 *	@repo		https://github.com/Dragon-Knight/Fading
 */

#ifndef Fading_h
#define Fading_h

#include "Arduino.h"

template<uint8_t _size>
class Fading
{
	public:
		using callback_t = bool (*)(uint8_t index, int32_t value, bool complete);
		
		Fading(callback_t callback)
		{
			this->_callback = callback;
			
			for(uint_fast8_t index = 0; index < _size; ++index)
			{
				this->SetParam(index, 0, 0, 0, 0);
			}
			
			return;
		}
		
		Fading(callback_t callback, int32_t min, int32_t max, uint32_t step, uint32_t interval)
		{
			this->_callback = callback;
			
			for(uint_fast8_t index = 0; index < _size; ++index)
			{
				this->SetParam(index, min, max, step, interval);
			}
			
			return;
		}
		
		bool SetParam(uint8_t index, int32_t min, int32_t max, uint32_t step, uint32_t interval)
		{
			bool result = false;
			
			if(index < _size)
			{
				this->_data[index].min = min;
				this->_data[index].max = max;
				this->_data[index].step = step;
				this->_data[index].interval = interval;
				this->_data[index].value = min;
				this->_data[index].tovalue = min;
				this->_data[index].update = 0;
				
				result = true;
			}
			
			return result;
		}
		
		bool SetTo(uint8_t index, int32_t value)
		{
			bool result = false;
			
			if(index < _size)
			{
				if(value >= this->_data[index].min && value <= this->_data[index].max)
				{
					this->_data[index].value = value;
					this->_data[index].tovalue = value;
					
					this->_callback(index, this->_data[index].value, true);
					
					result = true;
				}
			}
			
			return result;
		}
		
		bool SetToMin(uint8_t index)
		{
			bool result = false;
			
			if(index < _size)
			{
				this->_data[index].value = this->_data[index].min;
				this->_data[index].tovalue = this->_data[index].min;
				
				this->_callback(index, this->_data[index].value, true);
				
				result = true;
			}
			
			return result;
		}
		
		bool SetToMax(uint8_t index)
		{
			bool result = false;
			
			if(index < _size)
			{
				this->_data[index].value = this->_data[index].max;
				this->_data[index].tovalue = this->_data[index].max;
				
				this->_callback(index, this->_data[index].value, true);
				
				result = true;
			}
			
			return result;
		}
		
		int32_t Get(uint8_t index, bool force = false)
		{
			int32_t result = 0;
			
			if(index < _size)
			{
				if(this->_data[index].value == this->_data[index].tovalue || force == true)
				{
					result = this->_data[index].value;
				}
			}
			
			return result;
		}
		
		bool FadeTo(uint8_t index, int32_t value)
		{
			bool result = false;
			
			if(index < _size)
			{
				if(value >= this->_data[index].min && value <= this->_data[index].max)
				{
					this->_data[index].tovalue = value;
					
					result = true;
				}
			}
			
			return result;
		}
		
		bool FadeToMin(uint8_t index)
		{
			bool result = false;
			
			if(index < _size)
			{
				this->_data[index].tovalue = this->_data[index].min;
				
				result = true;
			}
			
			return result;
		}
		
		bool FadeToMax(uint8_t index)
		{
			bool result = false;
			
			if(index < _size)
			{
				this->_data[index].tovalue = this->_data[index].max;
				
				result = true;
			}
			
			return result;
		}
		
		void Processing(uint32_t currentTime = millis())
		{
			for(uint_fast8_t index = 0; index < _size; ++index)
			{
				if(this->_data[index].value != this->_data[index].tovalue && (this->_data[index].update + this->_data[index].interval) <= currentTime)
				{
					this->_data[index].value = this->Move(this->_data[index].value, this->_data[index].tovalue, this->_data[index].step);
					this->_data[index].update = currentTime;
					
					this->_callback(index, this->_data[index].value, (this->_data[index].value == this->_data[index].tovalue));
				}
			}
			
			return;
		}
	private:
		int_fast32_t Move(int_fast32_t value, int_fast32_t tovalue, uint_fast32_t step)
		{
			int_fast32_t result;
			
			if(value > tovalue)
			{
				if((int_fast32_t)(value - step) > tovalue)
				{
					result = value - step;
				}
				else
				{
					result = tovalue;
				}
			}
			else
			{
				if((int_fast32_t)(value + step) < tovalue)
				{
					result = value + step;
				}
				else
				{
					result = tovalue;
				}
			}
			
			return result;
		}
		
		struct dataStruct_t
		{
			int_fast32_t min;		// Минимальное значение value.
			int_fast32_t max;		// Максимальное значение value.
			uint_fast32_t step;		// Размер шага.
			uint_fast32_t interval;	// Интервал обновления, в мс.
			int_fast32_t value;		// Текущее значение.
			int_fast32_t tovalue;	// Значение, к которому стремится value.
			uint_fast32_t update;	// Время последнего обновления.
		} _data[_size];
		
		callback_t _callback;
};

#endif