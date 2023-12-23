#ifndef CAR_BOOKING_H
#define CAR_BOOKING_H

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
        private:
            int id_;
            int customer_id_;
            int car_id_;
            float price_;
            int timestamp_start_;
            int timestamp_end_;
    };
}

#endif
