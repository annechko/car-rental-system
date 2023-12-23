#include "car_booking.h"

namespace crs::core::car
{
    car_booking::car_booking(
        int customer_id,
        int car_id,
        float price,
        int timestamp_start,
        int timestamp_end
    ) : customer_id_(customer_id), car_id_(car_id), price_(price),
        timestamp_start_(timestamp_start), timestamp_end_(timestamp_end)
    {

    }

    car_booking::car_booking()
    {

    }

    const int car_booking::get_id() const
    {
        return id_;
    }

    void car_booking::set_id(int id)
    {
        id_ = id;
    }

    int car_booking::get_customer_id() const
    {
        return customer_id_;
    }

    void car_booking::set_customer_id(int customer_id)
    {
        customer_id_ = customer_id;
    }

    int car_booking::get_car_id() const
    {
        return car_id_;
    }

    void car_booking::set_car_id(int car_id)
    {
        car_id_ = car_id;
    }

    float car_booking::get_price() const
    {
        return price_;
    }

    void car_booking::set_price(float price)
    {
        price_ = price;
    }

    int car_booking::get_timestamp_start() const
    {
        return timestamp_start_;
    }

    void car_booking::set_timestamp_start(int timestamp_start)
    {
        timestamp_start_ = timestamp_start;
    }

    int car_booking::get_timestamp_end() const
    {
        return timestamp_end_;
    }

    void car_booking::set_timestamp_end(int timestamp_end)
    {
        timestamp_end_ = timestamp_end;
    }
}

