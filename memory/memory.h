#ifndef _MEMORY_H
#define _MEMORY_H

#include <cstdint>
#include <fmt/core.h>
#include <iostream>
#include <stdexcept>
#include <vector>

#define DEFAULT_MEMORY_SIZE 2'048

class Memory
{
    private:
		// uint8_t, std::byte, char also work as single-byte types
        std::vector<unsigned char> ram_;
		uint64_t size_;  // store the original user provided size, useful for bounds checking

		/**
		 * @brief determine if an address is in bounds or not
		 *
		 * @param address
		 * @return true
		 * @return false
		 */
		bool inBounds(uint64_t address) const;

    public:
        /**
        * @brief Default Memory constructor
        *
        * This constructor requires no parameters and sets a default
        * Memory size of 1KB, or 1,024
        *
        * @param size The desired size of memory
        */
        Memory(uint64_t size = DEFAULT_MEMORY_SIZE) : ram_(std::vector<unsigned char>(size)), size_(size) {};

        /**
        * @brief store data to memory
        *
        * This function stores a single byte to the specified address
		*
		* @param address The location to which the byte will be stored
		* @param byte the byte to store
        */
        int store(uint64_t address, unsigned char byte);

        /**
        * @brief load data from memory
        *
        * This function loads a single byte from the specified address
		*
		* @param address The location from which the byte will be read
		* @return the byte read from memory
		*/
        unsigned char load(uint64_t address) const;

		/**
		 * @brief return the size of memory
		 *
		 * @return uint64_t
		 */
		uint64_t size() const;

		/**
		 * @brief clear memory
		 *
		 */
		void clear();

		/**
		 * @brief dump memory in hex for inspection
		 *
		 */
		void dump();
};


#endif
