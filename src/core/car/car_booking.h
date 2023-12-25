#ifndef CAR_BOOKING_H
#define CAR_BOOKING_H
#include <string>

namespace crs::core::car
{
    class car_booking
    {
        public:
            car_booking();
            car_booking(
                int customer_id,
                int car_id,
                float price,
                int timestamp_start,
                int timestamp_end
            );
            void approve();
            const int get_id() const;
            void set_id(int id);
            int get_customer_id() const;
            void set_customer_id(int customer_id);
            int get_car_id() const;
            void set_car_id(int car_id);
            float get_price() const;
            void set_price(float price);
            int get_timestamp_start() const;
            void set_timestamp_start(int timestamp_start);
            int get_timestamp_end() const;
            void set_timestamp_end(int timestamp_end);
            int get_status() const;
            void set_status(int status);
            const std::string get_status_string() const;
            const bool is_new() const;
            const bool is_approved() const;
        private:
            static const int STATUS_NEW;
            static const int STATUS_APPROVED;
            void init();
            int id_;
            int customer_id_;
            int car_id_;
            float price_;
            int timestamp_start_;
            int timestamp_end_;
            int status_;
    };
}

#endif
