# Crow-based TODO App Demo

This is a simple TODO app demo built using the [Crow](https://github.com/CrowCpp/Crow) C++ microframework. The application provides basic CRUD functionality for managing TODO items via RESTful API endpoints. It also uses SQLite for database storage.

## Features

* **REST API** with the following routes:
  + `GET /item/all`: Get all TODO items
  + `POST /item/create`: Create a new TODO item
  + `GET /item/read/<id>`: Get a TODO item by ID
  + `PUT /item/update`: Update a TODO item
  + `DELETE /item/delete/<id>`: Delete a TODO item by ID
* Uses Crow for HTTP server functionality.
* SQLite for local data storage.

## Prerequisites

* **C++17 or later**
* **CMake 3.5 or later**
* **Vcpkg** for package management
* **Crow**, **Asio**, **Boost**, and **SQLite3** libraries installed via Vcpkg

This project uses Vcpkg to manage dependencies. Make sure Vcpkg is installed and the environment is set up correctly.
Before proceeding, install the required packages using Vcpkg:

```bash
vcpkg install crow asio boost sqlite3
```

## Installation

1. **Clone the repository:**

```bash
git clone <repository-url>
cd <repository-directory>
make
```
