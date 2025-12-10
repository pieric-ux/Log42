# Log42

`Log42` is a **C++98 static logging library**, inspired by Python's `logging` module. It provides a flexible system for recording messages at different levels, with support for handlers and formatters, and a default output stream to `std::cerr`.

---

## Table of Contents

- [Log42](#log42)
	- [Table of Contents](#table-of-contents)
	- [Introduction](#introduction)
	- [Installation and Integration](#installation-and-integration)
		- [Compilation](#compilation)
		- [Using in a Project](#using-in-a-project)
		- [Including in Code](#including-in-code)
	- [Architecture and Concepts](#architecture-and-concepts)
		- [Key Concepts](#key-concepts)
	- [Log Levels](#log-levels)
	- [Formatters and Attributes](#formatters-and-attributes)
		- [Example of Custom Formatter](#example-of-custom-formatter)
	- [Handlers](#handlers)
		- [Example](#example)
	- [Typical Usage](#typical-usage)
	- [Customization](#customization)
	- [References](#references)

---

## Introduction

`Log42` provides a lightweight and extensible logging system for C++98.

* Namespace: `log42`
* Default handler: `std::cerr`
* Inspired by Python's `logging`, but fully independent and usable as a static library (`liblog42.a`).

The principle is simple: a **Logger** emits messages that pass through a **Handler** and a **Formatter** to produce the final output.

---

## Installation and Integration

### Compilation

```bash
# Build the library
cd Log42
make
```

### Using in a Project

```bash
g++ main.cpp -I/path/to/Log42/include -L/path/to/Log42/lib -llog42 -o my_app
```

### Including in Code

```cpp
#include <log42/Log42.hpp>
```

---

## Architecture and Concepts

### Key Concepts

The **Manager** is the central piece of the logging system. It handles the creation and retrieval of loggers, maintains their hierarchy, and manages global settings.

| Element   | Description                                                                 |
| --------- | --------------------------------------------------------------------------- |
| Manager   | Central component managing logger creation, hierarchy, and global settings. |
| Logger    | Emits log messages at different levels.                                     |
| Handler   | Determines where and how messages are sent (console, file, etc.).           |
| Formatter | Defines the message formatting.                                             |
| LogRecord | Contains information about a log message (level, text, timestamp, etc.).	  |

Diagrams are available in the repo:

* `Log42.drawio`

---

## Log Levels

| Level    | Value | When to Use                                                       |
| -------- | ----- | ----------------------------------------------------------------- |
| NOTSET   | 0     | All messages are logged if no level is set.                       |
| DEBUG    | 1     | Detailed information for diagnosing a problem.                    |
| INFO     | 2     | Confirmation that things are working as expected.                 |
| WARNING  | 3     | Unexpected situation or potential problem (e.g., low disk space). |
| ERROR    | 4     | Serious problem preventing execution of a function.               |
| CRITICAL | 5     | Critical error that may stop the program.                         |

---

## Formatters and Attributes

Available placeholders in log message formats:

| Placeholder          | Description                                       |
| -------------------- | ------------------------------------------------- |
| `%(asctime)`         | Human-readable log creation time.                 |
| `%(created)`         | Exact log creation time in seconds.               |
| `%(filename)`        | Filename portion of pathname.                     |
| `%(funcName)`        | Name of the calling function.                     |
| `%(levelname)`       | Level name (`DEBUG`, `INFO`, etc.).               |
| `%(levelno)`         | Numeric log level.                                |
| `%(lineno)`          | Line number.                                      |
| `%(message)`         | Final formatted message.                          |
| `%(module)`          | Module name (filename portion).                   |
| `%(msecs)`           | Millisecond portion of log creation.              |
| `%(name)`            | Name of the logger.                               |
| `%(pathname)`        | Full path to source file.                         |
| `%(relativeCreated)` | Elapsed time relative to the start of the program.|

### Example of Custom Formatter

```cpp
log42::formatter::Formatter fmt("[%(asctime)] - %(name) - %(levelname) - %(message)");
```

---

## Handlers

* **Default Handler**: `StreamHandler` → `std::cerr`
* **Customizable**: you can create a `FileHandler` or any derived handler.

### Example

```cpp
// Use the MAKE_SHARED macro to create a raii::SharedPtr.
// addHandler expects a raii::SharedPtr<log42::handler::Handler>.
// Example:
common::core::raii::SharedPtr<log42::handler::FileHandler> consoleHandler = MAKE_SHARED(log42::handler::StreamHandler, std::cout);
logger->addHandler(common::core::raii::staticPointerCast<log42::handler::Handler>(consoleHandler));

// Variant: create a SharedPtr directly to the base type
common::core::raii::SharedPtr<log42::handler::Handler> genericHandler =
	common::core::raii::staticPointerCast<log42::handler::Handler>(MAKE_SHARED(log42::handler::StreamHandler, std::cout));
logger->addHandler(genericHandler);
```

---

## Typical Usage

```cpp
#include <log42/Log42.hpp>

int main() {
    try {
		ROOT_DEBUG("Debug root message");
		ROOT_INFO("Info root message");
		ROOT_WARNING("Warning root message");
		ROOT_ERROR("Error root message");
		ROOT_CRITICAL("Critical root message");

		shutdown();
	} 
	catch (const std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
	}
    return 0;
}
```

---

## Customization

* Create a custom `Formatter`: `		Formatter fmt("[%(asctime)] - %(name) - %(levelname) - %(message) - file: %(filename) - function: %(funcName)() at line: %(lineno)", "%Y-%m-%d %H:%M:%S");`
* Add multiple `Handlers`
* Dynamically set log levels
* Propagate logs to multiple outputs

---

## References

* Python `logging` documentation: [https://docs.python.org/3/library/logging.html](https://docs.python.org/3/library/logging.html)
* `.drawio` diagrams available in the repo for class structure and log flow.
* Example `main.cpp` in the repo demonstrates usage of Log42.
* License: MIT.
