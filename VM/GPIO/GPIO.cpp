#include "../Log/Log.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
using namespace std; 

#define IN  0
#define OUT 1
 
#define LOW  0
#define HIGH 1
Log g_log; 

int
GPIOExport(int pin)
{
#define BUFFER_MAX 3
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (-1 == fd) {
		stringstream ss;
                ss << "Failed to open export for writing! GPIO pin #" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 
int
GPIOUnexport(int pin)
{
	char buffer[BUFFER_MAX];
	ssize_t bytes_written;
	int fd;
 
	fd = open("/sys/class/gpio/unexport", O_WRONLY);
	if (-1 == fd) {
		stringstream ss;
                ss << "Failed to open unexport for writing! GPIO pin #" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
	write(fd, buffer, bytes_written);
	close(fd);
	return(0);
}
 
int
GPIODirection(int pin, int dir)
{
	static const char s_directions_str[]  = "in\0out";
 
#define DIRECTION_MAX 35
	char path[DIRECTION_MAX];
	int fd;
 
	snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		stringstream ss;
                ss << "Failed to access gpio direction for writing! GPIO pin#" << pin << " direction#" << dir;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	if (-1 == write(fd, &s_directions_str[IN == dir ? 0 : 3], IN == dir ? 2 : 3)) {
		stringstream ss;
                ss << "Failed to set gpio direction! GPIO pin#" << pin << " direction#" << dir;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	close(fd);
	return(0);
}
 
int
GPIORead(int pin)
{
#define VALUE_MAX 30
	char path[VALUE_MAX];
	char value_str[3];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (-1 == fd) {
		stringstream ss;
                ss << "Failed to access gpio for readng! GPIO pin#" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	if (-1 == read(fd, value_str, 3)) {
                stringstream ss;
		ss << "Failed to read value! GPIO pin#" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	close(fd);
 
	return(atoi(value_str));
}
 
int
GPIOWrite(int pin, int value)
{
	static const char s_values_str[] = "01";
 
	char path[VALUE_MAX];
	int fd;
 
	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_WRONLY);
	if (-1 == fd) {
		stringstream ss;
                ss << "Failed to access gpio value for writing! GPIO pin#" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	if (1 != write(fd, &s_values_str[LOW == value ? 0 : 1], 1)) {
		stringstream ss;
                ss << "Failed to write value! GPIO pin#" << pin;
                g_log.v("System", ss.str());
		return(-1);
	}
 
	close(fd);
        
	return(0);
}
