# Car Rental System

## About

This application is a small console command-line tool written in **C++** for managing car rental process.

Source code is on GitHub https://github.com/annechko/car-rental-system

# Table of Contents

1. [Functionality](#functionality)
1. [Usage](#usage)
    1. [Output of help command](#output-of-help-command)
1. [List of available commands](#list-of-available-commands)
1. [System architecture](#system-architecture)
    1. [Application](#application)
    1. [Commands](http://localhost:6419/#commands)
    1. [Basic command](http://localhost:6419/#basic-command)
    1. [Domain](http://localhost:6419/#domain)
1. [External dependencies](http://localhost:6419/#external-dependencies)
    1. [sqlite_orm](#sqlite_orm)
    1. [cxxopts](#cxxopts)
    1. [bcrypt](#bcrypt)
    1. [tabulate](#tabulate)
1. [Entity relationship diagram](#entity-relationship-diagram)
1. [Use cases](#use-cases)
1. [Tests](#tests)

## Functionality

* User Management:
  * user registration, with different roles: customer and admin
  * user login (for some commands)
* Car Management:
  * add car (admin) (ID, make, model, year, mileage, minimum rent period in days, maximum rent period.)
  * get car list
  * update car (admin)
  * delete car (admin)
* Rental Booking:
  * book car (customer, specify dates) (check minimum-maximum rent period before book car)
  * see list of own bookings (customer)
  * see list of all customer bookings (admin)
  * calculate the rental fees based on the selected car and rental duration
* Rental Management:
  * approve rental request (admin)
  * reject rental request (admin)

## Usage

To see a prompt on how to use the app, simply enter the executable file name and press Enter.

You will be presented with information about all available commands and options for each command, along with their respective functionalities.

```commandline
./car_rental_system
```

To view a prompt for a specific command, type the executable file name, the command name and **-h** or **--help**

```commandline
./car_rental_system car:update -h
```

![Alt Text](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExYzlkZGJmN2g3cmh5cHZ4dWJsOHZvMXFjbWV3d3R5amkzbmk3dmpnbyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/wvu94sM3RFLoBvs34R/giphy.gif)

### Output of help command

These are all the commands and their help.

```commandline
Car Rental System - help with the rental process, users and cars management.
Usage:
  car_rental_system <command> [options]

  -h, --help  Print help.


Usage:
  car_rental_system register [OPTION...]


  -u, --username arg  Username for a new user.
  -p, --password arg  Password for a new user.
  -a, --admin         Assign admin permissions (testing purposes).


Usage:
  car_rental_system car:list [OPTION...]


      --start arg       start which date you want to book a car, format 
                        dd/mm/yyy: 31/12/2020. (default: "")
      --end arg         Until when you want to book a car, format 
                        dd/mm/yyy: 31/12/2020. (default: "")
  -k, --make arg        Company that made a car, for example: Ford, Honda, 
                        Volkswagen. (default: "")
  -o, --model arg       Car's specific name, for example: Escape, Civic, or 
                        Jetta. (default: "")
      --year-from arg   Show cars with a model year greater than the 
                        specified year. (default: 0)
      --year-to arg     Show cars with a model year less than the specified 
                        year. (default: 0)
      --price-from arg  Show cars with a price per day greater than the 
                        specified year. (default: 0.0)
      --price-to arg    Show cars with a price per day less than the 
                        specified year. (default: 0.0)
      --sort arg        Sort cars in a "sort-order" (ascending by default) 
                        by the field which is one of 
                        [make|model|year|price|min-rent|max-rent]. 
                        (default: "")
      --sort-order arg  Sort cars in ascending or descending order, one of 
                        [asc|desc]. Requires sort option as well. (default: 
                        "")


Usage:
  car_rental_system car:delete [OPTION...]
Admin only.

  -u, --username arg  Login as user. (default: "")
  -p, --password arg  Login password. (default: "")
  -i, --id arg        Id of the car to delete.


Usage:
  car_rental_system car:add [OPTION...]
Admin only.

  -u, --username arg       Login as user. (default: "")
  -p, --password arg       Login password. (default: "")
  -k, --make arg           Company that made a car, for example: Ford, 
                           Honda, Volkswagen.
  -o, --model arg          Car's specific name, for example: Escape, Civic, 
                           or Jetta.
  -y, --year arg           Model year.
  -a, --mileage arg        Number of miles that car can travel using one 
                           gallon of fuel. (default: 0)
  -c, --price-per-day arg  Price to rent this car for 1 day.
      --min-rent arg       The minimum rent period in days. (default: 0)
      --max-rent arg       The maximum rent period in days. (default: 0)


Usage:
  car_rental_system rent:calculate [OPTION...]


  -i, --id arg     Id of the car to book.
  -s, --start arg  From which date you want to book a car, format 
                   dd/mm/yyy: 31/12/2020.
  -e, --end arg    Until when you want to book a car, format dd/mm/yyy: 
                   31/12/2020.


Usage:
  car_rental_system booking:list [OPTION...]
Authenticated only.

  -u, --username arg  Login as user. (default: "")
  -p, --password arg  Login password. (default: "")


Usage:
  car_rental_system car:update [OPTION...]
Admin only.

  -u, --username arg       Login as user. (default: "")
  -p, --password arg       Login password. (default: "")
  -i, --id arg             Id of the car to update.
  -k, --make arg           Company that made a car, for example: Ford, 
                           Honda, Volkswagen. (default: "")
  -o, --model arg          Car's specific name, for example: Escape, Civic, 
                           or Jetta. (default: "")
  -y, --year arg           Model year. (default: -1)
  -a, --mileage arg        Number of miles that car can travel using one 
                           gallon of fuel. (default: -1)
  -c, --price-per-day arg  Price to rent this car for 1 day. (default: 0)
      --min-rent arg       The minimum rent period in days. (default: -1)
      --max-rent arg       The maximum rent period in days. (default: -1)


Usage:
  car_rental_system booking:add [OPTION...]
Customer only.

  -u, --username arg  Login as user. (default: "")
  -p, --password arg  Login password. (default: "")
  -i, --id arg        Id of the car to book.
  -s, --start arg     From which date you want to book a car, format 
                      dd/mm/yyy: 31/12/2020.
  -e, --end arg       Until when you want to book a car, format dd/mm/yyy: 
                      31/12/2020.


Usage:
  car_rental_system booking:update [OPTION...]
Admin only.

  -u, --username arg  Login as user. (default: "")
  -p, --password arg  Login password. (default: "")
  -i, --id arg        Id of the car booking.
  -a, --approve       Change status to approved.
  -r, --reject        Change status to rejected.


```

## List of available commands

* Authentication NOT required:
  * ```car_rental_system register ``` - add new user (customer or admin)
  * ```car_rental_system car:list ``` - show a list of all cars. There are many option to filter the list (by price, year, rent period, etc.)
  * ```car_rental_system rent:calculate ``` - show the total price for renting a car for specified period.

* Authenticated (any role):
  * ```car_rental_system booking:list ``` - customers will see their bookings, admin will see bookings of all the customers.

* Admin only:
  * ```car_rental_system car:delete ```
  * ```car_rental_system car:add ```
  * ```car_rental_system car:update ```
  * ```car_rental_system booking:update   ``` - update a status of specified booking, reject or accept a booking.
* Customer only:
  * ```car_rental_system booking:add ``` - create a booking for specified car and days.

## System architecture

### Application

All the application classes are located in the namespace `crs` (car rental system), so we do not overlap with any library or standard classes,
functions, etc.

In `main.cpp` we create an application object (`crs::console::application`) and run it, passing the input arguments.

It will write all its output to the stream we pass to it in the constructor (that way we can use it for testing purposes,
providing `std::stringstream` insteadof `std::cout` and then checking the output that our application creates).

```c++
int main(int argc, char* argv[])
{
    auto app = new crs::console::application(argc, argv, std::cout);

    try
    {
        app->handle();
    }
    catch (const std::exception& exception)
    {
        std::cout << crs::console::text_helper::red(exception.what()) << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
```

While in tests:

```c++

std::stringstream buffer;
auto app = new crs::console::application(argc, argv, buffer);

// then check
// buffer.str() == "expected output"

```

The application class has a dictionary of so-called commands
(`std::unordered_map<std::string, crs::console::command::abstract_command*>`) where a key is a command name and a corresponding value is a command
object itself.

The application creates all the commands classes and then delegates all the work to one of the commands.

### Commands

For every command that you call from terminal such as `car_rental_system car:add` there is a class that derives from basic abstract
class `crs::console::command::abstract_command`.

Every command class has

- a name (equals to one that you type in terminal while running the application, such as `car:add`, `register`, `booking:list`)
- `get_permission_level` method that returns an allowed role of a user to run this command (customer or admin)

```c++
namespace crs::console
{
    enum ROLE
    {
        CUSTOMER = 0,
        ADMIN = 1,
        ANY = 2,
        AUTHENTICATED = 3
    };
}
```

- `handle` method that does everything
- `configure_options` method to specify all the options needed for the command (`-u`, `-p`, `--year`, etc.).

Abstract command class:

```c++
namespace crs::console::command
{
    class abstract_command
    {
        public:
            abstract_command();
            virtual void handle(const cxxopts::ParseResult& options, std::ostream& output) = 0;
            virtual const std::string get_name() const = 0;
            virtual const crs::console::ROLE get_permission_level() const = 0;
            virtual void configure_options(cxxopts::OptionAdder& options);
        protected:
            cxxopts::OptionAdder& add_auth_params(cxxopts::OptionAdder& options_builder);
            const void authenticate(const cxxopts::ParseResult& parsed_options);
            const crs::core::user::user* user_;
        private:
            static const std::string OPTION_USERNAME;
            static const std::string OPTION_PASSWORD;
            const crs::core::service::auth_service* auth_service_;
    };
}

```

So the main logic and purpose of the application class is to create the commands, ask every one of them to configure their own options, then detect a
command name that was specified while running the application from terminal and delegate all the work to the needed command.

```c++
auto parsed_cmnd_options = options_commands[command_name]->parse(argc_, argv_);
auto command = commands_[command_name];
command->handle(parsed_cmnd_options, output_);
```

That way I tried to follow the **O**(pen-closed) principle from **SOLID** - when you need to add new functionality (for example delete a booking) you
will **not** modify any existing code but you will add a new command and write your new logic there.

You get new behaviour by adding code, not changing it.

So this application is easily extensible.

### Basic command

Let's look at a typical command implementation - `car_rental_system car:delete` with explaining comments.

```c++
#include "car_delete.h"
#include "core/core_exception.hpp"
#include <ostream>

namespace crs::console::command
{
    car_delete::car_delete()
    {
        // initialise all the needed dependencies.
        // in an ideal world there will be a dependency injection
        // but for the learning purposes I left it as a simple manual initialization here
        car_service_ = new crs::core::service::car_service;
    }

    const std::string car_delete::get_name() const
    {
        // the application class instance will ask for this name 
        // and compare it with the command name from the command-line input 
        return std::string("car:delete");
    }

    void car_delete::handle(const cxxopts::ParseResult& options, std::ostream& output)
    {
        // call a method from abstract parent class
        // same implementation (logic) for all children of abstract_command
        // it will find a user by specified username
        // check his password from DB to the command-input one 
        // then check the role of this user and compare to the allowed role of this command 
        // (from car_delete::get_permission_level())
        authenticate(options);

        // extract the needed options from the input
        // for
        // car_rental_system car:delete -i 1 
        // id will be 1
        int id = options["id"].as<int>();
        if (id <= 0)
        {
            throw crs::core::core_exception("Id must be greater than 0.");
        }

        // delegate an actual work to a service
        // the service will deal with the database, etc.
        car_service_->delete_car(id);
        output << "Car with id = " + std::to_string(id) + " was deleted!" << std::endl;
    }

    void car_delete::configure_options(cxxopts::OptionAdder& options_builder)
    {
        // what option you can specify when calling this command
        // --id 1
        // or
        // -i 1 
        add_auth_params(options_builder)
            ("i,id", "Id of the car to delete.", cxxopts::value<int>());
    }

    const crs::console::ROLE car_delete::get_permission_level() const
    {
        // can be run by admin only.
        return crs::console::ROLE::ADMIN;
    }
}
```

### Domain

I wanted to use a hexagonal architecture for this application.

_Hexagonal architecture is a pattern that uses the mechanism of ports and adapters to achieve separation of concerns and isolate external systems and
other external code such as user interfaces and databases from the core application._

So all core/domain logic is located in
`src/core` folder and can be reused in a case if I add GUI.

All console-specific logic is inside `src/console` folder.

My adapters for now are the commands classes, where I obtain all arguments from user console input and call core services classes.

If I add GUI or act as an API for mobile applications I will be able to call the same services, do the same logic for managing DB, just will get all
the arguments from http requests or from GUI components (inputs, forms, etc.)

## External dependencies

External libraries I use:

### sqlite_orm

To execute all database related commands (select, update, delete, etc.).

Library repository https://github.com/fnc12/sqlite_orm.git

### cxxopts

Help with parsing command-line arguments and options and configuring allowed options, also creates help output for all configured options.

Library repository  https://github.com/jarro2783/cxxopts

### bcrypt

To securely store user passwords in DB. You should never store plain passwords for security reasons, so I hash a given password when create a user,
then store this hash in DB. So the next time this user provides his password for log in I can only compare that password hash with the stored hash.

Library repository  https://github.com/hilch/Bcrypt.cpp

### tabulate

Help with drawing tables in console for car and booking lists.

Library repository  https://github.com/p-ranav/tabulate

I do not have any external library code in my repository, I specify them as external dependencies in CMakeLists.txt and then make it available to use
in my code.

The `FetchContent_Declare` function specifies the details of the library, such as its name, the GitHub repository URL, and the version tag.
The `FetchContent_MakeAvailable` function is then used to download and make the library available for use in the project:

```cmake
include(FetchContent)
FetchContent_Declare(
        sqlite_orm
        GIT_REPOSITORY https://github.com/fnc12/sqlite_orm.git
        GIT_TAG v1.8.2
)
FetchContent_MakeAvailable(sqlite_orm)

# link it to use in my code
target_link_libraries(car_rental_system PRIVATE sqlite_orm)


```

## Entity relationship diagram

There are only 3 tables

- user (stores information about users)
- car (information about cars)
- car_booking (relation between cars and users with extra information, which user book which car for which dates and total price for a booking)

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYR50kvt7rvDYzT1j-xDxlQ6UvcxSGrzE0wbUlW9F1QzShbVOW1qfiTxICqZLk8ktnsKYwqzdD_Ave37Nx2OpGm8pu_dPA=w2560-h1308" width="400"/>

## Use cases

Register 2 users - admin with name `a` and customer with name `c`:

```commandline
./car_rental_system register -u c -p p
./car_rental_system register -u a -p p -a
```

Add 2 cars:

```commandline
./car_rental_system car:add -u a -p p --make toyota --model x2 --price-per-day 5 --year 2022 --min-rent 1 --max-rent 100
./car_rental_system car:add -u a -p p --make mazda --model cx-60 --price-per-day 2 --year 2023 --min-rent 7
```

Show cars:

```commandline
./car_rental_system car:list
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYS4g9iKImmlPXAOVWNcP-roumqQWflqyOYCMjUSsvCpLXU_Bne5MIkxg2BYOB7Iuo1VjJV_DOwYQjvqvZ6wlmb1AaKnHg=w2560-h918" width="900"/>


Show cars with filters:

```commandline
./car_rental_system car:list  --start 01/01/2025 --end 01/01/2025
./car_rental_system car:list  --start 01/01/2025 --end 01/02/2025
```

Check a rent price to book a toyota car for one week since February 15, 2024:

```commandline
./car_rental_system rent:calculate -i 1 --start 15/02/2024 --end 22/02/2024
```

Book a toyota car for customer with name `c` for one week since February 15, 2024:

```commandline
./car_rental_system booking:add -i 1 --start 15/02/2024 --end 22/02/2024 -u c -p p
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYQwlkXdD5qqpTskjdQPlMa4Xf65ueGzAsQXdb5iFzvK7t-giQQ4ik_mB2eh4qW_CDDTEJCkYuK8huI3ITZEhmbGYVFM1Q=w2560-h918" width="900"/>

See a new booking with status NEW:

```commandline
./car_rental_system booking:list  -u c -p p
```

Approve a new booking as admin:

```commandline
./car_rental_system booking:update -i 1  -u a -p p --approve
```

See a new booking with status APPROVED:

```commandline
./car_rental_system booking:list  -u c -p p
```

Book a mazda car for customer with name `c` for one week since February 15, 2024:

```commandline
./car_rental_system booking:add -i 2 --start 15/02/2024 --end 22/02/2024 -u c -p p
```

Reject a new booking as admin:

```commandline
./car_rental_system booking:update -i 2  -u a -p p --reject
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYTOcw35QkumYkeHE3sgdcJ6AxWwoli3nh4yQxHmMsWTkPJLK2RkaJfNyRXIZV9krDvP2GuvsC7oJYN09-tGFjm7Gq-I5g=w2560-h918" width="900"/>

See two bookings, the second one with status REJECTED:

```commandline
./car_rental_system booking:list  -u c -p p
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYQ0SLYDcRUen1Z18dIaJD0woMrlTyWaTmESj7KskCyj0JIKtFY2DHoQeZ1zEz7EAapfrIY7FIibdmSbWM78rcA_wZnftQ=w2560-h918" width="900"/>

Update a car with ID = 1, change model to "x3":

```commandline
./car_rental_system car:update -i 1 -u a -p p --model x3 
```

Check car list with filter by make:

```commandline
./car_rental_system car:list  --make to
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYTbkWyHmFo3QrMrR-BUbQrFrPLtKoPy7VB9J7LyYM7gGyh975TQtq6Dfvgx-nFQZlurYGxfBVR3amw_7R2PLjftGdcISw=w2560-h918" width="900"/>


Create a car, see it in the list, delete it, check the list without this car:

```commandline
./car_rental_system car:add -u a -p p --make BMW --model R --price-per-day 50 --year 2002 --min-rent 1 --max-rent 10
./car_rental_system car:list 
./car_rental_system car:delete -i 3 -u a -p p 
./car_rental_system car:list 
```

<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYRraKp3heuyqS87NW-SlCv8l0n4l-t3CpIewUIcR5QEv_lV1tyKrCLm_1gibi3DvWkg01iW1MD4liuuaEM952vvB62Y=w2560-h918" width="900"/>

## Tests

There are simple acceptance tests in `tests/` folder. I run them with ctest. You can run them in IDE (I use CLion).
Also, those tests are automatically running in GitHub pipelines on every push in the GitHub repository with the sources.


<img alt="tests.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYS4RZh6anqqKERyCsOGNqhx-fzPhBlyvI0zJKxHLNjXMWa_ZcOTI01Nx1k9uGNA1ifClbtc_y0HbnTmMLgGsyv8qiIluA=w2560-h918" width="800"/>

