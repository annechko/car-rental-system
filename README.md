# Car Rental System

## About

This application is a small console command-line tool written in **C++** for managing car rental process.

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
car_rental_system
```

To view a prompt for a specific command, type the executable file name, the command name and **-h** or **--help**

```commandline
car_rental_system car:update -h
```

![Alt Text](https://media0.giphy.com/media/v1.Y2lkPTc5MGI3NjExOHE1bjd5dHFtamJicXd1OGNqeHZmdXoya3gwZGR6d2FvbHN0cWpoayZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/BQFlrDRU3uUdY0SIfq/giphy.gif)

## List of available commands

* Authentication NOT required:
  * ```car_rental_system register ```
  * ```car_rental_system car:list ```
  * ```car_rental_system rent:calculate ```

* Authenticated (any role):
  * ```car_rental_system booking:list ```

* Admin only:
  * ```car_rental_system car:delete ```
  * ```car_rental_system car:add ```
  * ```car_rental_system car:update ```
  * ```car_rental_system booking:update   ```
* Customer only:
  * ```car_rental_system booking:add ```

architecture
patterns used 
commands


external libraries, how they added, what they do
(cmake)

uml use cases - img

db relation diagram - img
<img alt="img.png" src="https://lh3.googleusercontent.com/u/0/drive-viewer/AEYmBYR50kvt7rvDYzT1j-xDxlQ6UvcxSGrzE0wbUlW9F1QzShbVOW1qfiTxICqZLk8ktnsKYwqzdD_Ave37Nx2OpGm8pu_dPA=w2560-h1308" width="400"/>

preview how to use - video

tests with ctest
tests on push
tests in IDE - img