# Log42

`Log42` is a **C++98 static logging library**, inspired by Python's `logging` module. It provides a flexible system for recording messages at different levels, with support for handlers and formatters, and a default output stream to `std::cerr`.

---

## Table of Contents

1. [Introduction](#introduction)
2. [Installation and Integration](#installation-and-integration)
3. [Architecture and Concepts](#architecture-and-concepts)
4. [Log Levels](#log-levels)
5. [Formatters and Attributes](#formatters-and-attributes)
6. [Handlers](#handlers)
7. [Typical Usage](#typical-usage)
8. [Customization](#customization)
9. [References](#references)

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
#include "Log42.hpp"
```

---

## Architecture and Concepts

### Key Concepts

| Element   | Description                                                              |
| --------- | ------------------------------------------------------------------------ |
| Logger    | Emits log messages at different levels.                                  |
| Handler   | Determines where and how messages are sent (console, file, etc.).        |
| Formatter | Defines the message formatting.                                          |
| LogRecord | Contains information about a log message (level, text, timestamp, etc.). |

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
log42::Formatter formatter("[%(asctime)] - %(name) - %(levelname) - %(message)");
```

---

## Handlers

* **Default Handler**: `StreamHandler` → `std::cerr`
* **Customizable**: you can create a `FileHandler` or any derived handler.

### Example

```cpp
log42::handler::StreamHandler *consoleHandler = new StreamHandler(std::cout);
logger->addHandler(consoleHandler);
```

---

## Typical Usage

```cpp
#include "log42.hpp"

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
